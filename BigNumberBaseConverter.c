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

BigNumber* createBigNumber(int capacity) {
    BigNumber *number = (BigNumber*) malloc(sizeof(BigNumber));
    number->digits = (int*) malloc(sizeof(int) * capacity);
    number->size = 0;
    number->capacity = capacity;
    return number;
}

void appendBigNumber(BigNumber *number, int digit) {
    if (number->size == number->capacity) {
        number->capacity *= 2;
        number->digits = (int*) realloc(number->digits, sizeof(int) * number->capacity);
    }
    number->digits[number->size++] = digit;
}

void freeBigNumber(BigNumber *number) {
    free(number->digits);
    free(number);
}

void printBigNumber(BigNumber *number) {
    for (int i = number->size - 1; i >= 0; i--) {
        printf("%d", number->digits[i]);
    }
    printf("\n");
}

void my_strrev(char *str) {
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

char* trim(char* str) {
    char* end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}

char *file_reads(char *filepath) {
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

int* str_to_int_array(char* str, int length) {
    int* array = (int*)malloc(sizeof(int) * length);
    int i = 0;
    while (*str != '\0') {
        array[i++] = *str - '0';
        str++;
    }
    array[i] = '\0';
    return array;
}

// To return value of a char. For example, 2 is
// returned for '2'.  10 is returned for 'A', 11
// for 'B'
int val(char c) {
    if (c >= '0' && c <= '9') return (int)c - '0';
    else return (int)c - 'A' + 10;
}

// Function to caclulate modulu of two large number
char* bignumber_mod(int* number1, int length1, int* number2, int length2, int* resultLength) {
    // As result can be very large store it in string
    char* result = (char*)malloc(sizeof(char) * length1);
    int i = 0;
    int temp = number1[i];
    while (temp < length2) temp = temp * 10 + number1[++i];
    while (length1 > i) {
        // Store result in result i.e. temp / length2
        result[i] = (temp / length2) + '0';
        i++;
        // Take next digit of number
        temp = (temp % length2) * 10 + number1[i];
    }
    // Store result in result
    result[i] = (temp / length2) + '0';
    i++;
    result[i] = '\0'; // Append string terminator
    // If remainder is 0, then store 0 in result
    // As result is integer, convert it into string
    if (temp % length2 == 0) {
        *resultLength = i;
        return result;
    }
    // If remainder is non-zero, then store remainder
    // in result
    // As result is integer, convert it into string
    char* result2 = (char*)malloc(sizeof(char) * length1);
    sprintf(result2, "%d", temp % length2);
    *resultLength = strlen(result2);
    return result2;
}

// Function to calculate and return the divide of two large numbers
int* bignumber_divide(int* number1, int length1, int* number2, int length2, int* resultLength) {
    int* result = (int*)malloc(sizeof(int) * 1000);
    int i = 0, temp = 0;
    while (i < length1) {
        temp = temp * 10 + number1[i];
        if (temp < number2[0]) {
            if (i != 0) {
                result[i] = 0;
                i++;
            }
        } else {
            result[i] = temp / number2[0];
            temp = temp % number2[0];
            i++;
        }
    }
    result[i] = '\0';
    *resultLength = i;
    return result;
}

//  Convert a positive number `number` to its digit representation in base `n`.
int* convert_base10_to_n(int* number, int length, int* resultLength, int new_base) {
    int* result = (int*)malloc(sizeof(int) * 1000);
    int i = 0;
    while (true) {
        int* temp = bignumber_divide(number, length, &new_base, 1, &length);
        int* temp2 = bignumber_mod(number, length, &new_base, 1, &length);
        result[i] = temp2[0];
        i++;
        if (length == 1 && temp[0] == 0) {
            break;
        }
        number = temp;
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
    if(argc != 4 && argc != 5) {
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
