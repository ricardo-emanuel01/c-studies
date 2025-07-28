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
    ListPtr new_element = (ListPtr)malloc(sizeof(List));
    if (new_element == NULL) return 1;

    ListPtr current = list;
    while (current->next->val != INT_MIN) {
        current = current->next;
    }

    new_element->val = val;
    new_element->next = current->next;
    current->next = new_element;

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
    ListPtr new_element = (ListPtr)malloc(sizeof(List));
    if (new_element == NULL) return 1;

    ListPtr current = list;

    while (current->next->val != INT_MIN && index > 0) {
        index--;
        current = current->next;
    }

    new_element->val = val;
    new_element->next = current->next;
    current->next = new_element;

    return 0;
}

// The name 'remove' is already defined in stdio.h
int removeLL(ListPtr list, int to_remove) {
    ListPtr current = list;
    
    while (current->next->val != INT_MIN && current->next->val != to_remove) {
        current = current->next;
    }
    
    if (current->next->val == to_remove) {
        ListPtr element_to_remove = current->next;
        current->next = current->next->next;
        free(element_to_remove);

        return 0;
    }

    // The element does not exist on the list
    return 1;
}

void freeList(ListPtr *list) {
    // Will be at least two elements on every list
    ListPtr current_element = *list;
    ListPtr next_element = current_element->next;

    // In that case the code does not check 'next' field of NULL reference
    while (next_element != NULL) {
        free(current_element);
        current_element = next_element;
        next_element = next_element->next;
    }
    free(current_element);
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
    int remove_res = removeLL(list, 100);
    if (remove_res != 0) printf("Remove returned: %d\n", remove_res);
    remove_res = removeLL(list, 10);
    if (remove_res != 0) printf("Remove returned: %d\n", remove_res);
    printList(list);

    freeList(&list);

    return 0;
}
