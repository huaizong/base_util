#include <stdio.h>
#include <stdlib.h>
#include "search.h"

int binary_search(int ary[], int low, int high, int flag, int val);

//@flag = 0, head
//@flag = 1, tail
int binary_search(int ary[], int low, int high, int flag, int val)
{
    if(low < 0 || high < 0 ||  low > high || flag < 0) {
        return -1;
    }
    int mid;
    int cmp_mod = 0;
    while(low <= high) {
        mid = low + (high-low)/2;
        printf("low:%d high:%d mid_ary[%d]:%d\n", low, high, mid, ary[mid]);
        if(ary[mid] < val) {
            low =  mid + 1;
            cmp_mod = -1;
        } else if(ary[mid] > val) {
            high = mid - 1;
            cmp_mod = 1;
        } else {
            return mid;
        }
    }    
    return -1;
}




