/*
 
 Teaching: ATC I
 Exercise: T1
 Studant: Leonardo Costa (no. 62936)
 2011-2012
 SCM Repository: http://goo.gl/J8NqV
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eng_notation_si_pref.h"

#define FALSE 0
#define TRUE 1

#define SERIE_L 's'
#define SERIE_H 'S'
#define PARALLEL_L 'p'
#define PARALLEL_H 'P'
#define PARALLEL_H 'P'
#define INPUT "%[ 0-9.psPS()]"
#define OHMS "Ω" /* If this does not work reliably on your system, use the conventional surrogate "ohms" for "Ω" */


int isNum(char c);
void input_s(char *in, const char pattern[], const char msg[], int size, const int force_size);
float calc_ParallelSerie(char ex[]);


int main (int argc, const char * argv[])
{
  
  float res_eq = 0.0;
  char ex[10000];
  
  if (argc > 1 && argv[1] && argv[2] && argv[1][0] == '-' && argv[1][1] == 'p') {
    
    strcpy(ex, argv[2]);
    res_eq = calc_ParallelSerie(ex);
    
    if(argv[1][2] == 'f')
    {
      printf("%s%s", eng(res_eq, 4, 0), OHMS);
    }
    else
    {
      printf("%.2f", res_eq);
    }
  }
  else {
    printf( "\nTeaching: ATC I\n" );
    printf( "Exercise: T1\n" );
    printf( "Studant: Leonardo Costa (no. 62936)\n" );
    printf( "Year: 2011-2012\n" );

    printf("\nHELP:");
    printf("\n\texpression syntax");
    printf("\n\t\t%c | %c - parallel", PARALLEL_L, PARALLEL_H);
    printf("\n\t\t%c | %c - serie", SERIE_L, SERIE_H);
    printf("\n\n\tfor command-line pipe use");
    printf("\n\t   req -p \"EXPRESSION\"");
    printf("\n\tOR format in engineering notation");
    printf("\n\t   req -pf \"EXPRESSION\"");
    printf("\n\n\tEXAMPLES:");
    printf("\n\treq -p \"(40 p 50) s (85.9 p 45)\" > file.txt # result = \"51.75\"");
    printf("\n\treq -pf \"(25000 S 1000) P 3500\" > file.txt # result = \"3.070 k%s\"", OHMS);
    printf("\n\n");
    input_s(ex, INPUT, "Input Parallel-Serie Expression:\n", 10000, 0);
    res_eq = calc_ParallelSerie(ex);
    printf("\n-> equivalent resistor: %s%s\n", eng(res_eq, 4, 0), OHMS);
  }
  
  return 0;
}


int isNum(char c){
  switch (c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
      return TRUE;
      break;
    default:
      return FALSE;
      break;
  }
}

void input_s(char *in, const char pattern[], const char msg[], int size, const int force_size)
{
  /* set char size crop */
  size -= 1;
  
  int run = 1;
  char reader[size];
  
  printf ("%s", msg);
  while( run )
  {    
    if( (scanf( pattern, reader ) > 0) && ( !force_size || (strlen(reader) == size)) )
    {
      run = 0;
    }
    else
    {
      printf("Insertion error . Try again!\n%s", msg);
    }
    
    /* clear buffer */
    while(getchar()!=(int)'\n');
  }
  
  /* fit string size */
  strncpy(in, reader, size);
  
  
}


float calc_ParallelSerie(char ex[]){
  
  char subex[strlen(ex)];
  
  int i=-1;
  int f=0;
  int open = 0;
  int close = 0;
  int open_idx = -1;
  int close_idx = -1;
  int subex_idx = 0;
  
  float num1 = 0.0;
  float num2 = 0.0;
  char num_parse[100] = "";
  int num_capture = 1;
  
  char ps[2] = " \0";
  char cmd;
  
  while(TRUE){
    i++;
    
    /* end of expression */
    if(ex[i] == '\0'){
      break; 
    }
    else {
      if(ex[i] == '(')
      {        
        open_idx = i;
        
        /* parse expression */
        while(TRUE)
        {

          /* counter opened and closed brackets */
          if(ex[i] == '(')
          {
            open++;
          }
          else if(ex[i] == ')')
          {
            close++;
          }

          /* exectrat sub-expression */
          if(open > 0 && open == close){
            
            close_idx = i;
            
            subex_idx = 0;
            for(f = open_idx+1; f <= (close_idx-1); f++)
            {
              subex[subex_idx] = ex[f];
              subex_idx++;
            }
            
            subex[subex_idx+1] = '\0';
            
            if(num_capture == 1)
            {
              num1 = calc_ParallelSerie(subex);
              num_capture = 2;
            }
            else if(num_capture == 2)
            {
              num2 = calc_ParallelSerie(subex);
              num_capture = -1;
            }
            
            /* reset control vars */
            open = 0;
            close = 0;
            open_idx = -1;
            close_idx = -1;
            break;
            
          }
          i++;
        }
        
      }
      
      /* parse char number */
      else if(isNum(ex[i]))
      {
        
        ps[0] = ex[i];
        ps[1] = '\0';
        strcat(num_parse, ps);
        
        /* check end of number */
        if(isNum(ex[i+1]) == FALSE){
          if(num_capture == 1)
          {
            num1 = atof(num_parse);
            num_capture = 2;
            num_parse[0] = '\0';
          }
          else if(num_capture == 2)
          {
            num2 = atof(num_parse);
            num_capture = -1;
            num_parse[0] = '\0';
          }
        } 
      }
      
      /* get operator */
      else if(ex[i] == SERIE_L || ex[i] == SERIE_H || ex[i] == PARALLEL_L || ex[i] == PARALLEL_H)
      {
        cmd = ex[i];
      }
    }
    
    /* calculate equivalent resistor */
    if(num_capture == -1)
    { 
      if(cmd == SERIE_L || cmd == SERIE_L)
      {
        num1 = num1 + num2;
      }
      else if(cmd == PARALLEL_L || cmd == PARALLEL_H)
      {
        num1 = (num1*num2)/(num1+num2);
      }
      
      num_capture = 2;
    }
    
    
  }/* end while */
  
  return num1;
}