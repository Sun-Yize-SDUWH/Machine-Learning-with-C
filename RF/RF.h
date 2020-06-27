#ifndef DT
#define DT

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct treeBranch
{
    int flag;
    int index;
    double value;
    double output;
    struct treeBranch *leftBranch;
    struct treeBranch *rightBranch;
};

struct dataset
{
    int row1;
    int row2;
    double ***splitdata;
};

struct dataset *test_split(int index, double value, int row, int col, double **data);
double gini_index(int index, double value, int row, int col, double **dataset, double *class, int classnum);
struct treeBranch *get_split(int row, int col, double **dataset, double *class, int classnum, int n_features);
double to_terminal(int row, int col, double **data, double *class, int classnum);
void split(struct treeBranch *tree, int row, int col, double **data, double *class, int classnum, int depth, int min_size, int max_depth, int n_features);
struct treeBranch *build_tree(int row, int col, double **data, int min_size, int max_depth, int n_features);
struct treeBranch **random_forest(int row, int col, double **data, int min_size, int max_depth, int n_features, int n_trees, float sample_size);
double treepredict(double *test, struct treeBranch *tree);
double predict(double *test, struct treeBranch **tree,  int n_trees);

#endif