#include <stdio.h>
#include <string.h>
int test000(void);
int test001(void);

int main()
{
    printf("%s\n", getmemory());
    const char *str = getmemory();
    printf("%s\n", str);
    return 0;
    printf("%d\n", 2*3 < 9& 8);
    printf("%d\n", 2*3 < (9& 8));
    printf("%d\n", (2*3 < 9) & 8);
    return 0;
}

int test000(void)
{
int x=10, y=15; 
x = x++; 
y = ++y; 
printf("%d %d\n",x,y); 
return 0;
}

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

static int old_revert_queue(Queue *queue)
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
    int i;
    for(i = 0; i < 10; i++) {
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
    revert_queue(&queue);
    walk = queue.head;
    while(walk) {
        printf("%d ", walk->val);
        walk = walk->next;
    }
    printf("\n");
}
        
        
        

