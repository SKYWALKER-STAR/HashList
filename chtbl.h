#ifndef CHTBL_H
#define CHTBL_H
#define PRIME_TBLSIZE 100

typedef struct chtbl {
	int 	buckets;
	unsigned int 	(*h)(const void *key);
	int 	(*match)(const void *key1,const void *key2);
	void	(*destroy)(void *data);
	int 	size;
	List	table;
}CHTbl;

unsigned int hashpjw(const void *key);
int chtbl_init(CHTbl *chtbl,int buckets,unsigned int (*h)(const void *key),
		int (*match)(const void *key1,const void *key2),
		void (*destroy)(void *data));
int chtbl_insert(CHTbl *chtbl,const void *data);
int chtbl_lookup(const CHTbl *chtbl,void **data);
#endif
