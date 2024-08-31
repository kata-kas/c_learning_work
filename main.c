#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

const int BASE = 10;
const unsigned int SHIFT_1 = 1U;
const unsigned int SHIFT_2 = 2U;
const unsigned int SHIFT_4 = 4U;
const unsigned int SHIFT_8 = 8U;
const unsigned int SHIFT_16 = 16U;

unsigned int findHighestPowerOfTwo(unsigned int limit) {
    if (limit == 0) {
        return 0;
    }
    limit |= (limit >> SHIFT_1);
    limit |= (limit >> SHIFT_2);
    limit |= (limit >> SHIFT_4);
    limit |= (limit >> SHIFT_8);
    limit |= (limit >> SHIFT_16);
    return limit - (limit >> SHIFT_1);
}

int main() {
    char *inputBuffer = NULL;
    size_t buffer_size = 0;
    unsigned int number = 0;
    char *endptr = NULL;

    printf("Enter a number: ");
    if (getline(&inputBuffer, &buffer_size, stdin) == -1) {
        printf("Error reading input.\n");
        free(inputBuffer);
        return EXIT_FAILURE;
    }

    errno = 0;
    unsigned long value = strtoul(inputBuffer, &endptr, BASE);
    if (errno != 0 || (*endptr != '\n' && *endptr != '\0')) {
        printf("Invalid input. Please enter a valid unsigned integer.\n");
        free(inputBuffer);
        return EXIT_FAILURE;
    }

    if (value > UINT_MAX) {
        printf("Input exceeds the maximum value for an unsigned int.\n");
        free(inputBuffer);
        return EXIT_FAILURE;
    }

    number = (unsigned int) value;

    unsigned int highestPowerOfTwo = findHighestPowerOfTwo(number);
    printf("The highest power of two less than or equal to %u is %u\n", number, highestPowerOfTwo);

    free(inputBuffer);
    return EXIT_SUCCESS;
}