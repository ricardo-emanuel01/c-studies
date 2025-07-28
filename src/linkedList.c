# include <limits.h>
# include <stdio.h>
# include <stdlib.h>


typedef struct List {
    int val;
    struct List *next;
} List, *ListPtr;

ListPtr createList() {
    /*
        Define sentinels

        In that case every insert and remove will occur between two elements
        and the head will be the same always
    */
    ListPtr left = (ListPtr)malloc(sizeof(List));
    if (left == NULL) return NULL;

    left->next = (ListPtr)calloc(1, sizeof(List));
    // Can generate memory leak
    if (left->next == NULL) return NULL;

    left->val = left->next->val = INT_MIN;

    return left;
}

int append(ListPtr list, int val) {
    ListPtr newElement = (ListPtr)malloc(sizeof(List));
    if (newElement == NULL) return 1;

    ListPtr current = list;
    while (current->next->val != INT_MIN) {
        current = current->next;
    }

    newElement->val = val;
    newElement->next = current->next;
    current->next = newElement;

    return 0;
}

void printList(ListPtr list) {
    ListPtr current = list->next;
    int empty = 1;
    
    while (current->val != INT_MIN) {
        printf("%d --> ", current->val);
        current = current->next;
        empty = 0;
    }

    if (empty == 1) puts("The List is empty!");
    else puts("");
}

// If index > list size the value will be appended
int insertAt(ListPtr list, int val, int index) {
    ListPtr newElement = (ListPtr)malloc(sizeof(List));
    if (newElement == NULL) return 1;

    ListPtr current = list;

    while (current->next->val != INT_MIN && index > 0) {
        index--;
        current = current->next;
    }

    newElement->val = val;
    newElement->next = current->next;
    current->next = newElement;

    return 0;
}

// The name 'remove' is already defined in stdio.h
int removeLL(ListPtr list, int toRemove) {
    ListPtr current = list;
    
    while (current->next->val != INT_MIN && current->next->val != toRemove) {
        current = current->next;
    }
    
    if (current->next->val == toRemove) {
        ListPtr elementToRemove = current->next;
        current->next = current->next->next;
        free(elementToRemove);

        return 0;
    }

    // The element does not exist on the list
    return 1;
}

void freeList(ListPtr *list) {
    // Will be at least two elements on every list
    ListPtr currentElement = *list;
    ListPtr nextElement = currentElement->next;

    // In that case the code does not check 'next' field of NULL reference
    while (nextElement != NULL) {
        free(currentElement);
        currentElement = nextElement;
        nextElement = nextElement->next;
    }
    free(currentElement);
}

int main() {
    ListPtr list = createList();
    append(list, 5);
    append(list, 2);
    append(list, 10);
    append(list, 27);
    insertAt(list, 33, 0);
    insertAt(list, 0, 30);
    insertAt(list, 97, 3);
    printList(list);
    int removeRes = removeLL(list, 100);
    if (removeRes != 0) printf("Remove returned: %d\n", removeRes);
    removeRes = removeLL(list, 10);
    if (removeRes != 0) printf("Remove returned: %d\n", removeRes);
    printList(list);

    freeList(&list);

    return 0;
}
