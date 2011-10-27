/*
 
 Teaching: ATC I
 Exercise: T2
 Studant: Leonardo Costa (no. 62936)
 2011-2012
 SCM Repository: http://goo.gl/J8NqV
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"


void Inputs(char *in, const char pattern[], const char msg[], int size, const int force_size)
{
  /* set char size crop */
  size -= 1;
  
  int run = TRUE;
  char reader[size];
  
  printf ("%s", msg);
  while( run )
  {    
    if( (scanf( pattern, reader ) > 0) && ( !force_size || (strlen(reader) == size)) )
    {
      run = FALSE;
    }
    else
    {
      printf("Erro de inserção. Tente de novo!\n%s", msg);
    }
    
    /* clear buffer */
    while(getchar()!=(int)'\n');
  }
  
  /* fit string size */
  strncpy(in, reader, size);
  
  
}


void Inputd(void *in, const char pattern[], const char msg[])
{
  int run = TRUE;
  
  printf ("%s", msg);
  while( run )
  {
    if( (scanf( pattern, in ) > 0) )
    {
      run = FALSE;
    }
    else
    {
      printf("Erro de inserção. Tente de novo!\n%s", msg);
    }
    
    /* clear buffer */
    while(getchar()!=(int)'\n');
  }
}


void Menu(){
    int run = TRUE;
    int opt;
    
    while(run){
        printf("1) Inserir livro\n");
        printf("2) Editar livro\n");
        printf("3) Apagar livro\n");
        printf("4) Listar livros\n");
        printf("5) Pesquisar livros (procura em todos os campos)\n");
        printf("\n");
        printf("0) Sair\n");
        printf("\n");
        Inputd( &opt, "%d", "\nDigite a opcao? " );
        
        switch( opt )
        {
          case 1:
            Insertbook();
            break;

          case 2:
            Editbook();
            break;

          case 3:
            Deletebook();
            break;

          case 4:
            Listbooks();
            break;

          case 5:
            Searchbook();
            break;

          case 0:
            run = FALSE;
            break;
        }
    }
}

void Inputbook(t_book * book){
    
    Inputs(book->id, P_ID, "Digite o ID? ", SIZE_ID, FALSE);
    Inputs(book->cdu, P_CDU, "Digite o CDU? ", SIZE_CDU, FALSE);
    Inputs(book->title, P_TEXT, "Digite o titulo? ", SIZE_TITLE, FALSE);
    Inputs(book->author, P_TEXT, "Digite o autor? ", SIZE_AUTHOR, FALSE);
    Inputs(book->publisher, P_TEXT, "Digite a editora? ", SIZE_PUBLISHER, FALSE);
    Inputs(book->description, P_TEXT, "Digite a descricao? ", SIZE_DESCRIPTION, FALSE);
    Inputd(&(book->year), "%d", "Digite o ano da publicacao? ");
    Inputd(&(book->qtd), "%d", "Digite a quantidade? ");
    
}

void Insertbook(){
    t_book book;
    Inputbook(&book);
    
    int status = Insert(&book);
    
    if(status == 1){
        printf("Livro inserido com sucesso.\n\n");
    }
    else if(status == -1){
        printf("\nJa existe livro com o ID '%s'. Tente de novo\n\n", book.id);
    }
    else {
        printf("Error ao tentar guardar os dados.\n");
    }
    
    
}

void Editbook(){
    char id[SIZE_ID];
    Inputs(id, P_TEXT, "Qual o ID do livro a editar? ", SIZE_ID, FALSE);
    t_book book;
    Inputbook(&book);
    if(!Edit(id, &book)){
        printf("Error ao tentar guardar os dados.\n");
    }
}

void Deletebook(){
    char id[SIZE_ID];
    Inputs(id, P_TEXT, "Qual o ID do livro a apagar? ", SIZE_ID, FALSE);

    if(!Delete(id)){
        printf("Error ao tentar apagar.\n");
    } else {
        printf("Livro com o ID '%s' apagado.\n\n", id);
    }
}

void Listbooks(){
    printf("\nListar livros\n");
    printf("==================================\n");
    if(!List()){
        printf("Error ao tentar listar.\n");
    }
}

void Searchbook(){
    char s[100];
    Inputs(s, P_TEXT, "Procurar livro por? ", 100, FALSE);
    
    printf("\nListar livros por '%s'\n", s);
    printf("==================================\n");
    if(!Search(s)){
        printf("Error ao tentar listar.\n");
    }
    
}

void Showbook(t_book book){
    printf("ID: %s - CDU: %s - Ano: %d - Qtd: %d\n",
                book.id, book.cdu, book.year, book.qtd);
    printf("Autor: %s - Editor: %s\n", book.author, book.publisher);
    printf("Titulo: %s\nDescricao: %s\n-------\n", book.title, book.description);
}

void Showtotal(int records){
    if(records > 0){
        printf("Foram encontrados %d livros\n\n", records);
    } else {
        printf("Nao existe registos\n\n");
    }
}


