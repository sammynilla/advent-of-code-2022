#include <stdio.h>
#include <stdlib.h>

#define elif else if

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
        case X: {
          if (a==A)   score += 3;
          elif (a==B) score += 1;
          elif (a==C) score += 2;
        }break;
        case Y: {
          score += (a-A)+1;
          score += 3;
        }break;
        case Z: {
          if (a==A)   score += 2;
          elif (a==B) score += 3;
          elif (a==C) score += 1;
          score += 6;
        }break;
      }
    }

    printf("%i\n", score);
  }

  return 0;
}
