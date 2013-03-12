#include<stdio.h>

int main()
{
int x=10, y=15; 
x = x++; 
y = ++y; 
printf("%d %d\n",x,y); 
}

typedef struct s_Node {
    int val;
    struct s_Node * next;
}Node;

typedef struct s_Queue {
    Node *head;
    Node *tail;
}Queue;

void test()
{
    Queue queue;
    Node nodes[10];
    memset(&queue, 0, sizeof(queue));
    memset(nodes, 0, sizeof(nodes));
    for(int i = 0; i < 10; i++) {
        nodes.val = i;
        if(queue.head == NULL) {
            queue.head = queue.tail = &nodes[i];
        } else {
            queue.tail->next = &nodes[i];
        }
    }
    Node *walk = queue->walk;
    while(walk) {
        printf('%d ', walk->val);
    }
    printf("\n");
        
        
        

