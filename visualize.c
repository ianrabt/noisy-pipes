#include <stdio.h>

int main(void)
{
     int i = 1;
     int c;
     while ((c = getchar()) != EOF) {
          putchar(c);
          fprintf(stderr, "%2x ", c);
          if(!i)
               fprintf(stderr, "\n");

          i = (i + 1) % 8;
     }
}
