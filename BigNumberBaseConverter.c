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

// Convert number `a` from base `f` to base `t`
// void convert_base(char* a, int f, int t) {
//     // For example: a is our huge number in base `f` and we are going to convert that number to base `t`
//     if (f == t) {
//         printf("%s", a);
//         return;
//     }
//     int len = strlen(a);
//     char *result = (char *)malloc(1000000);
//     strrev(result);
//     printf("%s", result);
// }

/* Determine if a 64 bit unsigned interger is overflow */
bool is_overflow(uint64_t input_val) {
	size_t msb = (size_t) log2(input_val);

	return (msb < 63) ? 0 : 1;
}

/* Generates and return a 64 bit *common* */
uint64_t pre_process(char *input, const int size, const int from) {
	uint64_t common = 0;
	int i, base;
	base = from;

	/* (x= from char to int, y= from char(letter) to int) in Hex. */
	int type, type_x, type_y = 'W';
	type = type_x = '0';

	strrev(input);
	for(i = 0; i < size; i++) {
		if(base == 16)
			(!isdigit(input[i])) ? (type = type_y) : (type = type_x);
		common = common + ((input[i] - type) * (pow(base, i)));
	}
	
	if(is_overflow(common)) {
		fprintf(stderr, "core: number is too large\n");
		return 0;
	}

	return common;
}

/* Processes *common* and return the size of output array*/
int pos_process(char *output, uint64_t common, const int to) {
	if(common == 0)
		/* terminate with output = '0' when common is 0 */
		return (output[0] = '0') != '0' ? 0 : 1;

	int i, size, base = to;
	bool ishex = (base != 16) ? 0 : 1;

	for(i = 0, size = 0; common != 0; i++, size++) {
		output[i] = (common % base) + '0';

		if(ishex && ((output[i] - '0') > 9))
			output[i] += 39; /* Magical mystery number */

		common = common / base;
	}

	strrev(output);
	output[size] = '\0';

	return size; /* Return the size of array */
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

/* External interface */
int convert(const int from, const int to, char *input, char *output) {
	int size = pos_process(output, 
		pre_process(input, strlen(input), from), to);

	return size; /* Return the size of output[] */
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

    // convert_base(number, from, to);

    char output[1000000];
    int size = convert(from, to, number, output);
    for (int i = 0; i < size; i++) {
        printf("%c", output[i]);
    }

    printf("\n");
    
    return 0;
}
