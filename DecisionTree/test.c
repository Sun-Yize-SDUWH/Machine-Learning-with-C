#include "DT.h"

int main()
{
    printf("\n12233\n");
    int row = 9, col = 3;
    double **dataset = (double **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; ++i)
    {
        dataset[i] = (double *)malloc(col * sizeof(double));
    } //动态申请二维数组
    double data[10][3] = {2.771244718, 1.784783929, 0,
                          1.728571309, 1.169761413, 0,
                          3.678319846, 2.81281357, 0,
                          3.961043357, 2.61995032, 0,
                          2.999208922, 2.209014212, 0,
                          7.497545867, 3.162953546, 1,
                          9.00220326, 3.339047188, 1,
                          7.444542326, 0.476683375, 1,
                          10.12493903, 3.234550982, 1};
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            dataset[i][j] = data[i][j];
        }
    }
    double test[2] = {3.678319846, 2.81281357};
    int min_size = 2, max_depth = 1;
    struct treeBranch *result = build_tree(row, col, dataset, min_size, max_depth);
    double output = predict(test, result);
    printf("\n%f\n", output);
    free(dataset);
    dataset = NULL;
}