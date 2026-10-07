#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 100
#define BUFFER_SIZE 1024

int main(void) {
  char buf[BUFFER_SIZE];
  long numbers[MAX_NUMBERS];
  int count = 0;

  puts("Let The Program Find Your Needs!\n");

  for (;;) {
    fputs("Enter a series of numbers: ", stdout);

    if (fgets(buf, sizeof(buf), stdin) != NULL) {
      if (strchr(buf, '\n') == NULL) {
        // Consume remaining characters until newline or EOF
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
          ;
        break;
      } else {
        // Remove the newline for cleaner string processing
        buf[strcspn(buf, "\n")] = '\0';
      }
    }

    char *endptr;
    char *ptr = buf;
    int success = 1;

    // Parse integers until newline or end of string
    while (*ptr) {
      // Skip leading whitespace and commas
      while (isspace((unsigned char)*ptr) || *ptr == ',') {
        ptr++;
      }

      if (*ptr == '\n' || *ptr == '\0') {
        break;
      }

      if (!isdigit((unsigned char)*ptr) && *ptr != '-' && *ptr != '+') {
        puts("Only accepts numbers and space/commas to separate them.\n");
        success = 0;
        break;
      }

      errno = 0;
      long value = strtol(ptr, &endptr, 10);
      if (errno == ERANGE) {
        puts("Number is too big/small.\n");
        success = 0;
        break;
      } else if (ptr == endptr) {
        puts("Enter a number.\n");
        success = 0;
        break;
      }

      if (count >= MAX_NUMBERS) {
        puts("Total data can't exceed 100.\n");
        success = 0;
        break;
      }

      numbers[count++] = value;
      ptr = endptr; // Move to next character after the number
    }

    if (success && count > 0) { // if \n is the only input, count = 0, resets
      break;
    } else {
      count = 0;
    }
  }

  // Sum and Average
  long sum = 0;
  for (int i = 0; i < count; i++) {
    sum += numbers[i];
  }
  printf("\nSum: %ld\n", sum);
  double avg = (double)sum / count;
  printf("Average: %.2f\n", avg);

  // Min and Max
  long min = numbers[0];
  long max = numbers[0];
  for (int i = 1; i < count; i++) {
    if (numbers[i] < min) {
      min = numbers[i];
    }
    if (numbers[i] > max) {
      max = numbers[i];
    }
  }
  printf("\nMin: %ld\n", min);
  printf("Max: %ld\n", max);

  // Odds and Evens
  fputs("\nOdd numbers: ", stdout);
  for (int i = 0; i < count; i++) {
    if (numbers[i] & 1) {
      printf("%ld, ", numbers[i]);
    }
  }
  fputs("\nEven numbers: ", stdout);
  for (int i = 0; i < count; i++) {
    if ((numbers[i] & 1) == 0) {
      printf("%ld, ", numbers[i]);
    }
  }

  puts("\n\nThanks for using this Program!");

  return 0;
}
