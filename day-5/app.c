#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const char* filename = "data.txt";

typedef struct {
  char box[50];
  int size;
} box_stack;

enum { BOX_COUNT = 9 };
static box_stack stack_list[BOX_COUNT] = {
  { "QWPSZRHD", 8 },
  { "VBRWQHF" , 7 },
  { "CVSH"    , 4 },
  { "HFG"     , 3 },
  { "PGJBZ"   , 5 },
  { "QTJHWFL" , 7 },
  { "ZTWDLVJN", 8 },
  { "DTZCJGHF", 8 },
  { "WPVMBH"  , 6 },
};

int main(int argc, char** argv) {
  char buf[1024] = {0};
  FILE* file = fopen(filename, "r");

  char* token;
  static int data[3];
  size_t iter;
  for (;;) {
    fgets(buf, 1024, file);
    if (buf[0] == '\n') break;

    iter = 0;
    token = strtok(buf, "efmortv ");
    while (token) {
      data[iter] = atoi(token);
      /* printf("%i\t", data[iter]); */
      token = strtok(NULL, "efmortv ");
      iter++;
    }
    /* puts(""); */

    {
      size_t to_remove = data[0];
      box_stack* stack1 = &stack_list[data[1]-1];
      box_stack* stack2 = &stack_list[data[2]-1];
      char swap;

      while (to_remove) {
        swap = stack1->box[stack1->size-1];
        /* printf("swap: %c\n", swap); */
        stack2->box[stack2->size] = swap;
        stack2->size++;
        stack1->box[stack1->size-1] = 0;
        stack1->size--;
        to_remove--;
      }
    }
  }

  {
    size_t i;
    for (i = 0; i < BOX_COUNT; ++i) {
      printf("%c", stack_list[i].box[stack_list[i].size-1]);
    }
    puts("");
  }
  return 0;
}
