#include <stdio.h>
#include <stdlib.h>

static const char* filename = "data.txt";

int main(int argc, char** argv) {
  char buf[1024] = {0};
  FILE* file = fopen(filename, "r");
  {
    enum CHARS { A=65, B, C, X=88, Y, Z };
    static int score;
    int a, b;
    for (;;) {
      fgets(buf, 1024, file);
      /* quick and dirty way to check for EOF in our data set */
      if (buf[0] == '\n') { break; }

      a = (int)(buf[0]);
      b = (int)(buf[2]);

      switch (b) {
        case X: score += 1; break;
        case Y: score += 2; break;
        case Z: score += 3; break;
      }

      switch (a) {
        case A: {
          if (b == X) score += 3;
          else if (b == Y) score += 6;
        }break;
        case B: {
          if (b == Y) score += 3;
          else if (b == Z) score += 6;
        }break;
        case C: {
          if (b == Z) score += 3;
          else if (b == X) score += 6;
        }break;
      }
    }

    printf("%i\n", score);
  }

  return 0;
}
