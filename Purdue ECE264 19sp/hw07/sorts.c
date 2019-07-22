#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "sorts.h"

void merge_sort_array(int* array, size_t size) {
    List initial_list = create_list(array, size);
    merge_sort_list(&initial_list);
    List store_array = initial_list;
    if(size != 0) {
        for(size_t i = 0; i < size; i++)
        {
            array[i] = store_array.head -> value;
            store_array.head = store_array.head -> next;
        }
        empty_list(&initial_list);
    }
    return;
}

void _store_array(BSTNode* root, int* array, int* order) {
    if (root != NULL) {
        _store_array(root -> left, array, order);
        array[*order] = root -> value;
        (*order) ++;
        _store_array(root -> right, array, order);
    }
    return;
}

void tree_sort_array(int* array, size_t size) {
    BST sort_bst = create_bst(array, size);
    int order = 0;
    _store_array(sort_bst.root, array, &order);
    empty_bst(&sort_bst);
    return;
}


int _compare_integers(const void* a, const void* b) {
    if((*(int*)a) < (*(int*)b)) {
        return -1;
    } else if((*(int*)a) == (*(int*)b)) {
        return 0;
    } else {
        return 1;
    }
}

void quick_sort_array(int* array, size_t size) {
    qsort(array, size, sizeof(int), _compare_integers);
    return;
}

ListNode* _create_list_node(int value_in_node) {
    ListNode* node_of_list = malloc(sizeof(*node_of_list));
    node_of_list -> value = value_in_node;
    node_of_list -> next = NULL;
    return node_of_list;
}

List create_list(const int* array, int size) {
    List null_list = {
        .head = NULL,
        .tail = NULL,
        .size = 0
    };

    if (size == 0) {
        return null_list;
    }
    ListNode* head = _create_list_node(array[0]);
    ListNode* node = head;
    ListNode* tail = head;
    if (head == NULL) {
        return null_list;
    }

    if (size >= 2) {
        node = _create_list_node(array[1]);
        tail -> next = node;
        tail = node;
    }
    
    for(int i = 2; i < size; i++)
    {
        node = _create_list_node(array[i]);
        tail -> next = node;
        tail = node;
    }
    
    List sort_list = {
        .head = head,
        .tail = tail,
        .size = size
    };

    return sort_list;
}

void merge_sort_list(List* list) {
    if (list -> size > 2) {
        int half_size = list -> size / 2;
        ListNode* middle_node = list -> head;
        for(int i = 1; i < half_size; i++) {
            middle_node = middle_node -> next;
        }

        List first_part = {
            .head = list -> head,
            .tail = middle_node,
            .size = half_size
        };

        List second_part = {
            .head = middle_node -> next,
            .tail = list -> tail,
            .size = list -> size - half_size
        };
        first_part.tail -> next = NULL;

        merge_sort_list(&first_part);
        merge_sort_list(&second_part);
        
        List result_list = {
            .head = NULL,
            .tail = NULL,
            .size = list -> size
        };
        
        if (first_part.head -> value <= second_part.head -> value) {
            result_list.head = first_part.head;
            first_part.head = first_part.head -> next;
        } else {
            result_list.head = second_part.head;
            second_part.head = second_part.head -> next;
        }
        result_list.tail = result_list.head;
        
        while(first_part.head != NULL && second_part.head != NULL) {
            if (first_part.head -> value <= second_part.head -> value) {
                result_list.tail -> next = first_part.head;
                result_list.tail = result_list.tail -> next;
                first_part.head = first_part.head -> next;
            } else {
                result_list.tail -> next = second_part.head;
                result_list.tail = result_list.tail -> next;
                second_part.head = second_part.head -> next;
            }
        }

        if (first_part.head == NULL) {
            while(second_part.head != NULL) {
                result_list.tail -> next = second_part.head;
                result_list.tail = result_list.tail -> next;
                second_part.head = second_part.head -> next;
            }
        } else if(second_part.head == NULL) {
            while(first_part.head != NULL) {
                result_list.tail -> next = first_part.head;
                result_list.tail = result_list.tail -> next;
                first_part.head = first_part.head -> next;
            }
        }
        
        *list = result_list;
    } else if(list -> size == 2 || list -> size == 1) {
        if (list -> head -> value > list -> tail -> value) {
            int exchange_value = list -> head -> value;
            list -> head -> value = list -> tail -> value;
            list -> tail -> value = exchange_value;
        }
    } 
    return;
}

void empty_list(List* list) {
    if(list -> size != 0) {
        while(list -> head -> next != NULL) {
            ListNode* delete_node = list -> head;
            list -> head = list -> head -> next;
            free(delete_node);
        }
        free(list -> head);
        list -> head = NULL;
        list -> tail = NULL;
    }
}


BSTNode* _create_bst_node(int value) {
    BSTNode* node_of_bst = malloc(sizeof(* node_of_bst));
    node_of_bst -> value = value;
    node_of_bst -> left = NULL;
    node_of_bst -> right = NULL;
    return node_of_bst;
}

void _insert_node(BSTNode** root, int value) {
    if (*root == NULL) {
        *root = _create_bst_node(value);
    } else if(value <= (*root) -> value) {
        _insert_node(&((*root) -> left), value);
    } else {
        _insert_node(&((*root) -> right), value);
    }
}

BST create_bst(const int* array, int size) {
    BST sort_bst = {
        .root = NULL,
        .size = size
    };
    if (size == 0) {
        return sort_bst;
    }

    sort_bst.root = _create_bst_node(array[0]);
    for(int i = 1; i < size; i++) {
        _insert_node(&sort_bst.root, array[i]);
    }
    return sort_bst;
}


void empty_bst(BST* bst) {
    if(bst -> root != NULL) {
        BST clear_bst_left = {
            .root = bst -> root -> left
        };
        BST clear_bst_right = {
            .root = bst -> root -> right
        };
        empty_bst(&clear_bst_left);
        empty_bst(&clear_bst_right);
        free(bst -> root);
        bst -> root = NULL;
    }
    return;
}