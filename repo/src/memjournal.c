/*** Generated by CAnnotate ***/ 
// COVERAGE CRITERIA : ABS AOR COR ROR MCC 
#include "coverage.h"
/*
** 2008 October 7
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
** This file contains code use to implement an in-memory rollback journal.
** The in-memory rollback journal is used to journal transactions for
** ":memory:" databases and when the journal_mode=MEMORY pragma is used.
**
** Update:  The in-memory journal is also used to temporarily cache
** smaller journals that are not critical for power-loss recovery.
** For example, statement journals that are not too big will be held
** entirely in memory, thus reducing the number of file I/O calls, and
** more importantly, reducing temporary file creation events.  If these
** journals become too large for memory, they are spilled to disk.  But
** in the common case, they are usually small and no file I/O needs to
** occur.
*/
#include "sqliteInt.h"

/* Forward references to internal structures */
typedef struct MemJournal MemJournal;
typedef struct FilePoint FilePoint;
typedef struct FileChunk FileChunk;

/*
** The rollback journal is composed of a linked list of these structures.
**
** The zChunk array is always at least 8 bytes in size - usually much more.
** Its actual size is stored in the MemJournal.nChunkSize variable.
*/
struct FileChunk {
  FileChunk *pNext;               /* Next chunk in the journal */
  u8 zChunk[8];                   /* Content of this chunk */
};

/*
** By default, allocate this many bytes of memory for each FileChunk object.
*/
#define MEMJOURNAL_DFLT_FILECHUNKSIZE 1024

/*
** For chunk size nChunkSize, return the number of bytes that should
** be allocated for each FileChunk structure.
*/
#define fileChunkSize(nChunkSize) (sizeof(FileChunk) + ((nChunkSize)-8))

/*
** An instance of this object serves as a cursor into the rollback journal.
** The cursor can be either for reading or writing.
*/
struct FilePoint {
  sqlite3_int64 iOffset;          /* Offset from the beginning of the file */
  FileChunk *pChunk;              /* Specific chunk into which cursor points */
};

/*
** This structure is a subclass of sqlite3_file. Each open memory-journal
** is an instance of this class.
*/
struct MemJournal {
  const sqlite3_io_methods *pMethod; /* Parent class. MUST BE FIRST */
  int nChunkSize;                 /* In-memory chunk-size */

  int nSpill;                     /* Bytes of data before flushing */
  FileChunk *pFirst;              /* Head of in-memory chunk-list */
  FilePoint endpoint;             /* Pointer to the end of the file */
  FilePoint readpoint;            /* Pointer to the end of the last xRead() */

  int flags;                      /* xOpen flags */
  sqlite3_vfs *pVfs;              /* The "real" underlying VFS */
  const char *zJournal;           /* Name of the journal file */
};

/*
** Read data from the in-memory journal file.  This is the implementation
** of the sqlite3_vfs.xRead method.
*/
static int memjrnlRead(
  sqlite3_file *pJfd,    /* The journal file from which to read */
  void *zBuf,            /* Put the results here */
  int iAmt,              /* Number of bytes to read */
  sqlite_int64 iOfst     /* Begin reading at this offset */
){
  MemJournal *p = (MemJournal *)pJfd;
  u8 *zOut = zBuf;
  
// ABS Label 7
if(iAmt < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 7);
}
int nRead = iAmt;
  int iChunkOffset;
  FileChunk *pChunk;

  
// ABS Label 8
if(p->endpoint.iOffset < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 8);
}

// ROR Label 9
if(((iAmt + iOfst) <= p->endpoint.iOffset) != ((iAmt + iOfst) > p->endpoint.iOffset))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 9);
}
// ROR Label 10
if(((iAmt + iOfst) < p->endpoint.iOffset) != ((iAmt + iOfst) > p->endpoint.iOffset))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 10);
}
// ROR Label 11
if(((iAmt + iOfst) >= p->endpoint.iOffset) != ((iAmt + iOfst) > p->endpoint.iOffset))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 11);
}
if( (iAmt+iOfst)>p->endpoint.iOffset ){
    
// MCC Label 12
if(( 10 | (2 << 8) ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 12);
}
// MCC Label 13
if(( !(10 | (2 << 8)) ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 13);
}
return SQLITE_IOERR_SHORT_READ;
  }
  assert( p->readpoint.iOffset==0 || p->readpoint.pChunk!=0 );
  
// ABS Label 14
if(iOfst < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 14);
}
// ABS Label 15
if(p->readpoint.iOffset < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 15);
}

// COR Label 16
if((p->readpoint.iOffset != iOfst && iOfst == 0) != (p->readpoint.iOffset != iOfst || iOfst == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 16);
}

// ROR Label 17
if((p->readpoint.iOffset == iOfst) != (p->readpoint.iOffset != iOfst))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 17);
}
// ROR Label 18
if((iOfst != 0) != (iOfst == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 18);
}

// MCC Label 19
if(p->readpoint.iOffset != iOfst && iOfst == 0 ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 19);
}
// MCC Label 20
if(p->readpoint.iOffset != iOfst && !(iOfst == 0) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 20);
}
// MCC Label 21
if(!(p->readpoint.iOffset != iOfst) && iOfst == 0 ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 21);
}
// MCC Label 22
if(!(p->readpoint.iOffset != iOfst) && !(iOfst == 0) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 22);
}
if( p->readpoint.iOffset!=iOfst || iOfst==0 ){
    sqlite3_int64 iOff = 0;
    pChunk = p->pFirst;

// ABS Label 23
if((pChunk) < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 23);
}
// ABS Label 24
if(iOfst < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 24);
}

// COR Label 25
if(((pChunk) || (iOff + p->nChunkSize) <= iOfst) != ((pChunk) && (iOff + p->nChunkSize) <= iOfst))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 25);
}

// ROR Label 26
if(((iOff + p->nChunkSize) < iOfst) != ((iOff + p->nChunkSize) <= iOfst))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 26);
}
// ROR Label 27
if(((iOff + p->nChunkSize) > iOfst) != ((iOff + p->nChunkSize) <= iOfst))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 27);
}
// ROR Label 28
if(((iOff + p->nChunkSize) >= iOfst) != ((iOff + p->nChunkSize) <= iOfst))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 28);
}

// MCC Label 29
if((pChunk) && (iOff + p->nChunkSize) <= iOfst ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 29);
}
// MCC Label 30
if((pChunk) && !((iOff + p->nChunkSize) <= iOfst) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 30);
}
// MCC Label 31
if(!((pChunk)) && (iOff + p->nChunkSize) <= iOfst ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 31);
}
// MCC Label 32
if(!((pChunk)) && !((iOff + p->nChunkSize) <= iOfst) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 32);
}
for(; 
        ALWAYS(pChunk) && (iOff+p->nChunkSize)<=iOfst;
        pChunk=pChunk->pNext
    ){
      iOff += p->nChunkSize;
    };
// ABS Label 33
if((pChunk) < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 33);
}
// ABS Label 34
if(iOfst < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 34);
}

// COR Label 35
if(((pChunk) || (iOff + p->nChunkSize) <= iOfst) != ((pChunk) && (iOff + p->nChunkSize) <= iOfst))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 35);
}

// ROR Label 36
if(((iOff + p->nChunkSize) < iOfst) != ((iOff + p->nChunkSize) <= iOfst))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 36);
}
// ROR Label 37
if(((iOff + p->nChunkSize) > iOfst) != ((iOff + p->nChunkSize) <= iOfst))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 37);
}
// ROR Label 38
if(((iOff + p->nChunkSize) >= iOfst) != ((iOff + p->nChunkSize) <= iOfst))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 38);
}

// MCC Label 39
if((pChunk) && (iOff + p->nChunkSize) <= iOfst ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 39);
}
// MCC Label 40
if((pChunk) && !((iOff + p->nChunkSize) <= iOfst) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 40);
}
// MCC Label 41
if(!((pChunk)) && (iOff + p->nChunkSize) <= iOfst ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 41);
}
// MCC Label 42
if(!((pChunk)) && !((iOff + p->nChunkSize) <= iOfst) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 42);
}

  }else{
    pChunk = p->readpoint.pChunk;
    assert( pChunk!=0 );
  }

  iChunkOffset = (int)(iOfst%p->nChunkSize);
  do {
    
// ABS Label 43
if(iChunkOffset < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 43);
}
// ABS Label 44
if(p->nChunkSize < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 44);
}

// AOR Label 45
if(p->nChunkSize / iChunkOffset != p->nChunkSize - iChunkOffset)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 45);
}
// AOR Label 46
if(p->nChunkSize + iChunkOffset != p->nChunkSize - iChunkOffset)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 46);
}
// AOR Label 47
if(p->nChunkSize * iChunkOffset != p->nChunkSize - iChunkOffset)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 47);
}
int iSpace = p->nChunkSize - iChunkOffset;
    int nCopy = MIN(nRead, (p->nChunkSize - iChunkOffset));
    memcpy(zOut, (u8*)pChunk->zChunk + iChunkOffset, nCopy);
    zOut += nCopy;
    nRead -= iSpace;
    iChunkOffset = 0;
  } while( nRead>=0 && (pChunk=pChunk->pNext)!=0 && nRead>0 );;
  p->readpoint.iOffset = pChunk ? iOfst+iAmt : 0;
  p->readpoint.pChunk = pChunk;

  return SQLITE_OK;
}

/*
** Free the list of FileChunk structures headed at MemJournal.pFirst.
*/
static void memjrnlFreeChunks(FileChunk *pFirst){
  FileChunk *pIter;
  FileChunk *pNext;
  pIter = pFirst;

// ABS Label 48
if(pIter < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 48);
}
for(; pIter; pIter=pNext){
    pNext = pIter->pNext;
    sqlite3_free(pIter);
  };
// ABS Label 49
if(pIter < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 49);
}
 
}

/*
** Flush the contents of memory to a real file on disk.
*/
static int memjrnlCreateFile(MemJournal *p){
  int rc;
  sqlite3_file *pReal = (sqlite3_file*)p;
  
// ABS Label 50
if(*p < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 50);
}
MemJournal copy = *p;

  memset(p, 0, sizeof(MemJournal));
  rc = sqlite3OsOpen(copy.pVfs, copy.zJournal, pReal, copy.flags, 0);
  
// ABS Label 51
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 51);
}

// ROR Label 52
if((rc != 0) != (rc == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 52);
}
if( rc==SQLITE_OK ){
    
// ABS Label 53
if(copy.nChunkSize < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 53);
}
int nChunk = copy.nChunkSize;
    i64 iOff = 0;
    FileChunk *pIter;
    pIter = copy.pFirst;

// ABS Label 54
if(pIter < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 54);
}
for(; pIter; pIter=pIter->pNext){
      
// ABS Label 56
if(copy.endpoint.iOffset < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 56);
}
// ABS Label 57
if(iOff < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 57);
}

// AOR Label 58
if(iOff - nChunk != iOff + nChunk)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 58);
}
// AOR Label 59
if(iOff / nChunk != iOff + nChunk)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 59);
}
// AOR Label 60
if(iOff * nChunk != iOff + nChunk)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 60);
}

// ROR Label 61
if((iOff + nChunk <= copy.endpoint.iOffset) != (iOff + nChunk > copy.endpoint.iOffset))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 61);
}
// ROR Label 62
if((iOff + nChunk < copy.endpoint.iOffset) != (iOff + nChunk > copy.endpoint.iOffset))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 62);
}
// ROR Label 63
if((iOff + nChunk >= copy.endpoint.iOffset) != (iOff + nChunk > copy.endpoint.iOffset))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 63);
}
if( iOff + nChunk > copy.endpoint.iOffset ){
        nChunk = copy.endpoint.iOffset - iOff;
      }
      rc = sqlite3OsWrite(pReal, (u8*)pIter->zChunk, nChunk, iOff);
      
// ABS Label 64
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 64);
}
if( rc ) { break;
}
      iOff += nChunk;
    };
// ABS Label 55
if(pIter < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 55);
}

    
// ABS Label 65
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 65);
}

// ROR Label 66
if((rc != 0) != (rc == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 66);
}
if( rc==SQLITE_OK ){
      /* No error has occurred. Free the in-memory buffers. */
      
// ABS Label 67
if(copy.pFirst < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 67);
}
memjrnlFreeChunks(copy.pFirst);
    }
  }
  
// ABS Label 68
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 68);
}

// ROR Label 69
if((rc == 0) != (rc != 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 69);
}
if( rc!=SQLITE_OK ){
    /* If an error occurred while creating or writing to the file, restore
    ** the original before returning. This way, SQLite uses the in-memory
    ** journal data to roll back changes made to the internal page-cache
    ** before this function was called.  */
    
// ABS Label 70
if(pReal < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 70);
}
sqlite3OsClose(pReal);
    *p = copy;
  }
  
// ABS Label 71
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 71);
}
return rc;
}


/*
** Write data to the file.
*/
static int memjrnlWrite(
  sqlite3_file *pJfd,    /* The journal file into which to write */
  const void *zBuf,      /* Take data to be written from here */
  int iAmt,              /* Number of bytes to write */
  sqlite_int64 iOfst     /* Begin writing at this offset into the file */
){
  MemJournal *p = (MemJournal *)pJfd;
  
// ABS Label 72
if(iAmt < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 72);
}
int nWrite = iAmt;
  u8 *zWrite = (u8 *)zBuf;

  /* If the file should be created now, create it and write the new data
  ** into the file on disk. */
  
// ABS Label 73
if(p->nSpill < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 73);
}

// COR Label 74
if((p->nSpill > 0 || (iAmt + iOfst) > p->nSpill) != (p->nSpill > 0 && (iAmt + iOfst) > p->nSpill))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 74);
}

// ROR Label 75
if((p->nSpill <= 0) != (p->nSpill > 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 75);
}
// ROR Label 76
if((p->nSpill < 0) != (p->nSpill > 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 76);
}
// ROR Label 77
if((p->nSpill >= 0) != (p->nSpill > 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 77);
}
// ROR Label 78
if(((iAmt + iOfst) <= p->nSpill) != ((iAmt + iOfst) > p->nSpill))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 78);
}
// ROR Label 79
if(((iAmt + iOfst) < p->nSpill) != ((iAmt + iOfst) > p->nSpill))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 79);
}
// ROR Label 80
if(((iAmt + iOfst) >= p->nSpill) != ((iAmt + iOfst) > p->nSpill))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 80);
}

// MCC Label 81
if(p->nSpill > 0 && (iAmt + iOfst) > p->nSpill ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 81);
}
// MCC Label 82
if(p->nSpill > 0 && !((iAmt + iOfst) > p->nSpill) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 82);
}
// MCC Label 83
if(!(p->nSpill > 0) && (iAmt + iOfst) > p->nSpill ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 83);
}
// MCC Label 84
if(!(p->nSpill > 0) && !((iAmt + iOfst) > p->nSpill) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 84);
}
if( p->nSpill>0 && (iAmt+iOfst)>p->nSpill ){
    int rc = memjrnlCreateFile(p);
    
// ABS Label 85
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 85);
}

// ROR Label 86
if((rc != 0) != (rc == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 86);
}
if( rc==SQLITE_OK ){
      rc = sqlite3OsWrite(pJfd, zBuf, iAmt, iOfst);
    }
    
// ABS Label 87
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 87);
}
return rc;
  }

  /* If the contents of this write should be stored in memory */
  else{
    /* An in-memory journal file should only ever be appended to. Random
    ** access writes are not required. The only exception to this is when
    ** the in-memory journal is being used by a connection using the
    ** atomic-write optimization. In this case the first 28 bytes of the
    ** journal file may be written as part of committing the transaction. */ 
    assert( iOfst==p->endpoint.iOffset || iOfst==0 );
#if defined(SQLITE_ENABLE_ATOMIC_WRITE) \
 || defined(SQLITE_ENABLE_BATCH_ATOMIC_WRITE)
    if( iOfst==0 && p->pFirst ){
      assert( p->nChunkSize>iAmt );
      memcpy((u8*)p->pFirst->zChunk, zBuf, iAmt);
    }else
#else
    assert( iOfst>0 || p->pFirst==0 );
#endif
    {
      
// ABS Label 88
if(nWrite < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 88);
}

// ROR Label 89
if((nWrite <= 0) != (nWrite > 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 89);
}
// ROR Label 90
if((nWrite < 0) != (nWrite > 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 90);
}
// ROR Label 91
if((nWrite >= 0) != (nWrite > 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 91);
}
while( nWrite>0 ){
        
// ABS Label 96
if(p->endpoint.pChunk < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 96);
}
FileChunk *pChunk = p->endpoint.pChunk;
        int iChunkOffset = (int)(p->endpoint.iOffset%p->nChunkSize);
        int iSpace = MIN(nWrite, p->nChunkSize - iChunkOffset);

        
// ABS Label 97
if(iChunkOffset < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 97);
}

// ROR Label 98
if((iChunkOffset != 0) != (iChunkOffset == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 98);
}
if( iChunkOffset==0 ){
          /* New chunk is required to extend the file. */
          FileChunk *pNew = sqlite3_malloc(fileChunkSize(p->nChunkSize));
          if( !pNew ){
            
// MCC Label 99
if(( 10 | (12 << 8) ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 99);
}
// MCC Label 100
if(( !(10 | (12 << 8)) ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 100);
}
return SQLITE_IOERR_NOMEM_BKPT;
          }
          pNew->pNext = 0;
          
// ABS Label 101
if(pChunk < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 101);
}
if( pChunk ){
            assert( p->pFirst );
            pChunk->pNext = pNew;
          }else{
            assert( !p->pFirst );
            p->pFirst = pNew;
          }
          p->endpoint.pChunk = pNew;
        }

        memcpy((u8*)p->endpoint.pChunk->zChunk + iChunkOffset, zWrite, iSpace);
        zWrite += iSpace;
        nWrite -= iSpace;
        p->endpoint.iOffset += iSpace;
      };
// ABS Label 92
if(nWrite < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 92);
}

// ROR Label 93
if((nWrite <= 0) != (nWrite > 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 93);
}
// ROR Label 94
if((nWrite < 0) != (nWrite > 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 94);
}
// ROR Label 95
if((nWrite >= 0) != (nWrite > 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 95);
}

    }
  }

  return SQLITE_OK;
}

/*
** Truncate the in-memory file.
*/
static int memjrnlTruncate(sqlite3_file *pJfd, sqlite_int64 size){
  MemJournal *p = (MemJournal *)pJfd;
  assert( p->endpoint.pChunk==0 || p->endpoint.pChunk->pNext==0 );
  
// ABS Label 102
if(p->endpoint.iOffset < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 102);
}
// ABS Label 103
if(size < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 103);
}

// ROR Label 104
if((size <= p->endpoint.iOffset) != (size < p->endpoint.iOffset))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 104);
}
// ROR Label 105
if((size > p->endpoint.iOffset) != (size < p->endpoint.iOffset))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 105);
}
// ROR Label 106
if((size >= p->endpoint.iOffset) != (size < p->endpoint.iOffset))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 106);
}
if( size<p->endpoint.iOffset ){
    FileChunk *pIter = 0;
    
// ABS Label 107
if(size < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 107);
}

// ROR Label 108
if((size != 0) != (size == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 108);
}
if( size==0 ){
      
// ABS Label 109
if(p->pFirst < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 109);
}
memjrnlFreeChunks(p->pFirst);
      p->pFirst = 0;
    }else{
      i64 iOff = p->nChunkSize;
      pIter = p->pFirst;

// ABS Label 110
if((pIter) < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 110);
}
// ABS Label 111
if(iOff < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 111);
}
// ABS Label 112
if(size < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 112);
}

// COR Label 113
if(((pIter) || iOff <= size) != ((pIter) && iOff <= size))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 113);
}

// ROR Label 114
if((iOff < size) != (iOff <= size))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 114);
}
// ROR Label 115
if((iOff > size) != (iOff <= size))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 115);
}
// ROR Label 116
if((iOff >= size) != (iOff <= size))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 116);
}

// MCC Label 117
if((pIter) && iOff <= size ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 117);
}
// MCC Label 118
if((pIter) && !(iOff <= size) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 118);
}
// MCC Label 119
if(!((pIter)) && iOff <= size ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 119);
}
// MCC Label 120
if(!((pIter)) && !(iOff <= size) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 120);
}
for(; ALWAYS(pIter) && iOff<=size; pIter=pIter->pNext){
        iOff += p->nChunkSize;
      };
// ABS Label 121
if((pIter) < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 121);
}
// ABS Label 122
if(iOff < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 122);
}
// ABS Label 123
if(size < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 123);
}

// COR Label 124
if(((pIter) || iOff <= size) != ((pIter) && iOff <= size))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 124);
}

// ROR Label 125
if((iOff < size) != (iOff <= size))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 125);
}
// ROR Label 126
if((iOff > size) != (iOff <= size))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 126);
}
// ROR Label 127
if((iOff >= size) != (iOff <= size))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 127);
}

// MCC Label 128
if((pIter) && iOff <= size ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 128);
}
// MCC Label 129
if((pIter) && !(iOff <= size) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 129);
}
// MCC Label 130
if(!((pIter)) && iOff <= size ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 130);
}
// MCC Label 131
if(!((pIter)) && !(iOff <= size) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 131);
}

      
// ABS Label 132
if((pIter) < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 132);
}
if( ALWAYS(pIter) ){
        
// ABS Label 133
if(pIter->pNext < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 133);
}
memjrnlFreeChunks(pIter->pNext);
        pIter->pNext = 0;
      }
    }

    p->endpoint.pChunk = pIter;
    p->endpoint.iOffset = size;
    p->readpoint.pChunk = 0;
    p->readpoint.iOffset = 0;
  }
  return SQLITE_OK;
}

/*
** Close the file.
*/
static int memjrnlClose(sqlite3_file *pJfd){
  MemJournal *p = (MemJournal *)pJfd;
  
// ABS Label 134
if(p->pFirst < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 134);
}
memjrnlFreeChunks(p->pFirst);
  return SQLITE_OK;
}

/*
** Sync the file.
**
** If the real file has been created, call its xSync method. Otherwise, 
** syncing an in-memory journal is a no-op. 
*/
static int memjrnlSync(sqlite3_file *pJfd, int flags){
  UNUSED_PARAMETER2(pJfd, flags);
  return SQLITE_OK;
}

/*
** Query the size of the file in bytes.
*/
static int memjrnlFileSize(sqlite3_file *pJfd, sqlite_int64 *pSize){
  MemJournal *p = (MemJournal *)pJfd;
  *pSize = (sqlite_int64) p->endpoint.iOffset;
  return SQLITE_OK;
}

/*
** Table of methods for MemJournal sqlite3_file object.
*/
static const struct sqlite3_io_methods MemJournalMethods = {
  1,                /* iVersion */
  memjrnlClose,     /* xClose */
  memjrnlRead,      /* xRead */
  memjrnlWrite,     /* xWrite */
  memjrnlTruncate,  /* xTruncate */
  memjrnlSync,      /* xSync */
  memjrnlFileSize,  /* xFileSize */
  0,                /* xLock */
  0,                /* xUnlock */
  0,                /* xCheckReservedLock */
  0,                /* xFileControl */
  0,                /* xSectorSize */
  0,                /* xDeviceCharacteristics */
  0,                /* xShmMap */
  0,                /* xShmLock */
  0,                /* xShmBarrier */
  0,                /* xShmUnmap */
  0,                /* xFetch */
  0                 /* xUnfetch */
};

/* 
** Open a journal file. 
**
** The behaviour of the journal file depends on the value of parameter 
** nSpill. If nSpill is 0, then the journal file is always create and 
** accessed using the underlying VFS. If nSpill is less than zero, then
** all content is always stored in main-memory. Finally, if nSpill is a
** positive value, then the journal file is initially created in-memory
** but may be flushed to disk later on. In this case the journal file is
** flushed to disk either when it grows larger than nSpill bytes in size,
** or when sqlite3JournalCreate() is called.
*/
int sqlite3JournalOpen(
  sqlite3_vfs *pVfs,         /* The VFS to use for actual file I/O */
  const char *zName,         /* Name of the journal file */
  sqlite3_file *pJfd,        /* Preallocated, blank file handle */
  int flags,                 /* Opening flags */
  int nSpill                 /* Bytes buffered before opening the file */
){
  MemJournal *p = (MemJournal*)pJfd;

  /* Zero the file-handle object. If nSpill was passed zero, initialize
  ** it using the sqlite3OsOpen() function of the underlying VFS. In this
  ** case none of the code in this module is executed as a result of calls
  ** made on the journal file-handle.  */
  memset(p, 0, sizeof(MemJournal));
  
// ABS Label 135
if(nSpill < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 135);
}

// ROR Label 136
if((nSpill != 0) != (nSpill == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 136);
}
if( nSpill==0 ){
    return sqlite3OsOpen(pVfs, zName, pJfd, flags, 0);
  }

  
// ABS Label 137
if(nSpill < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 137);
}

// ROR Label 138
if((nSpill <= 0) != (nSpill > 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 138);
}
// ROR Label 139
if((nSpill < 0) != (nSpill > 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 139);
}
// ROR Label 140
if((nSpill >= 0) != (nSpill > 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 140);
}
if( nSpill>0 ){
    p->nChunkSize = nSpill;
  }else{
    p->nChunkSize = 8 + MEMJOURNAL_DFLT_FILECHUNKSIZE - sizeof(FileChunk);
    assert( MEMJOURNAL_DFLT_FILECHUNKSIZE==fileChunkSize(p->nChunkSize) );
  }

  pJfd->pMethods = (const sqlite3_io_methods*)&MemJournalMethods;
  p->nSpill = nSpill;
  p->flags = flags;
  p->zJournal = zName;
  p->pVfs = pVfs;
  return SQLITE_OK;
}

/*
** Open an in-memory journal file.
*/
void sqlite3MemJournalOpen(sqlite3_file *pJfd){
  
// ABS Label 141
if(pJfd < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 141);
}
sqlite3JournalOpen(0, 0, pJfd, 0, -1);
}

#if defined(SQLITE_ENABLE_ATOMIC_WRITE) \
 || defined(SQLITE_ENABLE_BATCH_ATOMIC_WRITE)
/*
** If the argument p points to a MemJournal structure that is not an 
** in-memory-only journal file (i.e. is one that was opened with a +ve
** nSpill parameter or as SQLITE_OPEN_MAIN_JOURNAL), and the underlying 
** file has not yet been created, create it now.
*/
int sqlite3JournalCreate(sqlite3_file *pJfd){
  int rc = SQLITE_OK;
  MemJournal *p = (MemJournal*)pJfd;
  if( pJfd->pMethods==&MemJournalMethods && (
#ifdef SQLITE_ENABLE_ATOMIC_WRITE
     p->nSpill>0
#else
     /* While this appears to not be possible without ATOMIC_WRITE, the
     ** paths are complex, so it seems prudent to leave the test in as
     ** a NEVER(), in case our analysis is subtly flawed. */
     NEVER(p->nSpill>0)
#endif
#ifdef SQLITE_ENABLE_BATCH_ATOMIC_WRITE
     || (p->flags & SQLITE_OPEN_MAIN_JOURNAL)
#endif
  )){
    rc = memjrnlCreateFile(p);
  }
  return rc;
}
#endif

/*
** The file-handle passed as the only argument is open on a journal file.
** Return true if this "journal file" is currently stored in heap memory,
** or false otherwise.
*/
int sqlite3JournalIsInMemory(sqlite3_file *p){
  
// ABS Label 142
if(p->pMethods < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 142);
}

// ROR Label 143
if((p->pMethods != &MemJournalMethods) != (p->pMethods == &MemJournalMethods))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 143);
}
return p->pMethods==&MemJournalMethods;
}

/* 
** Return the number of bytes required to store a JournalFile that uses vfs
** pVfs to create the underlying on-disk files.
*/
int sqlite3JournalSize(sqlite3_vfs *pVfs){
  
// MCC Label 144
if(( ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 144);
}
return MAX(pVfs->szOsFile, (int)sizeof(MemJournal));
}
