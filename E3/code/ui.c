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
#include "manager.h"

#define TRUE 1
#define FALSE 0


void inputs(char *in, const char pattern[], const char msg[], int size, const int force_size)
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


void inputd(void *in, const char pattern[], const char msg[])
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



void menu(){
    int run = TRUE;
    int opt;
    
    while(run){
        printf("1) Listar Estacao\n");
        printf("2) Inserir/Editar Estacao\n");
        printf("3) Listar Automatico\n");
        printf("4) Listar Manual\n");
        printf("\n");
        printf("0) Sair\n");
        printf("\n");
        inputd( &opt, "%d", "\nDigite a opcao? " );
        
        switch( opt )
        {
          case 1:
            showStations();
            break;      
          case 2:
            edit();
            break;

          case 3:
            readTemperatureAutomatic();
            break;

          case 4:
            readTemperatureManual();
            break;
          case 0:
            run = FALSE;
            break;
        }
    }
}

void edit(){
    
    t_station s;
    int id;
    int automatic = -1;
    int active = -1;
    int celsius = -1;
    
    showStations();
    
    puts("formato:(ID decimal de 0..31) (automatico 1/0) (active 1/0) (celsius 1/0)");
    scanf("%u %d %d %d", &id, &automatic, &active, &celsius);
    
    if(id>=0 && id<SIZE_STATION_ID && automatic!=-1 && active!=-1 && celsius!=-1){    
        s.id = id;
        s.automatic = automatic ? 32 : 0;
        s.active = active ? 64 : 0;
        s.celsius = celsius ? 128 : 0;
        
        setStation(s);
        showStations();
        saveStations();
    } else {
        puts("> Erro de formata ou ID fora da gama\n");
    }

}