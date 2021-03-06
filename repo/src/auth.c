/*** Generated by CAnnotate ***/ 
// COVERAGE CRITERIA : ABS AOR COR ROR MCC 
#include "coverage.h"
/*
** 2003 January 11
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** This file contains code used to implement the sqlite3_set_authorizer()
** API.  This facility is an optional feature of the library.  Embedded
** systems that do not need this facility may omit it by recompiling
** the library with -DSQLITE_OMIT_AUTHORIZATION=1
*/
#include "sqliteInt.h"

/*
** All of the code in this file may be omitted by defining a single
** macro.
*/
#ifndef SQLITE_OMIT_AUTHORIZATION

/*
** Set or clear the access authorization function.
**
** The access authorization function is be called during the compilation
** phase to verify that the user has read and/or write access permission on
** various fields of the database.  The first argument to the auth function
** is a copy of the 3rd argument to this routine.  The second argument
** to the auth function is one of these constants:
**
**       SQLITE_CREATE_INDEX
**       SQLITE_CREATE_TABLE
**       SQLITE_CREATE_TEMP_INDEX
**       SQLITE_CREATE_TEMP_TABLE
**       SQLITE_CREATE_TEMP_TRIGGER
**       SQLITE_CREATE_TEMP_VIEW
**       SQLITE_CREATE_TRIGGER
**       SQLITE_CREATE_VIEW
**       SQLITE_DELETE
**       SQLITE_DROP_INDEX
**       SQLITE_DROP_TABLE
**       SQLITE_DROP_TEMP_INDEX
**       SQLITE_DROP_TEMP_TABLE
**       SQLITE_DROP_TEMP_TRIGGER
**       SQLITE_DROP_TEMP_VIEW
**       SQLITE_DROP_TRIGGER
**       SQLITE_DROP_VIEW
**       SQLITE_INSERT
**       SQLITE_PRAGMA
**       SQLITE_READ
**       SQLITE_SELECT
**       SQLITE_TRANSACTION
**       SQLITE_UPDATE
**
** The third and fourth arguments to the auth function are the name of
** the table and the column that are being accessed.  The auth function
** should return either SQLITE_OK, SQLITE_DENY, or SQLITE_IGNORE.  If
** SQLITE_OK is returned, it means that access is allowed.  SQLITE_DENY
** means that the SQL statement will never-run - the sqlite3_exec() call
** will return with an error.  SQLITE_IGNORE means that the SQL statement
** should run but attempts to read the specified column will return NULL
** and attempts to write the column will be ignored.
**
** Setting the auth function to NULL disables this hook.  The default
** setting of the auth function is NULL.
*/
int sqlite3_set_authorizer(
  sqlite3 *db,
  int (*xAuth)(void*,int,const char*,const char*,const char*,const char*),
  void *pArg
){
#ifdef SQLITE_ENABLE_API_ARMOR
  if( !sqlite3SafetyCheckOk(db) ) return SQLITE_MISUSE_BKPT;
#endif
  
// ABS Label 7
if(db->mutex < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 7);
}
sqlite3_mutex_enter(db->mutex);
  db->xAuth = (sqlite3_xauth)xAuth;
  db->pAuthArg = pArg;
  
// ABS Label 9
if(db->xAuth < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 9);
}
if( db->xAuth ) { 
// ABS Label 10
if(db < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 10);
}
sqlite3ExpirePreparedStatements(db, 1);
}
  
// ABS Label 8
if(db->mutex < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 8);
}
sqlite3_mutex_leave(db->mutex);
  return SQLITE_OK;
}

/*
** Write an error message into pParse->zErrMsg that explains that the
** user-supplied authorization function returned an illegal value.
*/
static void sqliteAuthBadReturnCode(Parse *pParse){
  
// ABS Label 11
if(pParse < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 11);
}
sqlite3ErrorMsg(pParse, "authorizer malfunction");
  pParse->rc = SQLITE_ERROR;
}

/*
** Invoke the authorization callback for permission to read column zCol from
** table zTab in database zDb. This function assumes that an authorization
** callback has been registered (i.e. that sqlite3.xAuth is not NULL).
**
** If SQLITE_IGNORE is returned and pExpr is not NULL, then pExpr is changed
** to an SQL NULL expression. Otherwise, if pExpr is NULL, then SQLITE_IGNORE
** is treated as SQLITE_DENY. In this case an error is left in pParse.
*/
int sqlite3AuthReadCol(
  Parse *pParse,                  /* The parser context */
  const char *zTab,               /* Table name */
  const char *zCol,               /* Column name */
  int iDb                         /* Index of containing database. */
){
  
// ABS Label 12
if(pParse->db < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 12);
}
sqlite3 *db = pParse->db;          /* Database handle */
  
// ABS Label 13
if(db->aDb[iDb].zDbSName < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 13);
}
char *zDb = db->aDb[iDb].zDbSName; /* Schema name of attached database */
  int rc;                            /* Auth callback return code */

  
// ABS Label 14
if(db->init.busy < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 14);
}
if( db->init.busy ) { return SQLITE_OK;
}
  rc = db->xAuth(db->pAuthArg, SQLITE_READ, zTab,zCol,zDb,pParse->zAuthContext
#ifdef SQLITE_USER_AUTHENTICATION
                 ,db->auth.zAuthUser
#endif
                );
  
// ABS Label 15
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 15);
}

// ROR Label 16
if((rc != 1) != (rc == 1))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 16);
}
if( rc==SQLITE_DENY ){
    char *z = sqlite3_mprintf("%s.%s", zTab, zCol);
    
// ABS Label 19
if(db->nDb < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 19);
}
// ABS Label 20
if(iDb < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 20);
}

// COR Label 21
if((db->nDb > 2 && iDb != 0) != (db->nDb > 2 || iDb != 0))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 21);
}

// ROR Label 22
if((db->nDb <= 2) != (db->nDb > 2))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 22);
}
// ROR Label 23
if((db->nDb < 2) != (db->nDb > 2))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 23);
}
// ROR Label 24
if((db->nDb >= 2) != (db->nDb > 2))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 24);
}
// ROR Label 25
if((iDb == 0) != (iDb != 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 25);
}

// MCC Label 26
if(db->nDb > 2 && iDb != 0 ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 26);
}
// MCC Label 27
if(db->nDb > 2 && !(iDb != 0) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 27);
}
// MCC Label 28
if(!(db->nDb > 2) && iDb != 0 ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 28);
}
// MCC Label 29
if(!(db->nDb > 2) && !(iDb != 0) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 29);
}
if( db->nDb>2 || iDb!=0 ) { z = sqlite3_mprintf("%s.%z", zDb, z);
}
    
// ABS Label 17
if(pParse < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 17);
}

// ABS Label 18
if(z < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 18);
}
sqlite3ErrorMsg(pParse, "access to %z is prohibited", z);
    pParse->rc = SQLITE_AUTH;
  }else { 
// ABS Label 30
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 30);
}

// COR Label 31
if((rc != 2 || rc != 0) != (rc != 2 && rc != 0))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 31);
}

// ROR Label 32
if((rc == 2) != (rc != 2))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 32);
}
// ROR Label 33
if((rc == 0) != (rc != 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 33);
}

// MCC Label 34
if(rc != 2 && rc != 0 ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 34);
}
// MCC Label 35
if(rc != 2 && !(rc != 0) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 35);
}
// MCC Label 36
if(!(rc != 2) && rc != 0 ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 36);
}
// MCC Label 37
if(!(rc != 2) && !(rc != 0) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 37);
}
if( rc!=SQLITE_IGNORE && rc!=SQLITE_OK ){
    
// ABS Label 38
if(pParse < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 38);
}
sqliteAuthBadReturnCode(pParse);
  };}

  
// ABS Label 39
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 39);
}
return rc;
}

/*
** The pExpr should be a TK_COLUMN expression.  The table referred to
** is in pTabList or else it is the NEW or OLD table of a trigger.  
** Check to see if it is OK to read this particular column.
**
** If the auth function returns SQLITE_IGNORE, change the TK_COLUMN 
** instruction into a TK_NULL.  If the auth function returns SQLITE_DENY,
** then generate an error.
*/
void sqlite3AuthRead(
  Parse *pParse,        /* The parser context */
  Expr *pExpr,          /* The expression to check authorization on */
  Schema *pSchema,      /* The schema of the expression */
  SrcList *pTabList     /* All table that pExpr might refer to */
){
  Table *pTab = 0;      /* The table being read */
  const char *zCol;     /* Name of the column of the table */
  int iSrc;             /* Index in pTabList->a[] of table being read */
  int iDb;              /* The index of the database the expression refers to */
  int iCol;             /* Index of column in table */

  assert( pExpr->op==TK_COLUMN || pExpr->op==TK_TRIGGER );
  assert( !IN_RENAME_OBJECT );
  assert( pParse->db->xAuth!=0 );
  iDb = sqlite3SchemaToIndex(pParse->db, pSchema);
  
// ABS Label 40
if(iDb < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 40);
}

// ROR Label 41
if((iDb <= 0) != (iDb < 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 41);
}
// ROR Label 42
if((iDb > 0) != (iDb < 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 42);
}
// ROR Label 43
if((iDb >= 0) != (iDb < 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 43);
}
if( iDb<0 ){
    /* An attempt to read a column out of a subquery or other
    ** temporary table. */
    return;
  }

  
// ROR Label 44
if((pExpr->op != 77) != (pExpr->op == 77))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 44);
}
if( pExpr->op==TK_TRIGGER ){
    pTab = pParse->pTriggerTab;
  }else{
    assert( pTabList );
    iSrc = 0;

// ABS Label 45
if(iSrc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 45);
}
// ABS Label 46
if(pTabList->nSrc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 46);
}

// ROR Label 47
if((iSrc <= pTabList->nSrc) != (iSrc < pTabList->nSrc))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 47);
}
// ROR Label 48
if((iSrc > pTabList->nSrc) != (iSrc < pTabList->nSrc))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 48);
}
// ROR Label 49
if((iSrc >= pTabList->nSrc) != (iSrc < pTabList->nSrc))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 49);
}
for(; iSrc<pTabList->nSrc; iSrc++){
      
// ABS Label 55
if(pExpr->iTable < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 55);
}
// ABS Label 56
if(pTabList->a[iSrc].iCursor < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 56);
}

// ROR Label 57
if((pExpr->iTable != pTabList->a[iSrc].iCursor) != (pExpr->iTable == pTabList->a[iSrc].iCursor))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 57);
}
if( pExpr->iTable==pTabList->a[iSrc].iCursor ){
        pTab = pTabList->a[iSrc].pTab;
        break;
      }
    };
// ABS Label 50
if(iSrc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 50);
}
// ABS Label 51
if(pTabList->nSrc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 51);
}

// ROR Label 52
if((iSrc <= pTabList->nSrc) != (iSrc < pTabList->nSrc))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 52);
}
// ROR Label 53
if((iSrc > pTabList->nSrc) != (iSrc < pTabList->nSrc))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 53);
}
// ROR Label 54
if((iSrc >= pTabList->nSrc) != (iSrc < pTabList->nSrc))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 54);
}

  }
  iCol = pExpr->iColumn;
  
// ABS Label 58
if(pTab < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 58);
}

// ROR Label 59
if((pTab != 0) != (pTab == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 59);
}
if( pTab==0 ) { return;
}

  
// ABS Label 60
if(iCol < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 60);
}

// ROR Label 61
if((iCol < 0) != (iCol >= 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 61);
}
// ROR Label 62
if((iCol > 0) != (iCol >= 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 62);
}
// ROR Label 63
if((iCol <= 0) != (iCol >= 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 63);
}
if( iCol>=0 ){
    assert( iCol<pTab->nCol );
    zCol = pTab->aCol[iCol].zName;
  }else { 
// ROR Label 64
if((pTab->iPKey < 0) != (pTab->iPKey >= 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 64);
}
// ROR Label 65
if((pTab->iPKey > 0) != (pTab->iPKey >= 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 65);
}
// ROR Label 66
if((pTab->iPKey <= 0) != (pTab->iPKey >= 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 66);
}
if( pTab->iPKey>=0 ){
    assert( pTab->iPKey<pTab->nCol );
    zCol = pTab->aCol[pTab->iPKey].zName;
  }else{
    zCol = "ROWID";
  };}

  assert( iDb>=0 && iDb<pParse->db->nDb );
  if( SQLITE_IGNORE==sqlite3AuthReadCol(pParse, pTab->zName, zCol, iDb) ){
    pExpr->op = TK_NULL;
  }
}

/*
** Do an authorization check using the code and arguments given.  Return
** either SQLITE_OK (zero) or SQLITE_IGNORE or SQLITE_DENY.  If SQLITE_DENY
** is returned, then the error count and error message in pParse are
** modified appropriately.
*/
int sqlite3AuthCheck(
  Parse *pParse,
  int code,
  const char *zArg1,
  const char *zArg2,
  const char *zArg3
){
  
// ABS Label 67
if(pParse->db < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 67);
}
sqlite3 *db = pParse->db;
  int rc;

  /* Don't do any authorization checks if the database is initialising
  ** or if the parser is being invoked from within sqlite3_declare_vtab.
  */
  assert( !IN_RENAME_OBJECT || db->xAuth==0 );
  
// ABS Label 68
if(db->xAuth < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 68);
}

// COR Label 69
if((db->xAuth == 0 || db->init.busy && (pParse->eParseMode != 0)) != (db->xAuth == 0 || db->init.busy || (pParse->eParseMode != 0)))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 69);
}
// COR Label 70
if((db->xAuth == 0 && db->init.busy) != (db->xAuth == 0 || db->init.busy))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 70);
}

// ROR Label 71
if((db->xAuth != 0) != (db->xAuth == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 71);
}

// MCC Label 72
if(db->xAuth == 0 && db->init.busy && ( pParse->eParseMode != 0 ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 72);
}
// MCC Label 73
if(db->xAuth == 0 && db->init.busy && ( !(pParse->eParseMode != 0) ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 73);
}
// MCC Label 74
if(db->xAuth == 0 && !(db->init.busy) && ( pParse->eParseMode != 0 ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 74);
}
// MCC Label 75
if(db->xAuth == 0 && !(db->init.busy) && ( !(pParse->eParseMode != 0) ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 75);
}
// MCC Label 76
if(!(db->xAuth == 0) && db->init.busy && ( pParse->eParseMode != 0 ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 76);
}
// MCC Label 77
if(!(db->xAuth == 0) && db->init.busy && ( !(pParse->eParseMode != 0) ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 77);
}
// MCC Label 78
if(!(db->xAuth == 0) && !(db->init.busy) && ( pParse->eParseMode != 0 ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 78);
}
// MCC Label 79
if(!(db->xAuth == 0) && !(db->init.busy) && ( !(pParse->eParseMode != 0) ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 79);
}
if( db->xAuth==0 || db->init.busy || IN_SPECIAL_PARSE ){
    return SQLITE_OK;
  }

  /* EVIDENCE-OF: R-43249-19882 The third through sixth parameters to the
  ** callback are either NULL pointers or zero-terminated strings that
  ** contain additional details about the action to be authorized.
  **
  ** The following testcase() macros show that any of the 3rd through 6th
  ** parameters can be either NULL or a string. */
  testcase( zArg1==0 );
  testcase( zArg2==0 );
  testcase( zArg3==0 );
  testcase( pParse->zAuthContext==0 );

  rc = db->xAuth(db->pAuthArg, code, zArg1, zArg2, zArg3, pParse->zAuthContext
#ifdef SQLITE_USER_AUTHENTICATION
                 ,db->auth.zAuthUser
#endif
                );
  
// ABS Label 80
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 80);
}

// ROR Label 81
if((rc != 1) != (rc == 1))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 81);
}
if( rc==SQLITE_DENY ){
    
// ABS Label 82
if(pParse < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 82);
}
sqlite3ErrorMsg(pParse, "not authorized");
    pParse->rc = SQLITE_AUTH;
  }else { 
// ABS Label 83
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 83);
}

// COR Label 84
if((rc != 0 || rc != 2) != (rc != 0 && rc != 2))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 84);
}

// ROR Label 85
if((rc == 0) != (rc != 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 85);
}
// ROR Label 86
if((rc == 2) != (rc != 2))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 86);
}

// MCC Label 87
if(rc != 0 && rc != 2 ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 87);
}
// MCC Label 88
if(rc != 0 && !(rc != 2) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 88);
}
// MCC Label 89
if(!(rc != 0) && rc != 2 ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 89);
}
// MCC Label 90
if(!(rc != 0) && !(rc != 2) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 90);
}
if( rc!=SQLITE_OK && rc!=SQLITE_IGNORE ){
    rc = SQLITE_DENY;
    
// ABS Label 91
if(pParse < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 91);
}
sqliteAuthBadReturnCode(pParse);
  };}

  
// ABS Label 92
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 92);
}
return rc;
}

/*
** Push an authorization context.  After this routine is called, the
** zArg3 argument to authorization callbacks will be zContext until
** popped.  Or if pParse==0, this routine is a no-op.
*/
void sqlite3AuthContextPush(
  Parse *pParse,
  AuthContext *pContext, 
  const char *zContext
){
  assert( pParse );
  pContext->pParse = pParse;
  pContext->zAuthContext = pParse->zAuthContext;
  pParse->zAuthContext = zContext;
}

/*
** Pop an authorization context that was previously pushed
** by sqlite3AuthContextPush
*/
void sqlite3AuthContextPop(AuthContext *pContext){
  
// ABS Label 93
if(pContext->pParse < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 93);
}
if( pContext->pParse ){
    pContext->pParse->zAuthContext = pContext->zAuthContext;
    pContext->pParse = 0;
  }
}

#endif /* SQLITE_OMIT_AUTHORIZATION */
