#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
struct Node {
    int ID;
    int score;
    struct Node* next;
    struct Node* down;
};

// 创建新节点
struct Node* createNode(int ID, int score) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->ID = ID;
    newNode->score = score;
    newNode->next = NULL;
    newNode->down = NULL;
    return newNode;
}

// 生成随机序列作为输入数据
void generateRandomSequence(struct Node** sequence) {
    int ID, score;
    struct Node* newNode;

    while (1) {
        ID = rand() % 11;
        if (ID == -1) {
            break;
        }
        score = rand() % 101;

        newNode = createNode(ID, score);
        newNode->next = *sequence;
        *sequence = newNode;
    }
}

// 创建梳子形状链表
void createCombsLinkedList(struct Node* sequence, struct Node** head, struct Node** tail) {
    struct Node* current;
    struct Node* prev;
    struct Node* new_node;

    *head = createNode(-1, -1); // 头节点
    *tail = *head; // 尾部节点指针初始指向头节点

    while (sequence) {
        int ID = sequence->ID;
        int score = sequence->score;

        new_node = createNode(ID, score);

        // 在横向链表中按学号降序插入新节点
        current = (*head)->next;
        prev = *head;
        while (current && current->ID >= ID) {
            prev = current;
            current = current->next;
        }

        new_node->next = current;
        prev->next = new_node;

        // 在纵向链表中按成绩大小插入新节点
        current = prev->down;
        while (current && current->score < score) {
            prev = current;
            current = current->down;
        }

        new_node->down = current;
        prev->down = new_node;

        // 更新尾部节点指针
        *tail = new_node;

        sequence = sequence->next;
    }
}

// 遍历链表，输出学生的学号和考试成绩
void traverseLinkedList(struct Node* head) {
    struct Node* current = head->next;
    while (current) {
        printf("学号: %d, 成绩: %d\n", current->ID, current->score);
        current = current->next;
    }
}

// 根据学号查找学生的成绩
int findStudentByID(struct Node* head, int studentID) {
    struct Node* current = head->next;
    while (current) {
        if (current->ID == studentID) {
            return current->score;
        }
        current = current->next;
    }
    return -1;
}

// 根据成绩范围查找在该范围内的学生
void findStudentsInRange(struct Node* head, int minScore, int maxScore) {
    struct Node* current = head;
    while (current->down) {
        current = current->down;
        if (current->score >= minScore && current->score <= maxScore) {
            printf("学号: %d, 成绩: %d\n", current->ID, current->score);
        }
    }
}

// 插入新的学生节点，保持链表的有序性
void insertStudentNode(struct Node* head, struct Node** tail, int ID, int score) {
    struct Node* new_node = createNode(ID, score);

    // 在横向链表中按学号降序插入新节点
    struct Node* current = head->next;
    struct Node* prev = head;
    while (current && current->ID >= ID) {
        prev = current;
        current = current->next;
    }

    new_node->next = current;
    prev->next = new_node;

    // 在纵向链表中按成绩大小插入新节点
    current = prev->down;
    while (current && current->score < score) {
        prev = current;
        current = current->down;
    }

    new_node->down = current;
    prev->down = new_node;

    // 更新尾部节点指针
    if (current == NULL) {
        *tail = new_node;
    }
}

// 删除特定学生节点
void deleteStudentNode(struct Node* head, struct Node** tail, int studentID) {
    struct Node* current = head->next;
    struct Node* prev = head;
    while (current) {
        if (current->ID == studentID) {
            prev->next = current->next;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (current) {
        current = prev->down;
        prev->down = current->down;
    }

    if (current == *tail) {
        // 如果删除的是尾部节点，则需要更新尾部节点指针
        current = head;
        while (current->down) {
            current = current->down;
            if (current->next == NULL) {
                *tail = current;
                break;
            }
        }
    }
}

int main() {
    struct Node* sequence = NULL;
    struct Node* head = NULL;
    struct Node* tail = NULL;

    generateRandomSequence(&sequence);
    createCombsLinkedList(sequence, &head, &tail);

    printf("链表内容：\n");
    traverseLinkedList(head);

    int studentID = 2;
    int score = findStudentByID(head, studentID);
    printf("学号为 %d 的学生成绩为：%d\n", studentID, score);

    int minScore = 60;
    int maxScore = 80;
    printf("成绩在 %d 到 %d 之间的学生有：\n", minScore, maxScore);
    findStudentsInRange(head, minScore, maxScore);

    int newStudentID = 8;
    int newScore = 90;
    insertStudentNode(head, &tail, newStudentID, newScore);
    printf("插入新学生后的链表内容：\n");
    traverseLinkedList(head);

    int deleteStudentID = 4;
    deleteStudentNode(head, &tail, deleteStudentID);
    printf("删除学号为 %d 的学生后的链表内容：\n", deleteStudentID);
    traverseLinkedList(head);

    return 0;
}
