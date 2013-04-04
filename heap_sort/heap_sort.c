#include <stdio.h>
#include <stdlib.h>

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
    printf("\n");
    return 0;
}
