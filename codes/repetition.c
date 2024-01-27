#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void print_usage(char *program_name)
{
     fprintf(stderr, "Usage: %s [encode/decode] REPETITIONS\n", program_name);
     fprintf(stderr, "  where REPETITIONS is an odd integer > 0.\n");
}

void encode(long repetitions) {
     int c;

     /* Repetitions can be any value, and the final output must be
        chunked in "frames" (chars.) */

     // CHAR_BIT - output_bits_filled represents how much of output
     // has been calculated.
     unsigned char output_bits_filled = 0;
     // the output "frame" mentioned earlier
     unsigned char output = 0;

     // loop through each byte of input.
     while ((c = getchar()) != EOF) {
          /* cast `c` to an unsigned char, to avoid bugs with
             implementation-defined right shifts (`>>`) of negative
             values (blanks are often filled with set sign bit) */
          const unsigned char current_c = c;
          for (int i = 0; i < CHAR_BIT; i++) {
               /* Loop through each bit of c, least to most
                  significant.

                  We then build up output, least to most significant
                  bit, with repetitions of each bit of c. */
               char current_bit = (current_c >> i) & 1;

               /* i must be a long to avoid overflows -- in practice,
                  the user would be up to no good, if this ever were
                  an issue. */
               // TODO off by one error according to debugger...also we build output the wrong direction currently
               for (long i = 0; i < repetitions; i++) {
                    // remember, until set, all bits of output are zero.
                    output |= current_bit;
                    output = output << 1;
                    // when we've filled a full character, output and reset:
                    if (++output_bits_filled == CHAR_BIT) {
                         putchar(output);
                         output = 0;
                         output_bits_filled = 0;
                    }
               }
          }
     }
}

// TODO most of this is the same as encode -- merge with that function
void decode(long repetitions) {
     assert(repetitions % 2 == 1);
     int c;
     while ((c = getchar()) != EOF) {
          const unsigned char current_c = c;
          long bits_processed = 0;
          long sum = 0;

          unsigned char output = 0;
          unsigned char output_bits_filled = 0;
          for (int i = 0; i < CHAR_BIT; i++) {
               sum += (current_c >> i) & 1;
               bits_processed++;

               if (bits_processed == repetitions) {
                    // use majority rule -- TODO assumes 1 and 0 are
                    // equally likely!
                    unsigned char current_bit = (sum > repetitions / 2) ? 1 : 0;
                    output |= current_bit;
                    output = output << 1;

                    if (++output_bits_filled == CHAR_BIT) {
                         putchar(output);
                         output = 0;
                         output_bits_filled = 0;
                    }
               }
          }
     }
}

int main(int argc, char** argv) {
     if (argc != 3) {
          print_usage(argv[0]);
          exit(EXIT_FAILURE);
     }

     bool encode_arg;
     if (strcmp(argv[1], "encode") == 0) {
          encode_arg = true;
     } else if (strcmp(argv[1], "decode") == 0) {
          encode_arg = false;
     } else {
          print_usage(argv[0]);
          exit(EXIT_FAILURE);
     }

     // convert repetitions argument to int
     errno = 0;
     // used to check that entire argv[2] is valid, not just prefix.
     char *endptr;
     long repetitions = strtol(argv[2], &endptr, 0);

     if (repetitions == 0 && errno == ERANGE) {
          print_usage(argv[0]);
          fprintf(stderr, "REPETITIONS was too large (long overflow occured).\n");
          exit(EXIT_FAILURE);
     }

     // see `man 3 strtol`.
     bool entire_string_was_valid = *argv[1] != '\0' && *endptr == '\0';
     if (!entire_string_was_valid || repetitions < 1) {
          print_usage(argv[0]);
          fprintf(stderr, "REPETITIONS must be a positive integer.\n");
          exit(EXIT_FAILURE);
     }

     if (repetitions % 2 == 0) {
          print_usage(argv[0]);
          fprintf(stderr, "REPETITIONS must be an odd integer.\n");
          exit(EXIT_FAILURE);
     }

     if (encode_arg)
          encode(repetitions);
     else
          decode(repetitions);

     return 0;
}
