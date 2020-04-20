#include<stdio.h>

// perceptron算法
// 函数参数依次为：整体样本（包括输入和输出），步长，样本数，输入（自变量）维数。
float* perceptron(float **matrix,float step,int num,int col)
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
                output += w[temp2] * matrix[temp1][temp2];
            }
            output += b;
            // 点是否被分类正确
            if (matrix[temp1][col] * output <= 0)
            {
                for (int temp2 = 0; temp2 < col; temp2++)
                {
                    w[temp2] += step * matrix[temp1][col] * matrix[temp1][temp2];
                }
                b += step * matrix[temp1][col];
                flag = 1;
            }
        }
    }while (flag != 0);

    // 将计算权重w与偏置b输出
    printf("计算得到的权重w=[ ");
    for (int t = 0; t < col; t++)
    {
        printf("%f ",w[t]);
    }
    printf("]\n偏置b = %f\n",b);
    
    // 将权重与偏置作为参数返回
    w[col]=b;
    float *pw=w;
    return pw;
}

int main()
{
    // 从文件中读取训练所需数据
    float flower[100][3]={0};
    FILE *fp;
    fp = fopen("./iris.txt","r");
    for(int t = 0;t < 100;t++)
    {
        for (int i = 0; i < 3; i++)
        {
            fscanf(fp, "%e", &flower[t][i]);
        }
    }
    fclose(fp);

    // 处理数据，将对应矩阵作为参数进行传递
    float *p[sizeof(flower) / sizeof(flower[0])];
    for (int i1 = 0; i1 < sizeof(flower) / sizeof(flower[0]); i1++)
    {
        p[i1] = flower[i1];
    }

    // 调用perceptron算法，返回对应w和b
    float *p1;
    p1 = perceptron(p,0.1,100,2);
    
}
