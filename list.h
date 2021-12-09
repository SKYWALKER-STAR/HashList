#ifndef GOOD_LIST_H
#define GOOD_LIST_H

struct node;
struct list;

typedef struct node 	*PtrToNode;
typedef struct list	*PtrToList;
typedef PtrToNode	Element;
typedef PtrToList	List;

struct node {
	void		*data;
	Element		next;
};

struct list {
	int 		size;
	Element		head;
	Element		tail;
	int		(*match)(const void *key1,const void *key2);
	void		(*destroy)(void *data);
};

void list_init(List list,void (*destroy)(void *data));
void list_destroy(List list);
int list_ins_next(List list,Element element,const void *data);
int list_rem_next(List list,Element element,void **data);

inline int list_is_element(List list,void *data);

#define list_size(list) list->size
#define	list_head(list) list->head
#define list_tail(list) list->tail
#define list_is_head(list,element) ((element) == (list)->head ? 1 : 0)
#define list_is_tail(element) element->next == NULL ? 1 : 0
#define list_data(element) element->data
#define list_next(element) element->next

#define DATATYPE int


#endif
