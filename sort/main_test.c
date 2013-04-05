#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include "sort.h"

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
    for(i = 0; i < size; i++) {
        fscanf(fn, "%d", &a[i]);
    }
    printf("orignal:");
    for(i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\nsorted:");
    //bubble_sort(a, size);
    //quick_sort(a, size);
    quick_sort_n(a, size, 2);
    for(i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\nsearch:");
    int val = -1;
    scanf("%d", &val); 
    printf("result: %d\n", binary_search(a, 0, size-1, 0, val));
    return 0;
}
