/*
 * @Name: Big/Huge Number Base Converter C
 * @Author: Max Base
 * @Date: 2022/10/31
 * @Repository: https://github.com/BaseMax/BigNumberBaseConverterC
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strrev

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
void convert_base(char* a, int f, int t) {
    int i;
    int len = strlen(a);
    int num = 0;
    for(i = 0; i < len; i++) {
        if(a[i] >= '0' && a[i] <= '9') {
            num = num * f + (a[i] - '0');
        }
        else if(a[i] >= 'A' && a[i] <= 'Z') {
            num = num * f + (a[i] - 'A' + 10);
        }
        else if(a[i] >= 'a' && a[i] <= 'z') {
            num = num * f + (a[i] - 'a' + 10);
        }
    }

    // TODO: We need to determine the size of the array
    int size = (int) strlen(a) * (t / f);
    char *res = (char*)malloc(sizeof(char) * size);
    int j = 0;
    while(num != 0) {
        int r = num % t;
        if(r >= 0 && r <= 9) {
            res[j++] = r + '0';
        }
        else {
            res[j++] = r - 10 + 'A';
        }
        num = num / t;
    }
    res[j] = '\0';

    strrev(res);

    printf("%s", res);
}

int main(int argc, char** argv) {
    if(argc < 4) {
        printf("Usage: %s [number] [from] [to]\n", argv[0]);
        return 1;
    }

    char* number = argv[1];
    int from = atoi(argv[2]);
    int to = atoi(argv[3]);

    printf("Number: %s\n", number);
    printf("From: %d\n", from);
    printf("To: %d\n", to);

    printf("Result: ");
    convert_base(number, from, to);
    printf("\n");
    
    return 0;
}
