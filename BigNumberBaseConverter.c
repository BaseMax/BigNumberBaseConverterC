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

// Convert a huge number from base 10 to `to`
// Convert a number from base 10 to base n
// Writing a number P in base n is equivalent to finding the coefficients of successive powers of n such as

// P
// =
// c
// 0
// ⋅
// n
// 0
// +
// c
// 1
// ⋅
// n
// 1
// +
// c
// 2
// ⋅
// n
// 2
// +
// ... with 
// c
// 0
// ,
// c
// 1
// ,
// c
// 2
// ...
// the digits in the base n of P.

// Let's illustrate this with an example. How to convert 1205 to 9 base ?

// We start by writing the powers of 9. We stop at the power immediately greater than our number 1205: 
// 1
// (
// 9
// 0
// )
// ,
// 9
// (
// 9
// 1
// )
// ,
// 81
// (
// 9
// 2
// )
// ,
// 729
// (
// 9
// 3
// )
// ,
// 6561
// (
// 9
// 4
// >
// 1205
// )


// 9
// 3
// <
// 1205
// <
// 9
// 4
// . So, 1205 will have 4 digits in base 9 and will be written as follows,

// Equation (1):
// 1205
// =
// a
// 3
// ⋅
// 9
// 3
// +
// a
// 2
// ⋅
// 9
// 2
// +
// a
// 1
// ⋅
// 9
// 1
// +
// a
// 0
// ⋅
// 9
// 0
//  i.e. 1205 is represented by "
// a
// 3
// a
// 2
// a
// 1
// a
// 0
// " in base 9 with,

// a
// 0
// ,
// a
// 1
// ,
// a
// 2
// ,
// a
// 3
//  digits from base 9 i.e. numbers from 0.1,... 7 and 8.

// Equation (1) can be written in the form,

// 1205
// =
// a
// 3
// ⋅
// 9
// 3
// +
// r
//  with r < 
// 9
// 3
//  does this remind you of anything ? this is the Euclidean division of 1205 by 
// 9
// 3
//  i.e. 729.

// By doing the Euclidean division, we get 1205 ÷ 729 = 1 remainder 476

// So we have 
// a
// 3
// =
// 1
//  and 
// r
// =
// a
// 2
// ⋅
// 9
// 2
// +
// a
// 1
// ⋅
// 9
// 1
// +
// a
// 0
// ⋅
// 9
// 0
// =
// 476


// Similarly, one can write,

// 476
// =
// a
// 2
// ⋅
// 9
// 2
// +
// s
//  with s < 
// 9
// 2
// , similarly, this is the Euclidean division of 476 by 
// 9
// 2
//  i.e. 81.

// By doing the Euclidean division, we get 476 ÷ 81 = 5 remainder 71

// We deduce 
// a
// 2
// =
// 5
//  and 
// s
// =
// a
// 1
// ⋅
// 9
// 1
// +
// a
// 0
// ⋅
// 9
// 0
// =
// 71


// We reiterate the same process, 71 ÷ 9 = 7 remains 8, we deduce, 
// a
// 1
//  = 7 and 
// a
// 0
//  = 8

// It has been proved successively,
// a
// 3
// =
// 1

// a
// 2
// =
// 5

// a
// 1
// =
// 7

// a
// 0
// =
// 8


// 1205 in base 9 is written 1578 in base 9.

// To summarize this method,

// To convert a number P from base 10 to base n
// - Write powers of n (target base)
// - Frame P by 2 successive powers of n (by the way, this determines the number of digits of P in base n)
// - Do the Euclidean division of P by the power of n identified in the previous step (lowest value of the two powers)
// - The quotient of this division is equal to the first digit of P (starting from the left) in base n
// - Repeat successively these divisions by using the remainder as the new dividend and the immediately lower power as divisor until reaching power 1 of n.

int* str_to_int_array(char* str, int length) {
    int* array = (int*)malloc(sizeof(int) * length);
    int i = 0;
    while (*str != '\0') {
        array[i++] = *str - '0';
        str++;
    }
    return array;
}

// To return value of a char. For example, 2 is
// returned for '2'.  10 is returned for 'A', 11
// for 'B'
int val(char c) {
    if (c >= '0' && c <= '9') return (int)c - '0';
    else return (int)c - 'A' + 10;
}

// Function to convert a number from given base 'b'
// to decimal
char *toDeci(char *str, int base) {
    if (base == 10) return str;

    int length = strlen(str);
    int size = base < 10 ? length * length : length;
    char *result = malloc(sizeof(char) * size + 1);

    int power = 1; // Initialize power of base
    int num = 0;  // Initialize result
    int i;
 
    // Decimal equivalent is str[len-1]*1 + str[len-2]*base + str[len-3]*(base^2) + ...
    for (i = len - 1; i >= 0; i--) {
        // A digit in input number must be less than number's base
        if (val(str[i]) >= base) {
           printf("Invalid Number");
           return NULL;
        }

        result[i] = val(str[i]) * power;
 
        num += val(str[i]) * power;
        // power = power * base;
    }
 
    return num;
}

void my_convert(char* input, int to) {
    int len = strlen(input);

    // Convert the input string to an array of integers
    int* arr = str_to_int_array(input, len);

    // Convert the input number from base 10 to base `to`

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
        number = argv[1];
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

    if (from != 10) {
        int deci = toDeci(number, from);
        printf("%d", deci);
    } else {
        my_convert(number, to);
    }

    my_convert(number, to);
    printf("\n");
    
    return 0;
}
