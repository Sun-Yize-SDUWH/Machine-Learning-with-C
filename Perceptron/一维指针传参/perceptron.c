#include<stdio.h>

// perceptron算法
// 函数参数依次为：整体样本的首地址（包括输入和输出），步长，样本数，输入（自变量）维数。
// 在取二维数组元素时，二维数组的第i行第j列元素为*(matrix+i*(col+1)+j)
float* perceptron(float *matrix,float step,int num,int col)
{
    // 定义感知机初始权重w和偏置b为0
    float w[col],b=0;
    for (int i1 = 0; i1 < col; i1++)
    {
        w[i1]=0;
    }

    // 标志变量，检测是否仍存在误分点
    int flag;
    // perceptron函数
    do{
        flag = 0;
        for (int temp1 = 0; temp1 < num; temp1++)
        {
            float output = 0;
            for (int temp2 = 0; temp2 < col; temp2++)
            {
                output += w[temp2] * (*(matrix+temp1*(col+1)+temp2));
            }
            output += b;
            // 点是否被分类正确
            if ((*(matrix + temp1 * (col + 1) + col)) * output <= 0)
            {
                for (int temp2 = 0; temp2 < col; temp2++)
                {
                    w[temp2] += step * (*(matrix + temp1  * (col + 1) + col)) * (*(matrix + temp1 * (col + 1) + temp2));
                }
                b += step * (*(matrix + temp1  * (col + 1) + col));
                flag = 1;
            }
        }
    }while (flag != 0);

    // 将计算权重w与偏置b输出
    printf("Perceptron:\n计算得到的权重 w=[ ");
    for (int t = 0; t < col; t++)
    {
        printf("%f ",w[t]);
    }
    printf("]\n偏置 b = %f\n",b);
    
    // 将权重与偏置作为参数返回
    w[col]=b;
    float *pw=w;
    return pw;
}
