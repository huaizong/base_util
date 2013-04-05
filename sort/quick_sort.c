#include "sort.h"
static int adjust_ary_00(int ary[], int left, int right);
static int quick_sort_impl(int ary[], int left, int right);
int quick_sort_n_impl(int ary[], int left, int right, int n);
int quick_sort(int ary[], int num)
{
    return quick_sort_impl(ary, 0, num-1);
}

int quick_sort_n(int ary[], int num, int n)
{
    quick_sort_n_impl(ary, 0, num-1, n);
    return quick_sort_impl(ary, num-n, num-1);
}
/*
    @ret 返回隔离位置
*/
int adjust_ary_00(int ary[], int left, int right)
{
    int x = ary[left];
    while(left < right) {
        while(left < right && ary[right] >= x) {
            right--;
        }
        if(left < right) {
            ary[left] = ary[right];
            left++;
        }
        while(left < right && ary[left] < x) {
            left++;
        }
        if(left < right) {
            ary[right] = ary[left];
            right--;
        }
    }
    ary[left] =  x;
    return left;
}

int adjust_ary_01(int ary[], int left, int right)
{
    int mid = (left+right)/2;
    int x = ary[mid];
    while(left < right) {
        while(left < mid && ary[left] <= x) {
            left++;
        }
        while(right > mid && ary[right] >= x) {
            right--;
        }
        if(left < right) {
            int tmp = ary[right];
            ary[right] = ary[left];
            ary[left] = tmp;
            left++;
            right--;
        }
    }
    return mid;
}

int quick_sort_impl(int ary[], int left, int right)
{
    if(left < right) {
        int pivot = adjust_ary_00(ary, left, right);
        quick_sort_impl(ary, left, pivot-1);
        quick_sort_impl(ary, pivot+1, right);
    }
    return 0;
}

int quick_sort_n_impl(int ary[], int left, int right, int n)
{
    if(left < right) {
        int pivot = adjust_ary_00(ary, left, right);
        if((right - pivot + 1) < n) {
            quick_sort_impl(ary, left, pivot-1);
        }
        quick_sort_impl(ary, pivot+1, right);
    }
    return 0;
}

