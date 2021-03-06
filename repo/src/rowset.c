/*** Generated by CAnnotate ***/ 
// COVERAGE CRITERIA : ABS AOR COR ROR MCC 
#include "coverage.h"
/*
** 2008 December 3
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
**
** This module implements an object we call a "RowSet".
**
** The RowSet object is a collection of rowids.  Rowids
** are inserted into the RowSet in an arbitrary order.  Inserts
** can be intermixed with tests to see if a given rowid has been
** previously inserted into the RowSet.
**
** After all inserts are finished, it is possible to extract the
** elements of the RowSet in sorted order.  Once this extraction
** process has started, no new elements may be inserted.
**
** Hence, the primitive operations for a RowSet are:
**
**    CREATE
**    INSERT
**    TEST
**    SMALLEST
**    DESTROY
**
** The CREATE and DESTROY primitives are the constructor and destructor,
** obviously.  The INSERT primitive adds a new element to the RowSet.
** TEST checks to see if an element is already in the RowSet.  SMALLEST
** extracts the least value from the RowSet.
**
** The INSERT primitive might allocate additional memory.  Memory is
** allocated in chunks so most INSERTs do no allocation.  There is an 
** upper bound on the size of allocated memory.  No memory is freed
** until DESTROY.
**
** The TEST primitive includes a "batch" number.  The TEST primitive
** will only see elements that were inserted before the last change
** in the batch number.  In other words, if an INSERT occurs between
** two TESTs where the TESTs have the same batch nubmer, then the
** value added by the INSERT will not be visible to the second TEST.
** The initial batch number is zero, so if the very first TEST contains
** a non-zero batch number, it will see all prior INSERTs.
**
** No INSERTs may occurs after a SMALLEST.  An assertion will fail if
** that is attempted.
**
** The cost of an INSERT is roughly constant.  (Sometimes new memory
** has to be allocated on an INSERT.)  The cost of a TEST with a new
** batch number is O(NlogN) where N is the number of elements in the RowSet.
** The cost of a TEST using the same batch number is O(logN).  The cost
** of the first SMALLEST is O(NlogN).  Second and subsequent SMALLEST
** primitives are constant time.  The cost of DESTROY is O(N).
**
** TEST and SMALLEST may not be used by the same RowSet.  This used to
** be possible, but the feature was not used, so it was removed in order
** to simplify the code.
*/
#include "sqliteInt.h"


/*
** Target size for allocation chunks.
*/
#define ROWSET_ALLOCATION_SIZE 1024

/*
** The number of rowset entries per allocation chunk.
*/
#define ROWSET_ENTRY_PER_CHUNK  \
                       ((ROWSET_ALLOCATION_SIZE-8)/sizeof(struct RowSetEntry))

/*
** Each entry in a RowSet is an instance of the following object.
**
** This same object is reused to store a linked list of trees of RowSetEntry
** objects.  In that alternative use, pRight points to the next entry
** in the list, pLeft points to the tree, and v is unused.  The
** RowSet.pForest value points to the head of this forest list.
*/
struct RowSetEntry {            
  i64 v;                        /* ROWID value for this entry */
  struct RowSetEntry *pRight;   /* Right subtree (larger entries) or list */
  struct RowSetEntry *pLeft;    /* Left subtree (smaller entries) */
};

/*
** RowSetEntry objects are allocated in large chunks (instances of the
** following structure) to reduce memory allocation overhead.  The
** chunks are kept on a linked list so that they can be deallocated
** when the RowSet is destroyed.
*/
struct RowSetChunk {
  struct RowSetChunk *pNextChunk;        /* Next chunk on list of them all */
  struct RowSetEntry aEntry[ROWSET_ENTRY_PER_CHUNK]; /* Allocated entries */
};

/*
** A RowSet in an instance of the following structure.
**
** A typedef of this structure if found in sqliteInt.h.
*/
struct RowSet {
  struct RowSetChunk *pChunk;    /* List of all chunk allocations */
  sqlite3 *db;                   /* The database connection */
  struct RowSetEntry *pEntry;    /* List of entries using pRight */
  struct RowSetEntry *pLast;     /* Last entry on the pEntry list */
  struct RowSetEntry *pFresh;    /* Source of new entry objects */
  struct RowSetEntry *pForest;   /* List of binary trees of entries */
  u16 nFresh;                    /* Number of objects on pFresh */
  u16 rsFlags;                   /* Various flags */
  int iBatch;                    /* Current insert batch */
};

/*
** Allowed values for RowSet.rsFlags
*/
#define ROWSET_SORTED  0x01   /* True if RowSet.pEntry is sorted */
#define ROWSET_NEXT    0x02   /* True if sqlite3RowSetNext() has been called */

/*
** Allocate a RowSet object.  Return NULL if a memory allocation
** error occurs.
*/
RowSet *sqlite3RowSetInit(sqlite3 *db){
  RowSet *p = sqlite3DbMallocRawNN(db, sizeof(*p));
  
// ABS Label 7
if(p < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 7);
}
if( p ){
    int N = sqlite3DbMallocSize(db, p);
    p->pChunk = 0;
    p->db = db;
    p->pEntry = 0;
    p->pLast = 0;
    p->pForest = 0;
    p->pFresh = (struct RowSetEntry*)(ROUND8(sizeof(*p)) + (char*)p);
    p->nFresh = (u16)((N - ROUND8(sizeof(*p)))/sizeof(struct RowSetEntry));
    p->rsFlags = ROWSET_SORTED;
    p->iBatch = 0;
  }
  
// ABS Label 8
if(p < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 8);
}
return p;
}

/*
** Deallocate all chunks from a RowSet.  This frees all memory that
** the RowSet has allocated over its lifetime.  This routine is
** the destructor for the RowSet.
*/
void sqlite3RowSetClear(void *pArg){
  RowSet *p = (RowSet*)pArg;
  struct RowSetChunk *pChunk, *pNextChunk;
  pChunk = p->pChunk;

// ABS Label 9
if(pChunk < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 9);
}
for(; pChunk; pChunk = pNextChunk){
    pNextChunk = pChunk->pNextChunk;
    
// ABS Label 11
if(p->db < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 11);
}
sqlite3DbFree(p->db, pChunk);
  };
// ABS Label 10
if(pChunk < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 10);
}

  p->pChunk = 0;
  p->nFresh = 0;
  p->pEntry = 0;
  p->pLast = 0;
  p->pForest = 0;
  p->rsFlags = ROWSET_SORTED;
}

/*
** Deallocate all chunks from a RowSet.  This frees all memory that
** the RowSet has allocated over its lifetime.  This routine is
** the destructor for the RowSet.
*/
void sqlite3RowSetDelete(void *pArg){
  
// ABS Label 12
if(pArg < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 12);
}
sqlite3RowSetClear(pArg);
  
// ABS Label 13
if(((RowSet *)pArg)->db < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 13);
}

// ABS Label 14
if(pArg < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 14);
}
sqlite3DbFree(((RowSet*)pArg)->db, pArg);
}

/*
** Allocate a new RowSetEntry object that is associated with the
** given RowSet.  Return a pointer to the new and completely uninitialized
** object.
**
** In an OOM situation, the RowSet.db->mallocFailed flag is set and this
** routine returns NULL.
*/
static struct RowSetEntry *rowSetEntryAlloc(RowSet *p){
  assert( p!=0 );
  
// ROR Label 15
if((p->nFresh != 0) != (p->nFresh == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 15);
}
if( p->nFresh==0 ){  /*OPTIMIZATION-IF-FALSE*/
    /* We could allocate a fresh RowSetEntry each time one is needed, but it
    ** is more efficient to pull a preallocated entry from the pool */
    struct RowSetChunk *pNew;
    pNew = sqlite3DbMallocRawNN(p->db, sizeof(*pNew));
    
// ABS Label 16
if(pNew < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 16);
}

// ROR Label 17
if((pNew != 0) != (pNew == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 17);
}
if( pNew==0 ){
      return 0;
    }
    pNew->pNextChunk = p->pChunk;
    p->pChunk = pNew;
    p->pFresh = pNew->aEntry;
    p->nFresh = ROWSET_ENTRY_PER_CHUNK;
  }
  p->nFresh--;
  return p->pFresh++;
}

/*
** Insert a new value into a RowSet.
**
** The mallocFailed flag of the database connection is set if a
** memory allocation fails.
*/
void sqlite3RowSetInsert(RowSet *p, i64 rowid){
  struct RowSetEntry *pEntry;  /* The new entry */
  struct RowSetEntry *pLast;   /* The last prior entry */

  /* This routine is never called after sqlite3RowSetNext() */
  assert( p!=0 && (p->rsFlags & ROWSET_NEXT)==0 );

  pEntry = rowSetEntryAlloc(p);
  
// ABS Label 18
if(pEntry < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 18);
}

// ROR Label 19
if((pEntry != 0) != (pEntry == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 19);
}
if( pEntry==0 ) { return;
}
  pEntry->v = rowid;
  pEntry->pRight = 0;
  pLast = p->pLast;
  
// ABS Label 20
if(pLast < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 20);
}
if( pLast ){
    
// ABS Label 21
if(pLast->v < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 21);
}
// ABS Label 22
if(rowid < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 22);
}

// ROR Label 23
if((rowid < pLast->v) != (rowid <= pLast->v))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 23);
}
// ROR Label 24
if((rowid > pLast->v) != (rowid <= pLast->v))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 24);
}
// ROR Label 25
if((rowid >= pLast->v) != (rowid <= pLast->v))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 25);
}
if( rowid<=pLast->v ){  /*OPTIMIZATION-IF-FALSE*/
      /* Avoid unnecessary sorts by preserving the ROWSET_SORTED flags
      ** where possible */
      p->rsFlags &= ~ROWSET_SORTED;
    }
    pLast->pRight = pEntry;
  }else{
    p->pEntry = pEntry;
  }
  p->pLast = pEntry;
}

/*
** Merge two lists of RowSetEntry objects.  Remove duplicates.
**
** The input lists are connected via pRight pointers and are 
** assumed to each already be in sorted order.
*/
static struct RowSetEntry *rowSetEntryMerge(
  struct RowSetEntry *pA,    /* First sorted list to be merged */
  struct RowSetEntry *pB     /* Second sorted list to be merged */
){
  struct RowSetEntry head;
  struct RowSetEntry *pTail;

  pTail = &head;
  assert( pA!=0 && pB!=0 );
  for(;;){
    assert( pA->pRight==0 || pA->v<=pA->pRight->v );
    assert( pB->pRight==0 || pB->v<=pB->pRight->v );
    
// ABS Label 26
if(pA->v < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 26);
}
// ABS Label 27
if(pB->v < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 27);
}

// ROR Label 28
if((pA->v < pB->v) != (pA->v <= pB->v))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 28);
}
// ROR Label 29
if((pA->v > pB->v) != (pA->v <= pB->v))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 29);
}
// ROR Label 30
if((pA->v >= pB->v) != (pA->v <= pB->v))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 30);
}
if( pA->v<=pB->v ){
      
// ABS Label 31
if(pA->v < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 31);
}
// ABS Label 32
if(pB->v < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 32);
}

// ROR Label 33
if((pA->v <= pB->v) != (pA->v < pB->v))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 33);
}
// ROR Label 34
if((pA->v > pB->v) != (pA->v < pB->v))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 34);
}
// ROR Label 35
if((pA->v >= pB->v) != (pA->v < pB->v))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 35);
}
if( pA->v<pB->v ) { pTail = pTail->pRight = pA;
}
      pA = pA->pRight;
      
// ABS Label 36
if(pA < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 36);
}

// ROR Label 37
if((pA != 0) != (pA == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 37);
}
if( pA==0 ){
        pTail->pRight = pB;
        break;
      }
    }else{
      pTail = pTail->pRight = pB;
      pB = pB->pRight;
      
// ABS Label 38
if(pB < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 38);
}

// ROR Label 39
if((pB != 0) != (pB == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 39);
}
if( pB==0 ){
        pTail->pRight = pA;
        break;
      }
    }
  };
  
// ABS Label 40
if(head.pRight < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 40);
}
return head.pRight;
}

/*
** Sort all elements on the list of RowSetEntry objects into order of
** increasing v.
*/ 
static struct RowSetEntry *rowSetEntrySort(struct RowSetEntry *pIn){
  unsigned int i;
  struct RowSetEntry *pNext, *aBucket[40];

  memset(aBucket, 0, sizeof(aBucket));
  
// ABS Label 41
if(pIn < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 41);
}
while( pIn ){
    pNext = pIn->pRight;
    pIn->pRight = 0;
    i = 0;

// ABS Label 43
if(aBucket[i] < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 43);
}
// ABS Label 44
if(i < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 44);
}
for(; aBucket[i]; i++){
      pIn = rowSetEntryMerge(aBucket[i], pIn);
      aBucket[i] = 0;
    };
// ABS Label 45
if(aBucket[i] < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 45);
}
// ABS Label 46
if(i < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 46);
}

    aBucket[i] = pIn;
    pIn = pNext;
  };
// ABS Label 42
if(pIn < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 42);
}

  pIn = aBucket[0];
  i = 1;

// AOR Label 47
if(sizeof (aBucket) - sizeof (aBucket[0]) != sizeof (aBucket) / sizeof (aBucket[0]))  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 47);
}
// AOR Label 48
if(sizeof (aBucket) + sizeof (aBucket[0]) != sizeof (aBucket) / sizeof (aBucket[0]))  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 48);
}
// AOR Label 49
if(sizeof (aBucket) * sizeof (aBucket[0]) != sizeof (aBucket) / sizeof (aBucket[0]))  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 49);
}

// ROR Label 50
if((i <= sizeof (aBucket) / sizeof (aBucket[0])) != (i < sizeof (aBucket) / sizeof (aBucket[0])))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 50);
}
// ROR Label 51
if((i > sizeof (aBucket) / sizeof (aBucket[0])) != (i < sizeof (aBucket) / sizeof (aBucket[0])))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 51);
}
// ROR Label 52
if((i >= sizeof (aBucket) / sizeof (aBucket[0])) != (i < sizeof (aBucket) / sizeof (aBucket[0])))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 52);
}
for(; i<sizeof(aBucket)/sizeof(aBucket[0]); i++){
    
// ABS Label 59
if(aBucket[i] < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 59);
}
// ABS Label 60
if(i < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 60);
}

// ROR Label 61
if((aBucket[i] != 0) != (aBucket[i] == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 61);
}
if( aBucket[i]==0 ) { continue;
}
    pIn = pIn ? rowSetEntryMerge(pIn, aBucket[i]) : aBucket[i];
  };
// AOR Label 53
if(sizeof (aBucket) - sizeof (aBucket[0]) != sizeof (aBucket) / sizeof (aBucket[0]))  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 53);
}
// AOR Label 54
if(sizeof (aBucket) + sizeof (aBucket[0]) != sizeof (aBucket) / sizeof (aBucket[0]))  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 54);
}
// AOR Label 55
if(sizeof (aBucket) * sizeof (aBucket[0]) != sizeof (aBucket) / sizeof (aBucket[0]))  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 55);
}

// ROR Label 56
if((i <= sizeof (aBucket) / sizeof (aBucket[0])) != (i < sizeof (aBucket) / sizeof (aBucket[0])))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 56);
}
// ROR Label 57
if((i > sizeof (aBucket) / sizeof (aBucket[0])) != (i < sizeof (aBucket) / sizeof (aBucket[0])))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 57);
}
// ROR Label 58
if((i >= sizeof (aBucket) / sizeof (aBucket[0])) != (i < sizeof (aBucket) / sizeof (aBucket[0])))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 58);
}

  
// ABS Label 62
if(pIn < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 62);
}
return pIn;
}


/*
** The input, pIn, is a binary tree (or subtree) of RowSetEntry objects.
** Convert this tree into a linked list connected by the pRight pointers
** and return pointers to the first and last elements of the new list.
*/
static void rowSetTreeToList(
  struct RowSetEntry *pIn,         /* Root of the input tree */
  struct RowSetEntry **ppFirst,    /* Write head of the output list here */
  struct RowSetEntry **ppLast      /* Write tail of the output list here */
){
  assert( pIn!=0 );
  
// ABS Label 63
if(pIn->pLeft < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 63);
}
if( pIn->pLeft ){
    struct RowSetEntry *p;
    
// ABS Label 64
if(pIn->pLeft < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 64);
}

// ABS Label 65
if(ppFirst < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 65);
}
rowSetTreeToList(pIn->pLeft, ppFirst, &p);
    p->pRight = pIn;
  }else{
    *ppFirst = pIn;
  }
  
// ABS Label 66
if(pIn->pRight < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 66);
}
if( pIn->pRight ){
    
// ABS Label 67
if(pIn->pRight < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 67);
}

// ABS Label 68
if(ppLast < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 68);
}
rowSetTreeToList(pIn->pRight, &pIn->pRight, ppLast);
  }else{
    *ppLast = pIn;
  }
  assert( (*ppLast)->pRight==0 );
}


/*
** Convert a sorted list of elements (connected by pRight) into a binary
** tree with depth of iDepth.  A depth of 1 means the tree contains a single
** node taken from the head of *ppList.  A depth of 2 means a tree with
** three nodes.  And so forth.
**
** Use as many entries from the input list as required and update the
** *ppList to point to the unused elements of the list.  If the input
** list contains too few elements, then construct an incomplete tree
** and leave *ppList set to NULL.
**
** Return a pointer to the root of the constructed binary tree.
*/
static struct RowSetEntry *rowSetNDeepTree(
  struct RowSetEntry **ppList,
  int iDepth
){
  struct RowSetEntry *p;         /* Root of the new tree */
  struct RowSetEntry *pLeft;     /* Left subtree */
  
// ABS Label 69
if(*ppList < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 69);
}

// ROR Label 70
if((*ppList != 0) != (*ppList == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 70);
}
if( *ppList==0 ){ /*OPTIMIZATION-IF-TRUE*/
    /* Prevent unnecessary deep recursion when we run out of entries */
    return 0; 
  }
  
// ABS Label 71
if(iDepth < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 71);
}

// ROR Label 72
if((iDepth <= 1) != (iDepth > 1))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 72);
}
// ROR Label 73
if((iDepth < 1) != (iDepth > 1))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 73);
}
// ROR Label 74
if((iDepth >= 1) != (iDepth > 1))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 74);
}
if( iDepth>1 ){   /*OPTIMIZATION-IF-TRUE*/
    /* This branch causes a *balanced* tree to be generated.  A valid tree
    ** is still generated without this branch, but the tree is wildly
    ** unbalanced and inefficient. */
    pLeft = rowSetNDeepTree(ppList, iDepth-1);
    p = *ppList;
    
// ABS Label 75
if(p < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 75);
}

// ROR Label 76
if((p != 0) != (p == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 76);
}
if( p==0 ){     /*OPTIMIZATION-IF-FALSE*/
      /* It is safe to always return here, but the resulting tree
      ** would be unbalanced */
      
// ABS Label 77
if(pLeft < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 77);
}
return pLeft;
    }
    p->pLeft = pLeft;
    *ppList = p->pRight;
    p->pRight = rowSetNDeepTree(ppList, iDepth-1);
  }else{
    p = *ppList;
    *ppList = p->pRight;
    p->pLeft = p->pRight = 0;
  }
  
// ABS Label 78
if(p < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 78);
}
return p;
}

/*
** Convert a sorted list of elements into a binary tree. Make the tree
** as deep as it needs to be in order to contain the entire list.
*/
static struct RowSetEntry *rowSetListToTree(struct RowSetEntry *pList){
  int iDepth;           /* Depth of the tree so far */
  struct RowSetEntry *p;       /* Current tree root */
  struct RowSetEntry *pLeft;   /* Left subtree */

  assert( pList!=0 );
  p = pList;
  pList = p->pRight;
  p->pLeft = p->pRight = 0;
  iDepth = 1;

// ABS Label 79
if(pList < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 79);
}
for(; pList; iDepth++){
    pLeft = p;
    p = pList;
    pList = p->pRight;
    p->pLeft = pLeft;
    p->pRight = rowSetNDeepTree(&pList, iDepth);
  };
// ABS Label 80
if(pList < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 80);
}

  
// ABS Label 81
if(p < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 81);
}
return p;
}

/*
** Extract the smallest element from the RowSet.
** Write the element into *pRowid.  Return 1 on success.  Return
** 0 if the RowSet is already empty.
**
** After this routine has been called, the sqlite3RowSetInsert()
** routine may not be called again.
**
** This routine may not be called after sqlite3RowSetTest() has
** been used.  Older versions of RowSet allowed that, but as the
** capability was not used by the code generator, it was removed
** for code economy.
*/
int sqlite3RowSetNext(RowSet *p, i64 *pRowid){
  assert( p!=0 );
  assert( p->pForest==0 );  /* Cannot be used with sqlite3RowSetText() */

  /* Merge the forest into a single sorted list on first call */
  
// ROR Label 82
if(((p->rsFlags & 2) != 0) != ((p->rsFlags & 2) == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 82);
}
if( (p->rsFlags & ROWSET_NEXT)==0 ){  /*OPTIMIZATION-IF-FALSE*/
    
// ROR Label 83
if(((p->rsFlags & 1) != 0) != ((p->rsFlags & 1) == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 83);
}
if( (p->rsFlags & ROWSET_SORTED)==0 ){  /*OPTIMIZATION-IF-FALSE*/
      p->pEntry = rowSetEntrySort(p->pEntry);
    }
    p->rsFlags |= ROWSET_SORTED|ROWSET_NEXT;
  }

  /* Return the next entry on the list */
  
// ABS Label 84
if(p->pEntry < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 84);
}
if( p->pEntry ){
    *pRowid = p->pEntry->v;
    p->pEntry = p->pEntry->pRight;
    
// ABS Label 85
if(p->pEntry < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 85);
}

// ROR Label 86
if((p->pEntry != 0) != (p->pEntry == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 86);
}
if( p->pEntry==0 ){ /*OPTIMIZATION-IF-TRUE*/
      /* Free memory immediately, rather than waiting on sqlite3_finalize() */
      sqlite3RowSetClear(p);
    }
    return 1;
  }else{
    return 0;
  }
}

/*
** Check to see if element iRowid was inserted into the rowset as
** part of any insert batch prior to iBatch.  Return 1 or 0.
**
** If this is the first test of a new batch and if there exist entries
** on pRowSet->pEntry, then sort those entries into the forest at
** pRowSet->pForest so that they can be tested.
*/
int sqlite3RowSetTest(RowSet *pRowSet, int iBatch, sqlite3_int64 iRowid){
  struct RowSetEntry *p, *pTree;

  /* This routine is never called after sqlite3RowSetNext() */
  assert( pRowSet!=0 && (pRowSet->rsFlags & ROWSET_NEXT)==0 );

  /* Sort entries into the forest on the first test of a new batch.
  ** To save unnecessary work, only do this when the batch number changes.
  */
  
// ABS Label 87
if(iBatch < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 87);
}
// ABS Label 88
if(pRowSet->iBatch < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 88);
}

// ROR Label 89
if((iBatch == pRowSet->iBatch) != (iBatch != pRowSet->iBatch))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 89);
}
if( iBatch!=pRowSet->iBatch ){  /*OPTIMIZATION-IF-FALSE*/
    p = pRowSet->pEntry;
    
// ABS Label 90
if(p < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 90);
}
if( p ){
      struct RowSetEntry **ppPrevTree = &pRowSet->pForest;
      
// ROR Label 91
if(((pRowSet->rsFlags & 1) != 0) != ((pRowSet->rsFlags & 1) == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 91);
}
if( (pRowSet->rsFlags & ROWSET_SORTED)==0 ){ /*OPTIMIZATION-IF-FALSE*/
        /* Only sort the current set of entries if they need it */
        p = rowSetEntrySort(p);
      }
      pTree = pRowSet->pForest;

// ABS Label 92
if(pTree < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 92);
}
for(; pTree; pTree=pTree->pRight){
        ppPrevTree = &pTree->pRight;
        
// ABS Label 94
if(pTree->pLeft < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 94);
}

// ROR Label 95
if((pTree->pLeft != 0) != (pTree->pLeft == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 95);
}
if( pTree->pLeft==0 ){
          pTree->pLeft = rowSetListToTree(p);
          break;
        }else{
          struct RowSetEntry *pAux, *pTail;
          
// ABS Label 96
if(pTree->pLeft < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 96);
}
rowSetTreeToList(pTree->pLeft, &pAux, &pTail);
          pTree->pLeft = 0;
          p = rowSetEntryMerge(pAux, p);
        }
      };
// ABS Label 93
if(pTree < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 93);
}

      
// ABS Label 97
if(pTree < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 97);
}

// ROR Label 98
if((pTree != 0) != (pTree == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 98);
}
if( pTree==0 ){
        *ppPrevTree = pTree = rowSetEntryAlloc(pRowSet);
        
// ABS Label 99
if(pTree < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 99);
}
if( pTree ){
          pTree->v = 0;
          pTree->pRight = 0;
          pTree->pLeft = rowSetListToTree(p);
        }
      }
      pRowSet->pEntry = 0;
      pRowSet->pLast = 0;
      pRowSet->rsFlags |= ROWSET_SORTED;
    }
    pRowSet->iBatch = iBatch;
  }

  /* Test to see if the iRowid value appears anywhere in the forest.
  ** Return 1 if it does and 0 if not.
  */
  pTree = pRowSet->pForest;

// ABS Label 100
if(pTree < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 100);
}
for(; pTree; pTree=pTree->pRight){
    p = pTree->pLeft;
    
// ABS Label 102
if(p < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 102);
}
while( p ){
      
// ABS Label 104
if(iRowid < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 104);
}
// ABS Label 105
if(p->v < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 105);
}

// ROR Label 106
if((p->v <= iRowid) != (p->v < iRowid))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 106);
}
// ROR Label 107
if((p->v > iRowid) != (p->v < iRowid))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 107);
}
// ROR Label 108
if((p->v >= iRowid) != (p->v < iRowid))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 108);
}
if( p->v<iRowid ){
        p = p->pRight;
      }else { 
// ABS Label 109
if(iRowid < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 109);
}
// ABS Label 110
if(p->v < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 110);
}

// ROR Label 111
if((p->v <= iRowid) != (p->v > iRowid))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 111);
}
// ROR Label 112
if((p->v < iRowid) != (p->v > iRowid))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 112);
}
// ROR Label 113
if((p->v >= iRowid) != (p->v > iRowid))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 113);
}
if( p->v>iRowid ){
        p = p->pLeft;
      }else{
        return 1;
      };}

    };
// ABS Label 103
if(p < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 103);
}

  };
// ABS Label 101
if(pTree < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 101);
}

  return 0;
}
