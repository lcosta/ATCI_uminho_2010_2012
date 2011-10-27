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
#include "manager.h"
#include "ui.h"


int Findsubstr(char *listPointer, char *itemPointer){
  int t;
  char *p, *p2;

  for(t=0; listPointer[t]; t++) {
    p = &listPointer[t];
    p2 = itemPointer;

    while(*p2 && *p2==*p) {
      p++;
      p2++;
    }
    if(!*p2) return t;
  }
   return -1;
}


int Insert(t_book * book){

    FILE * pFile;
    pFile = fopen (DB_FILE, "r+b");
    if (pFile!=NULL){
        book->status = 'a';
        
        // insert in clear space
        t_book bookR;
        int i=1;
        int run=TRUE;
        int exist_id=FALSE;
        
        // test if id exist
        while (!feof(pFile) && fread (&bookR,1, sizeof(t_book),pFile)) {
            if(strcmp(bookR.id, book->id) == 0){
                exist_id=TRUE;
            }
        }
        
        if(!exist_id){
            rewind(pFile);
            while (run && !feof(pFile) && fread (&bookR,1, sizeof(t_book),pFile)) {
                if(bookR.status == 'd'){
                    fseek( pFile , (sizeof(t_book) * i)-sizeof(t_book) , SEEK_SET );
                    fwrite (book , 1 , sizeof(t_book) , pFile);
                    run=FALSE;
                } else {
                    i++;
                }
            }
        
            // insert in EOF
            if(run){
                fwrite (book , 1 , sizeof(t_book) , pFile );
            }
            fclose (pFile);
            return 1;
        } else {
            return -1;
        }
    }
    return 0;
}

int Edit(char id[], t_book * book){
    
    FILE * pFile;
    pFile = fopen (DB_FILE, "r+b");
    
    if (pFile!=NULL){
        t_book bookR;
        book->status = 'a';
        int i=1;
        while (!feof(pFile) && fread (&bookR,1, sizeof(t_book),pFile)) {

            if(strcmp(bookR.id, id) == 0){
                fseek (pFile , (sizeof(t_book) * i)-sizeof(t_book) , SEEK_SET);
                strcpy(book->id, bookR.id);
                fwrite (book , 1 , sizeof(t_book) , pFile);
                fclose(pFile);
                return 1;
            } else {
                i++;
            }

        }    
        fclose(pFile);

        return -1;
    }
    return 0;
}

int Delete(char id[]){
    
    FILE * pFile;
    pFile = fopen (DB_FILE, "r+b");
    
    if (pFile!=NULL){
        t_book bookR;
        int i=1;
        int run=TRUE;
        while (run && !feof(pFile) && fread (&bookR,1, sizeof(t_book),pFile)) {

            if(strcmp(bookR.id, id) == 0){
                fseek ( pFile , (sizeof(t_book) * i)-sizeof(t_book) , SEEK_SET );
                bookR.status = 'd';
                fwrite (&bookR , 1 , sizeof(t_book) , pFile);
                run=FALSE;
            } else {
                i++;
            }

        }    
        fclose (pFile);

        return 1;
    }
    return 0;
}

int List(){
    FILE * pFile;
    pFile = fopen (DB_FILE, "rb");
    
    if (pFile!=NULL){
        t_book book;
        int i = 0;
        while (!feof(pFile) && fread (&book,1, sizeof(t_book),pFile)) {
            if(book.status == 'a'){
                Showbook(book);
                i++;
            }
        }    
        fclose (pFile);
        Showtotal(i);
        return 1;
    }
    
    return 0;
}

int Search(char s[]){
    FILE * pFile;
    pFile = fopen (DB_FILE, "rb");
    if (pFile!=NULL){
        t_book book;
        int i = 0;
        while (!feof(pFile) && fread (&book,1, sizeof(t_book),pFile)) {
            if((book.status == 'a') && ((Findsubstr(book.title, s) != -1) || (Findsubstr(book.author, s) != -1) ||
                    (Findsubstr(book.description, s) != -1) || (Findsubstr(book.publisher, s) != -1) ||
                     (Findsubstr(book.id, s) != -1) || (Findsubstr(book.cdu, s) != -1) || 
                     book.year == atoi(s))){
                         
                Showbook(book);
                i++;
            }
        }    
        fclose (pFile);
        Showtotal(i);
        return 1;
    }
    
    return 0;
}

