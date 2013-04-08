#include <stdio.h>
#include <stdlib.h>


static int adjust_ary_00(int ary[], int left, int right);
static int quick_sort_impl(int ary[], int left, int right);
static int quick_sort_n_impl(int ary[], int left, int right, int n);
static int quick_sort_n(int ary[], int num, int n);
int main(int argc, char **argv)
{
    int total, k;
    scanf("%d %d", &total, &k);
    int i;
    if(total < 0) {
        return -1;
    }
    int *a = calloc(total, sizeof(int));
    for(i = 0; i < total; i++) {
        scanf("%d", &a[i]);
    }
    quick_sort_n(a, total, k);
    for(i = 0; i < k; i++) {
        printf("%d ", a[i]);
    }
    free(a);
    return 0;
}

int quick_sort_n(int ary[], int num, int n)
{
    quick_sort_n_impl(ary, 0, num-1, n);
    return quick_sort_impl(ary, 0, n-1);
}
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
        quick_sort_impl(ary, left, pivot-1);
        if(pivot - left < n-1) {
            quick_sort_impl(ary, pivot+1, right);
        }
    }
    return 0;
}

