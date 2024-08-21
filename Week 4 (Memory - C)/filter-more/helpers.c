#include "helpers.h"
#include <math.h>

int Gx_kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int Gy_kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /*Getting the average between red blue and green, then swapping the self
            rgb value to the average value*/
            float red = image[i][j].rgbtRed;
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float average = round((red + blue + green) / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid_width = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < mid_width; j++)
        {
            /*Creating a temporary variable to save the currently RGB value*/
            float temp_initialRed = image[i][j].rgbtRed;
            float temp_initialBlue = image[i][j].rgbtBlue;
            float temp_initialGreen = image[i][j].rgbtGreen;

            /*Swapping the initial value from reversed value*/
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;

            /*Adding temporary values to swapped value*/
            image[i][width - 1 - j].rgbtRed = temp_initialRed;
            image[i][width - 1 - j].rgbtBlue = temp_initialBlue;
            image[i][width - 1 - j].rgbtGreen = temp_initialGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /*Creating a temporary variable to store the blur results*/
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /*Initiallizing variables to store the sum of each RGB values*/
            int counter_values = 0;
            int avg_red_sum = 0;
            int avg_blue_sum = 0;
            int avg_green_sum = 0;

            for (int starth = -1; starth <= 1; starth++)
            {
                for (int startw = -1; startw <= 1; startw++)
                {
                    int actual_h = i + starth;
                    int actual_w = j + startw;
                    // Checking if the calculated position is within the image boundaries
                    if (actual_h >= 0 && actual_h <= width - 1 && actual_w >= 0 & actual_w < width)
                    {
                        /*Adding to the variables and plus one to the counter values*/
                        avg_red_sum += image[actual_h][actual_w].rgbtRed;
                        avg_blue_sum += image[actual_h][actual_w].rgbtBlue;
                        avg_green_sum += image[actual_h][actual_w].rgbtGreen;
                        counter_values++;
                    }
                }
            }

            /*Calculating the average and storing in the temporary variable*/
            temp[i][j].rgbtRed = round((float) avg_red_sum / counter_values);
            temp[i][j].rgbtBlue = round((float) avg_blue_sum / counter_values);
            temp[i][j].rgbtGreen = round((float) avg_green_sum / counter_values);
        }
    }

    // Copy the blurred image from the temporary variable back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    /*Creating a temporary variable to store edge-detected px*/
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /*Initializing variables for storing gradients*/
            int gx_red = 0;
            int gy_red = 0;
            int gx_blue = 0;
            int gy_blue = 0;
            int gx_green = 0;
            int gy_green = 0;

            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int x_idx = i + x;
                    int y_idx = j + y;

                    /*Checking if the neighboring is withing the img bounds*/
                    if (x_idx >= 0 && x_idx < height && y_idx >= 0 && y_idx < width)
                    {
                        /*Computing gradients in x and y directions for each RGB*/
                        gx_red += Gx_kernel[x + 1][y + 1] * image[x_idx][y_idx].rgbtRed;
                        gy_red += Gy_kernel[x + 1][y + 1] * image[x_idx][y_idx].rgbtRed;

                        gx_blue += Gx_kernel[x + 1][y + 1] * image[x_idx][y_idx].rgbtBlue;
                        gy_blue += Gy_kernel[x + 1][y + 1] * image[x_idx][y_idx].rgbtBlue;

                        gx_green += Gx_kernel[x + 1][y + 1] * image[x_idx][y_idx].rgbtGreen;
                        gy_green += Gy_kernel[x + 1][y + 1] * image[x_idx][y_idx].rgbtGreen;
                    }
                }
            }

            /*Getting the magnitude for each collor channel and storing the edge-detected px*/
            int edge_red = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            int edge_green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int edge_blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));

            if (edge_red > 255)
            {
                edge_red = 255;
            }
            if (edge_blue > 255)
            {
                edge_blue = 255;
            }
            if (edge_green > 255)
            {
                edge_green = 255;
            }

            temp[i][j].rgbtRed = edge_red;
            temp[i][j].rgbtBlue = edge_blue;
            temp[i][j].rgbtGreen = edge_green;
        }
    }
    /*Copying from the temporary array to the image*/
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
