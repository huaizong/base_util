#include <stdio.h>
#include "sort.h"
int bubble_sort(int ary[], int num)
{
    int i;
    int tmp;
    int changed;
    while(1) {
        changed = 0;
        for(i = 0; i < num; i++) {
            printf("%d ", ary[i]);
        }
        printf("\n");
        for(i = 0; i < num-1; i++) {
            if(ary[i] > ary[i+1]) {
                tmp = ary[i+1];
                ary[i+1] =  ary[i];
                ary[i] =  tmp;
                changed = 1;
            }
        }
        if(changed == 0) {
            break;
        }
    }
    return 0;
}
