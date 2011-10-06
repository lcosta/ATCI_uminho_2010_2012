#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define SERIE 's'
#define PARALLEL 'p'

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

float calc_ParallelSerie(char ex[]){
  char subex[strlen(ex)];
  
  //printf("%s\n", ex);
  
  int i=-1;
  int f=0;
  int open = 0;
  int close = 0;
  int open_idx = -1;
  int close_idx = -1;
  int subex_idx = 0;
  
  float num1;
  float num2;
  char num_parse[10] = "";
  int num_capture = 1;
  
  float res_eq = 0.0;
  char ps[2] = " \0";
  char cmd;
  
  while(1){
    i++;
    
    if(ex[i] == '\0'){
      break; 
    }
    else {
      //printf("ex%i - %c\n", i, ex[i]);
      //printf("subex%i - %c\n", i, subex[i]);
      
      
      
      
      if(ex[i] == '(')
      {
        
        // colocar aqui clico para encontrar o )
        // passar i para a posicao )+1
        
        open++;
        if(open_idx == -1)
        {
          open_idx = i;
        }
      }
      else if(ex[i] == ')')
      {
        close++;
      }
      else if(isNum(ex[i]))
      {
        //printf("%c", ex[i]);
        
        
        ps[0] = ex[i];
        //ps[1] = '\0';
        strcat(num_parse, ps);
        
        if(isNum(ex[i+1]) == FALSE){
          printf("%s\n", num_parse);
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
      else if(ex[i] == SERIE || ex[i] == PARALLEL)
      {
        cmd = ex[i];
      }
      
      // exectrat
      if(open > 0 && open == close){
        
          close_idx = i;
          
          //open_idx++; // remove first ( char
          //close_idx--; // remove last ) char
          
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
          
          /*
           printf("open_idx: %i\n", open_idx);
           printf("close_idx: %i\n", close_idx);
           printf("subex: %s\n", subex);
           */
          
          // clear
          i = close_idx;
          open = 0;
          close = 0;
          open_idx = -1;
          close_idx = -1;
          /*
           subex_idx = 0;
           subex[0] = '\0';
           */
          
      }
      
      
    }
    
    // calc
    if(num_capture == -1)
    {
      //printf("req: %f %c %f", num1, cmd, num2);
      
      if(cmd == SERIE)
      {
        num1 = num1 + num2;
      }
      else if(cmd == PARALLEL)
      {
        num1 = (num1*num2)/(num1+num2);
      }
      
      
      num_capture = 2;
    }
    
    
  }// end while
  return num1;
}


int main(){
  //             0    5    1    1    2  
  //                       0    5    0
  //  char ex[] = "50 p ((20 s 40) p (70 s ((90 p 80) p (30 s 10))))";
  //  char ex[] =       "(20 s 40) p (70 s ((90 p 80) p (30 s 10))))";
  //char ex[] =                      "70.67 s ((90 p 80) p (30 s 10))";
  
  char ex[] = "(50 s 50) s (50 s 50)";
  
  //           50 p (60 p (70 s (42.35 p 40)))
  //           50 p (60 p (70 s 20.57))
  //           50 p (60 p 90.57)
  //           20.96
  
  
  
  printf("R EQ: %f\n", calc_ParallelSerie(ex));

  
  return 0;
}


/*
 
 50 p (
 (20 s 40)
 p
 (70 s 
 (
 (90 p 80)
 p
 (30 s 10)
 )
 )
 )
 
 */