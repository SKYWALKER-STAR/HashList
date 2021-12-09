#include "list.h"
#include "chtbl.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int match(const void *key1,const void *key2)
{
	int *data1,*data2;
	
	data1 = (int*)key1;
	data2 = (int*)key2;
	
	if (memcmp(data1,data2,sizeof(int)))
		return -1;
	
	return 0;
}

int main()
{
	int rv;
	int q = 21;
	int *resdata = &q;
	int data = 21;
	CHTbl hashtable;
	
	rv = chtbl_init(&hashtable,120,hashpjw,match,NULL);
	rv = chtbl_insert(&hashtable,&data);
	
	rv = chtbl_lookup(&hashtable,(void**)&resdata);
	printf("%d\n",rv);
	return rv;
}
