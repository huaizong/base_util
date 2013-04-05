#include "sort.h"
int select_sort(int ary[], int num)
{
    int i, j;
    int tmp;
    for(i = 0; i < num-1; i++) {
        for(j = i+1; j < num; j++) {
            if(ary[i] > ary[j]) {
                tmp = ary[j];
                ary[j] =  ary[i];
                ary[i] =  tmp;
            }
        }
    }
    return 0;
}
