/*** Generated by CAnnotate ***/ 
// COVERAGE CRITERIA : ABS AOR COR ROR MCC 
#include "coverage.h"
/*
** 2001 September 15
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** This file contains the sqlite3_get_table() and sqlite3_free_table()
** interface routines.  These are just wrappers around the main
** interface routine of sqlite3_exec().
**
** These routines are in a separate files so that they will not be linked
** if they are not used.
*/
#include "sqliteInt.h"

#ifndef SQLITE_OMIT_GET_TABLE

/*
** This structure is used to pass data from sqlite3_get_table() through
** to the callback function is uses to build the result.
*/
typedef struct TabResult {
  char **azResult;   /* Accumulated output */
  char *zErrMsg;     /* Error message text, if an error occurs */
  u32 nAlloc;        /* Slots allocated for azResult[] */
  u32 nRow;          /* Number of rows in the result */
  u32 nColumn;       /* Number of columns in the result */
  u32 nData;         /* Slots used in azResult[].  (nRow+1)*nColumn */
  int rc;            /* Return code from sqlite3_exec() */
} TabResult;

/*
** This routine is called once for each row in the result table.  Its job
** is to fill in the TabResult structure appropriately, allocating new
** memory as necessary.
*/
static int sqlite3_get_table_cb(void *pArg, int nCol, char **argv, char **colv){
  TabResult *p = (TabResult*)pArg;  /* Result accumulator */
  int need;                         /* Slots needed in p->azResult[] */
  int i;                            /* Loop counter */
  char *z;                          /* A single column of result */

  /* Make sure there is enough space in p->azResult to hold everything
  ** we need to remember from this invocation of the callback.
  */
  
// ABS Label 7
if(argv < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 7);
}
// ABS Label 8
if(p->nRow < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 8);
}

// COR Label 9
if((p->nRow == 0 || argv != 0) != (p->nRow == 0 && argv != 0))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 9);
}

// ROR Label 10
if((p->nRow != 0) != (p->nRow == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 10);
}
// ROR Label 11
if((argv == 0) != (argv != 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 11);
}

// MCC Label 12
if(p->nRow == 0 && argv != 0 ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 12);
}
// MCC Label 13
if(p->nRow == 0 && !(argv != 0) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 13);
}
// MCC Label 14
if(!(p->nRow == 0) && argv != 0 ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 14);
}
// MCC Label 15
if(!(p->nRow == 0) && !(argv != 0) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 15);
}
if( p->nRow==0 && argv!=0 ){
    need = nCol*2;
  }else{
    need = nCol;
  }
  
// ABS Label 16
if(p->nAlloc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 16);
}
// ABS Label 17
if(p->nData < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 17);
}

// AOR Label 18
if(p->nData - need != p->nData + need)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 18);
}
// AOR Label 19
if(p->nData / need != p->nData + need)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 19);
}
// AOR Label 20
if(p->nData * need != p->nData + need)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 20);
}

// ROR Label 21
if((p->nData + need <= p->nAlloc) != (p->nData + need > p->nAlloc))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 21);
}
// ROR Label 22
if((p->nData + need < p->nAlloc) != (p->nData + need > p->nAlloc))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 22);
}
// ROR Label 23
if((p->nData + need >= p->nAlloc) != (p->nData + need > p->nAlloc))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 23);
}
if( p->nData + need > p->nAlloc ){
    char **azNew;
    p->nAlloc = p->nAlloc*2 + need;
    azNew = sqlite3Realloc( p->azResult, sizeof(char*)*p->nAlloc );
    
// ABS Label 24
if(azNew < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 24);
}

// ROR Label 25
if((azNew != 0) != (azNew == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 25);
}
if( azNew==0 ) { goto malloc_failed;
}
    p->azResult = azNew;
  }

  /* If this is the first row, then generate an extra row containing
  ** the names of all columns.
  */
  
// ABS Label 26
if(p->nRow < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 26);
}

// ROR Label 27
if((p->nRow != 0) != (p->nRow == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 27);
}
if( p->nRow==0 ){
    p->nColumn = nCol;
    i = 0;

// ABS Label 28
if(i < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 28);
}
// ABS Label 29
if(nCol < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 29);
}

// ROR Label 30
if((i <= nCol) != (i < nCol))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 30);
}
// ROR Label 31
if((i > nCol) != (i < nCol))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 31);
}
// ROR Label 32
if((i >= nCol) != (i < nCol))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 32);
}
for(; i<nCol; i++){
      z = sqlite3_mprintf("%s", colv[i]);
      
// ABS Label 38
if(z < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 38);
}

// ROR Label 39
if((z != 0) != (z == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 39);
}
if( z==0 ) { goto malloc_failed;
}
      p->azResult[p->nData++] = z;
    };
// ABS Label 33
if(i < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 33);
}
// ABS Label 34
if(nCol < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 34);
}

// ROR Label 35
if((i <= nCol) != (i < nCol))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 35);
}
// ROR Label 36
if((i > nCol) != (i < nCol))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 36);
}
// ROR Label 37
if((i >= nCol) != (i < nCol))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 37);
}

  }else { 
// ABS Label 40
if(nCol < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 40);
}

// ROR Label 41
if(((int)p->nColumn == nCol) != ((int)p->nColumn != nCol))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 41);
}
if( (int)p->nColumn!=nCol ){
    sqlite3_free(p->zErrMsg);
    p->zErrMsg = sqlite3_mprintf(
       "sqlite3_get_table() called with two or more incompatible queries"
    );
    p->rc = SQLITE_ERROR;
    return 1;
  };}


  /* Copy over the row data
  */
  
// ABS Label 42
if(argv < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 42);
}

// ROR Label 43
if((argv == 0) != (argv != 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 43);
}
if( argv!=0 ){
    i = 0;

// ABS Label 44
if(i < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 44);
}
// ABS Label 45
if(nCol < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 45);
}

// ROR Label 46
if((i <= nCol) != (i < nCol))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 46);
}
// ROR Label 47
if((i > nCol) != (i < nCol))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 47);
}
// ROR Label 48
if((i >= nCol) != (i < nCol))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 48);
}
for(; i<nCol; i++){
      
// ABS Label 54
if(argv[i] < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 54);
}
// ABS Label 55
if(i < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 55);
}

// ROR Label 56
if((argv[i] != 0) != (argv[i] == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 56);
}
if( argv[i]==0 ){
        z = 0;
      }else{
        int n = sqlite3Strlen30(argv[i])+1;
        z = sqlite3_malloc64( n );
        
// ABS Label 57
if(z < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 57);
}

// ROR Label 58
if((z != 0) != (z == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 58);
}
if( z==0 ) { goto malloc_failed;
}
        memcpy(z, argv[i], n);
      }
      p->azResult[p->nData++] = z;
    };
// ABS Label 49
if(i < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 49);
}
// ABS Label 50
if(nCol < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 50);
}

// ROR Label 51
if((i <= nCol) != (i < nCol))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 51);
}
// ROR Label 52
if((i > nCol) != (i < nCol))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 52);
}
// ROR Label 53
if((i >= nCol) != (i < nCol))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 53);
}

    p->nRow++;
  }
  return 0;

malloc_failed:
  p->rc = SQLITE_NOMEM_BKPT;
  return 1;
}

/*
** Query the database.  But instead of invoking a callback for each row,
** malloc() for space to hold the result and return the entire results
** at the conclusion of the call.
**
** The result that is written to ***pazResult is held in memory obtained
** from malloc().  But the caller cannot free this memory directly.  
** Instead, the entire table should be passed to sqlite3_free_table() when
** the calling procedure is finished using it.
*/
int sqlite3_get_table(
  sqlite3 *db,                /* The database on which the SQL executes */
  const char *zSql,           /* The SQL to be executed */
  char ***pazResult,          /* Write the result table here */
  int *pnRow,                 /* Write the number of rows in the result here */
  int *pnColumn,              /* Write the number of columns of result here */
  char **pzErrMsg             /* Write error messages here */
){
  int rc;
  TabResult res;

#ifdef SQLITE_ENABLE_API_ARMOR
  if( !sqlite3SafetyCheckOk(db) || pazResult==0 ) return SQLITE_MISUSE_BKPT;
#endif
  *pazResult = 0;
  
// ABS Label 59
if(pnColumn < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 59);
}
if( pnColumn ) { *pnColumn = 0;
}
  
// ABS Label 60
if(pnRow < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 60);
}
if( pnRow ) { *pnRow = 0;
}
  
// ABS Label 61
if(pzErrMsg < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 61);
}
if( pzErrMsg ) { *pzErrMsg = 0;
}
  res.zErrMsg = 0;
  res.nRow = 0;
  res.nColumn = 0;
  res.nData = 1;
  res.nAlloc = 20;
  res.rc = SQLITE_OK;
  res.azResult = sqlite3_malloc64(sizeof(char*)*res.nAlloc );
  
// ABS Label 62
if(res.azResult < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 62);
}

// ROR Label 63
if((res.azResult != 0) != (res.azResult == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 63);
}
if( res.azResult==0 ){
     db->errCode = SQLITE_NOMEM;
     return SQLITE_NOMEM_BKPT;
  }
  res.azResult[0] = 0;
  rc = sqlite3_exec(db, zSql, sqlite3_get_table_cb, &res, pzErrMsg);
  assert( sizeof(res.azResult[0])>= sizeof(res.nData) );
  res.azResult[0] = SQLITE_INT_TO_PTR(res.nData);
  
// ROR Label 64
if(((rc & 255) != 4) != ((rc & 255) == 4))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 64);
}
if( (rc&0xff)==SQLITE_ABORT ){
    sqlite3_free_table(&res.azResult[1]);
    
// ABS Label 65
if(res.zErrMsg < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 65);
}
if( res.zErrMsg ){
      
// ABS Label 66
if(pzErrMsg < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 66);
}
if( pzErrMsg ){
        sqlite3_free(*pzErrMsg);
        *pzErrMsg = sqlite3_mprintf("%s",res.zErrMsg);
      }
      sqlite3_free(res.zErrMsg);
    }
    db->errCode = res.rc;  /* Assume 32-bit assignment is atomic */
    
// ABS Label 67
if(res.rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 67);
}
return res.rc;
  }
  sqlite3_free(res.zErrMsg);
  
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
    sqlite3_free_table(&res.azResult[1]);
    
// ABS Label 70
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 70);
}
return rc;
  }
  
// ABS Label 71
if(res.nAlloc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 71);
}
// ABS Label 72
if(res.nData < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 72);
}

// ROR Label 73
if((res.nAlloc <= res.nData) != (res.nAlloc > res.nData))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 73);
}
// ROR Label 74
if((res.nAlloc < res.nData) != (res.nAlloc > res.nData))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 74);
}
// ROR Label 75
if((res.nAlloc >= res.nData) != (res.nAlloc > res.nData))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 75);
}
if( res.nAlloc>res.nData ){
    char **azNew;
    azNew = sqlite3Realloc( res.azResult, sizeof(char*)*res.nData );
    
// ABS Label 76
if(azNew < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 76);
}

// ROR Label 77
if((azNew != 0) != (azNew == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 77);
}
if( azNew==0 ){
      sqlite3_free_table(&res.azResult[1]);
      db->errCode = SQLITE_NOMEM;
      return SQLITE_NOMEM_BKPT;
    }
    res.azResult = azNew;
  }
  *pazResult = &res.azResult[1];
  
// ABS Label 78
if(pnColumn < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 78);
}
if( pnColumn ) { *pnColumn = res.nColumn;
}
  
// ABS Label 79
if(pnRow < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 79);
}
if( pnRow ) { *pnRow = res.nRow;
}
  
// ABS Label 80
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 80);
}
return rc;
}

/*
** This routine frees the space the sqlite3_get_table() malloced.
*/
void sqlite3_free_table(
  char **azResult            /* Result returned from sqlite3_get_table() */
){
  
// ABS Label 81
if(azResult < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 81);
}
if( azResult ){
    int i, n;
    azResult--;
    assert( azResult!=0 );
    n = SQLITE_PTR_TO_INT(azResult[0]);
    i = 1;

// ABS Label 82
if(i < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 82);
}
// ABS Label 83
if(n < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 83);
}

// ROR Label 84
if((i <= n) != (i < n))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 84);
}
// ROR Label 85
if((i > n) != (i < n))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 85);
}
// ROR Label 86
if((i >= n) != (i < n))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 86);
}
for(; i<n; i++){ 
// ABS Label 92
if(azResult[i] < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 92);
}
// ABS Label 93
if(i < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 93);
}
if( azResult[i] ) { sqlite3_free(azResult[i]); 
}};
// ABS Label 87
if(i < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 87);
}
// ABS Label 88
if(n < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 88);
}

// ROR Label 89
if((i <= n) != (i < n))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 89);
}
// ROR Label 90
if((i > n) != (i < n))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 90);
}
// ROR Label 91
if((i >= n) != (i < n))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 91);
}

    sqlite3_free(azResult);
  }
}

#endif /* SQLITE_OMIT_GET_TABLE */
