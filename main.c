#include <stdio.h>
#include <stdlib.h>

#define HOLE_INTEGER 0
#define HOLE_STRING "H (Hole)"
#define PROCESS_STRING "P"
#define MALLOC_ERROR_CODE 100
#define INVALID_POSITION_CODE 101
#define EMPTY_LINKED_LIST_CODE 102

struct Node {
    int processNumber;
    int base;
    int limit;
    struct Node * next;
};

typedef struct Node* Link;

void printLinkedList(Link head, int count) {
    if (!head) {
        printf("\n");
        return;
    }
    count++;
    int processNumber = head->processNumber;
    if (processNumber == HOLE_INTEGER) {
        printf("Node %d: %s, base = %d, limit = %d", count, HOLE_STRING, head->base, head->limit);
    } else {
        printf("Node %d: %s%d, base = %d, limit = %d", count, PROCESS_STRING, processNumber, head->base, head->limit);
    }
    if (head->next) {
        printf("\n");
    }
    printLinkedList(head->next, count);
}

Link createNode(int processNumber, int base, int limit) {
    Link link = (Link) malloc(sizeof(struct Node));
    if (!link) {
        perror("Memory allocation error");
        exit(MALLOC_ERROR_CODE);
    }
    link->processNumber = processNumber;
    link->base = base;
    link->limit= limit;
    link->next = NULL;
    return link;
}

Link createNodeWithNextNode(int processNumber, int base, int limit, Link next) {
    Link link = createNode(processNumber, base, limit);
    link->next = next;
    return link;
}

int linkedListLength(Link head) {
    if (!head) {
        return 0;
    }
    return 1 + linkedListLength(head->next);
}

void updateLinkBases(Link head) {
    if (!head) {
        return;
    }
    if (!head->next) {
        return;
    }
    head->next->base = head->base + head->limit;
    updateLinkBases(head->next);
}

void push(Link * head, int processNumber, int limit) {
    Link newHead = createNodeWithNextNode(processNumber, 0, limit, *head);
    *head = newHead;
    updateLinkBases(*head);
}

void pop(Link *head) {
    if (!*head) {
        perror("Empty Linked List");
        exit(EMPTY_LINKED_LIST_CODE);
    }
    Link oldHead = *head;
    *head = (*head)->next;
    free(oldHead);
}

void addHoleAtPosition(Link * head, int data, int position) {
    if (position > linkedListLength(*head) + 1 || position <= 0) {
        perror("Invalid position for linked list length");
        exit(INVALID_POSITION_CODE);
    }
    if (position == 1) {
        push(head, 0, data);
        return;
    }
    Link currentHead = *head;
    int count = 0;
    while (count < position - 2) {
        currentHead = currentHead->next;
        count++;
    }
    Link newNode = createNodeWithNextNode(0, 0, data, currentHead->next);
    currentHead->next = newNode;
}

void deleteElementAtPosition(Link * head, int position) {
    if (position > linkedListLength(*head) || position <= 0) {
        perror("Invalid position for linked list length");
        exit(INVALID_POSITION_CODE);
    }
    if (position == 1) {
        pop(head);
        return;
    }
    Link currentHead = *head;
    Link tempHead;
    int count = 0;
    while (count < position - 2) {
        currentHead = currentHead->next;
        count++;
    }
    tempHead = currentHead->next->next;
    free(currentHead->next);
    currentHead->next = tempHead;
}

void freeLinkedLists(Link * head) {
    Link tempHead;
    while(*head) {
        tempHead = (*head)->next;
        free(*head);
        *head = tempHead;
    }
}

int getLimitAtPosition(Link * head, int position) {
    if (position > linkedListLength(*head) || position < 0) {
        perror("Invalid position for linked list length");
        exit(INVALID_POSITION_CODE);
    }
    Link currentHead = *head;
    int count = 0;
    while (count < position - 1) {
        currentHead = currentHead->next;
        count++;
    }
    return currentHead->limit;
}

void combineBlocksFrom(Link * head, int startIndex, int endIndex) {
    int limitTotal = 0;
    int base = startIndex;
    for (int i = startIndex; i <= endIndex; i++) {
        limitTotal += getLimitAtPosition(head, startIndex);
        deleteElementAtPosition(head, startIndex);
    }
    addHoleAtPosition(head, limitTotal, base);
    updateLinkBases(*head);
}

void mergeFreeBlocks(Link * head) {
    Link currentHead = *head;
    int insideHole = 0;
    int startIndex = 0;
    int endIndex = 0;
    int count = 0;
    while (currentHead) {
        if (currentHead->processNumber == HOLE_INTEGER) {
            if (insideHole == 0) {
                startIndex = count + 1;
            }
            insideHole++;
        } else {
            if (insideHole > 1) {
                endIndex = count;
                combineBlocksFrom(head, startIndex, endIndex);
                count -= endIndex - startIndex;
            }
            insideHole = 0;
        }
        currentHead = currentHead->next;
        count++;
    }
    if (insideHole > 1) {
        endIndex = count;
        combineBlocksFrom(head, startIndex, endIndex);
    }
}

void compaction(Link * head) {
    mergeFreeBlocks(head);
    Link currentHead = *head;
    Link tempHead;
    int count = 1;
    int limitTotal = 0;
    int base;
    while (currentHead) {
        tempHead = currentHead->next;
        if (currentHead->processNumber == HOLE_INTEGER) {
            base = count;
            limitTotal += getLimitAtPosition(head, base);
            deleteElementAtPosition(head, base);
            count -= 1;
        }
        currentHead = tempHead;
        count++;
    }
    if (limitTotal > 0) {
        addHoleAtPosition(head, limitTotal, linkedListLength(*head) + 1);
    }
    (*head)->base = 0;
    updateLinkBases(*head);
}

void createMemory(Link * head) {
    push(head, 3, 16);
    push(head, HOLE_INTEGER, 1);
    push(head, HOLE_INTEGER, 1);
    push(head, HOLE_INTEGER, 1);
    push(head, HOLE_INTEGER, 1);
    push(head, HOLE_INTEGER, 1);
    push(head, HOLE_INTEGER, 1);
    push(head, 3, 16);
    push(head, HOLE_INTEGER, 1);
    push(head, HOLE_INTEGER, 1);
    push(head, 54, 16);
    push(head, HOLE_INTEGER, 1);
    push(head, 12, 16);
    push(head, 8, 16);
    push(head, 2, 1);
    push(head, 7, 6);
    push(head, HOLE_INTEGER, 1);
    push(head, HOLE_INTEGER, 1);
    push(head, HOLE_INTEGER, 1);
    push(head, 78, 1);
    push(head, HOLE_INTEGER, 1);
}

int main() {
    Link head = NULL;
    createMemory(&head);
    printf("---------MEMORY--------- \n");
    printLinkedList(head, 0);

    printf("\n---------AFTER MERGE FREE BLOCKS---------\n");
    mergeFreeBlocks(&head);
    printLinkedList(head, 0);

    printf("\n---------AFTER COMPACTION---------\n");
    compaction(&head);
    printLinkedList(head, 0);

    printf("\n---------AFTER FREE---------\n");
    freeLinkedLists(&head);
    printLinkedList(head, 0);

    printf("\n---------AFTER MERGE FREE BLOCKS---------\n");
    mergeFreeBlocks(&head);
    printLinkedList(head, 0);

    printf("\n---------AFTER COMPACTION---------\n");
    compaction(&head);
    printLinkedList(head, 0);
    return 0;
}
