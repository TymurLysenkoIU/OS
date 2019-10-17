#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdarg.h>
#include <math.h>

#define DEFAULT_PAGE_FRAMES 100
#define REFERENCE_FILE "./Lab 09 input.txt"
#define FIRST_BIT_OF_BYTE 0b10000000

// ----------------------------------------------------------------------------
// Implementation of double linked list

#ifndef DLL_NODE_H
#define DLL_NODE_H


/*!
 * @brief Represents a node in double linked list
 */
typedef
  struct dll_node
dll_node;

/*!
 * @brief Represents a node in double linked list
 */
struct dll_node
{
  /*!
   * @brief value Value of any type, stored within the current node
   */
  void* value;

  /*!
   * @brief left Pointer to a node on the left of the current
   */
  dll_node* left;
  dll_node* right;

  /*!
   * @brief Indicates if there was allocated memory for the value and value was
   * copied. Used to know if the value needs to be freed. Managed by the
   * functions, needs not to be modified by the user.
   */
  char value_allocated : 1;
};

/*!
 * @brief Creates a new dll_node with a memcopy of a value pointed by
 * <code>value</code>, left & right, which can be NULL
 * @param value Value stored within the created node
 * @param left Pointer to the node that is considered to be on the left from
 * the node being created
 * @param right Pointer to the node that is considered to be on the left from
 * the node being created
 * @return A newly created node with given assigned members
 */
dll_node* construct_dll_node_copy(
  void* value,
  const unsigned int type_size,
  dll_node* left,
  dll_node* right
);

/*!
 * @brief Creates a new dll_node with a memcopy of a value pointed by
 * <code>value</code>, that is not connected to
 * any other nodes
 * @param value Value stored within the created node
 * @return A newly created node with given assigned members
 */
dll_node* construct_single_dll_node_with_value_copy(
  void* value,
  const unsigned int type_size
);

/**
 * @brief Creates a new dll_node with a memcopy of a value pointed by
 * <code>value</code> & right, which can be NULL
 * @param value Value stored within the created node
 * @param right Pointer to the node that is considered to be on the left from
 * the node being created
 * @return A newly created node with given assigned members
 */
dll_node* construct_dll_node_with_value_right_copy(
  void* value,
  const unsigned int type_size,
  dll_node* right
);

/*!
 * @brief Creates a new dll_node with a memcopy of a value pointed by
 * <code>value</code> & left, which can be NULL
 * @param value Value stored within the created node
 * @param left Pointer to the node that is considered to be on the left from
 * the node being created
 * @return A newly created node with given assigned members
 */
dll_node* construct_dll_node_with_value_left_copy(
  void* value,
  const unsigned int type_size,
  dll_node* left
);

/*!
 * @brief Creates a new dll_node with a given value, left & right,
 * which can be NULL
 * @param value Value stored within the created node
 * @param left Pointer to the node that is considered to be on the left from
 * the node being created
 * @param right Pointer to the node that is considered to be on the left from
 * the node being created
 * @return A newly created node with given assigned members
 */
dll_node* construct_dll_node(
  void* value,
  dll_node* left,
  dll_node* right
);

/*!
 * @brief Creates a new dll_node with a given value, that is not connected to
 * any other nodes
 * @param value Value stored within the created node
 * @return A newly created node with given assigned members
 */
dll_node* construct_single_dll_node_with_value(
  void* value
);

/**
 * @brief Creates a new dll_node with a given value & right, which can be NULL
 * @param value Value stored within the created node
 * @param right Pointer to the node that is considered to be on the left from
 * the node being created
 * @return A newly created node with given assigned members
 */
dll_node* construct_dll_node_with_value_right(
  void* value,
  dll_node* right
);

/*!
 * @brief Creates a new dll_node with a given value & left, which can be NULL
 * @param value Value stored within the created node
 * @param left Pointer to the node that is considered to be on the left from
 * the node being created
 * @return A newly created node with given assigned members
 */
dll_node* construct_dll_node_with_value_left(
  void* value,
  dll_node* left
);


/*!
 * @brief Creates a new empty dll_node. It contains no value, left & right
 * (all are NULL-s)
 * @return A newly created empty node
 */
dll_node* construct_empty_dll_node(void);


/*!
 * @brief Frees memory allocated to a given dll_node
 * @param node_to_free Pointer to node which must be freed
 * @param destructor Function that frees memory for a value stored in the node.
 * If null, uses free function instead
 */
void free_dll_node(dll_node* node_to_free, void (*destructor)(void* value));

/*!
 * @brief Wrapper to <code>free_dll_node</code> to be used by
 * <code>dll_map_for_all_nodes</code> to release memory allocated to nodes of a
 * list.
 * @see <code>free_dll_node</code>
 * @see <code>dll_map_for_all_nodes</code>
 */
void free_dll_node_wrapper(dll_node* node_to_free, va_list args);

#endif // DLL_NODE_H


dll_node* construct_dll_node_copy(
  void* value,
  const unsigned int type_size,
  dll_node* left,
  dll_node* right
)
{
  dll_node* new_dll_node = malloc(sizeof(dll_node));
  new_dll_node->value = malloc(type_size);

  memcpy(new_dll_node->value, value, type_size);
  new_dll_node->left = left;
  new_dll_node->right = right;
  new_dll_node->value_allocated = 1;

  return new_dll_node;
}

dll_node* construct_single_dll_node_with_value_copy(
  void* value,
  const unsigned int type_size
)
{
  return construct_dll_node_copy(value, type_size, NULL, NULL);
}

dll_node* construct_dll_node_with_value_right_copy(
  void* value,
  const unsigned int type_size,
  dll_node* right
)
{
  return construct_dll_node_copy(value, type_size, NULL, right);
}

dll_node* construct_dll_node_with_value_left_copy(
  void* value,
  const unsigned int type_size,
  dll_node* left
)
{
  return construct_dll_node_copy(value, type_size, left, NULL);
}

dll_node* construct_dll_node(
  void* value,
  dll_node* left,
  dll_node* right
)
{
  dll_node* new_dll_node = malloc(sizeof(dll_node));

  new_dll_node->value = value;
  new_dll_node->left = left;
  new_dll_node->right = right;
  new_dll_node->value_allocated = 0;

  return new_dll_node;
}

dll_node* construct_single_dll_node_with_value(
  void* value
)
{
  construct_dll_node(value, NULL, NULL);
}

dll_node* construct_dll_node_with_value_right(
  void* value,
  dll_node* right
)
{
  construct_dll_node(value, NULL, right);
}

dll_node* construct_dll_node_with_value_left(
  void* value,
  dll_node* left
)
{
  construct_dll_node(value, left, NULL);
}

dll_node* construct_empty_dll_node(void)
{
  construct_dll_node(NULL, NULL, NULL);
}


void free_dll_node(
  dll_node* node_to_free,
  void (*destructor)(void* value)
)
{
  if (destructor)
  {
    destructor(node_to_free->value);
  }
  else if (node_to_free->value_allocated)
  {
    free(node_to_free->value);
  }

  free(node_to_free);
}

void free_dll_node_wrapper(dll_node* node_to_free, va_list args)
{
  void (*destructor)(void* value) = va_arg(
    args,
    void(*)(void* value)
  );

  free_dll_node(node_to_free, destructor);
}


#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

/*!
 * @brief Structure that implements a double linked list for any type
 * and utilizes an auxiliary pointer to its node - cursor, value of which
 * changes to point to a node that was accessed the last by different
 * operations on the list.
 */
typedef
  struct double_linked_list
  {
    /*!
     * @brief Number of elements in the list.
     */
    unsigned int size;
    /*!
     * @brief Size in bytes of a type stored in the list.
     */
    unsigned int type_size;

    #define dll_head_idx (0)
    #define dll_tail_idx(LIST_PTR) \
    ((LIST_PTR->size == 0) ? 0 : (LIST_PTR->size - 1))
    /*!
     * @brief Index of the node currently pointed by the cursor
     * in the list. If there are no elements in the list - cursor_idx == 0
     */
    unsigned int cursor_idx;

    /*!
     * @brief Points to the first node in the linked list.
     */
    dll_node* head;
    /*!
     * @brief Points to the last element in the linked list.
     */
    dll_node* tail;
    /*!
     * @brief Points to the last accessed element
     * by the operations performed on the list, such as add, get, etc.
     */
    dll_node* cursor;

    /*!
     * @brief Comparator for the elements stored in the list. Can be NULL.
     * If it is NULL, then all operations which require to compare elements
     * have no effect and behave as there is nothing to compare.
     */
    const int (*comp)(const void* left, const void* right);
    /*!
     * @brief Destructor for the pointer to the stored element. NULL, by
     * default, so usual free(value) is used.
     * @param value Pointer to the value to be freed.
     */
    void (*destr)(void* value);
  }
double_linked_list;


/*!
 * @brief Constructs a new empty double linked list, initialized with given
 * comparator and destructor.
 * @param type_size Size of a type that is stored in the list.
 * @param comp Comparator for elements stored in the list.
 * @param destr Destructor for elements stored in the list.
 * @return A pointer to the newly constructed double linked list.
 */
double_linked_list* construct_double_linked_list_with_comp_destr(
  const unsigned int type_size,
  const int (*comp)(const void* left, const void* right),
  void (*destr)(void* value)
);

/*!
 * @brief Constructs a new empty double linked list, initialized with given
 * comparator.
 * @param type_size Size of a type that is stored in the list.
 * @param comp Comparator for elements stored in the list.
 * @return A pointer to the newly constructed double linked list.
 */
double_linked_list* construct_double_linked_list_with_comp(
  const unsigned int type_size,
  const int (*comp)(const void* left, const void* right)
);

/*!
 * @brief Constructs a new empty double linked list, initialized with given
 * destructor.
 * @param type_size Size of a type that is stored in the list.
 * @param destr Destructor for elements stored in the list.
 * @return A pointer to the newly constructed double linked list.
 */
double_linked_list* construct_double_linked_list_with_destr(
  const unsigned int type_size,
  void (*destr)(void* value)
);

/*!
 * @brief Constructs a new empty double linked list,
 * initialized with default values.
 * @param type_size Size of a type that is stored in the list.
 * @return A pointer to the newly constructed double linked list.
 */
double_linked_list* construct_empty_double_linked_list(
  const unsigned int type_size
);

/*!
 * @brief Copies a given double linked list and returns a pointer to the double
 * linked list where it was copied.
 * @param list_to_copy List to copy from.
 * @return Pointer to a new double linked list with copied data.
 */
double_linked_list* copy_double_linked_list(double_linked_list* list_to_copy);


/*!
 * @brief Frees memory used by a double linked list.
 * @param dll List to free.
 */
void free_double_linked_list(double_linked_list* dll);

/*!
 * @brief Frees memory used by a double linked list.
 * @param dll List to free.
 */
void free_double_linked_list_wrapper(void* dll);


/*!
 * @brief Checks if a given double linked list is empty.
 * @param this List to perform the action for.
 * @return Returns a non-zero value if list is empty, otherwise - 0
 */
static inline const int dll_is_empty(const double_linked_list* this)
{
  return (this->size == 0);
}

/*!
 * @brief Checks if a given index is valid (that is, there is
 * an element at the index in the list) for a given double linked list.
 * @param this List to perform the action for.
 * @param idx Index to perform the action for.
 * @return Non-zero value if index is valid, 0 - otherwise.
 */
static inline const int dll_is_index_valid(
  const double_linked_list* this,
  const unsigned int idx
)
{
  return (idx < this->size);
}

/*!
 * @brief Checks if a given range [idx_from, idx_to] is,
 * valid (that is all values in range [idx_from, idx_to] are valid indexes and
 * idx_from <= idx_to) for a given double linked list.
 * @param this List to perform the action for.
 * @param idx_from The left value of a given range.
 * @param idx_to The right value of a given range.
 * @return Non-zero value if range is valid, 0 - otherwise.
 */
static inline const int dll_is_range_valid(
  const double_linked_list* this,
  const unsigned int idx_from,
  const unsigned int idx_to
)
{
  return dll_is_index_valid(this, idx_from) &&
         dll_is_index_valid(this, idx_to) &&
         (idx_from <= idx_to);
}


/*!
 * @brief Adds a copy of a given element (pointed by value) at the beginning of
 * a given double linked list.
 * @param this Double linked list @ which an element is to be inserted.
 * @param value Pointer to value to be copied into the list.
 * @return Pointer to the given list.
 */
double_linked_list* dll_prepend_copy(double_linked_list* this, void* value);

/*!
 * @brief Adds a given element at the beginning of a given double linked list.
 * @param this Double linked list @ which an element is to be inserted.
 * @param value Pointer to value, which (pointer) will be added into the list.
 * @return Pointer to the given list.
 */
double_linked_list* dll_prepend_value(double_linked_list* this, void* value);

/*!
 * @brief Adds a copy of a given element (pointed by value) at the end of
 * a given double linked list.
 * @param this Double linked list @ which an element is to be inserted.
 * @param value Pointer to value to be copied into the list.
 * @return Pointer to the given list.
 */
double_linked_list* dll_append_copy(double_linked_list* this, void* value);

/*!
 * @brief Adds a given element at the end of a given double linked list.
 * @param this Double linked list @ which an element is to be inserted.
 * @param value Pointer to value, which (pointer) will be added into the list.
 * @return Pointer to the given list.
 */
double_linked_list* dll_append_value(double_linked_list* this, void* value);

/*!
 * @brief Adds a copy of a given element (pointed by value) at a given index, so
 * that it is guaranteed for the element to reside at the index and the previous
 * element will have its index = index + 1. If index is invalid, then no value
 * is inserted.
 * @param this Double linked list @ which an element is to be inserted.
 * @param value Value to be inserted.
 * @param idx Index on which the operation is to be performed.
 * @return Pointer to the given list. If a given index <code>idx</code> is
 * invalid, NULL is returned.
 */
double_linked_list* dll_add_copy_at_idx(
  double_linked_list* this,
  void* value,
  const unsigned int idx
);

/*!
 * @brief Adds a given element at a given index, so
 * that it is guaranteed for the element to reside at the index and the previous
 * element will have its index = index + 1. If index is invalid, then no value
 * is inserted.
 * @param this Double linked list @ which an element is to be inserted.
 * @param value Value to be inserted.
 * @param idx Index on which the operation is to be performed.
 * @return Pointer to the given list. If a given index <code>idx</code> is
 * invalid, NULL is returned.
 */
double_linked_list* dll_add_value_at_idx(
  double_linked_list* this,
  void* value,
  const unsigned int idx
);


/*!
 * @brief Removes all elements from a given double linked list and sets related
 * members to appropriate values.
 * @param this List from which the element is to be removed.
 * @return Always returns a pointer to the given list.
 */
double_linked_list* dll_clear(double_linked_list* this);

/*!
 * @brief Removes the very first element from a given double linked list. If the
 * list is empty - nothing happens.
 * @param this List from which the element is to be removed.
 * @return Always returns a pointer to the given list.
 */
double_linked_list* dll_remove_first(double_linked_list* this);

/*!
 * @brief Removes the very last element from a given double linked list. If the
 * list is empty - nothing happens.
 * @param this List from which the element is to be removed.
 * @return Always returns a pointer to the given list.
 */
double_linked_list* dll_remove_last(double_linked_list* this);

/*!
 * @brief Removes an element at a given index in a given list. If the
 * list is empty or index is not valid - nothing happens.
 * @param this List from which the element is to be removed.
 * @param idx Index on which the operation is to be performed.
 * @return Always returns a pointer to the given list.
 */
double_linked_list* dll_remove_at_idx(
  double_linked_list* this,
  const unsigned int idx
);

/*!
 * @brief Removes the first element, value of which matches with a given value
 * from a given list. If the list is empty or has no elements matched with a
 * given value - nothing happens. If such value was deleted - cursor and its
 * index will be set to the node before the deleted one and its index
 * respectively if it was not the head, otherwise, sets cursor and its index to
 * the head.
 * @param this List from which the element is to be removed.
 * @param value Value first entry of which is to be removed from the list.
 * @return Always returns a pointer to the given list.
 */
double_linked_list* dll_remove_first_found(
  double_linked_list* this,
  const void* value
);

/*!
 * @brief Removes all elements from a given list, value of which match with
 * a given value. If the list is empty or has no elements matched with a
 * given value - nothing happens. If such value was deleted - cursor and its
 * index will be set to the node before the first deleted one and its index
 * respectively if it was not the head, otherwise, sets cursor and its index to
 * the head.
 * @param this List from which the element is to be removed.
 * @param value Value to match elements against.
 * @return Always returns a pointer to the given list.
 */
double_linked_list* dll_remove_all_found(
  double_linked_list* this,
  const void* value
);


/*!
 * @brief Returns a void* to the element at a given index in a given list.
 * @param this List to perform the action for.
 * @param idx Index to perform the action for.
 * @return void* to an element at index <code>idx</code>. If <code>idx</code>
 * is not valid - returns NULL.
 */
void* dll_get_at(double_linked_list* this, const unsigned int idx);

/*!
 * @brief Traverses a given double linked list, until it finds an element with
 * value <code>value</code>. If such value was found - cursor and its index
 * will be set to the found node containing the element and its index
 * respectively.
 * @param this List to perform the action for.
 * @param value Value to search for.
 * @return Value stored in the list equal to the given. If no such element was
 * found or comp is NULL - returns NULL.
 */
void* dll_find_first(double_linked_list* this, const void* value);


/*!
 * @brief Applies a given function to value of each element of a given list.
 * @param this List to perform the action for.
 * @param func_wrapper Function to be applied to each element. The function is a
 * wrapper to the original one, taking its arguments packed in
 * <code>va_list</code>. Inside, the wrapper should unpack the list and pass
 * each unpacked argument to the function it wraps function.
 * @param ... Other arguments that will be passed to a given function. These
 * arguments are forwarded directly to a given function without being copied. If
 * their number does not match with one required by <code>func_wrapper</code>,
 * the behavior is undefined.
 */
void dll_map_for_all(
  double_linked_list* this,
  void (*const func_wrapper)(void* this, va_list args),
  ...
);

#endif // DOUBLE_LINKED_LIST_H


/*!
 * @brief Works the same as <code>dll_map_for_all</code> except that the
 * <code>func_wrapper</code> is applied to nodes of a given list.
 * @see <code>dll_map_for_all</code>
 */
static void dll_map_for_all_nodes(
  double_linked_list* this,
  void (*const func_wrapper)(dll_node* this, va_list args),
  ...
)
{
  dll_node* cur_node = this->head;

  while (cur_node)
  {
    dll_node* right_node = cur_node->right;

    va_list args;
    va_start(args, func_wrapper);

    func_wrapper(cur_node, args);

    va_end(args);

    cur_node = right_node;
  }
}


double_linked_list* construct_double_linked_list_with_comp_destr(
  const unsigned int type_size,
  const int (*comp)(const void* left, const void* right),
  void (*destr)(void* value)
)
{
  double_linked_list* result = malloc(sizeof(double_linked_list));

  result->size = 0;
  result->type_size = type_size;
  result->head = NULL;
  result->tail = NULL;
  result->cursor = NULL;
  result->cursor_idx = 0;
  result->comp = comp;
  result->destr = destr;

  return result;
}

double_linked_list* construct_double_linked_list_with_comp(
  unsigned int type_size,
  const int (*comp)(const void* left, const void* right)
)
{
  return construct_double_linked_list_with_comp_destr(type_size, comp, NULL);
}

double_linked_list* construct_double_linked_list_with_destr(
  const unsigned int type_size,
  void (*destr)(void* value)
)
{
  return construct_double_linked_list_with_comp_destr(type_size, NULL, destr);
}

double_linked_list* construct_empty_double_linked_list(
  const unsigned int type_size
)
{
  return construct_double_linked_list_with_comp_destr(type_size, NULL, NULL);
}

/*!
 * @brief Auxiliary function used to perform a copying of a list.
 * @param value Value to append to a given list.
 * @param list Double linked list to copy to.
 * @see <code>dll_append</code>
 * @see <code>copy_double_linked_list</code>
 */
static void dll_append_reversed_arg_wrapper(
  dll_node* node_to_copy,
  va_list list
)
{
  double_linked_list* list_to_copy_to = va_arg(list, double_linked_list*);

  if (node_to_copy->value_allocated)
  {
    dll_append_copy(list_to_copy_to, node_to_copy->value);
  }
  else
  {
    dll_append_value(list_to_copy_to, node_to_copy->value);
  }
}

double_linked_list* copy_double_linked_list(double_linked_list* list_to_copy)
{
  double_linked_list* result = construct_double_linked_list_with_comp_destr(
    list_to_copy->type_size,
    list_to_copy->comp,
    list_to_copy->destr
  );

  // copy value from list_to_copy to result
  dll_map_for_all_nodes(
    list_to_copy,
    dll_append_reversed_arg_wrapper,
    result
  );

  return result;
}


void free_double_linked_list(double_linked_list* dll)
{
  dll_map_for_all_nodes(dll, free_dll_node_wrapper, dll->destr);
  free(dll);
}

void free_double_linked_list_wrapper(void* dll)
{
  free_double_linked_list(dll);
}


/*!
 * @brief Traverses a list starting at <code>from_node</code> which has index
 * <code>from_node_idx</code> in the right direction until index
 * <code>to_node_idx</code> is reached. If range [<code>from_node_idx</code>,
 * <code>to_node_idx</code>] is invalid - returns NULL. Sets cursor to the
 * node at <code>to_node_idx</code> in the list.
 * @param this List to perform the action for.
 * @param from_node Node at which traversal is started.
 * @param from_node_idx Index of <code>from_node</code> in <code>this</code>.
 * @param to_node_idx Index at which traversal stops.
 * @return Node at index <code>to_node_idx</code>. If a given range is invalid -
 * returns NULL.
 */
static dll_node* dll_traverse_right_from_to(
  double_linked_list* this,
  dll_node* from_node,
  unsigned int from_node_idx,
  unsigned int to_node_idx
)
{
  dll_node* result = NULL;

  if (dll_is_range_valid(this, from_node_idx, to_node_idx))
  {
    while (from_node_idx < to_node_idx)
    {
      from_node = from_node->right;
      ++from_node_idx;
    }

    result = (this->cursor = from_node);
    this->cursor_idx = from_node_idx;
  }

  return result;
}

/*!
 * @brief Traverses a list starting at <code>from_node</code> which has index
 * <code>from_node_idx</code> in the left direction until index
 * <code>to_node_idx</code> is reached. If range [<code>to_node_idx</code>,
 * <code>from_node_idx</code>] is invalid - returns NULL. Sets cursor to the
 * node at <code>to_node_idx</code> in the list.
 * @param this List to perform the action for.
 * @param from_node Node at which traversal is started.
 * @param from_node_idx Index of <code>from_node</code> in <code>this</code>.
 * @param to_node_idx Index at which traversal stops.
 * @return Node at index <code>to_node_idx</code>. If a given range is invalid -
 * returns NULL.
 */
static dll_node* dll_traverse_left_from_to(
  double_linked_list* this,
  dll_node* from_node,
  unsigned int from_node_idx,
  unsigned int to_node_idx
)
{
  dll_node* result = NULL;

  if (dll_is_range_valid(this, to_node_idx, from_node_idx))
  {
    while (from_node_idx > to_node_idx)
    {
      from_node = from_node->left;
      --from_node_idx;
    }

    result = (this->cursor = from_node);
    this->cursor_idx = from_node_idx;
  }

  return result;
}

/*!
 * @brief Traverses a list starting from a given node, which has a given index
 * in the list until it reaches the target index. Depending on the
 * <code>from_node_idx</code> and <code>to_node_idx</code> the appropriate
 * traversal is performed (left to right or right to left).
 * @param this List to perform the action for.
 * @param from_node Node at which traversal is started.
 * @param from_node_idx Index of <code>from_node</code> in <code>this</code>.
 * @param to_node_idx Index at which traversal stops.
 * @return Node at index <code>to_node_idx</code>. If a given range is invalid -
 * returns NULL.
 */
static dll_node* dll_traverse_from_to(
  double_linked_list* this,
  dll_node* from_node,
  const unsigned int from_node_idx,
  const unsigned int to_node_idx
)
{
  dll_node* result = NULL;

  if (dll_is_range_valid(this, from_node_idx, to_node_idx))
  {
    result = dll_traverse_right_from_to(
      this,
      from_node,
      from_node_idx,
      to_node_idx
    );
  }
  else if (dll_is_range_valid(this, to_node_idx, from_node_idx))
  {
    result = dll_traverse_left_from_to(
      this,
      from_node,
      from_node_idx,
      to_node_idx
    );
  }

  return result;
}

/*!
 * @brief Works the same as <code>dll_get_at</code>, except that it returns
 * a node itself.
 * @return Node at index <code>idx</code>. If <code>idx</code> is not valid -
 * returns NULL.
 * @see <code>dll_get_at</code>
 */
static dll_node* dll_get_node_at(
  double_linked_list* this,
  const unsigned int idx
)
{
  dll_node* result_node = NULL;

  if (dll_is_index_valid(this, idx))
  {
    const unsigned int dist_from_head = idx;
    const unsigned int dist_from_cursor = labs(
      (long)(this->cursor_idx) - idx
    );
    const unsigned int dist_from_tail = dll_tail_idx(this) - idx;

    if (
      (dist_from_cursor <= dist_from_head) &&
      (dist_from_cursor <= dist_from_tail)
    )
    {
      result_node = dll_traverse_from_to(
        this,
        this->cursor,
        this->cursor_idx,
        idx
      );
    }
    else if (dist_from_head <= dist_from_tail)
    {
      result_node = dll_traverse_from_to(this, this->head, dll_head_idx, idx);
    }
    else
    {
      result_node = dll_traverse_from_to(
        this,
        this->tail,
        dll_tail_idx(this),
        idx
      );
    }
  }

  return result_node;
}

/*!
 * @brief Traverses a given double linked list from the beginning and returns
 * a node, such that its value is equal to the given, i. e.
 * comp(node->value, value) == 0. If such node was found - cursor and its index
 * will be set to the found element and its index respectively.
 * @param this List to perform the action for.
 * @param value Value to compare against.
 * @return Node with value stored equal to the given. If no such node was found
 * or comp is NULL - returns NULL.
 */
static dll_node* dll_find_first_node(
  double_linked_list* this,
  const void* value
)
{
  dll_node* cur_node = NULL;

  if (this->comp)
  {
    cur_node = this->head;
    unsigned int cur_node_idx = dll_head_idx;

    while (cur_node)
    {
      if ((this->comp(cur_node->value, value)) == 0)
      {
        this->cursor = cur_node;
        this->cursor_idx = cur_node_idx;
        break;
      }

      cur_node = cur_node->right;
      ++cur_node_idx;
    }
  }

  return cur_node;
}


double_linked_list* dll_prepend_copy(double_linked_list* this, void* value)
{
  this->cursor = construct_dll_node_with_value_right_copy(
    value,
    this->type_size,
    this->head
  );
  this->cursor_idx = dll_head_idx;

  if (dll_is_empty(this))
  {
    this->tail = this->cursor;
  }
  else
  {
    this->head->left = this->cursor;
  }

  this->head = this->cursor;
  ++(this->size);

  return this;
}

double_linked_list* dll_prepend_value(double_linked_list* this, void* value)
{
  this->cursor = construct_dll_node_with_value_right(
    value,
    this->head
  );
  this->cursor_idx = dll_head_idx;

  if (dll_is_empty(this))
  {
    this->tail = this->cursor;
  }
  else
  {
    this->head->left = this->cursor;
  }

  this->head = this->cursor;
  ++(this->size);

  return this;
}

double_linked_list* dll_append_copy(double_linked_list* this, void* value)
{
  this->cursor = construct_dll_node_with_value_left_copy(
    value,
    this->type_size,
    this->tail
  );
  this->cursor_idx = dll_tail_idx(this) + 1;

  if (dll_is_empty(this))
  {
    this->head = this->cursor;
  }
  else
  {
    this->tail->right = this->cursor;
  }

  this->tail = this->cursor;
  ++(this->size);

  return this;
}

double_linked_list* dll_append_value(double_linked_list* this, void* value)
{
  this->cursor = construct_dll_node_with_value_left(
    value,
    this->tail
  );
  this->cursor_idx = dll_tail_idx(this) + 1;

  if (dll_is_empty(this))
  {
    this->head = this->cursor;
  }
  else
  {
    this->tail->right = this->cursor;
  }

  this->tail = this->cursor;
  ++(this->size);

  return this;
}

double_linked_list* dll_add_copy_at_idx(
  double_linked_list* this,
  void* value,
  const unsigned int idx
)
{
  double_linked_list* result = NULL;
  dll_node* node_at_idx = dll_get_node_at(this, idx);

  if (node_at_idx)
  {
    if (idx == dll_head_idx)
    {
      dll_prepend_copy(this, value);
    }
    else if (idx == dll_tail_idx(this))
    {
      dll_append_copy(this, value);
    }
    else
    {
      dll_node* prev_node = node_at_idx->left;

      this->cursor = construct_dll_node_copy(
        value,
        this->type_size,
        prev_node,
        node_at_idx
      );
      // this->cursor_idx already has a correct index

      node_at_idx->left = (prev_node->right = this->cursor);
      ++(this->size);
    }

    result = this;
  }

  return result;
}

double_linked_list* dll_add_value_at_idx(
  double_linked_list* this,
  void* value,
  const unsigned int idx
)
{
  double_linked_list* result = NULL;
  dll_node* node_at_idx = dll_get_node_at(this, idx);

  if (node_at_idx)
  {
    if (idx == dll_head_idx)
    {
      dll_prepend_value(this, value);
    }
    else if (idx == dll_tail_idx(this))
    {
      dll_append_value(this, value);
    }
    else
    {
      dll_node* prev_node = node_at_idx->left;

      this->cursor = construct_dll_node(
        value,
        prev_node,
        node_at_idx
      );
      // this->cursor_idx already has a correct index

      node_at_idx->left = (prev_node->right = this->cursor);
      ++(this->size);
    }

    result = this;
  }

  return result;
}


double_linked_list* dll_clear(double_linked_list* this)
{
  dll_map_for_all_nodes(this, free_dll_node_wrapper, this->destr);
  this->size = this->cursor_idx = 0;
  this->cursor = this->head = this->tail = NULL;

  return this;
}

double_linked_list* dll_remove_first(double_linked_list* this)
{
  if (this->size == 1)
  {
    dll_clear(this);
  }
  else
  {
    dll_node* node_to_remove = this->head;

    this->head = (this->cursor = this->head->right);
    this->head->left = NULL;
    if (this->tail == this->head)
    {
      this->tail->left = NULL;
    }
    this->cursor_idx = dll_head_idx;

    --(this->size);

    free_dll_node(node_to_remove, this->destr);
  }

  return this;
}

double_linked_list* dll_remove_last(double_linked_list* this)
{
  if (this->size == 1)
  {
    dll_clear(this);
  }
  else
  {
    dll_node* node_to_remove = this->tail;

    this->tail = (this->cursor = this->tail->left);
    this->tail->right = NULL;
    if (this->head == this->tail)
    {
      this->head->right = NULL;
    }
    --(this->size);
    this->cursor_idx = dll_tail_idx(this);

    free_dll_node(node_to_remove, this->destr);
  }

  return this;
}

double_linked_list* dll_remove_at_idx(
  double_linked_list* this,
  const unsigned int idx
)
{
    if (idx == dll_head_idx)
    {
      dll_remove_first(this);
    }
    else if (idx == dll_tail_idx(this))
    {
      dll_remove_last(this);
    }
    else
    {
      dll_node* node_to_remove = dll_get_node_at(this, idx);

      if (node_to_remove)
      {
        this->cursor = (node_to_remove->left->right = node_to_remove->right);
        node_to_remove->right->left = node_to_remove->left;
        --(this->size);

        free_dll_node(node_to_remove, this->destr);
      }
    }

  return this;
}

double_linked_list* dll_remove_first_found(
  double_linked_list* this,
  const void* value
)
{
  if (dll_find_first_node(this, value))
  {
    if (this->cursor == this->head)
    {
      dll_remove_first(this);
    }
    else if (this->cursor == this->tail)
    {
      dll_remove_last(this);
    }
    else
    {
      this->cursor->left->right = this->cursor->right;
      dll_node* new_cursor = (this->cursor->right->left = this->cursor->left);
      free_dll_node(this->cursor, this->destr);
      this->cursor = new_cursor;
      --(this->cursor_idx);
      --(this->size);
    }
  }

  return this;
}

double_linked_list* dll_remove_all_found(
  double_linked_list* this,
  const void* value
)
{
  if (this->comp)
  {
    dll_remove_first_found(this, value);

    dll_node* cur_node = this->cursor;

    while (cur_node == this->head)
    {
      dll_remove_first_found(this, value);
      cur_node = this->cursor;
    }

    cur_node = cur_node->right;

    while (cur_node)
    {
      dll_node* right = cur_node->right;

      if (this->comp(cur_node->value, value) == 0)
      {
        if (cur_node == this->tail)
        {
          dll_remove_last(this);
        }
        else
        {
          cur_node->left->right = right;
          right->left = cur_node->left;
          free_dll_node(cur_node, this->destr);
          --(this->size);
        }
      }

      cur_node = right;
    }
  }

  return this;
}


void* dll_get_at(double_linked_list* this, const unsigned int idx)
{
  dll_node* result_node = dll_get_node_at(this, idx);

  return (result_node) ? result_node->value : NULL;
}

void* dll_find_first(double_linked_list* this, const void* value)
{
  return (dll_find_first_node(this, value)) ? this->cursor->value : NULL;
}


void dll_map_for_all(
  double_linked_list* this,
  void (*const func_wrapper)(void* this, va_list args),
  ...
)
{
  dll_node* cur_node = this->head;

  while (cur_node)
  {
    dll_node* right_node = cur_node->right;

    va_list args;
    va_start(args, func_wrapper);

    func_wrapper(cur_node->value, args);

    va_end(args);

    cur_node = right_node;
  }
}

// End of double linked list implementation
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// The task solution

typedef
  struct
  {
    unsigned char is_loaded;
    unsigned char counter;
    long long page_number;
  }
page_data_t;


double_linked_list* read_reference_file(const char* restrict file_path)
{
  double_linked_list* result = construct_empty_double_linked_list(sizeof(long long));

  FILE* file = fopen(file_path, "r");

  if (file)
  {
    char* read_string = NULL;
    size_t buffer_size = 0;
    while (getdelim(&read_string, &buffer_size, ' ', file) > 0)
    {
      long long current_value = 0;
      sscanf(read_string, "%lld", &current_value);
      dll_append_copy(result, &current_value);
    }
    fclose(file);
  }
  else
  {
    printf("The file %s does not exist.\n", file_path);
  }

  return result;
}


int main(int argc, char* argv[])
{
  // Deal with configs
  size_t num_page_frames = DEFAULT_PAGE_FRAMES;
  if (argc > 1)
  {
    sscanf(argv[1], "%zu", &num_page_frames);
  }

  char* file_path = REFERENCE_FILE;
  if (argc > 2)
  {
    file_path = argv[2];
  }
  double_linked_list* page_references = read_reference_file(file_path);


  // Simulation
  page_data_t* page_frames_data = calloc(num_page_frames, sizeof(page_data_t));
  size_t hits = 0,
         misses = 0;
  page_data_t* not_frequently_used_page = page_frames_data;
  for (size_t i = 0; i < page_references->size; ++i)
  {
    long long cur_page_number = *(long long*)(dll_get_at(page_references, i));
    char hit = 0;
    for (size_t j = 0; j < num_page_frames; ++j)
    {
      if (page_frames_data[j].is_loaded)
      {
        page_frames_data[j].counter >> 1;

        hit = (page_frames_data[j].page_number == cur_page_number);
        if (hit)
        {
          ++hits;
          page_frames_data[j].counter += FIRST_BIT_OF_BYTE;
          break;
        }
        else
        {
          if (page_frames_data[j].counter < not_frequently_used_page->counter)
          {
            not_frequently_used_page = (page_frames_data + j);
          }
        }
      }
      else
      {
        not_frequently_used_page = (page_frames_data + j);
        break;
      }
    }

    if (!hit)
    {
      ++misses;

      // load the page into memory
      not_frequently_used_page->page_number = cur_page_number;
      not_frequently_used_page->counter = FIRST_BIT_OF_BYTE;
      not_frequently_used_page->is_loaded = 1;
    }
  }

  printf(
    "Hits: %lu\n"
    "Misses: %lu\n"
    "Ratio: %f\n"
    ,
    hits,
    misses,
    ((double)hits / (double)misses)
  );

  // Free memory
  free(page_frames_data);
  free_double_linked_list(page_references);
  return 0;
}
