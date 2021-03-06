/*** Generated by CAnnotate ***/ 
// COVERAGE CRITERIA : ABS AOR COR ROR MCC 
#include "coverage.h"
/*
** 2001 September 22
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** This is the implementation of generic hash-tables
** used in SQLite.
*/
#include "sqliteInt.h"
#include <assert.h>

/* Turn bulk memory into a hash table object by initializing the
** fields of the Hash structure.
**
** "pNew" is a pointer to the hash table that is to be initialized.
*/
void sqlite3HashInit(Hash *pNew){
  assert( pNew!=0 );
  pNew->first = 0;
  pNew->count = 0;
  pNew->htsize = 0;
  pNew->ht = 0;
}

/* Remove all entries from a hash table.  Reclaim all memory.
** Call this routine to delete a hash table or to reset a hash table
** to the empty state.
*/
void sqlite3HashClear(Hash *pH){
  HashElem *elem;         /* For looping over all elements of the table */

  assert( pH!=0 );
  elem = pH->first;
  pH->first = 0;
  sqlite3_free(pH->ht);
  pH->ht = 0;
  pH->htsize = 0;
  
// ABS Label 7
if(elem < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 7);
}
while( elem ){
    
// ABS Label 9
if(elem->next < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 9);
}
HashElem *next_elem = elem->next;
    sqlite3_free(elem);
    elem = next_elem;
  };
// ABS Label 8
if(elem < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 8);
}

  pH->count = 0;
}

/*
** The hashing function.
*/
static unsigned int strHash(const char *z){
  unsigned int h = 0;
  unsigned char c;
  while( (c = (unsigned char)*z++)!=0 ){     /*OPTIMIZATION-IF-TRUE*/
    /* Knuth multiplicative hashing.  (Sorting & Searching, p. 510).
    ** 0x9e3779b1 is 2654435761 which is the closest prime number to
    ** (2**32)*golden_ratio, where golden_ratio = (sqrt(5) - 1)/2. */
    h += sqlite3UpperToLower[c];
    h *= 0x9e3779b1;
  };
  
// ABS Label 10
if(h < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 10);
}
return h;
}


/* Link pNew element into the hash table pH.  If pEntry!=0 then also
** insert pNew into the pEntry hash bucket.
*/
static void insertElement(
  Hash *pH,              /* The complete hash table */
  struct _ht *pEntry,    /* The entry into which pNew is inserted */
  HashElem *pNew         /* The element to be inserted */
){
  HashElem *pHead;       /* First element already in pEntry */
  
// ABS Label 11
if(pEntry < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 11);
}
if( pEntry ){
    pHead = pEntry->count ? pEntry->chain : 0;
    pEntry->count++;
    pEntry->chain = pNew;
  }else{
    pHead = 0;
  }
  
// ABS Label 12
if(pHead < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 12);
}
if( pHead ){
    pNew->next = pHead;
    pNew->prev = pHead->prev;
    
// ABS Label 13
if(pHead->prev < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 13);
}
if( pHead->prev ){ pHead->prev->next = pNew; }
    else             { pH->first = pNew; }
    pHead->prev = pNew;
  }else{
    pNew->next = pH->first;
    
// ABS Label 14
if(pH->first < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 14);
}
if( pH->first ){ pH->first->prev = pNew; }
    pNew->prev = 0;
    pH->first = pNew;
  }
}


/* Resize the hash table so that it cantains "new_size" buckets.
**
** The hash table might fail to resize if sqlite3_malloc() fails or
** if the new size is the same as the prior size.
** Return TRUE if the resize occurs and false if not.
*/
static int rehash(Hash *pH, unsigned int new_size){
  struct _ht *new_ht;            /* The new hash table */
  HashElem *elem, *next_elem;    /* For looping over existing elements */

#if SQLITE_MALLOC_SOFT_LIMIT>0
  
// AOR Label 18
if(new_size - sizeof(struct _ht) != new_size * sizeof(struct _ht))  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 18);
}
// AOR Label 19
if(new_size + sizeof(struct _ht) != new_size * sizeof(struct _ht))  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 19);
}
// AOR Label 20
if(new_size / sizeof(struct _ht) != new_size * sizeof(struct _ht))  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 20);
}

// ROR Label 21
if((new_size * sizeof(struct _ht) <= 1024) != (new_size * sizeof(struct _ht) > 1024))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 21);
}
// ROR Label 22
if((new_size * sizeof(struct _ht) < 1024) != (new_size * sizeof(struct _ht) > 1024))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 22);
}
// ROR Label 23
if((new_size * sizeof(struct _ht) >= 1024) != (new_size * sizeof(struct _ht) > 1024))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 23);
}
if( new_size*sizeof(struct _ht)>SQLITE_MALLOC_SOFT_LIMIT ){
    new_size = SQLITE_MALLOC_SOFT_LIMIT/sizeof(struct _ht);
  }
  
// ABS Label 24
if(new_size < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 24);
}
// ABS Label 25
if(pH->htsize < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 25);
}

// ROR Label 26
if((new_size != pH->htsize) != (new_size == pH->htsize))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 26);
}
if( new_size==pH->htsize ) { return 0;
}
#endif

  /* The inability to allocates space for a larger hash table is
  ** a performance hit but it is not a fatal error.  So mark the
  ** allocation as a benign. Use sqlite3Malloc()/memset(0) instead of 
  ** sqlite3MallocZero() to make the allocation, as sqlite3MallocZero()
  ** only zeroes the requested number of bytes whereas this module will
  ** use the actual amount of space allocated for the hash table (which
  ** may be larger than the requested amount).
  */
  sqlite3BeginBenignMalloc();
  new_ht = (struct _ht *)sqlite3Malloc( new_size*sizeof(struct _ht) );
  sqlite3EndBenignMalloc();

  
// ABS Label 27
if(new_ht < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 27);
}

// ROR Label 28
if((new_ht != 0) != (new_ht == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 28);
}
if( new_ht==0 ) { return 0;
}
  sqlite3_free(pH->ht);
  pH->ht = new_ht;
  pH->htsize = new_size = sqlite3MallocSize(new_ht)/sizeof(struct _ht);
  
// AOR Label 15
if(new_size - sizeof(struct _ht) != new_size * sizeof(struct _ht))  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 15);
}
// AOR Label 16
if(new_size + sizeof(struct _ht) != new_size * sizeof(struct _ht))  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 16);
}
// AOR Label 17
if(new_size / sizeof(struct _ht) != new_size * sizeof(struct _ht))  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 17);
}
memset(new_ht, 0, new_size*sizeof(struct _ht));
  elem = pH->first , pH->first = 0;

// ABS Label 29
if(elem < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 29);
}
for(; elem; elem = next_elem){
    unsigned int h = strHash(elem->pKey) % new_size;
    next_elem = elem->next;
    
// ABS Label 31
if(pH < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 31);
}

// ABS Label 32
if(elem < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 32);
}
insertElement(pH, &new_ht[h], elem);
  };
// ABS Label 30
if(elem < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 30);
}

  return 1;
}

/* This function (for internal use only) locates an element in an
** hash table that matches the given key.  If no element is found,
** a pointer to a static null element with HashElem.data==0 is returned.
** If pH is not NULL, then the hash for this key is written to *pH.
*/
static HashElem *findElementWithHash(
  const Hash *pH,     /* The pH to be searched */
  const char *pKey,   /* The key we are searching for */
  unsigned int *pHash /* Write the hash value here */
){
  HashElem *elem;                /* Used to loop thru the element list */
  unsigned int count;            /* Number of elements left to test */
  unsigned int h;                /* The computed hash */
  static HashElem nullElement = { 0, 0, 0, 0 };

  
// ABS Label 33
if(pH->ht < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 33);
}
if( pH->ht ){   /*OPTIMIZATION-IF-TRUE*/
    struct _ht *pEntry;
    h = strHash(pKey) % pH->htsize;
    pEntry = &pH->ht[h];
    elem = pEntry->chain;
    count = pEntry->count;
  }else{
    h = 0;
    elem = pH->first;
    count = pH->count;
  }
  
// ABS Label 34
if(pHash < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 34);
}
if( pHash ) { *pHash = h;
}
  while( count-- ){
    assert( elem!=0 );
    if( sqlite3StrICmp(elem->pKey,pKey)==0 ){ 
      
// ABS Label 35
if(elem < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 35);
}
return elem;
    }
    elem = elem->next;
  };
  return &nullElement;
}

/* Remove a single entry from the hash table given a pointer to that
** element and a hash on the element's key.
*/
static void removeElementGivenHash(
  Hash *pH,         /* The pH containing "elem" */
  HashElem* elem,   /* The element to be removed from the pH */
  unsigned int h    /* Hash value for the element */
){
  struct _ht *pEntry;
  
// ABS Label 36
if(elem->prev < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 36);
}
if( elem->prev ){
    elem->prev->next = elem->next; 
  }else{
    pH->first = elem->next;
  }
  
// ABS Label 37
if(elem->next < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 37);
}
if( elem->next ){
    elem->next->prev = elem->prev;
  }
  
// ABS Label 38
if(pH->ht < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 38);
}
if( pH->ht ){
    pEntry = &pH->ht[h];
    
// ABS Label 39
if(elem < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 39);
}
// ABS Label 40
if(pEntry->chain < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 40);
}

// ROR Label 41
if((pEntry->chain != elem) != (pEntry->chain == elem))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 41);
}
if( pEntry->chain==elem ){
      pEntry->chain = elem->next;
    }
    assert( pEntry->count>0 );
    pEntry->count--;
  }
  sqlite3_free( elem );
  pH->count--;
  
// ABS Label 42
if(pH->count < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 42);
}

// ROR Label 43
if((pH->count != 0) != (pH->count == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 43);
}
if( pH->count==0 ){
    assert( pH->first==0 );
    assert( pH->count==0 );
    
// ABS Label 44
if(pH < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 44);
}
sqlite3HashClear(pH);
  }
}

/* Attempt to locate an element of the hash table pH with a key
** that matches pKey.  Return the data for this element if it is
** found, or NULL if there is no match.
*/
void *sqlite3HashFind(const Hash *pH, const char *pKey){
  assert( pH!=0 );
  assert( pKey!=0 );
  return findElementWithHash(pH, pKey, 0)->data;
}

/* Insert an element into the hash table pH.  The key is pKey
** and the data is "data".
**
** If no element exists with a matching key, then a new
** element is created and NULL is returned.
**
** If another element already exists with the same key, then the
** new data replaces the old data and the old data is returned.
** The key is not copied in this instance.  If a malloc fails, then
** the new data is returned and the hash table is unchanged.
**
** If the "data" parameter to this function is NULL, then the
** element corresponding to "key" is removed from the hash table.
*/
void *sqlite3HashInsert(Hash *pH, const char *pKey, void *data){
  unsigned int h;       /* the hash of the key modulo hash table size */
  HashElem *elem;       /* Used to loop thru the element list */
  HashElem *new_elem;   /* New element added to the pH */

  assert( pH!=0 );
  assert( pKey!=0 );
  elem = findElementWithHash(pH,pKey,&h);
  
// ABS Label 47
if(elem->data < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 47);
}
if( elem->data ){
    
// ABS Label 48
if(elem->data < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 48);
}
void *old_data = elem->data;
    
// ABS Label 49
if(data < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 49);
}

// ROR Label 50
if((data != 0) != (data == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 50);
}
if( data==0 ){
      
// ABS Label 51
if(pH < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 51);
}

// ABS Label 52
if(elem < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 52);
}

// ABS Label 53
if(h < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 53);
}
removeElementGivenHash(pH,elem,h);
    }else{
      elem->data = data;
      elem->pKey = pKey;
    }
    
// ABS Label 54
if(old_data < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 54);
}
return old_data;
  }
  
// ABS Label 55
if(data < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 55);
}

// ROR Label 56
if((data != 0) != (data == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 56);
}
if( data==0 ) { return 0;
}
  new_elem = (HashElem*)sqlite3Malloc( sizeof(HashElem) );
  
// ABS Label 57
if(new_elem < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 57);
}

// ROR Label 58
if((new_elem != 0) != (new_elem == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 58);
}
if( new_elem==0 ) { 
// ABS Label 59
if(data < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 59);
}
return data;
}
  new_elem->pKey = pKey;
  new_elem->data = data;
  pH->count++;
  
// ABS Label 60
if(pH->count < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 60);
}
// ABS Label 61
if(pH->htsize < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 61);
}

// AOR Label 62
if(2 - pH->htsize != 2 * pH->htsize)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 62);
}
// AOR Label 63
if(2 + pH->htsize != 2 * pH->htsize)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 63);
}
// AOR Label 64
if(2 / pH->htsize != 2 * pH->htsize)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 64);
}

// COR Label 65
if((pH->count >= 10 || pH->count > 2 * pH->htsize) != (pH->count >= 10 && pH->count > 2 * pH->htsize))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 65);
}

// ROR Label 66
if((pH->count < 10) != (pH->count >= 10))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 66);
}
// ROR Label 67
if((pH->count > 10) != (pH->count >= 10))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 67);
}
// ROR Label 68
if((pH->count <= 10) != (pH->count >= 10))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 68);
}
// ROR Label 69
if((pH->count <= 2 * pH->htsize) != (pH->count > 2 * pH->htsize))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 69);
}
// ROR Label 70
if((pH->count < 2 * pH->htsize) != (pH->count > 2 * pH->htsize))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 70);
}
// ROR Label 71
if((pH->count >= 2 * pH->htsize) != (pH->count > 2 * pH->htsize))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 71);
}

// MCC Label 72
if(pH->count >= 10 && pH->count > 2 * pH->htsize ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 72);
}
// MCC Label 73
if(pH->count >= 10 && !(pH->count > 2 * pH->htsize) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 73);
}
// MCC Label 74
if(!(pH->count >= 10) && pH->count > 2 * pH->htsize ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 74);
}
// MCC Label 75
if(!(pH->count >= 10) && !(pH->count > 2 * pH->htsize) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 75);
}
if( pH->count>=10 && pH->count > 2*pH->htsize ){
    if( rehash(pH, pH->count*2) ){
      assert( pH->htsize>0 );
      h = strHash(pKey) % pH->htsize;
    }
  }
  
// ABS Label 45
if(pH < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 45);
}

// ABS Label 46
if(new_elem < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 46);
}
insertElement(pH, pH->ht ? &pH->ht[h] : 0, new_elem);
  return 0;
}
