#include <stdio.h>
#include <stdbool.h>

#define SIZE 100

typedef struct RingQueue {
    int front, rear;
    char queue[SIZE];
} RingQueue;

// 函数声明
void init(RingQueue* q);
bool is_full(RingQueue* q);
bool is_empty(RingQueue* q);
void enqueue(RingQueue* q, char item);
void dequeue(RingQueue* q);
void display(RingQueue* q);

int main() {
    RingQueue queue1, queue2;

    // 初始化两个队列
    init(&queue1);
    init(&queue2);

    char input_string[] = "1234aB56789aaB0";

    for (int i = 0; input_string[i] != '\0'; i++) {
        char char_current = input_string[i];

        if (char_current >= '0' && char_current <= '9') {
            if ((char_current - '0') % 2 == 0) {
                enqueue(&queue1, char_current);
            }
            else {
                enqueue(&queue2, char_current);
            }
        }
        else if (char_current >= 'a' && char_current <= 'z') {
            dequeue(&queue1);
            continue;
        }
        else if (char_current >= 'A' && char_current <= 'Z') {
            dequeue(&queue2);
            continue;
        }
    }

    printf("队列1: ");
    display(&queue1);
    printf("\n队列2: ");
    display(&queue2);
    return 0;
}

void init(RingQueue* q) {
    q->front = 0;
    q->rear = 0;
}

bool is_full(RingQueue* q) {
    return (q->rear + 1) % SIZE == q->front;
}

bool is_empty(RingQueue* q) {
    return q->rear == q->front;
}

void enqueue(RingQueue* q, char item) {
    if (!is_full(q)) {
        q->queue[q->rear] = item;
        q->rear = (q->rear + 1) % SIZE;
    }
}

void dequeue(RingQueue* q) {
    if (!is_empty(q)) {
        char item = q->queue[q->front];
        q->front = (q->front + 1) % SIZE;
        printf("%d\n", item-48);
    }
}

void display(RingQueue* q) {
    int i = q->front;
    while (i != q->rear) {
        printf("%c ", q->queue[i]);
        i = (i + 1) % SIZE;
    }
}
