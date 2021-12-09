#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void list_init(List list,void (*destroy)(void *data))
{
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->destroy = destroy;
	
	return;
}

void list_destroy(List list)
{
	void *data;
	Element ptr;
	
	while(list_size(list) > 0) {
		if (list_rem_next(list,NULL,(void**)&data) == 0 && 
			list->destroy != NULL)
		list->destroy(data);
	}
	
	memset(list,0,sizeof(struct list));
	return ;
}

int list_ins_next(List list,Element element,const void *data)
{
	Element new_element;
	
	if ((new_element = (struct node*)malloc(sizeof(struct node))) == NULL)
		return -1;

	new_element->data = (void*)data;
	
	if (element == NULL) {
		if (list_size(list) == 0) 
		list->tail = new_element;

		new_element->next = list->head;
		list->head = new_element;
	} else {
		
		if (element->next == NULL)
		list->tail = new_element;

		new_element->next = element->next;
		element->next = new_element;
	}
	
	list->size++;
	return 0;
}

int list_rem_next(List list,Element element,void **data)
{
	Element old_element;

	if (list_size(list) == 0)
		return -1;
	
	if (element == NULL) {
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;

		if (list_size(list) == 1)
		list->tail = NULL;
	} else {
		if (element->next == NULL)
			return -1;

		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;
	
		if (element->next == NULL)
		list->tail = element;
	}
	
	free(old_element);
	list->size--;
	return 0;
}

inline int list_is_element(List list,void *data)
{
	Element ptr;
	
	if (!list_size(list))
		return 0;

	ptr = list->head;
	
	while (ptr != NULL) {
		if (memcmp(data,ptr->data,sizeof(DATATYPE)))
			return 1;
		ptr = ptr->next;
	}
	
	return 0;
}
