/* Print a floating-point number in engineering notation */
/* Documentation: http://www.cs.tut.fi/~jkorpela/c/eng.html */

#ifndef _ENG_NOTATION_SI_PREF_H_
#define _ENG_NOTATION_SI_PREF_H_

#define MICRO "µ"

#define PREFIX_START (-24)
/* Smallest power of ten for which there is a prefix defined.
   If the set of prefixes will be extended, change this constant
   and update the table "prefix". */

#define PREFIX_END (PREFIX_START+\
(int)((sizeof(prefix)/sizeof(char *)-1)*3))

#include <stdio.h>
#include <math.h>

char *eng(double value, int digits, int numeric);

#endif