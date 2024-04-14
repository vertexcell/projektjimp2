typedef struct node_t {
    int data;
    struct node_t *next;
} node_t;

typedef struct queue_t {
    node_t* front;
    node_t* end;
} queue_t;

void initiate_queue(queue_t *q);

void push(queue_t *q, int value);

int pop(queue_t *q);

void drop_queue(queue_t *q);
int queue_is_empty(queue_t *q);
