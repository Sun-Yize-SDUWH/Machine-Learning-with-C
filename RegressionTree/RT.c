#include <stdio.h>
#define FLT_MAX 3.402823466e+38F

// Regression Tree 函数代码

// 判断最大最小值函数，用于判断对应变量的取值区间范围
float *minmax(float **matrix, int num, int col)
{
    float max = matrix[0][col], min = matrix[0][col];
    for (int temp1 = 1; temp1 < num; temp1++)
    {
        if (matrix[temp1][col] > max)
            max = matrix[temp1][col];
        if (matrix[temp1][col] < min)
            min = matrix[temp1][col];
    }

    // 将计算得出的最大最小值，生成数组返回
    static float a[2];
    a[0]=min,a[1]=max;
    float *p = a;
    return p;
}

// 回归树主函数，输入参数分别为：所有取值点，取值点个数，变量个数
// 返回参数为：j值（第几个变量），s值（切分点为多少），小于s时的c1值，大于s时的c2值
float *regressionTree(float **matrix, int num, int col)
{
    // 定义数组，取出对应特征所有样本中，最大值和最小值
    float *p1;
    // 平方误差最小值，初始值设定为一较大值,最大值和最小值差值
    float minfun = FLT_MAX, diff;
    // c1均值与c2均值
    float avgc1, avgc2;
    // c1的和与c2的和
    float c1, c2, oc1, oc2;
    // 计数变量
    int count1, count2;
    // 计算均方误差时变量
    float sumc1, sumc2, sumall;
    // 求得的对应j值和s值
    int tj;float ts;

    // 先对逐个j进行遍历
    for (int j = 0; j < col; j++)
    {
        p1 = minmax(matrix, num, j);
        // 得到对应变量的取值区间
        diff = p1[1] - p1[0];
        // 对区间内逐个s遍历，每个s之间差值为1
        for (float s = p1[0]; s < diff; s++)
        {
            avgc1 = 0, avgc2 = 0, c1 = 0, c2 = 0, count1 = 0, count2 = 0, sumc1 = 0, sumc2 = 0;
            for (int temp2 = 0; temp2 < num; temp2++)
            {
                if (matrix[temp2][j] < s)
                {
                    count1++;
                    c1 += matrix[temp2][col];
                }
                else
                {
                    count2++;
                    c2 += matrix[temp2][col];
                }
            }

            // 判断经过切分后，是否有空集，如有空集直接令对应c值为零，避免除以0会报错
            if (count1 == 0 && count2 == 0)
                avgc1 = 0, avgc2 = 0;
            else if (count1 == 0 && count2 != 0)
                avgc1 = 0, avgc2 = c2 / count2;
            else if (count1 != 0 && count2 == 0)
                avgc1 = c1 / count1, avgc2 = 0;
            else
            {
                avgc1 = c1 / count1;
                avgc2 = c2 / count2;
            }

            // 计算两边点之和（均方误差）
            for (int temp2 = 0; temp2 < num; temp2++)
            {
                if (matrix[temp2][j] < s)
                    sumc1 += (matrix[temp2][j] - avgc1) * (matrix[temp2][j] - avgc1);
                else
                    sumc2 += (matrix[temp2][j] - avgc2) * (matrix[temp2][j] - avgc2);
            }
            sumall = sumc1 + sumc2;

            // 判断是否为当前最小的均方误差
            if (sumall < minfun)
            {
                minfun = sumall;
                tj = j;
                ts = s;
                oc1 = avgc1;
                oc2 = avgc2;
            }
        }
    }

    // 差值较小时，结束循环，返回结果
    if (minfun < 1000)
    {
        static float output[5] = {0, 0, 0, 0, 0};
        float *po = output;
        return po;
    }
    // 返回j值（第几个变量），s值（切分点为多少），标志变量，小于s时的c1值，大于s时的c2值
    else
    {
        static float output[5];
	output[0] = (float)tj, output[1] = ts, output[2] = 1,output[3] = oc1, output[4] = oc2;
        float *po = output;
        return po;
    }
}

// 利用递归，形成树结构，并对树的每条分支进行打印
// 输入参数分别为：当前分支所有样本，当前分支样本数，变量数，当前树层数，所有js存放二维数组，当前回归的次数
void treeformat(float **matrix, int num, int col, int nth, float **output, int th)
{
    // 取出返回的j，s，c1，c2
    float *p1;
    // 计数变量
    int count1 = 0, count2 = 0;
    // 整体样本的列数
    int t = col + 1;

    // 将输入矩阵放入回归树进行计算
    p1 = regressionTree(matrix, num, col);
    // 层数-1，当nth到达规定层数（或理解为到达叶节点）时停止并输出结果
    // th为当前在第几重递归，递归数+1
    nth--;th++;

    //如果到达规定层数，或误差值较小，没有太大改进，则输出结果
    if (p1[2] == 0 || nth == 0)
    {
        for (int temp4 = 0; temp4 < (th - 1); temp4++)
        {
            // 当为左子树时
            if (output[temp4][2] == 0)
                printf("第%d个变量小于%f——>", (int)(output[temp4][0]), output[temp4][1]);
            // 当为右子树时
            else
                printf("第%d个变量大于%f——>", (int)(output[temp4][0]), output[temp4][1]);
        }

        // 输出当前分支对应的输出值
        if (output[th - 2][2] == 0)
            printf("输出值为%f\n", output[th - 2][3]);
        else
            printf("输出值为%f\n", output[th - 2][4]);
    }
    // 如果没有到达层数，或误差函数仍很大，则继续递归
    else
    {
        // 根据j，s将样本点二分
        float matrix1[num][t], matrix2[num][t];
        for (int temp1 = 0; temp1 < num; temp1++)
        {
            if (matrix[temp1][(int)p1[0]] < p1[1])
            {
                for (int temp2 = 0; temp2 < t; temp2++)
                    matrix1[count1][temp2] = matrix[temp1][temp2];
                count1++;
            }
            else
            {
                for (int temp3 = 0; temp3 < t; temp3++)
                    matrix2[count2][temp3] = matrix[temp1][temp3];
                count2++;
            }
        }

        // 判断是否分为两堆，如果为两堆，则继续递归
        if (count1 != 0 && count2 != 0)
        {
            // 储存当前js值和对应的输出值
            for (int t = 0; t < 5; t++)
                output[th - 1][t] = p1[t];
            output[th - 1][2] = (float)0;

            // 处理样本点
            float *p2[count1];
            for (int i1 = 0; i1 < count1; i1++)
                p2[i1] = matrix1[i1];
            // 左子树开始递归
            treeformat(p2, count1, col, nth, output, th);

            // 标志变量，代表切换成右子树
            output[th - 1][2] = (float)1;

            // 处理样本点
            float *p3[count2];
            for (int i2 = 0; i2 < count2; i2++)
                p3[i2] = matrix2[i2];
            // 右子树开始递归
            treeformat(p3, count2, col, nth, output, th);
        }
        // 如果仅有一堆，则停止递归，输出当前分支和输出值
        else
        {
            for (int temp4 = 0; temp4 < (th - 1); temp4++)
            {
                // 左子树输出值
                if (output[temp4][2] == 0)
                    printf("第%d个变量小于%f——>", (int)(output[temp4][0]), output[temp4][1]);
                // 右子树输出值
                else
                    printf("第%d个变量大于%f——>", (int)(output[temp4][0]), output[temp4][1]);
            }
            if (output[th - 2][2] == 0)
                printf("输出值为%f\n", output[th - 2][3]);
            else
                printf("输出值为%f\n", output[th - 2][4]);
        }
    }
}

// 处理函数，对刚输入的参数进行处理，开辟j，s和对应输出值存放的二维数组内存
void treeprint(float **matrix, int num, int col, int nth)
{
    // 定义js和输出值存放的数组
    float jssum[nth - 1][5];
    float *p[nth - 1];
    // 处理数据
    for (int i1 = 0; i1 < (nth - 1); i1++)
        p[i1] = jssum[i1];
    // 放入回归树，开始递归
    treeformat(matrix, num, col, nth, p, 0);
}
