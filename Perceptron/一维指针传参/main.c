#include <stdio.h>

// 声明外部定义的感知机函数
extern float* perceptron(float *matrix,float step,int num,int col);

int main()
{
    // 从文件中读取训练所需数据
    float iris[100][3] = {0};
    FILE *fp;
    fp = fopen("./iris.txt", "r");
    for (int t = 0; t < 100; t++)
    {
        for (int i = 0; i < 3; i++)
        {
            fscanf(fp, "%f", &iris[t][i]);
        }
    }
    fclose(fp);

    // 获取二维数组第一个元素的首地址，作为参数
    float *p = &iris[0][0];

    // 调用perceptron算法，返回对应w和b
    float *p1;
    p1 = perceptron(p, 0.1, 100, 2);
}