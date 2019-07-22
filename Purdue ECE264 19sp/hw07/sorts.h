typedef struct _ListNode {
    int value;
    struct _ListNode* next;
} ListNode;

typedef struct 
{
    ListNode* head;
    ListNode* tail;
    int size;
} List;

typedef struct _BSTNode
{
    int value;
    struct _BSTNode* left;
    struct _BSTNode* right;
} BSTNode;

typedef struct
{
    BSTNode* root;
    int size;
} BST;

void merge_sort_array(int* array, size_t size);

void tree_sort_array(int* array, size_t size);

void quick_sort_array(int* array, size_t size);

List create_list(const int* array, int size);

void merge_sort_list(List* list);

void empty_list(List* list);

BST create_bst(const int* array, int size);

void empty_bst(BST* bst);