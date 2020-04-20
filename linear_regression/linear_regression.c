#include<stdio.h>

// 简单线性回归算法
// 利用最小二乘法思想实现，输入值分别为：整体数据样本，样本数
float* regression(float **matrix,int num)
{
    // 默认最后得出公式为y=ax+b型
    float a,b;
    // 分别计算x，y，x*y，x^2的和
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
    // 根据公式求出a，b的值
    b = (xy_sum - num*x_average*y_average)/(xx_sum-num*x_average*x_average);
    a = y_average - b * x_average;

    // 将a，b构成数组，作为参数返回
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

    // 输入样本矩阵和样本数
    result = regression(p,30);
    // 返回计算参数
    printf("SLR:在y=ax+b的情况下\na的值为%f\nb的值为%f",result[0],result[1]);
}
