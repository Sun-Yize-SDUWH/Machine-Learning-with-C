## 机器学习算法c语言重现
+ 18数据科学　孙易泽
+ 201800820135　

### 算法包括

+ Simple Linear Regression (SLR)
+ Perceptron
+ Regression Tree (RT)
+ k-Nearest Neighbors (KNN)
+ Random Forest (RF)

### 测试集选取包括

+ 鸢尾花数据　iris.txt
+ 广告投入与销售额关系 Advertising.txt
+ 可食用蘑菇数据集 mushroom.txt

### 代码环境

```
代码环境为: ubuntu18.04 + Visual Studio Code编写 + gcc通过命令行编译
gcc版本：7.5.0
```

### 测试方法

+ Simple Linear Regression (SLR)

  在对应文件夹的终端中，如下命令可直接进行程序的编译和运行

  gcc -o main main.c SLR.c
  ./main
  
+ Perceptron

  在对应文件夹的终端中，如下命令可直接进行程序的编译和运行
  
  gcc -o main main.c perceptron.c
  ./main
  
+ Regression Tree

  在对应文件夹的终端中，如下命令可直接进行程序的编译和运行
  
  gcc -o main main.c RT.c
  ./main
  
+ KNN

  在对应文件夹的终端中，如下命令可直接进行程序的编译和运行
  
  gcc -o main main.c KNN.c
  ./main
  
+ Random Forest

  在对应文件夹的终端中，如下命令可直接进行程序的编译和运行
  
  gcc -o main main.c RF.c
  ./main