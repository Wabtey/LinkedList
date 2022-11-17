/* Structure of an element of a linked list */
typedef struct s_list {
	int value;
	struct s_list* next;
} list_elem_t;

/// Contains our target and context
/// used in find_first_element_with_value() and remove()
typedef
struct
{
  list_elem_t * head, parent, target;
} head_parent_target;


/* Prototypes */
int insert_head(list_elem_t** l, int value);
int insert_tail(list_elem_t** l, int value);
int remove_element(list_elem_t** ppl, int value);
list_elem_t* get_tail(list_elem_t* l);
void reverse_list(list_elem_t** l);
list_elem_t* find_element(list_elem_t* l, int index);
head_parent_target find_first_element_with_value(list_elem_t* l, int value);
void erase_list(list_elem_t** ppl);


