#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const char* filename = "data.txt";

int main(int argc, char** argv) {
  char buf[1024] = {0};
  FILE* file = fopen(filename, "r");

  size_t iter = 0;
  int pairs = 0;
  static int id[4];
  char* token;
  for (;;) {
    fgets(buf, 1024, file);
    if (buf[0] == '\n') break;

    iter = 0;
    token = strtok(buf, "-,");
    while (token) {
      id[iter] = atoi(token);
      token = strtok(NULL, "-,");
      iter++;
    }

    printf("<%i,%i>", id[0], id[1]);
    printf("<%i,%i>", id[2], id[3]);

    if ((id[0] <= id[3] && id[0] >= id[2]) ||
        (id[2] <= id[1] && id[2] >= id[0])) {
      printf("\t| overlap\n");
      pairs++;
      continue;
    }
    printf("\n");
  }

  printf("\nPairs: %i\n", pairs);
  return 0;
}
