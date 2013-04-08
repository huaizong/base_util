//1024 求连续子数组的最大和
//一个整形数组，数组里有正数也有负数。
//数组中连续的一个或多个整数组成一个子数组，每个子数组都有一个和，求所有子数组的和的最大值，要求时间复杂度为O(n)。
//例如输入的数组为1, -2, 3, 10, -4, 7, 2, -5，那么最大的子数组为3, 10, -4, 7, 2，因此输出为该子数组的和18。

#include <stdio.h>
#include <string.h>

//请完成下面MaxSum函数
int MaxSum(int* a,int n)
{
  //write your code here
  if(n < 1) {
      return 0;
  }
  int i, sum, walk;
  walk = 0;
  sum = a[0];
  int beg, end;
  beg = end = 0;
  for(i = 0; i < n; i++) {
    if(walk >= 0) {
        walk += a[i];
    } else {
        walk = a[i];
        beg = i;
    }
    if(sum < walk) {
        sum = walk;
        end = i;
    }
  }
  printf("org:");
  for(i = 0; i < n; i++) {
     printf("%d ", a[i]);
  }
  printf("\n");
  
  printf("res(%d-%d):", beg, end);
  for(i = beg; i <= end; i++) {
     printf("%d ", a[i]);
  }
  printf("\n");

  return sum;
}

//start 提示：本行为自动阅卷起始唯一标识，请勿删除或增加。
//完成下面main函数，自行测试下
int main()
{   
    //wirte your code here;
    int a[]= {-11, -2, -3, -10, 4, 7, 2, -5};
    fprintf(stdout, "sum: %d\n", MaxSum(a, sizeof(a)/sizeof(int)));
    return 0;  
} 
//end   提示：本行为自动阅卷结束唯一标识，请勿删除或增加。
