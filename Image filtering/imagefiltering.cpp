#include <iostream>
#include <fstream>
using namespace std;
#define MAX_VALUE 255

void applySepia(unsigned char &red, unsigned char &green, unsigned char &blue)
{
    int sepiaRed = (int)((red * 0.393) + (green * 0.769) + (blue * 0.189));
    int sepiaGreen = (int)((red * 0.349) + (green * 0.686) + (blue * 0.168));
    int sepiaBlue = (int)((red * 0.272) + (green * 0.534) + (blue * 0.131));

    if (sepiaRed > MAX_VALUE)
        sepiaRed = MAX_VALUE;
    if (sepiaGreen > MAX_VALUE)
        sepiaGreen = MAX_VALUE;
    if (sepiaBlue > MAX_VALUE)
        sepiaBlue = MAX_VALUE;

    red = (unsigned char)sepiaRed;
    green = (unsigned char)sepiaGreen;
    blue = (unsigned char)sepiaBlue;
}

void applyGrayscale(unsigned char &red, unsigned char &green, unsigned char &blue)
{
    unsigned char grayscale = (unsigned char)((red + green + blue) / 3);

    red = green = blue = grayscale;
}

void applyInvert(unsigned char &red, unsigned char &green, unsigned char &blue)
{
    red = MAX_VALUE - red;
    green = MAX_VALUE - green;
    blue = MAX_VALUE - blue;
}
void applyHighContrast(unsigned char &red, unsigned char &green, unsigned char &blue)
{
    if (red > MAX_VALUE / 2)
    red = MAX_VALUE;
    else red = 0;

    if (green > MAX_VALUE / 2) 
    green = MAX_VALUE;
    else green = 0;

    if (blue > MAX_VALUE / 2) 
    blue = MAX_VALUE;
    else blue = 0;
}
void adjustBrightness(unsigned char &red, unsigned char &green, unsigned char &blue, int brightnessFactor)
{
    int newRed = red + brightnessFactor;
    int newGreen = green + brightnessFactor;
    int newBlue = blue + brightnessFactor;

    red = (unsigned char)min(max(newRed, 0), MAX_VALUE);
    green = (unsigned char)min(max(newGreen, 0), MAX_VALUE);
    blue = (unsigned char)min(max(newBlue, 0), MAX_VALUE);
}

void adjustSaturation(unsigned char &red, unsigned char &green, unsigned char &blue, float saturationFactor)
{
    // Convert RGB to HSL (Hue, Saturation, Lightness)
    float r = red / 255.0;
    float g = green / 255.0;
    float b = blue / 255.0;

    float maxColor = max(max(r, g), b);
    float minColor = min(min(r, g), b);

    float lightness = (maxColor + minColor) / 2;

    if (maxColor == minColor) {
        saturationFactor = 0;
    } else {
        if (lightness < 0.5) {
            saturationFactor = (maxColor - minColor) / (maxColor + minColor);
        } else {
            saturationFactor = (maxColor - minColor) / (2.0 - maxColor - minColor);
        }
    }

    // Apply saturation factor
    r = lightness + saturationFactor * (r - lightness);
    g = lightness + saturationFactor * (g - lightness);
    b = lightness + saturationFactor * (b - lightness);

    // Convert back to RGB
    red = (unsigned char)(r * 255.0);
    green = (unsigned char)(g * 255.0);
    blue = (unsigned char)(b * 255.0);
}

int main()
{
    int choice;
    char continueChoice;

    do
    {
        cout << "Filter Options:\n";
        cout << "1. Grayscale\n";
        cout << "2. Invert\n";
        cout << "3. Sepia\n";
        cout << "4. High Contrast\n";
        cout << "5. Adjust Brightness\n";
        cout << "6. Adjust Saturation\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 7)
        {
            break;
        }

        ifstream inputFile("img.bmp", ios::binary);
        ofstream outputFile("output.bmp", ios::binary);

        if (!inputFile || !outputFile)
        {
            cout << "Error opening file.\n";
            return 1;
        }

        unsigned char header[54];
        inputFile.read(reinterpret_cast<char *>(header), sizeof(unsigned char) * 54);
        outputFile.write(reinterpret_cast<const char *>(header), sizeof(unsigned char) * 54);

        int height = *(int *)&header[18];
        int width = *(int *)&header[22];

        cout << "Image dimensions:\n";
        cout << "Width: " << width << "\n";
        cout << "Height: " << height << "\n";

        int imageSize = height * width;
        unsigned char *pixels = new unsigned char[imageSize * 3];
        

        for (int i = 0; i < imageSize; i++)
        {
            pixels[i * 3 + 2] = inputFile.get();
            pixels[i * 3 + 1] = inputFile.get();
            pixels[i * 3] = inputFile.get();
            if(choice==5)
            {
            int brightnessFactor;
                cout << "Enter brightness factor (-255 to 255): ";
                cin >> brightnessFactor;
                for (int i = 0; i < imageSize; i++) {
                    pixels[i * 3 + 2] = inputFile.get();
                    pixels[i * 3 + 1] = inputFile.get();
                    pixels[i * 3] = inputFile.get();
                    adjustBrightness(pixels[i * 3], pixels[i * 3 + 1], pixels[i * 3 + 2], brightnessFactor);
                    outputFile.put(pixels[i * 3 + 2]);
                    outputFile.put(pixels[i * 3 + 1]);
                    outputFile.put(pixels[i * 3]);
        
                }
                break;
            }
            if(choice==6)
            {
            float saturationFactor;
                cout << "Enter saturation factor (0 to 2): ";
                cin >> saturationFactor;
                for (int i = 0; i < imageSize; i++) {
                    pixels[i * 3 + 2] = inputFile.get();
                    pixels[i * 3 + 1] = inputFile.get();
                    pixels[i * 3] = inputFile.get();
                    adjustSaturation(pixels[i * 3], pixels[i * 3 + 1], pixels[i * 3 + 2], saturationFactor);
                    outputFile.put(pixels[i * 3 + 2]);
                    outputFile.put(pixels[i * 3 + 1]);
                    outputFile.put(pixels[i * 3]);
        
                }
                break;
            }
            


            switch (choice)
            {
            case 1:
                applyGrayscale(pixels[i * 3], pixels[i * 3 + 1], pixels[i * 3 + 2]);
                break;
            case 2:
                applyInvert(pixels[i * 3], pixels[i * 3 + 1], pixels[i * 3 + 2]);
                break;
            case 3:
                applySepia(pixels[i * 3], pixels[i * 3 + 1], pixels[i * 3 + 2]);
                break;
            case 4:
                applyHighContrast(pixels[i * 3], pixels[i * 3 + 1], pixels[i * 3 + 2]);
             break;
            default:
                cout << "Invalid choice. No filter applied.\n";
            }

            outputFile.put(pixels[i * 3 + 2]);
            outputFile.put(pixels[i * 3 + 1]);
            outputFile.put(pixels[i * 3]);
        }
        

        cout << "Filter applied successfully.\n";

        inputFile.close();
        outputFile.close();
        delete[] pixels;

        cout << "Do you want to continue (Y/N)? ";
        cin >> continueChoice;

    } while (continueChoice == 'Y' || continueChoice == 'y');

    return 0;
}
