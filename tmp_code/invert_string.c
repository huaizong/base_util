#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_Node {
    char *data;
    int  len;
    struct s_Node *next;
}Node;

typedef struct s_Link {
    int num;
    Node *head;
}Link;

int invert_word(char *a)
{
    if(a == NULL){
        return -1;
    }
    Link link;
    memset(&link, 0, sizeof(Link));
    while(*a) {
        int type = isblank(*a);
        Node *cur = (Node *)calloc(1, sizeof(Node));
        cur->data = a;
        cur->len++;
        if(link.head != NULL) {
            cur->next = link.head;
        } 
        a++;
        link.num++;
        link.head = cur;
        while(*a) {
            if(isblank(*a) == type) {
                cur->len++;
                a++;
            } else {
                printf("[%.*s]\n", cur->len, cur->data);
                break;
            }
        }
    }
    Node *walk = link.head;
    Node *tmp = NULL;
    while(walk) {
        printf("%.*s", walk->len, walk->data);
        tmp = walk;
        walk =  walk->next;
        free(tmp);
    }
    link.head = NULL;
    printf("\n");
    return 0;
}

int main()
{
    char str[] = "Hello where are you from?";
    printf("%s\n", str);
    invert_word(str);
    return 0;
}
