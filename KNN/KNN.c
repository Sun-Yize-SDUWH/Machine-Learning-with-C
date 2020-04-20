#include<stdio.h>

// KNN算法
// 输入参数分别为：整体样本，要判断的输入，k值，样本总体数量，样本特征数，总共有几类
int KNN(float **matrix,float *inputs,int k,int num,int col,int class)
{
    // 定义欧氏距离数组
    float distance[num][2];
    for (int i1 = 0; i1 < num; i1++)
    {
        distance[i1][1]=0;
        distance[i1][0]=0;
    }
    // 定义前k个点中，各个类别数量的数组
    int classnum[class][2];
    for (int i2 = 0; i2 < class; i2++)
    {
        classnum[i2][0] = 0;
        classnum[i2][1] = i2+1;
    }
    // 冒泡排序交换时的中间变量
    float change1=0,change2=0;
    // 标志变量
    int flag=0;
    // 最后输出，确定输入的参数为哪一类
    int output=0;

    // 计算欧式距离
    for (int temp1 = 0; temp1 < num; temp1++)
    {
        for (int temp2 = 0; temp2 < col; temp2++)
        {
            distance[temp1][0] += (matrix[temp1][temp2] - inputs[temp2])*(matrix[temp1][temp2] - inputs[temp2]);
        }
        distance[temp1][1]=matrix[temp1][col];
    }

    for (int temp3 = 1; temp3 < num; temp3++)
    {
        for (int temp4 = 0; temp4 < num - temp3; temp4++)
        {
            if (distance[temp4][0] >= distance[temp4 + 1][0])
            {
                change1 = distance[temp4][0];
                change2 = distance[temp4][1];
                distance[temp4][0] = distance[temp4 + 1][0];
                distance[temp4][1] = distance[temp4 + 1][1];
                distance[temp4 + 1][0] = change1;
                distance[temp4 + 1][1] = change2;
            }
        }
    }

    // 进行冒泡排序
    for (int temp6 = 0; temp6 < k; temp6++)
    {
        for (int temp7 = 0; temp7 < class; temp7++)
        {
            if (distance[temp6][1] == classnum[temp7][1])
            {
                classnum[temp7][0] += 1;
            }
        }
    }

    // 前k个点进行投票
    for (int temp8 = 0; temp8 < k; temp8++)
    {
        for (int temp9 = 0; temp9 < class; temp9++)
        {
            if (classnum[temp8][0]<classnum[temp9][0])
            {
                flag += 1;
            }
        }
        if (flag == 0)
        {
            printf("KNN:前%d个最接近的样本中，第%d类最多，有%d个\n", k, classnum[temp8][1], classnum[temp8][0]);
            output = classnum[temp8][1];
            break;
        }else
        {
            flag = 0;
        }
    }
    return output;
}

int main()
{
    // 从文件中读取所需整体样本数据
    float iris[150][5] = {0};
    FILE *fp;
    fp = fopen("./iris.txt", "r");
    for (int t = 0; t < 150; t++)
    {
        for (int i = 0; i < 5; i++)
        {
            fscanf(fp, "%f", &iris[t][i]);
        }
    }
    fclose(fp);

    // 处理数据，将对应矩阵作为参数进行传递
    float *p[sizeof(iris) / sizeof(iris[0])];
    for (int i1 = 0; i1 < sizeof(iris) / sizeof(iris[0]); i1++)
    {
        p[i1] = iris[i1];
    }

    // 测试样本参数，输入KNN算法判断具体属于哪一类
    float test[4]={5,1,6,1};

    // KNN函数，输入值分别为：整体样本，要判断的输入，k值，样本总体数量，样本特征数，总共有几类
    int nth;
    nth = KNN(p,test,10,150,4,3);
    printf("输入样本经过判断，为第%d类\n",nth);
}
