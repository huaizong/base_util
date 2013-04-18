/*! \brief Test How Revert A Simple Link.
 *         Show how revert a simple link.
 *
 *  Just only test code.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int test000(void);
int test001(void);


typedef struct s_Node {
    int val;
    struct s_Node * next;
}Node;

typedef struct s_Queue {
    Node *head;
    Node *tail;
}Queue;

int merge_queue(Queue *a, Queue *b)
{
    if(a == NULL || b == NULL) {
        return -1;
    }
    Queue tmp;
    memset(&tmp, 0, sizeof(tmp));
    Queue *c= &tmp;
    Node *walk_a = a->head;
    Node *walk_b = b->head;
    Node *node = NULL;
    while(walk_a && walk_b) {
        if(walk_a->val < walk_b->val) {
            node = walk_a;
            walk_a = walk_a->next;
        } else {
            node = walk_b;
            walk_b = walk_b->next;
        }
        if(c->head == NULL) {
            c->head = c->tail = node;
        } else {
            c->tail->next = node;
            c->tail = node;
        }
    }
    while(walk_a) {
        node = walk_a;
        walk_a = walk_a->next;
        if(c->head == NULL) {
            c->head = c->tail = node;
        } else {
            c->tail->next = node;
            c->tail = node;
        }
    }
    while(walk_b) {
        node = walk_b;
        walk_b = walk_b->next;
        if(c->head == NULL) {
            c->head = c->tail = node;
        } else {
            c->tail->next = node;
            c->tail = node;
        }
    }
    if(c->tail) {
        c->tail->next = NULL;
    }
    memcpy(a, c, sizeof(*c));
    a->head = c->head;
    a->tail = c->tail;
    b->head = b->tail = NULL;
    printf("return succ\n");
    return 0;        
}



int test001()
{
    Queue a;
    Queue b;
    Node a_nodes[10];
    Node b_nodes[10];
    memset(&a, 0, sizeof(a));
    memset(&b, 0, sizeof(b));
    memset(a_nodes, 0, sizeof(a_nodes));
    memset(b_nodes, 0, sizeof(b_nodes));
    int i;
    srandom(time(NULL));

    a_nodes[i].val = random() % 10;
    b_nodes[i].val = random() % 10;
    for(i = 1; i < 10; i++) {
        a_nodes[i].val = a_nodes[i-1].val + random() % 10;
        if(a.head == NULL) {
            a.head = a.tail = &a_nodes[i];
        } else {
            a.tail->next = &a_nodes[i];
            a.tail = &a_nodes[i];
        }
    }
    for(i = 1; i < 10; i++) {
        b_nodes[i].val = b_nodes[i-1].val + random() % 10;
        if(b.head == NULL) {
            b.head = b.tail = &b_nodes[i];
        } else {
            b.tail->next = &b_nodes[i];
            b.tail = &b_nodes[i];
        }
    }
    Node *walk = a.head;
    printf("show a:\n");
    while(walk) {
        printf("%d ", walk->val);
        walk = walk->next;
    }
    printf("\n");
    walk = b.head;
    printf("show b:\n");
    while(walk) {
        printf("%d ", walk->val);
        walk = walk->next;
    }
    printf("return :%d\n", merge_queue(&a, &b));
    walk = a.head;
    printf("show a:\n");
    while(walk) {
        printf("%d ", walk->val);
        walk = walk->next;
    }
    printf("\n");
    return 0;
}

int main()
{
    return test001();
}
