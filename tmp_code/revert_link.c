/*! \brief Test How Revert A Simple Link.
 *         Show how revert a simple link.
 *
 *  Just only test code.
 */

#include <stdio.h>
#include <string.h>
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

static int revert_queue(Queue *queue)
{
    if(queue == NULL) {
        return -1;
    }
    Node *pre;
    Node *cur;
    Node *walk;
    pre = queue->head;
    cur =  pre->next;
    queue->tail = pre;
    pre->next = NULL;
    while(cur) 
    {
        walk = cur->next; 
        cur->next = pre;
        pre =  cur;
        cur = walk;
    }
    queue->head =  pre;
        
    return 0;        
}



int test001()
{
    Queue queue;
    Node nodes[10];
    memset(&queue, 0, sizeof(queue));
    memset(nodes, 0, sizeof(nodes));
    for(int i = 0; i < 10; i++) {
        nodes[i].val = i;
        if(queue.head == NULL) {
            queue.head = queue.tail = &nodes[i];
        } else {
            queue.tail->next = &nodes[i];
            queue.tail = &nodes[i];
        }
    }
    Node *walk = queue.head;
    while(walk) {
        printf("%d ", walk->val);
        walk = walk->next;
    }
    printf("\n");
    for(int i = 0; i < 5; i++) {
        revert_queue(&queue);
        walk = queue.head;
        while(walk) {
            printf("%d ", walk->val);
            walk = walk->next;
        }
        printf("\n");
    }
    return 0;
}

int main()
{
    return test001();
}
