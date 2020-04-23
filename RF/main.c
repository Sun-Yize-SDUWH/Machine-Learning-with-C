#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#include <time.h>
#define FLT_MAX 3.402823466e+38F

char decisionTreeOutput;

struct Class1
{
    int feturenum;
    char feturename[20];
    int flag;
} feture[] = {0};

struct Class2
{
    char classname;
    int classnum;
} class[]= {0};

void countnum(char *array, char *compare, int num, int classnum);
void featurenum(char **matrix, int num, int col);
char randomForest(char **matrix, char *sample, int num, int col, int treenum);
void decisionTree(char **matrix, char *sample, int num, int col);
float* gini(char **matrix,int num,int colfe,int col);


void countnum(char *array, char *compare, int num, int classnum)
{
    for (int i1 = 0; i1 < classnum; i1++)
    {
        class[i1].classname = compare[i1];
        class[i1].classnum = 0;
    }

    for (int i2 = 0; i2 < num; i2++)
    {
        for (int i3 = 0; i3 < classnum; i3++)
        {
            if (array[i2]==class[i3].classname)
            {
                class[i3].classnum++;
                break;
            }
        }
    }
}

void featurenum(char **matrix, int num, int col)
{
    int flag1 = 0;
    col++;
    for (int temp1 = 0; temp1 < col; temp1++)
    {
        feture[temp1].feturenum = 1;
        feture[temp1].feturename[0] = matrix[0][temp1];
        feture[temp1].flag = 0;
    }

    for (int i1 = 0; i1 < col; i1++)
    {
        for (int i2 = 0; i2 < num; i2++)
        {
            flag1 = 0;
            for (int i3 = 0; i3 < feture[i1].feturenum; i3++)
            {
                if (feture[i1].feturename[i3] == matrix[i2][i1])
                {
                    flag1 = 1;
                    break;
                }
            }
            if (flag1 == 0)
            {
                feture[i1].feturename[feture[i1].feturenum] = matrix[i2][i1];
                feture[i1].feturenum++;
            }
        }
    }
}

float *gini(char **matrix, int num, int colfe, int col)
{
    static float output[3];
    int count1, count2;
    float temp;
    float gini1, gini2, ginisum;
    float ginimin = FLT_MAX;
    char array1[num], array2[num];

    for (int i1 = 0; i1 < feture[colfe].feturenum; i1++)
    {

        count1 = 0, count2 = 0, temp = 0;
        for (int i2 = 0; i2 < num; i2++)
        {
            if (matrix[i2][colfe] == feture[colfe].feturename[i1])
            {
                array1[count1] = matrix[i2][col];
                count1++;
            }
            else
            {
                array2[count2] = matrix[i2][col];
                count2++;
            }
        }
        countnum(array1, feture[col].feturename, count1, feture[col].feturenum);
        for (int i3 = 0; i3 < feture[col].feturenum; i3++)
        {
            temp += ((float)class[i3].classnum / (float)count1) * ((float)class[i3].classnum / (float)count1);
        }

        temp = (float)1 - temp;
        gini1 = ((float)count1 / (float)num) * temp;

        temp = 0;
        countnum(array2, feture[col].feturename, count2, feture[col].feturenum);
        for (int i4 = 0; i4 < feture[col].feturenum; i4++)
        {
            temp += ((float)class[i4].classnum / (float)count2) * ((float)class[i4].classnum / (float)count2);
        }
        temp = 1 - temp;
        gini2 = ((float)count2 / (float)num) * temp;
        ginisum = gini1 + gini2;
        if (ginisum < ginimin)
        {
            ginimin = ginisum;
            output[0] = ginisum;
            output[1] = (float)colfe;
            output[2] = (float)i1;
        }
    }
    float *p = output;
    return p;
}

void decisionTree(char **matrix, char *sample, int num, int col)
{
    int flag1 = 1, flag2 = 0;
    float *tempgini;
    float ginimin = FLT_MAX;
    int j, s;
    int count1 = 0, count2 = 0;

    char leaf[num][col + 1];
    char output;
    char array[num];

    for (int i1 = 0; i1 < col - 1; i1++)
    {
        if (feture[i1].flag == 0)
        {
            flag1 = 0;
            break;
        }
    }

    for (int i2 = 0; i2 < num; i2++)
    {
        array[i2] = matrix[i2][col];
    }
    countnum(array, feture[col].feturename, num, feture[col].feturenum);
    for (int i3 = 0; i3 < feture[col].feturenum; i3++)
    {
        if (class[i3].classnum == num)
        {
            flag1 = 1;
            break;
        }
    }

    if (flag1 == 1 || flag2 == 1)
    {
        decisionTreeOutput = matrix[0][col];
    }
    else
    {
        for (int temp1 = 0; temp1 < col; temp1++)
        {
            if (feture[temp1].flag == 0)
            {
                tempgini = gini(matrix, num, temp1, col);
                if (tempgini[0] < ginimin)
                {
                    ginimin = tempgini[0];
                    j = temp1;
                    s = (int)tempgini[2];
                }
            }
        }
        feture[j].flag = 1;
        if (sample[j] == feture[j].feturename[s])
        {
            for (int temp2 = 0; temp2 < num; temp2++)
            {
                if (matrix[temp2][j] == feture[j].feturename[s])
                {
                    for (int temp3 = 0; temp3 < col + 1; temp3++)
                    {
                        leaf[count1][temp3] = matrix[temp2][temp3];
                    }
                    count1++;
                }
            }
            char *p1[sizeof(leaf) / sizeof(leaf[0])];
            for (int i1 = 0; i1 < sizeof(leaf) / sizeof(leaf[0]); i1++)
            {
                p1[i1] = leaf[i1];
            }
            decisionTree(p1, sample, count1, col);
        }
        else
        {
            for (int temp3 = 0; temp3 < num; temp3++)
            {
                if (matrix[temp3][j] != feture[j].feturename[s])
                {
                    for (int temp4 = 0; temp4 < col + 1; temp4++)
                    {
                        leaf[count2][temp4] = matrix[temp3][temp4];
                    }
                    count2++;
                }
            }
            char *p2[sizeof(leaf) / sizeof(leaf[0])];
            for (int i1 = 0; i1 < sizeof(leaf) / sizeof(leaf[0]); i1++)
            {
                p2[i1] = leaf[i1];
            }
            decisionTree(p2, sample, count2, col);
        }
    }
}

char randomForest(char **matrix, char *sample, int num, int col, int treenum)
{
    char random[num][col+1];
    char outputs[treenum];
    int randomnum;
    int classmax=0;
    char classname;
    int count=0;

    featurenum(matrix, num, col);

    for (int temp1 = 0; temp1 < treenum; temp1++)
    {
        count = 0;
        for (int i1 = 0; i1 < num; i1++)
        {
            srand(i1 * time(NULL));
            randomnum = rand() % (num - 2);
            for (int i2 = 0; i2 < col + 1; i2++)
            {
                random[count][i2] = matrix[randomnum][i2];
            }
            count++;
        }

        char *p[sizeof(random) / sizeof(random[0])];
        for (int i3 = 0; i3 < sizeof(random) / sizeof(random[0]); i3++)
        {
            p[i3] = random[i3];
        }
        decisionTree(p, sample, count, col);
        outputs[temp1] = decisionTreeOutput;
    }
    countnum(outputs, feture[col].feturename, treenum, feture[col].feturenum);
    for (int temp2 = 0; temp2 < feture[col].feturenum; temp2++)
    {
        if (class[temp2].classnum>classmax)
        {
            classmax = class[temp2].classnum;
            classname = class[temp2].classname;
        }
    }
    return classname;
}

int main()
{
    printf("随机森林程序运行中...\n");
    /********************
    以下几行为可修改的参数
    ********************/
    // 输入样本文件名
    char filename[] = "./mushroom.txt";
    // 输入样本数量
    int num = 8100;
    // 选取样本中最后多少行数据作为测试集
    int samplenum = 100;
    int num_x = num - samplenum;
    // 输入样本维度
    int col = 23;
    int col_x = col - 1;
    // 输入一共生成多少颗树
    int treenum = 6;
    float correct = 0;


    // 从文件中读取所需整体样本数据
    char data[num][col];
    FILE *fp;
    fp = fopen(filename, "r");
    for (int t = 0; t < num; t++)
        for (int i = 0; i < col; i++)
            fscanf(fp, "%[^,^\n]%*c", &data[t][i]);
    fclose(fp);

    // 处理数据，将对应矩阵作为参数进行传递
    char *p1[sizeof(data) / sizeof(data[0])];
    for (int i1 = 0; i1 < sizeof(data) / sizeof(data[0]); i1++)
    {
        p1[i1] = data[i1];
    }


    for (int i1 = 0; i1 < samplenum; i1++)
    {
        char sample[col];
        for (int i2 = 0; i2 < col; i2++)
        {
            sample[i2] = p1[num - i1 - 1][i2];
        }
        char p = randomForest(p1, sample, num_x, col_x, treenum);
        if (p==sample[col-1])
        {
            correct++;
        }
    }
    printf("样本集为%s\n共训练%d个样本，选取%d个作为测试集，森林包含%d棵树\n其中，测试集的正确率为%.1f%%。\n", filename, num_x, samplenum, treenum, correct / (float)samplenum * 100);
}
