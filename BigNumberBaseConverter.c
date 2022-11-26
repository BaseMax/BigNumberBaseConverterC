/*
 * @Name: Big/Huge Number Base Converter C
 * @Author: Max Base
 * @Date: 2022/10/31
 * @Repository: https://github.com/BaseMax/BigNumberBaseConverterC
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // strrev, strlen
#include <ctype.h> // isspace
#include <inttypes.h>
#include <math.h>

// A structure to store big numbers in an array
typedef struct {
    int *digits;
    int size;
    int capacity;
} BigNumber;

// Function to create a new empty BigNumber with a given capacity
BigNumber* createBigNumber(int capacity) {
    BigNumber *number = (BigNumber*) malloc(sizeof(BigNumber));
    number->digits = (int*) malloc(sizeof(int) * capacity);
    number->size = 0;
    number->capacity = capacity;
    return number;
}

// Function to deep copy a BigNumber
BigNumber* copyBigNumber(BigNumber *number) {
    BigNumber *copy = createBigNumber(number->capacity);
    for (int i = 0; i < number->size; i++) {
        copy->digits[i] = number->digits[i];
    }
    copy->size = number->size;
    return copy;
}

// Function to create a new BigNumber from a string
BigNumber* stringToBigNumber(char *string) {
    int length = strlen(string);
    BigNumber *number = createBigNumber(length);
    for (int i = length - 1; i >= 0; i--) {
        number->digits[number->size++] = string[i] - '0';
    }
    return number;
}

// Function to create a new BigNumber from a int
BigNumber* intToBigNumber(int number) {
    char string[100];
    sprintf(string, "%d", number);
    return stringToBigNumber(string);
}

// Function to add a new digit at the beginning of a BigNumber
void appendBeginBigNumber(BigNumber *number, int digit) {
    if (number->size == number->capacity) {
        number->capacity *= 2;
        number->digits = (int*) realloc(number->digits, sizeof(int) * number->capacity);
    }
    for (int i = number->size; i > 0; i--) {
        number->digits[i] = number->digits[i - 1];
    }
    number->digits[0] = digit;
    number->size++;
}

// Function to add a new digit at the end of a big number
void appendEndBigNumber(BigNumber *number, int digit) {
    if (number->size == number->capacity) {
        number->capacity *= 2;
        number->digits = (int*) realloc(number->digits, sizeof(int) * number->capacity);
    }
    number->digits[number->size++] = digit;
}

// Function to free the memory occupied by a big number
void freeBigNumber(BigNumber *number) {
    free(number->digits);
    free(number);
}

// Function to print a BigNumber
void printBigNumber(BigNumber *number) {
    for (int i = number->size - 1; i >= 0; i--) {
        printf("%d", number->digits[i]);
    }
    printf("\n");
}

// Function to reverse a string
void stringReverse(char *str) {
    int i = strlen(str) - 1, j = 0;
    char ch;
    while (i > j) {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
}

// Function to remove leading whitespaces of a string
char* stringTrim(char* str) {
    char* end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}

// Function to read contents of a file
char *fileReads(char *filepath) {
	FILE* file = fopen(filepath, "rb");
	if (file == NULL) {
		printf("Could not open file \"%s\".", filepath);
		exit(74);
	}

	fseek(file, 0L, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	char* buffer = (char*)malloc(fileSize + 1);
	if (buffer == NULL) {
		printf("Not enough memory to read \"%s\".", filepath);
		exit(74);
	}

	size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
	if (bytesRead < fileSize) {
		printf("Could not read the \"%s\".", filepath);
		exit(74);
	}

	buffer[bytesRead] = '\0';

	fclose(file);
	return buffer;
}

// To return value of a char. For example, 2 is returned for '2'.  10 is returned for 'A', 11 for 'B'
int convertCharToInt(char c) {
    if (c >= '0' && c <= '9') return (int)c - '0';
    else return (int) c - 'A' + 10;
}

// Function to caclulate modulu of two large number
BigNumber* ModBigNumber(BigNumber* number1, BigNumber* number2) {
    BigNumber *result = createBigNumber(1);
    int mod = 0;
    for (int i = number1->size - 1; i >= 0; i--) {
        mod = mod * 10 + number1->digits[i];
        appendEndBigNumber(result, mod / number2->digits[0]);
        mod = mod % number2->digits[0];
    }
    return result;
}

// Function to caclulate division of two large number
BigNumber* BigNumberDiv(BigNumber* number1, BigNumber* number2) {
    BigNumber *result = createBigNumber(1);
    BigNumber *temp = createBigNumber(number1->size);
    int idx = 0;
    int temp2 = number1->digits[number1->size - 1];
    while (temp2 < number2->digits[0]) temp2 = temp2 * 10 + number1->digits[--idx];
    while (number1->size > idx) {
        appendEndBigNumber(temp, temp2 / number2->digits[0]);
        idx++;
        if (idx == number1->size) break;
        temp2 = (temp2 % number2->digits[0]) * 10 + number1->digits[idx];
    }
    if (temp2 % number2->digits[0] == 0) {
        return temp;
    }
    return temp;
}

// Function to convert a positive number `number` to its digit representation in base `n`.
BigNumber* convertBase10ToN(BigNumber* number, int n) {
    BigNumber *digits = createBigNumber(number->capacity);
    BigNumber *base = intToBigNumber(n);
    BigNumber *temp = copyBigNumber(number);
    while (true) {
        BigNumber *mod = ModBigNumber(temp, base);
        appendBeginBigNumber(digits, mod->digits);
        temp = BigNumberDiv(temp, base);
        if (temp->digits[0] == 0) {
            break;
        }
    }
    // digits = []
    // while n > 0:
    //     digits.insert(0, n % b)
    //     n  = n // b
}

void my_convert(char* input, int to) {
    int len = strlen(input);

    // Convert the input string to an array of integers
    int* arr = str_to_int_array(input, len);
    printf("\n");
}

int main(int argc, char** argv) {
    if (argc != 4 && argc != 5) {
        printf("Usage: %s [number] [from] [to]\n", argv[0]);
        printf("Usage: %s -f [file] [from] [to]\n", argv[0]);
        return 1;
    }

    char* number;
    int from;
    int to;

    if (argc == 4) {
        number = trim(argv[1]);
        from = atoi(argv[2]);
        to = atoi(argv[3]);
    } else if (argc == 5) {
        number = file_reads(argv[2]);
        if (number == NULL) {
            printf("Error in reading the file!\n");
            return 1;
        }
        number = trim(number);
        from = atoi(argv[3]);
        to = atoi(argv[4]);
    }

    printf("Number: %s\n", number);
    printf("From: %d\n", from);
    printf("To: %d\n", to);

    printf("Result: ");

    // if (from != 10) {
    //     char* num10 = toDeci(number, from);
    //     printf("New Number in base 10: %s\n", num10);
    // } else {
    //     my_convert(number, to);
    // }

    my_convert(number, to);
    printf("\n");
    
    return 0;
}
