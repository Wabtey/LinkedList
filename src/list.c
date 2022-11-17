/**************************************************************************
 * L3Informatique						C/Unix
 * 			TP linked lists
 *
 * Group 	:
 * Name 1 : BOULAY Quentin
 * Name 2 : EPAIN Florian
 *
 **************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

/*
 * SYNOPSYS    :
 *   list_elem_t * create_element(int value)
 * DESCRIPTION :
 *   creates a new element, whose field next is initialized with NULL and the field
 *   value is initialized with the integer passed as argument.
 * PARAMETERS :
 *   value : value of the element
 * RESULT :
 *   NULL in case of error, otherwise a pointer over one strusture of type list_elem_t
 */
static list_elem_t *
create_element (int value)
{
  list_elem_t * newelt = malloc (sizeof (list_elem_t));
  if (newelt != NULL) {
    newelt->value = value;
    newelt->next = NULL;
  }
  return newelt;
}

/*
 * SYNOPSYS :
 *   int insert_head(list_elem_t * * l, int value)
 * DESCRIPTION :
 *   Insert an element at the head of the list
 *   *l points the new head of the list.
 * PARAMETERS :
 *   list_elem_t ** l : pointer to the pointer of the head of the list
 *   int value : value of the element that is added
 * RESULT :
 *    0 in case of successful insertion
 *   -1 if the insertion is impossible
 */
int
insert_head (list_elem_t * * l, int value)
{
  if (l == NULL) { return -1; }
  list_elem_t * new_elt = create_element (value);
  if (new_elt == NULL) { return -1; }

  new_elt->next = *l;
  *l = new_elt;
  return 0;
}

/*
 * SYNOPSYS :
 *   int insert_tail(list_elem_t * * l, int value)
 * DESCRIPTION :
 *   Insert an element at the tail of the list (* l points the head of the list)
 * PARAMETERS :
 *   list_elem_t ** l : pointer to the pointer of the head of the list
 *   int value : value of the element that is added
 * RESULT :
 *    0 in case of successful insertion
 *   -1 if the insertion is impossible
 */
int
insert_tail(list_elem_t * * l, int value) {

  if(l==NULL){ return -1; } 
  list_elem_t * head = *l;
  list_elem_t * newTail = create_element(value);

  // browse the list
  if ( head != NULL ) {

    list_elem_t * current = head;
    
    // current's linked to head
    head -> next = current->next;

    while(current -> next != NULL)
    {
      current = current -> next;
    }

    current -> next = newTail;

  }
  // if the list is empty 
  else {
    head = newTail;
  }

  *l=head;
  return 0;
 

}

/*
 * SYNOPSYS :
 *   list_elem_t * find_element(list_elem_t * l, int index)
 * DESCRIPTION :
 *   Return a pointer of the element at the position n°i of the list
 *   (The first element is situated at the position 0).
 * PARAMETERS :
 *   int index : position of the element to be found
 *   list_elem_t * l : pointer of the head of the list
 * RESULTAT :
 *   - a pointer to the element of the list in cas of success
 *   - NULL in case of error
 */
list_elem_t *
find_element(list_elem_t * l, int index) {

  list_elem_t * current = l;

  for (int i = 0 ; i < index ; i++)
  {
    if ( current==NULL ) { return NULL; } 
    current = current -> next;
  }

  return current;
}


/*
 * SYNOPSYS :
 *   list_elem_t * find_element(list_elem_t * l, int index)
 * DESCRIPTION :
 *   Return a pointer of the first element containing the value
 *   Should return the parent aswell to complete his mission with remove()
 *   AND return the head aswell containing the entire list
 * PARAMETERS :
 *   int value : value of the element to be found
 *   list_elem_t * l : pointer of the head of the list
 * RESULTAT :
 *   - three pointer of the list in case of success
 *     - to the element head
 *     - to the element parent
 *     - to the element with this value
 *   - NULL in case of error
 */
head_parent_target
find_first_element_with_value(list_elem_t * l, int value) {

    list_elem_t * current = l;
    // list_elem_t * null = NULL;

    if ( current==NULL ) {
        head_parent_target res;
        res.head = l;
        res.parent = *(list_elem_t *) NULL;
        res.target = *(list_elem_t *) NULL;

        // res.parent = *null;
        // res.target = *null;
        return res;
    } 
    
    // without && current-> next != NULL
    while ( current->value != value )
    {
      list_elem_t * parent = current;
      current = current -> next;
      if ( current==NULL ) {
          head_parent_target res;
          res.head = l;
          res.parent = *parent;
          // segmentation fault obtains with remove_test.txt
          res.target = *(list_elem_t *) NULL;
          return res;
      } 
      else if ( current->value == value ) {
          // should return the parent to be used in remove()
          // AND return the head aswell containing the entire list
          head_parent_target res;
          res.head = l;
          res.parent = *parent;
          res.target = *current;
          return res;
      }
    }

    head_parent_target res;
          res.head = l;
          res.parent = *(list_elem_t *) NULL;
          res.target = *(list_elem_t *) NULL;
    return res;
}

/*
 * SYNOPSYS :
 *   int remove_element(list_elem_t * * ppl, int value)
 * DESCRIPTION :
 *   Removes from the list the first element with a value equal to the argument value and 
 *   frees the memory space reserved by this element.
 *   Attention : Depending on the position, the head of the list may need to be modified
 * PARAMETERS :
 *   list_elem_t ** ppl : pointer to the pointer of the head of the list
 *   int value  : value to be removed from the list
 * RESULT :
 *    0 in case of success
 *   -1 in case of error
 */
int
remove_element(list_elem_t * * ppl, int value) {
     head_parent_target headParentTarget = find_first_element_with_value(*ppl, value);

     list_elem_t * head = headParentTarget.head;
     list_elem_t * parent = &headParentTarget.parent;
     list_elem_t * target = &headParentTarget.target;

     if (
        head != NULL   &&
        parent != NULL &&
        target != NULL
     ) {
          parent->next =  target->next;
          ppl = &head;
          free(target);
          return 0;
     }
     else { return -1; }
    //  switch( headParentTarget ) {
    //       case (NULL, NULL, NULL):
    //       case (head, NULL, NULL):
    //       case (head, parent, NULL): return -1; // break;
    //       case (head, parent, target): 
    //            // redundant if
    //            if (target != NULL) {
    //                 parent->next =  target->next;
    //                 ppl = *head;
    //                 free(target);
    //            }
    //            return 0;
    //            // break;
    //  }
}


/*
 * SYNOPSYS :
 *   void reverse_list(list_elem_t * * l)
 * DESCRIPTION :
 *   Modifies the list by inversing the order of the elements.
 *   So the 1st element becomes the last element, the 2nd becomes the before last element, etc.)
 * PARAMETRES :
 *   list_elem_t ** l : pointer to the pointer of the head of the list
 * RESULTAT :
 *   aucun 
 */
void
reverse_list(list_elem_t * * l) {
  // .addTail()
}

/*
 * SYNOPSYS :
 *   void erase_list(list_elem_t * * ppl)
 * DESCRIPTION :
 *   Before exiting the program, it erases the elements of the list 
 * PARAMETRES :
 *   list_elem_t ** l : pointer to the pointer of the head of the list
 * RESULTAT :
 *   aucun 
 */
void
erase_list(list_elem_t * * ppl) {
    // if(l==NULL){ return -1; } 
    list_elem_t * head = *ppl;

    if ( head != NULL ) {

        list_elem_t * before = head;
        list_elem_t * current = head->next;

        while (current->next != NULL) {
          free(before);
          before = current;
          current = current->next;          
      }
      // free(before);
      free(current);
    }

}

