/*
 
 Teaching: ATC I
 Exercise: T2
 Studant: Leonardo Costa (no. 62936)
 2011-2012
 SCM Repository: http://goo.gl/J8NqV
 
*/

#include <stdio.h>

#include "ui.h"


int main (int argc, const char * argv[])
{   
    // make DB file
    FILE * pFile;
    pFile = fopen (DB_FILE, "a+b");
    fclose(pFile);
    
    // start shell app
    Menu();   
    return 0;
}