#include <stdio.h>
#include <stdlib.h>

typedef
  struct linked_list_node
  {
    int data;
    struct linked_list_node* next;
  }
linked_list_node;

typedef
  struct linked_list
  {
    unsigned int size;
    linked_list_node* head;
  }
linked_list;

void print_list(const linked_list * const restrict list)
{
  const linked_list_node * restrict cur_node = list->head;

  while (cur_node)
  {
    printf("%d\n", cur_node->data);

    cur_node = cur_node->next;
  }
}

linked_list_node* insert_node(linked_list * const restrict list, const int val, const unsigned int idx)
{
  linked_list_node* result = NULL;

  if (idx <= list->size)
  {
    result = malloc(sizeof(linked_list_node));
    result->data = val;

    if (idx == 0)
    {
      result->next = list->head;
      list->head = result;
    }
    else
    {
      linked_list_node* prev_node = list->head;

      for (int i = 0; i < idx - 1; ++i)
      {
        prev_node = prev_node->next;
      }

      result->next = prev_node->next;
      prev_node->next = result;
    }

    ++(list->size);
  }

  return result;
}

linked_list_node* delete_node(linked_list * const restrict list, const unsigned int idx)
{
  linked_list_node* result = NULL;

  if (idx < list->size)
  {
    if (idx == 0)
    {
      result = list->head;
      list->head = list->head->next;
    }
    else
    {
      linked_list_node* prev_node = list->head;

      for (int i = 0; i < idx - 1; ++i)
      {
        prev_node = prev_node->next;
      }

      result = prev_node->next;
      prev_node->next = result->next;
    }

    --(list->size);
  }

  return result;
}

int main()
{
  linked_list l;
  l.size = 0;
  l.head = NULL;

  printf("Before deletion:\n");
  insert_node(&l, 10, 0);
  insert_node(&l, 20, 0);
  insert_node(&l, 5, 1);
  insert_node(&l, 8, 3);
  insert_node(&l, 89, 4);
  print_list(&l);

  printf("After deletion:\n");
  free(delete_node(&l, 4));
  free(delete_node(&l, 0));
  free(delete_node(&l, 1));
  print_list(&l);

  return 0;
}
