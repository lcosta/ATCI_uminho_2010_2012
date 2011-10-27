/*
 
 Teaching: ATC I
 Exercise: T2
 Studant: Leonardo Costa (no. 62936)
 2011-2012
 SCM Repository: http://goo.gl/J8NqV
 
*/

#ifndef _BIBLO_MANAGER_
#define _BIBLO_MANAGER_

#define DB_FILE "biblo.db"

/* ----- define filds size ----- */
#define SIZE_ID 20
#define SIZE_CDU 20
#define SIZE_TITLE 100
#define SIZE_AUTHOR 60
#define SIZE_DESCRIPTION 200
#define SIZE_PUBLISHER 20
/* ----------------------------- */

/* --- define filds pattern ---- */
#define P_ID "%[A-Z0-9]"
#define P_CDU "%[A-Z0-9.]"
#define P_TEXT "%[ a-zA-Z0-9+*/-.]"
/* ----------------------------- */

#define FALSE 0
#define TRUE 1




typedef struct t_book
{
  char id[SIZE_ID+1];
  char cdu[SIZE_CDU+1];
  
  char title[SIZE_TITLE+1];
  char author[SIZE_AUTHOR+1];
  char publisher[SIZE_PUBLISHER+1];
  char description[SIZE_DESCRIPTION+1];
  int year;
  int qtd;
  
  char status; // d - delete, a - active

} t_book;

int Findsubstr(char *listPointer, char *itemPointer);

int Insert(t_book * book);
int Edit(char id[], t_book * book);
int Delete(char id[]);
int List();
int Search(char s[]);

#endif

