/*
 
 Teaching: ATC I
 Exercise: T3
 Studant: Leonardo Costa (no. 62936)
 2011-2012
 SCM Repository: http://goo.gl/J8NqV
 
 Test Coverge and Algorithm
 
*/

#include <stdio.h>

#include "../code/manager.h"
#include "../code/manager.c"
#include "../code/macros.h"

#include "config_macros.h"


void test_file_config();
void test_masks();

int main(){
    
    test_file_config(FALSE);
    test_masks(TRUE);
    
    return 0;
}

void test_file_config(int run){
    
    if(!run) return;
    
    puts("Test Read config.dat");
    FILE * f_config = fopen("config.dat", "r");
    unsigned int station;
    int i = 1;
    if (f_config == NULL){
        printf("ficheiro nao existe");
    } else {
        while (!feof(f_config)){
            fscanf(f_config, "%2X", &station);
            printf("> %d -> %2X -> ID:%u, C:%u, AC:%u, AUT:%u\n", i++,
                   station, getId(station), getCelsius(station), getActive(station),
                   getAutomatic(station));
        }
    }
    puts(">\n");
    
}

void test_masks(int run){
    
    if(!run) return;
    
    int i = 0;
    //int test;
    
    puts("Test Masks");
    //test = ((_on[i] & i) && (_off[i] & (~_on[i])));
    do{
        //printf("%s index: %2X, on:%2X (%d) .. off: %2X (%d)\n", 
        //    (test ? "-" : "+"), i, _on[i], _on[i], _off[i], _off[i]);
        
        printf("§ index: %2X, on:%2X (%d) .. off: %2X (%d)\n", 
                i, _on[i], _on[i], _off[i], _off[i]);

    } while ( i++ < _8bits );
    puts(">\n");
    
    
    puts("Test Automatic Flag");
    printf("> %s\n>\n", (getAutomatic(0x20) ? MSG_OK_ERROR));
    
    puts("Test Active Flag");
    printf("> %s\n>\n", (getActive(0x40) ? MSG_OK_ERROR));
    
    puts("Test Celsius Flag");
    printf("> %s\n>\n", (getCelsius(0x80) ? MSG_OK_ERROR));
    
    puts("Test Set Celsius Flag True");
    printf("> %s\n>\n", (setCelsius(0x01, TRUE) & 0x81 ? MSG_OK_ERROR));
    
    puts("Test Set Celsius Flag False");
    printf("> %s\n>\n", (setCelsius(0xA7, FALSE) & 0x27 ? MSG_OK_ERROR));
    
    
    puts("Test ID Station for 7");
    printf(MSG_X_S, getId(0xA7), (getId(0xA7) == 7 ? MSG_OK_ERROR));
    
    puts("Test ID Station for 27");
    printf(MSG_X_S, getId(0xFB), (getId(0xFB) == 27 ? MSG_OK_ERROR));
    
}