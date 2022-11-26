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
        if (i != 0) {
            printf(",");
        }
    }
    printf("\n");
}

// Function to deep copy a BigNumber
BigNumber* copyBigNumber(BigNumber *number) {
    BigNumber *copy = createBigNumber(number->capacity);
    printf("test print: ");
    printBigNumber(number);
    for (int i = 0; i < number->size; i++) {
        copy->digits[i] = number->digits[i];
    }
    copy->size = number->size;
    return copy;
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

// Function to calculate modulu of two large number
BigNumber* BigNumberMod(BigNumber* number1, int number2) {
    int remainder = 0;
    for (int i = number1->size - 1; i >= 0; i--) {
        remainder = remainder * 10 + number1->digits[i];
        remainder = remainder % number2;
    }
    return intToBigNumber(remainder);
}

// Function to calculate subtraction of two large number
BigNumber* BigNumberSub(BigNumber* number1, BigNumber* number2) {
    BigNumber *result = createBigNumber(number1->size);
    int borrow = 0;
    for (int i = 0; i < number1->size; i++) {
        int sub = number1->digits[i] - borrow;
        if (i < number2->size) {
            sub -= number2->digits[i];
        }
        if (sub < 0) {
            sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result->digits[i] = sub;
    }
    result->size = number1->size;
    while (result->size > 1 && result->digits[result->size - 1] == 0) {
        result->size--;
    }
    return result;
}

// Function to calculate division of two large number
BigNumber* BigNumberDiv(BigNumber* number1, int number2) {
    BigNumber *result = createBigNumber(number1->size);
    int remainder = 0;
    for (int i = number1->size - 1; i >= 0; i--) {
        int dividend = number1->digits[i] + remainder * 10;
        result->digits[i] = dividend / number2;
        remainder = dividend % number2;
    }
    result->size = number1->size;
    while (result->size > 1 && result->digits[result->size - 1] == 0) {
        result->size--;
    }
    return result;
}

// Function to compare two large number
int BigNumberCompare(BigNumber* number1, BigNumber* number2) {
    if (number1->size > number2->size) return 1;
    if (number1->size < number2->size) return -1;
    for (int i = number1->size - 1; i >= 0; i--) {
        if (number1->digits[i] > number2->digits[i]) return 1;
        if (number1->digits[i] < number2->digits[i]) return -1;
    }
    return 0;
}

// Function to convert a positive number `number` to its digit representation in base `n`.
BigNumber* convertBase10ToN(BigNumber* number, int n) {
    BigNumber *digits = createBigNumber(number->capacity);
    BigNumber *temp = copyBigNumber(number);

    printf("n is %d\n", n);

    while (true) {
        // printf("temp is: ");
        // printBigNumber(temp);
        BigNumber *mod = BigNumberMod(temp, n);
        // printf("\tmod: ");
        // printBigNumber(mod);
        // printf("\told temp values: ");
        // printBigNumber(temp);
        for (int i = 0; i < mod->size; i++) {
            appendEndBigNumber(digits, mod->digits[i]);
        }

        temp = BigNumberDiv(temp, n);
        // printf("\tnew temp ---> ");
        // printBigNumber(temp);
        if (temp->size == 1 && temp->digits[0] == 0) break;
    }

    return digits;
}

int main(int argc, char** argv) {
    // 1100 % 60 = 20
    // BigNumber *a = intToBigNumber(1100);
    // BigNumber *c = BigNumberMod(a, 60);
    // printf("20\t");
    // printBigNumber(c); // 20

    // 1100 // 60 = 18
    // BigNumber *b = intToBigNumber(1100);
    // BigNumber *d = BigNumberDiv(b, 60);
    // printf("18\t");
    // printBigNumber(d); // 18

    if (argc != 4 && argc != 5) {
        printf("Usage: %s [number] [from] [to]\n", argv[0]);
        printf("Usage: %s -f [file] [from] [to]\n", argv[0]);
        return 1;
    }

    char* number;
    int from;
    int to;

    if (argc == 4) {
        number = stringTrim(argv[1]);
        from = atoi(argv[2]);
        to = atoi(argv[3]);
    } else if (argc == 5) {
        number = fileReads(argv[2]);
        if (number == NULL) {
            printf("Error in reading the file!\n");
            return 1;
        }
        number = stringTrim(number);
        from = atoi(argv[3]);
        to = atoi(argv[4]);
    }

    printf("Number: %s\n", number);
    printf("From: %d\n", from);
    printf("To: %d\n", to);

    printf("Result: ");
    BigNumber *number_10 = stringToBigNumber(number);
    BigNumber *number_n = convertBase10ToN(number_10, to);
    printBigNumber(number_n);
    
    return 0;
}
