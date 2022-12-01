#include <stdio.h>
#include <stdlib.h>

static const char* filename = "data.txt";

int main(int argc, char** argv) {
  char buf[1024];
  FILE* file = fopen(filename, "r");
  {
    static long big, sum, temp;
    char* endptr;
    for (;;) {
      if (!fgets(buf, 1024, file)) {
        printf("big: %ld\n", big);
        break;
      }

      temp = strtol(buf, &endptr, 10);

      if (endptr == buf) {
        big = sum > big ? sum: big;
        temp = sum = 0;
      }
      else {
        sum += temp;
      }
    }
  }

  return 0;
}
