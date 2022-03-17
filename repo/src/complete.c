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
** An tokenizer for SQL
**
** This file contains C code that implements the sqlite3_complete() API.
** This code used to be part of the tokenizer.c source file.  But by
** separating it out, the code will be automatically omitted from
** static links that do not use it.
*/
#include "sqliteInt.h"
#ifndef SQLITE_OMIT_COMPLETE

/*
** This is defined in tokenize.c.  We just have to import the definition.
*/
#ifndef SQLITE_AMALGAMATION
#ifdef SQLITE_ASCII
#define IdChar(C)  ((sqlite3CtypeMap[(unsigned char)C]&0x46)!=0)
#endif
#ifdef SQLITE_EBCDIC
extern const char sqlite3IsEbcdicIdChar[];
#define IdChar(C)  (((c=C)>=0x42 && sqlite3IsEbcdicIdChar[c-0x40]))
#endif
#endif /* SQLITE_AMALGAMATION */


/*
** Token types used by the sqlite3_complete() routine.  See the header
** comments on that procedure for additional information.
*/
#define tkSEMI    0
#define tkWS      1
#define tkOTHER   2
#ifndef SQLITE_OMIT_TRIGGER
#define tkEXPLAIN 3
#define tkCREATE  4
#define tkTEMP    5
#define tkTRIGGER 6
#define tkEND     7
#endif

/*
** Return TRUE if the given SQL string ends in a semicolon.
**
** Special handling is require for CREATE TRIGGER statements.
** Whenever the CREATE TRIGGER keywords are seen, the statement
** must end with ";END;".
**
** This implementation uses a state machine with 8 states:
**
**   (0) INVALID   We have not yet seen a non-whitespace character.
**
**   (1) START     At the beginning or end of an SQL statement.  This routine
**                 returns 1 if it ends in the START state and 0 if it ends
**                 in any other state.
**
**   (2) NORMAL    We are in the middle of statement which ends with a single
**                 semicolon.
**
**   (3) EXPLAIN   The keyword EXPLAIN has been seen at the beginning of 
**                 a statement.
**
**   (4) CREATE    The keyword CREATE has been seen at the beginning of a
**                 statement, possibly preceded by EXPLAIN and/or followed by
**                 TEMP or TEMPORARY
**
**   (5) TRIGGER   We are in the middle of a trigger definition that must be
**                 ended by a semicolon, the keyword END, and another semicolon.
**
**   (6) SEMI      We've seen the first semicolon in the ";END;" that occurs at
**                 the end of a trigger definition.
**
**   (7) END       We've seen the ";END" of the ";END;" that occurs at the end
**                 of a trigger definition.
**
** Transitions between states above are determined by tokens extracted
** from the input.  The following tokens are significant:
**
**   (0) tkSEMI      A semicolon.
**   (1) tkWS        Whitespace.
**   (2) tkOTHER     Any other SQL token.
**   (3) tkEXPLAIN   The "explain" keyword.
**   (4) tkCREATE    The "create" keyword.
**   (5) tkTEMP      The "temp" or "temporary" keyword.
**   (6) tkTRIGGER   The "trigger" keyword.
**   (7) tkEND       The "end" keyword.
**
** Whitespace never causes a state transition and is always ignored.
** This means that a SQL string of all whitespace is invalid.
**
** If we compile with SQLITE_OMIT_TRIGGER, all of the computation needed
** to recognize the end of a trigger can be omitted.  All we have to do
** is look for a semicolon that is not part of an string or comment.
*/
int sqlite3_complete(const char *zSql){
  u8 state = 0;   /* Current state, using numbers defined in header comment */
  u8 token;       /* Value of the next token */

#ifndef SQLITE_OMIT_TRIGGER
  /* A complex statement machine used to detect the end of a CREATE TRIGGER
  ** statement.  This is the normal case.
  */
  static const u8 trans[8][8] = {
                     /* Token:                                                */
     /* State:       **  SEMI  WS  OTHER  EXPLAIN  CREATE  TEMP  TRIGGER  END */
     /* 0 INVALID: */ {    1,  0,     2,       3,      4,    2,       2,   2, },
     /* 1   START: */ {    1,  1,     2,       3,      4,    2,       2,   2, },
     /* 2  NORMAL: */ {    1,  2,     2,       2,      2,    2,       2,   2, },
     /* 3 EXPLAIN: */ {    1,  3,     3,       2,      4,    2,       2,   2, },
     /* 4  CREATE: */ {    1,  4,     2,       2,      2,    4,       5,   2, },
     /* 5 TRIGGER: */ {    6,  5,     5,       5,      5,    5,       5,   5, },
     /* 6    SEMI: */ {    6,  6,     5,       5,      5,    5,       5,   7, },
     /* 7     END: */ {    1,  7,     5,       5,      5,    5,       5,   5, },
  };
#else
  /* If triggers are not supported by this compile then the statement machine
  ** used to detect the end of a statement is much simpler
  */
  static const u8 trans[3][3] = {
                     /* Token:           */
     /* State:       **  SEMI  WS  OTHER */
     /* 0 INVALID: */ {    1,  0,     2, },
     /* 1   START: */ {    1,  1,     2, },
     /* 2  NORMAL: */ {    1,  2,     2, },
  };
#endif /* SQLITE_OMIT_TRIGGER */

#ifdef SQLITE_ENABLE_API_ARMOR
  if( zSql==0 ){
    (void)SQLITE_MISUSE_BKPT;
    return 0;
  }
#endif

  
// ABS Label 7
if(*zSql < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 7);
}
while( *zSql ){
    switch( *zSql ){
      case ';': {  /* A semicolon */
        token = tkSEMI;
        break;
      }
      case ' ':
      case '\r':
      case '\t':
      case '\n':
      case '\f': {  /* White space is ignored */
        token = tkWS;
        break;
      }
      case '/': {   /* C-style comments */
        
// ROR Label 9
if((zSql[1] == '*') != (zSql[1] != '*'))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 9);
}
if( zSql[1]!='*' ){
          token = tkOTHER;
          break;
        }
        zSql += 2;
        
// COR Label 10
if((zSql[0] || (zSql[0] != '*' || zSql[1] != '/')) != (zSql[0] && (zSql[0] != '*' || zSql[1] != '/')))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 10);
}

// MCC Label 11
if(zSql[0] && ( zSql[0] != '*' && zSql[1] != '/' ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 11);
}
// MCC Label 12
if(zSql[0] && ( zSql[0] != '*' && !(zSql[1] != '/') ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 12);
}
// MCC Label 13
if(zSql[0] && ( !(zSql[0] != '*') && zSql[1] != '/' ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 13);
}
// MCC Label 14
if(zSql[0] && ( !(zSql[0] != '*') && !(zSql[1] != '/') ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 14);
}
// MCC Label 15
if(!(zSql[0]) && ( zSql[0] != '*' && zSql[1] != '/' ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 15);
}
// MCC Label 16
if(!(zSql[0]) && ( zSql[0] != '*' && !(zSql[1] != '/') ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 16);
}
// MCC Label 17
if(!(zSql[0]) && ( !(zSql[0] != '*') && zSql[1] != '/' ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 17);
}
// MCC Label 18
if(!(zSql[0]) && ( !(zSql[0] != '*') && !(zSql[1] != '/') ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 18);
}
while( zSql[0] && (zSql[0]!='*' || zSql[1]!='/') ){ zSql++; };
// COR Label 19
if((zSql[0] || (zSql[0] != '*' || zSql[1] != '/')) != (zSql[0] && (zSql[0] != '*' || zSql[1] != '/')))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 19);
}

// MCC Label 20
if(zSql[0] && ( zSql[0] != '*' && zSql[1] != '/' ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 20);
}
// MCC Label 21
if(zSql[0] && ( zSql[0] != '*' && !(zSql[1] != '/') ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 21);
}
// MCC Label 22
if(zSql[0] && ( !(zSql[0] != '*') && zSql[1] != '/' ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 22);
}
// MCC Label 23
if(zSql[0] && ( !(zSql[0] != '*') && !(zSql[1] != '/') ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 23);
}
// MCC Label 24
if(!(zSql[0]) && ( zSql[0] != '*' && zSql[1] != '/' ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 24);
}
// MCC Label 25
if(!(zSql[0]) && ( zSql[0] != '*' && !(zSql[1] != '/') ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 25);
}
// MCC Label 26
if(!(zSql[0]) && ( !(zSql[0] != '*') && zSql[1] != '/' ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 26);
}
// MCC Label 27
if(!(zSql[0]) && ( !(zSql[0] != '*') && !(zSql[1] != '/') ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 27);
}

        
// ROR Label 28
if((zSql[0] != 0) != (zSql[0] == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 28);
}
if( zSql[0]==0 ) { return 0;
}
        zSql++;
        token = tkWS;
        break;
      }
      case '-': {   /* SQL-style comments from "--" to end of line */
        
// ROR Label 29
if((zSql[1] == '-') != (zSql[1] != '-'))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 29);
}
if( zSql[1]!='-' ){
          token = tkOTHER;
          break;
        }
        
// COR Label 30
if((*zSql || *zSql != '\n') != (*zSql && *zSql != '\n'))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 30);
}

// ROR Label 31
if((*zSql == '\n') != (*zSql != '\n'))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 31);
}

// MCC Label 32
if(*zSql && *zSql != '\n' ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 32);
}
// MCC Label 33
if(*zSql && !(*zSql != '\n') ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 33);
}
// MCC Label 34
if(!(*zSql) && *zSql != '\n' ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 34);
}
// MCC Label 35
if(!(*zSql) && !(*zSql != '\n') ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 35);
}
while( *zSql && *zSql!='\n' ){ zSql++; };
// COR Label 36
if((*zSql || *zSql != '\n') != (*zSql && *zSql != '\n'))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 36);
}

// ROR Label 37
if((*zSql == '\n') != (*zSql != '\n'))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 37);
}

// MCC Label 38
if(*zSql && *zSql != '\n' ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 38);
}
// MCC Label 39
if(*zSql && !(*zSql != '\n') ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 39);
}
// MCC Label 40
if(!(*zSql) && *zSql != '\n' ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 40);
}
// MCC Label 41
if(!(*zSql) && !(*zSql != '\n') ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 41);
}

        
// ROR Label 42
if((*zSql != 0) != (*zSql == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 42);
}
if( *zSql==0 ) { 
// ROR Label 43
if((state != 1) != (state == 1))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 43);
}
return state==1;
}
        token = tkWS;
        break;
      }
      case '[': {   /* Microsoft-style identifiers in [...] */
        zSql++;
        
// COR Label 44
if((*zSql || *zSql != ']') != (*zSql && *zSql != ']'))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 44);
}

// ROR Label 45
if((*zSql == ']') != (*zSql != ']'))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 45);
}

// MCC Label 46
if(*zSql && *zSql != ']' ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 46);
}
// MCC Label 47
if(*zSql && !(*zSql != ']') ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 47);
}
// MCC Label 48
if(!(*zSql) && *zSql != ']' ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 48);
}
// MCC Label 49
if(!(*zSql) && !(*zSql != ']') ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 49);
}
while( *zSql && *zSql!=']' ){ zSql++; };
// COR Label 50
if((*zSql || *zSql != ']') != (*zSql && *zSql != ']'))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 50);
}

// ROR Label 51
if((*zSql == ']') != (*zSql != ']'))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 51);
}

// MCC Label 52
if(*zSql && *zSql != ']' ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 52);
}
// MCC Label 53
if(*zSql && !(*zSql != ']') ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 53);
}
// MCC Label 54
if(!(*zSql) && *zSql != ']' ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 54);
}
// MCC Label 55
if(!(*zSql) && !(*zSql != ']') ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 55);
}

        
// ROR Label 56
if((*zSql != 0) != (*zSql == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 56);
}
if( *zSql==0 ) { return 0;
}
        token = tkOTHER;
        break;
      }
      case '`':     /* Grave-accent quoted symbols used by MySQL */
      case '"':     /* single- and double-quoted strings */
      case '\'': {
        int c = *zSql;
        zSql++;
        
// ABS Label 57
if(c < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 57);
}

// COR Label 58
if((*zSql || *zSql != c) != (*zSql && *zSql != c))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 58);
}

// ROR Label 59
if((*zSql == c) != (*zSql != c))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 59);
}

// MCC Label 60
if(*zSql && *zSql != c ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 60);
}
// MCC Label 61
if(*zSql && !(*zSql != c) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 61);
}
// MCC Label 62
if(!(*zSql) && *zSql != c ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 62);
}
// MCC Label 63
if(!(*zSql) && !(*zSql != c) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 63);
}
while( *zSql && *zSql!=c ){ zSql++; };
// ABS Label 64
if(c < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 64);
}

// COR Label 65
if((*zSql || *zSql != c) != (*zSql && *zSql != c))  {
asm volatile (""::: "memory");
	report_label_coverage("COR", 65);
}

// ROR Label 66
if((*zSql == c) != (*zSql != c))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 66);
}

// MCC Label 67
if(*zSql && *zSql != c ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 67);
}
// MCC Label 68
if(*zSql && !(*zSql != c) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 68);
}
// MCC Label 69
if(!(*zSql) && *zSql != c ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 69);
}
// MCC Label 70
if(!(*zSql) && !(*zSql != c) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 70);
}

        
// ROR Label 71
if((*zSql != 0) != (*zSql == 0))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 71);
}
if( *zSql==0 ) { return 0;
}
        token = tkOTHER;
        break;
      }
      default: {
#ifdef SQLITE_EBCDIC
        unsigned char c;
#endif
        
// MCC Label 72
if(( (sqlite3CtypeMap[(unsigned char)(u8)*zSql] & 70) != 0 ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 72);
}
// MCC Label 73
if(( !((sqlite3CtypeMap[(unsigned char)(u8)*zSql] & 70) != 0) ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 73);
}
if( IdChar((u8)*zSql) ){
          /* Keywords and unquoted identifiers */
          int nId;
          nId = 1;

// MCC Label 74
if(( (sqlite3CtypeMap[(unsigned char)zSql[nId]] & 70) != 0 ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 74);
}
// MCC Label 75
if(( !((sqlite3CtypeMap[(unsigned char)zSql[nId]] & 70) != 0) ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 75);
}
for(; IdChar(zSql[nId]); nId++){};
// MCC Label 76
if(( (sqlite3CtypeMap[(unsigned char)zSql[nId]] & 70) != 0 ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 76);
}
// MCC Label 77
if(( !((sqlite3CtypeMap[(unsigned char)zSql[nId]] & 70) != 0) ) ) {
asm volatile (""::: "memory");
	report_label_coverage("MCC", 77);
}

#ifdef SQLITE_OMIT_TRIGGER
          token = tkOTHER;
#else
          switch( *zSql ){
            case 'c': case 'C': {
              if( nId==6 && sqlite3StrNICmp(zSql, "create", 6)==0 ){
                token = tkCREATE;
              }else{
                token = tkOTHER;
              }
              break;
            }
            case 't': case 'T': {
              if( nId==7 && sqlite3StrNICmp(zSql, "trigger", 7)==0 ){
                token = tkTRIGGER;
              }else { if( nId==4 && sqlite3StrNICmp(zSql, "temp", 4)==0 ){
                token = tkTEMP;
              }else { if( nId==9 && sqlite3StrNICmp(zSql, "temporary", 9)==0 ){
                token = tkTEMP;
              }else{
                token = tkOTHER;
              };}
;}

              break;
            }
            case 'e':  case 'E': {
              if( nId==3 && sqlite3StrNICmp(zSql, "end", 3)==0 ){
                token = tkEND;
              }else {
#ifndef SQLITE_OMIT_EXPLAIN
              if( nId==7 && sqlite3StrNICmp(zSql, "explain", 7)==0 ){
                token = tkEXPLAIN;
              }else
#endif
              {
                token = tkOTHER;
              };}

              break;
            }
            default: {
              token = tkOTHER;
              break;
            }
          }
#endif /* SQLITE_OMIT_TRIGGER */
          zSql += nId-1;
        }else{
          /* Operators and special symbols */
          token = tkOTHER;
        }
        break;
      }
    }
    state = trans[state][token];
    zSql++;
  };
// ABS Label 8
if(*zSql < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 8);
}

  
// ROR Label 78
if((state != 1) != (state == 1))  {
asm volatile (""::: "memory");
	report_label_coverage("ROR", 78);
}
return state==1;
}

#ifndef SQLITE_OMIT_UTF16
/*
** This routine is the same as the sqlite3_complete() routine described
** above, except that the parameter is required to be UTF-16 encoded, not
** UTF-8.
*/
int sqlite3_complete16(const void *zSql){
  sqlite3_value *pVal;
  char const *zSql8;
  int rc;

#ifndef SQLITE_OMIT_AUTOINIT
  rc = sqlite3_initialize();
  
// ABS Label 82
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 82);
}
if( rc ) { 
// ABS Label 83
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 83);
}
return rc;
}
#endif
  pVal = sqlite3ValueNew(0);
  
// ABS Label 79
if(pVal < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 79);
}

// ABS Label 80
if(zSql < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 80);
}
sqlite3ValueSetStr(pVal, -1, zSql, SQLITE_UTF16NATIVE, SQLITE_STATIC);
  zSql8 = sqlite3ValueText(pVal, SQLITE_UTF8);
  
// ABS Label 84
if(zSql8 < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 84);
}
if( zSql8 ){
    rc = sqlite3_complete(zSql8);
  }else{
    rc = SQLITE_NOMEM_BKPT;
  }
  
// ABS Label 81
if(pVal < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 81);
}
sqlite3ValueFree(pVal);
  
// ABS Label 85
if(rc < 0)  {
asm volatile (""::: "memory");
	report_label_coverage("ABS", 85);
}

// AOR Label 86
if(rc | 255 != rc & 255)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 86);
}
// AOR Label 87
if(rc ^ 255 != rc & 255)  {
asm volatile (""::: "memory");
	report_label_coverage("AOR", 87);
}
return rc & 0xff;
}
#endif /* SQLITE_OMIT_UTF16 */
#endif /* SQLITE_OMIT_COMPLETE */
