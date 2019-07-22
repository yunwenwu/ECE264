#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"

bool parse_int(int* a_value, char** a_pos) {
    if((**a_pos - '0' <= 9 && **a_pos >= '0') || **a_pos == '-') {
        int symbol = 1;
        if(**a_pos == '-') {
            symbol = -1;
            (*a_pos) ++;
            if ((**a_pos < '0') || (**a_pos - '0' > 9)) {
                return false;
            }
        }

        *a_value = 0;
        while((**a_pos - '0' <= 9) && (**a_pos != '\0') && (**a_pos - '0' >= 0)) {
            int v = **a_pos - '0';
            *a_value = *a_value * 10 + v;
            (*a_pos) ++;
        }

        *a_value = symbol * (*a_value);
        return true;
    }
    return false;
}

bool parse_string(char** a_string, char** a_pos) {
    if (**a_pos != '"') {
        return false;
    }
    char* test_length = *a_pos;
    int length = 1;
    bool is_str = false;
    while(*test_length != '\0') {
        length ++;
        test_length ++;
        if (*test_length == '\n') {
            break;
        }
        
        if (*test_length == '"') {
            is_str = true;
            break;
        }
    }
    if (is_str == false) {
        return false;
    }
    length ++;
    length -= 2;
    char* dup_str = malloc(length * sizeof(*dup_str));
    char* store_str = dup_str;

    (*a_pos) ++;
    do {
        *store_str = **a_pos;
        store_str ++;
        (*a_pos) ++;
    } while (**a_pos != '"');
    *store_str = '\0';
    *a_string = dup_str;
    (*a_pos) ++;
    return true;
}

Node* _create_node(char** a_pos, bool* correct_list) {
    Node* new_node = malloc(sizeof(*new_node));
    new_node -> next = NULL;
    Element new_element;
    if (**a_pos == ']') {
        *correct_list = true;
        new_element.type = ELEMENT_NULL;
        new_element.value.as_null = NULL;
        new_node -> element = new_element;
        return new_node;
    }
    
    *correct_list = parse_element(&new_element, a_pos);

    new_node -> element = new_element;
    return new_node;
}

bool parse_list(Node** a_head, char** a_pos) {
    if(**a_pos != '[') {
        return false;
    }
    (*a_pos) ++;

    bool correct_list = true;

    Node* head = _create_node(a_pos, &correct_list);
    *a_head = head;
    Node* last_node = head;
    if (correct_list == false) {
        return false;
    }
    
    while(**a_pos != ']') {
        while(**a_pos != ',' && **a_pos != ']') {
            if(**a_pos == '\0') {
                return false;
            }
	(*a_pos) ++;
        }
        
        (*a_pos) ++;
        if((**a_pos) - 1 == ',' && (**a_pos) == '\0') {
            return false;
        } else if((**a_pos)-1==']' && (**a_pos) == '\0') {
            break;
        } else{
            Node* new_node = _create_node(a_pos, &correct_list);
            if (correct_list == false) {
                return false;
            }
            last_node -> next = new_node;
            last_node = new_node;
        }
    }
    (*a_pos) ++;
    return true;
}


bool parse_element(Element* a_element, char** a_pos) {
    if (*a_pos == NULL) {
        return false;
    }
    while(true) {
        if (isspace(**a_pos) == false) {
            break;
        }
        (*a_pos) ++;
    }
    bool result = false;
    if (isdigit(**a_pos) || **a_pos == '-') {
        result = parse_int(&a_element->value.as_int, a_pos);
        if(result == true) {
            a_element -> type = ELEMENT_INT;
        }
    } else if(**a_pos == '"') {
        result = parse_string(&a_element->value.as_string, a_pos);
        if(result == true) {
            a_element -> type = ELEMENT_STRING;
        }
    } else if(**a_pos == '[') {
        result = parse_list(&a_element->value.as_list, a_pos);
        a_element -> type = ELEMENT_LIST;
    }
    return result;
}

void print_element(Element element) {
    if((&element) -> type == ELEMENT_INT) {
        printf("%d", (&element) -> value.as_int);
    } else if ((&element) -> type == ELEMENT_STRING) {
        printf("\"%s\"", (&element) -> value.as_string);
    } else if ((&element) -> type == ELEMENT_LIST) {
        printf("[");
        Element dup_element = element;
        while((&dup_element) -> value.as_list != NULL) {
            print_element((&dup_element) -> value.as_list->element);
            (&dup_element) -> value.as_list = (&dup_element) -> value.as_list -> next;
	        if((&dup_element) -> value.as_list != NULL) {
	            printf(",");
	        }
        }
        printf("]");
    } else if((&element) -> type == ELEMENT_NULL) {
        ;
    }
    return;
}


void free_element(Element element) {
    if((&element) -> type == ELEMENT_STRING) {
        free((&element) -> value.as_string);
    } else if((&element) -> type == ELEMENT_LIST) {
        Node* free_head = (&element) -> value.as_list;
        Node* free_list = free_head;
        while(free_head != NULL) {
            free_head = free_head -> next;
            free_element(free_list -> element);
            free(free_list);
            free_list = free_head;
        }
    } else if((&element) -> type == ELEMENT_INT) {
        ;
    }
    return;
}