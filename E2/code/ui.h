/*
 
 Teaching: ATC I
 Exercise: T2
 Studant: Leonardo Costa (no. 62936)
 2011-2012
 SCM Repository: http://goo.gl/J8NqV
 
*/

#ifndef _BIBLO_UI_SHELL_
#define _BIBLO_UI_SHELL_

#include "manager.h"

void Inputs(char *in, const char pattern[], const char msg[], int size, const int force_size);
void Inputd(void *in, const char pattern[], const char msg[]);

void Menu();
void Inputbook(t_book * book, int id_show);
void Insertbook();
void Editbook();
void Deletebook();
void Listbooks();
void Searchbook();
void Showbook(t_book book);

void Showtotal(int records);

#endif