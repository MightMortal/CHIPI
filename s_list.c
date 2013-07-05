/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * © 2013 MightMortal
 * Licence: -----
 */

#include "s_list.h"
#include <stdlib.h>

S_LIST* s_list_create() {
    S_LIST* result = (S_LIST*) malloc(sizeof(S_LIST));
    result->head = NULL;
    result->tail = NULL;
    result->size = 0;
    return result;
}

void s_list_destroy(S_LIST* list) {
    S_LIST_NODE* node = list->head;
    while (node) {
        free(node->prev);
        node->prev = NULL;
        list->size--;
        node = node->next;
    }
    free(list);
}

void* s_list_get_element(S_LIST* list, int index) {
    if (index > list->size || index < 0) {
        return NULL;
    }
    int pos = 0;
    S_LIST_NODE* node = list->head;
    while (pos != index) {
        node = node->next;
        pos++;
    }
    return node->value;
}

void s_list_push(S_LIST* list, void* value) {
    S_LIST_NODE* new_element = (S_LIST_NODE*)malloc(sizeof(S_LIST_NODE));
    new_element->next = NULL;
    new_element->prev = list->tail;
    new_element->value = value;
    if (list->size == 0) {
        list->head = new_element;
    }
    if (list->tail) {
        list->tail->next = new_element;
    }
    list->size++;
    list->tail = new_element;
}

void s_list_erase(S_LIST* list, int index) {
    if (index < 0 || index >= list->size) {
        return;
    }
    S_LIST_NODE* element = s_list_get_element(list, index);
    S_LIST_NODE* right_element = element->next;
    S_LIST_NODE* left_element = element->prev;
    if (right_element) {
        right_element->prev = left_element;
    }
    if (left_element) {
        left_element->next = right_element;
    }
    list->size--;
    free(element->value);
    free(element);
    element = NULL;
}