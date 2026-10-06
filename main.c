#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char buf[1024];
  long numbers[100];
  int count = 0;

  for (;;) {
    fputs("Enter a series of numbers (max. 100): ", stdout);

    if (!fgets(buf, sizeof(buf), stdin)) {
      return 0;
    }

    char *endptr;
    char *ptr = buf;
    int success = 0;

    // Parse integers until newline or end of string
    while (*ptr) {
      // Skip leading whitespace and commas
      while (isspace((unsigned char)*ptr) || *ptr == ',') {
        ptr++;
      }

      if (*ptr == '\n' || *ptr == '\0') {
        success = 1;
        break;
      }

      if (!isdigit((unsigned char)*ptr)) {
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

      if (count >= 100) {
        puts("Number can't exceed 100.\n");
        success = 0;
        break;
      }

      numbers[count++] = value;
      ptr = endptr; // Move to next character after the number
    }
    if (success) {
      break;
    } else {
      memset(numbers, 0, sizeof(numbers));
      count = 0;
    };
  }

  for (int i = 0; i < count; i++) {
    if (i == count - 1) {
      printf("%ld", numbers[i]);
      break;
    }
    printf("%ld, ", numbers[i]);
  }

  return 0;
}
