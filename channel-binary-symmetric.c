#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/errno.h>
#include <stdbool.h>
#include <assert.h>

void print_usage(char *program_name)
{
     fprintf(stderr, "Usage: %s FREQUENCY\n", program_name);
}

/*
 * Assumes random() has been setup appropriately. `frequency_true' is
 * probability this function returns true.
 */
bool random_bool(float frequency_true) {
     /*
      * POSIX random: returns in the range from 0 to (2**31)−1. Is
      * uniformly distrubted.
      *
      * Actual value of LONG_MAX is platform dependant.
      */
     const long random_max = 2147483647;

     return random() < random_max * frequency_true;
}

/*
 * Assumes random() has been setup appropriately.
 */
char flip_bits(char c, float frequency) {
     assert(0 <= frequency && frequency <= 1);

     // special cases
     if (frequency == 0)
          return c;
     if (frequency == 1)
          return ~c;

     int cbit = CHAR_BIT;
     for(int i = 0; i < CHAR_BIT; i++) {
          bool flip_bit = random_bool(frequency);
          if (flip_bit)
               c ^= (1 << i);
     }

     return c;
}

int main(int argc, char** argv) {
     if (argc != 2) {
          print_usage(argv[0]);
          exit(EXIT_FAILURE);
     }

     // convert frequency argument to float.
     errno = 0;
     char *endptr;
     float frequency = strtof(argv[1], &endptr);

     // If no conversion is performed, zero is returned and the value of nptr is
     // stored in the location referenced by endptr. Overflow is signalled by
     // storing ERANGE in errno.
     bool conversion_failure =
         (errno == ERANGE) || (frequency == 0 && argv[1] == endptr);

     if (conversion_failure || frequency < 0 || frequency > 1) {
          fprintf(stderr,
                  "%s is not a valid decimal (must be between 0.0 and 1.0)\n",
                  argv[1]);
          exit(EXIT_FAILURE);
     }

     // TODO support passing a seed as an argument.
     srandomdev();
     int c;
     while ((c = getchar()) != EOF) {
          putchar(flip_bits(c, frequency));
     }
}
