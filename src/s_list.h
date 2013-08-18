#ifndef CHIPI_8_S_LIST
#define CHIPI_8_S_LIST
/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * Licence: Apache Licence
 * Copyright 2013 MightMortal
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
