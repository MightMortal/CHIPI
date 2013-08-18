#ifndef CHIPI_8_S_LIST
#define CHIPI_8_S_LIST
/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * © 2013 MightMortal
 * Licence: -----
 */

typedef struct S_LIST_NODE_ {
  struct S_LIST_NODE_* prev;
  struct S_LIST_NODE_* next;
  void* value;
} S_LIST_NODE;

typedef struct S_LIST_ {
  S_LIST_NODE* head;
  S_LIST_NODE* tail;
  int size;
} S_LIST;

S_LIST* s_list_create();
void s_list_destroy(S_LIST* list);
void* s_list_get_element(S_LIST* list, int index);
void s_list_push(S_LIST* list, void* element);
void s_list_erase(S_LIST* list, int index);

#endif /* CHIPI_8_S_LIST */
