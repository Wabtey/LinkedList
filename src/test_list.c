/**************************************************************************
 * L3Informatique						C/Unix
 * 			TP linked lists
 *
 * Group 	:
 * Name 1 :
 * Name 2 :
 *
 **************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "list.h"

/* Compute the number of elements of the list */
int list_size(list_elem_t *p_list)
{
  int nb = 0;
  while (p_list != NULL)
  {
    nb += 1;
    p_list = p_list->next;
  }
  return nb;
}

/* Print the elements of the list */
void print_list(list_elem_t *p_list)
{
  list_elem_t *pl = p_list;
  printf("The list contains %d element(s)\n", list_size(p_list));
  while (pl != NULL)
  {
    printf("[%d]", pl->value);
    pl = pl->next;
    if (pl != NULL)
    {
      printf("->");
    }
  }
}

int main(int argc, char **argv)
{
  list_elem_t *head = NULL; // The pointer to the head of the list
  char menu[] =
      "\n Program of chained list \n"
      "  'h/t' : Insert an element to the head/tail of the list\n"
      "  'f'   : search of a list element\n"
      "  's'   : suppression of a list element\n"
      "  'r'   : reverse the order of the list elements\n"
      "  'x'   : exit the program\n"
      " What is your choice ?";
  int choice = 0; // choice from the menu
  int value = 0;  // inserted value
  int index = 0;
  printf("%s", menu);
  fflush(stdout);

  while (1)
  {
    fflush(stdin);
    choice = getchar();
    printf("\n");

    switch (choice)
    {
    case 'H':
    case 'h':
      printf("Value of the new element ? ");
      scanf("%d", &value);
      if (insert_head(&head, value) != 0)
      {
        printf("Error : impossible to add the element %d\n", value);
      };
      break;

    case 'T':
    case 't':
      printf("Value of the new element ? ");
      scanf("%d", &value);
      if (insert_tail(&head, value) != 0)
      {
        printf("Error : impossible to add the element %d\n", value);
      };
      break;

    case 'F':
    case 'f':
      printf("index of the searched element ? ");
      scanf("%d", &index);
      list_elem_t *elem = find_element(head, index);
      if (elem == NULL)
      {
        printf("Error : impossible to find the element %d\n", index);
      }
      else
      {
        printf(" searched element is %d\n", elem->value);
      }
      break;

      // case 'V' :
      // case 'v' :
      //   printf("index of the searched element ? ");
      //   scanf("%d",&value);
      //   list_elem_t * elembis = find_first_element_with_value(head,value);
      //   if ( elembis == NULL) {
      //     printf("Error : impossible to find a element containing %d\n",value);
      //   }
      //   else {
      //     printf(" searched element is %d\n", value);
      //   }
      //   break;

    case 'V':
    case 'v':
      printf("index of the searched element ? ");
      scanf("%d", &value);
      int index = find_index_element(head, value);
      if (index == -1)
      {
        printf("Error : impossible to find a element containing %d\n", value);
      }
      else
      {
        printf(" index of  %d is %d\n", value, index);
      }
      break;

    case 's':
    case 'S':
      printf("Value of the element to remove ? ");
      scanf("%d", &value);
      if (remove_element(&head, value) != 0)
      {
        printf("Error : impossible to remove the element %d\n", value);
      };

    case 'r':
    case 'R':
      reverse_list(&head);
      break;

    case 'x':
    case 'X':
      erase_list(&head);
      print_list(head);
      printf("list erased");
      return 0;

    default:
      break;
    }
    print_list(head);

    getchar(); // to consume a return character and avoid double display of the menu
    printf("%s\n", menu);
  }
  return 0;
}
