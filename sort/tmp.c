#include <stdio.h>

#include "sort.h"

static int adjust_ary(int ary[], int left, int right)
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
    ary[left] = x;
    return left;
}

static int quick_sort_impl(int ary[], int left, int right)
{
    if (left < right){
        int pivot = adjust_ary(ary, left, right);
        quick_sort_impl(ary, left, pivot-1);
        quick_sort_impl(ary, pivot+1, right);
    }
    return 0;
}

int quick_sort(int ary[], int num)
{
    return quick_sort_impl(ary, 0, num -1);
}
