#include <stdio.h>
#include <string.h>

static const char* filename = "data.txt";

int main(int argc, char** argv) {
  char buf[1024] = {0};
  FILE* file = fopen(filename, "r");
  {
    enum { CHAR_A = 65, CHAR_Z = 90, CHAR_a = 97, CHAR_z = 122 };
    enum { BUF_SIZE=30 };
    int sum = 0;
    size_t len, found_loc;
    char sack1[BUF_SIZE] = {0};
    char sack2[BUF_SIZE] = {0};
    for (;;) {
      fgets(buf, 1024, file);
      /* quick and dirty way to check for EOF in our data set */
      if (buf[0] == '\n') { break; }

      len = strlen(buf) - 1;
      {
        int i;
        size_t half_len = (len / 2);
        for (i = 0; i < BUF_SIZE; ++i) {
          if (i < half_len) sack1[i] = buf[i];
          else sack1[i] = 0;
        }
        for (i = 0; i < BUF_SIZE; ++i) {
          if (i < half_len) sack2[i] = buf[i+half_len];
          else sack2[i] = 0;
        }
      }

      found_loc = strcspn(sack1, sack2);
      {
        char item = sack1[found_loc];
        if (((int)item >= CHAR_A) && ((int)item <= CHAR_Z)) {
          sum += (item-CHAR_A)+27;
        }
        else if (((int)item >= CHAR_a) && ((int)item <= CHAR_z)) {
          sum += (item-CHAR_a)+1;
        }
      }
    }

    printf("Sum: %i\n", sum);
  }

  return 0;
}
