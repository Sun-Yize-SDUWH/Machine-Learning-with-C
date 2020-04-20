#include<stdio.h>

float* regression(float **matrix,int num)
{
    float a,b;
    float x_sum=0,y_sum=0,xy_sum=0,xx_sum=0;
    float x_average=0,y_average=0;

    for (int temp1 = 0; temp1 < num; temp1++)
    {
        x_sum += matrix[temp1][0];
        y_sum += matrix[temp1][1];
        xy_sum += matrix[temp1][0] * matrix[temp1][1];
        xx_sum += matrix[temp1][0] * matrix[temp1][0];
    }

    x_average = x_sum/num;
    y_average = y_sum/num;

    b = (xy_sum - num*x_average*y_average)/(xx_sum-num*x_average*x_average);
    a = y_average - b * x_average;
    
    float output[2]={a,b};
    float *po = output;
    return po;
}

int main()
{
    // 从文件中读取所需整体样本数据
    float data[30][2] = {0};
    FILE *fp;
    fp = fopen("./data.txt", "r");
    for (int t = 0; t < 30; t++)
    {
        for (int i = 0; i < 2; i++)
        {
            fscanf(fp, "%f", &data[t][i]);
        }
    }
    fclose(fp);

    // 处理数据，将对应矩阵作为参数进行传递
    float *p[sizeof(data) / sizeof(data[0])];
    for (int i1 = 0; i1 < sizeof(data) / sizeof(data[0]); i1++)
    {
        p[i1] = data[i1];
    }

    float *result;
    result = regression(p,30);
    printf("SLR:在y=ax+b的情况下\na的值为%f\nb的值为%f",result[0],result[1]);
}