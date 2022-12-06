#include <stdio.h>
#include <string.h>

static const char* filename = "data.txt";

int main(int argc, char** argv) {
  char buf[1024] = {0};
  FILE* file = fopen(filename, "r");
  {
    enum { BUF_SIZE=50 };
    char lines[3][BUF_SIZE] = {0};
    size_t iter, len;
    int sum = 0;
    static int group_count;
    for (;;) {
      /* static int group_count; */
      for (iter = 0; iter < 3; ++iter) {
        fgets(buf, 1024, file);
        /* quick and dirty way to check for EOF in our data set */
        if (buf[0] == '\n') goto quit;

        len = strlen(buf) - 1;
        {
          size_t i;
          for (i = 0; i < BUF_SIZE; ++i) {
            if (i < len) lines[iter][i] = buf[i];
            else lines[iter][i] = 0;
          }
        }
      }

      printf("%s\n%s\n%s\n", lines[0], lines[1], lines[2]);
      group_count++;
      {
        char compare = {0};
        int found_flag = 0;
        size_t index;

        for (index = 0; index < BUF_SIZE; ++index) {
          if (!lines[0][index]) break; /* run until first null terminating character */
          if (found_flag) break;

          compare = lines[0][index]; /* get current character */
          {
            size_t i;
            for (i = 0; i < BUF_SIZE; ++i) {
              if (!lines[1][i]) break;

              if ((int)lines[1][i] == (int)compare) {
                size_t j;
                for (j = 0; j < BUF_SIZE; ++j) {
                  if (!lines[2][j]) break;

                  if ((int)lines[2][j] == (int)compare) {
                    enum { CHAR_A = 65, CHAR_Z = 90, CHAR_a = 97, CHAR_z = 122 };
                    if (((int)compare >= CHAR_A) && ((int)compare <= CHAR_Z)) {
                      sum += (compare-CHAR_A)+27;
                    }
                    else if (((int)compare >= CHAR_a) && ((int)compare <= CHAR_z)) {
                      sum += (compare-CHAR_a)+1;
                    }
                    printf("found char \"%c\" within group #%i | SUM: %i\n\n", compare, group_count, sum);
                    found_flag = 1;
                    break;
                  }
                }
              }
              if (found_flag) break;
            }
          }
        }
      }
    }
  }

quit:
  return 0;
}
