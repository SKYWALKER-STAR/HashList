#include "list.h"
#include "chtbl.h"
#include <stdio.h>
#include <stdlib.h>

/* The hash function */
unsigned int hashpjw(const void *key)
{
	const char 	*ptr;
	unsigned int 	val;
	
	val = 0;
	ptr = key;
	
	while (*ptr != '\0')
	{
		unsigned int tmp;
		val = (val << 4) + (*ptr);
	
		if (tmp = (val & 0xf0000000))
		{
			val = val ^ (tmp >> 24);
			val = val ^ tmp;
		}
		
		ptr++;
	}
	
	return val % PRIME_TBLSIZE;
}

int chtbl_init(CHTbl *chtbl,int buckets,unsigned int (*h)(const void *key),
		int (*match)(const void *key1,const void *key2),
		void (*destroy)(void *data))
{
	int i;
	chtbl->buckets = buckets;
	chtbl->h = h;
	chtbl->match = match;
	chtbl->destroy = destroy;
	chtbl->size = 0;
	
	if ((chtbl->table = 
		(struct list*)malloc(sizeof(struct list) * buckets)) == NULL)
		return -1;
	
	for (i = 0;i < buckets;i++)
		list_init(&chtbl->table[i],destroy);
	return 0;
	
}

/*My version of chtbl_lookup */
inline int chtbl_lookup_ming(const CHTbl *chtbl,void **data)
{
	int bucket;
	Element ptr;
	bucket = chtbl->h(*data);
	
	ptr = chtbl->table[bucket].head;

	if (list_is_element(&chtbl->table[bucket],*data))
		return 0;
	else
		return 1;
}

int chtbl_lookup(const CHTbl *chtbl,void **data)
{
	int bucket = chtbl->h(*data);
	Element ptr;
	
	for (ptr = chtbl->table[bucket].head; ptr != NULL;ptr = list_next(ptr)) {
		/* match return 0 if sucess,-1 on faile */
		if (!chtbl->match(*data,ptr->data)) { 
			*data = list_data(ptr);
			return 0;
		}
	}
	
	return -1;
	
	
}

int chtbl_insert(CHTbl *chtbl,const void *data)
{
	void	*temp;
	int	bucket,
		retval;
	
	temp = (void*)data;
	if (chtbl_lookup(chtbl,&temp) == 0)
		return 1;
	bucket = chtbl->h(data);
	if ((retval = list_ins_next(&chtbl->table[bucket],NULL,data)) == 0 )
		chtbl->size++;
	return retval;
}
	
