#include <stdio.h>

float *regression(float **matrix, int num)
{
    float a, b;
    float x_sum = 0, y_sum = 0, xy_sum = 0, xx_sum = 0;
    float x_average = 0, y_average = 0;

    for (int temp1 = 0; temp1 < num; temp1++)
    {
        x_sum += matrix[temp1][0];
        y_sum += matrix[temp1][1];
        xy_sum += matrix[temp1][0] * matrix[temp1][1];
        xx_sum += matrix[temp1][0] * matrix[temp1][0];
    }

    x_average = x_sum / num;
    y_average = y_sum / num;

    b = (xy_sum - num * x_average * y_average) / (xx_sum - num * x_average * x_average);
    a = y_average - b * x_average;

    float output[2] = {a, b};
    float *po = output;
    return po;
}