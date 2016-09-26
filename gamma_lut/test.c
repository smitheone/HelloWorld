#include <stdio.h>
#include <stdlib.h>
int main(void)
{
   char *string, *stopstring;
   double x;
   float f;
   long double ld;

   string = "3.1415926This stopped it";
   f = (float)strtof(string, &stopstring);
   printf("string = \"%s\"\n", string);
   printf("   strtof = %f\n", f);
   printf("   Stopped scan at \"%s\"\n\n", stopstring);
   string = "100ergs";
   f = strtof(string, &stopstring);
   printf("string = \"%s\"\n", string);
   printf("   strtof = %f\n", f);
   printf("   Stopped scan at \"%s\"\n\n", stopstring);

   string = "3.1415926This stopped it";
   x = strtod(string, &stopstring);
   printf("string = \"%s\"\n", string);
   printf("   strtod = %f\n", x);
   printf("   Stopped scan at \"%s\"\n\n", stopstring);
   string = "100ergs";
   x = strtod(string, &stopstring);
   printf("string = \"%s\"\n", string);
   printf("   strtod = %f\n", x);
   printf("   Stopped scan at \"%s\"\n\n", stopstring);

   string = "3.1415926This stopped it";
   ld = strtold(string, &stopstring);
   printf("string = \"%s\"\n", string);
   printf("   strtold = %lf\n", ld);
   printf("   Stopped scan at \"%s\"\n\n", stopstring);
   string = "100ergs";
   ld = strtold(string, &stopstring);
   printf("string = \"%s\"\n", string);
   printf("   strtold = %lf\n", ld);
   printf("   Stopped scan at \"%s\"\n\n", stopstring);
}
