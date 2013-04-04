#include <stdio.h>
#include <stdlib.h>

int binary_search(int ary[], int low, int high, int flag, int val);
int main(int argc, char *argv[])
{
    FILE *fn = fopen(argv[1], "r");
    if(fn == NULL) {
        perror("fopen fail");
        return -1;
    }
    int size, i;
    int *a;
    fscanf(fn, "%d", &size);
    a = calloc(size, sizeof(int));
    a[0] = size;
    //堆实际上是一棵完全二叉树，其任何一非叶节点满足性质：
    //Key[i]<=key[2i+1]&&Key[i]<=key[2i+2]或者Key[i]>=Key[2i+1]&&key>=key[2i+2]
    for(i = 0; i < size; i++) {
        fscanf(fn, "%d", &a[i]);
    }
    for(i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\nsearch:");
    int val = -1;
    scanf("%d", &val); 
    printf("result: %d\n", binary_search(a, 0, size-1, 0, val));
    return 0;
}

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
        printf("%d %d %d %d\n", low, high, mid, ary[mid]);
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




