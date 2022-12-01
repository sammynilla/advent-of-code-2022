#include <stdio.h>
#include <stdlib.h>

static const char* filename = "data.txt";

int main(int argc, char** argv) {
  char buf[1024];
  FILE* file = fopen(filename, "r");
  {
    static long most_capacity[3];
    static long sum, temp;
    char* endptr = NULL;
    for (;;) {
      if (!fgets(buf, 1024, file)) {
        int i;
        sum = 0;
        for (i = 0; i < 3; ++i) { sum += most_capacity[i]; }
        printf("top capacities: %ld, %ld, %ld\n", most_capacity[0], most_capacity[1], most_capacity[2]);
        printf("total calories: %ld\n", sum);
        break;
      }

      temp = strtol(buf, &endptr, 10);

      if (endptr == buf) {
        int i;
        /* printf("sum: %ld\n", sum); */
        for (i = 0; i < 3; ++i) {
          if (sum > most_capacity[i]) {
            temp = most_capacity[i];
            most_capacity[i] = sum;
            most_capacity[i+1] = temp;
            break;
          }
        }
        temp = sum = 0;
      }
      else {
        sum += temp;
      }
    }
  }

  return 0;
}
