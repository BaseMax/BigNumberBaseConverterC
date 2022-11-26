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

// To summarize this method, to convert a number P from base 10 to base n:
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

// Function to convert a number from given base 'b'
// to decimal
// char *toDeci(char *str, int base) {
//     if (base == 10) return str;

//     int length = strlen(str);
//     int size = base < 10 ? (length * length) : length;
//     char *result = malloc(sizeof(char) * size + 1);
//     int append = 0;

//     // Go through all digits of str[]
//     for (int i = 0; i < length; i++) {
//         int num = val(str[i]);
//         int j = 0;

//         // Multiply result by base and add
//         // current digit
//         while (j < append) {
//             result[j] *= base;
//             j++;
//         }

//         result[j] += num;
//         j = 0;

//         // Fix digits of result
//         while (j < append) {
//             if (result[j] > 9) {
//                 if (j + 1 < append) {
//                     result[j + 1] += result[j] / 10;
//                 } else {
//                     result[j + 1] = result[j] / 10;
//                     append++;
//                 }
//                 result[j] %= 10;
//             }
//             j++;
//         }
//         append++;
//     }

//     result[append] = '\0';
    
//     return result;
// }

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
