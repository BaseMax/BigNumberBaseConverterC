# BigNumberBaseConverter C

A Super-Fast **C-Program** for converting very huge/big numbers from _one base_ to _another base_ without Limitation.

## Features

- **Super-Fast** - It's written in C, so it's super-fast.
- **No Limitation** - It can convert very huge/big numbers from _one base_ to _another base_ without any limitation.
- **Easy to Use** - It's very easy to use.
- **Cross-Platform** - It's cross-platform, so it can be used on any platform.
- **Open-Source** - It's open-source, so you can use it for free.

## Functions

- `int convertCharToInt(char c)`: Function to convert a character to its digit representation
- `char convertIntToChar(int n)`: Function to convert a digit to its character representation
- `BigNumber* BigNumberCreate(int capacity)`: Function to create a new empty BigNumber with a given capacity
- `BigNumber* stringToBigNumber(char *string)`: Function to create a new BigNumber from a string
- `BigNumber* intToBigNumber(int number)`: Function to create a new BigNumber from a int
- `void BigNumberAppendBegin(BigNumber *number, int digit)`: Function to add a new digit at the beginning of a BigNumber
- `void BigNumberAppendEnd(BigNumber *number, int digit)`: Function to add a new digit at the end of a big number
- `int BigNumberGet(BigNumber *number, int index)`: Function to get the digit at a given index of a BigNumber
- `int BigNumberGetNumber(BigNumber *number)`: Function to get the int representation of a BigNumber
- `void BigNumberFree(BigNumber *number)`: Function to free the memory occupied by a big number
- `void BigNumberPrintString(BigNumber *number)`: Function to print a BigNumber in charachter form
- `void BigNumberPrint(BigNumber *number)`: Function to print a BigNumber
- `BigNumber* copyBigNumber(BigNumber *number)`: Function to deep copy a BigNumber
- `void stringReverse(char *str)`: Function to reverse a string
- `char* stringTrim(char* str)`: Function to remove leading whitespaces of a string
- `char *fileReads(char *filepath)`: Function to read contents of a file
- `BigNumber* BigNumberMod(BigNumber* number1, int number2)`: Function to calculate modulu of two large number
- `BigNumber* BigNumberSub(BigNumber* number1, BigNumber* number2)`: Function to calculate subtraction of two large number
- `BigNumber* BigNumberDiv(BigNumber* number1, int number2)`: Function to calculate division of two large number
- `int BigNumberCompare(BigNumber* number1, BigNumber* number2)`: Function to compare two large number
- `BigNumber* convertBase10ToN(BigNumber* number, int n)`: Function to convert a positive number `number` to its digit representation in base `n`.

## Using

### Convert a number given from user

```bash
$ ./BigNumberBaseConverter 10 2 123456789
```

The above command will convert the number `123456789` from base `10` to base `2` and print the result.

### Convert a number from a file and save the result in another file

```bash
$ ./BigNumberBaseConverter -f input.txt 10 2 > result.txt
```

The above command will convert the number from the file `filename.txt` from base `10` to base `2` and print the result to the file `result.txt`.

### Convert a number from a file and print the result to the console

```bash
$ ./BigNumberBaseConverter -f input.txt 10 2
```

The above command will convert the number from the file `filename.txt` from base `10` to base `2` and print the result to the console.

© Copyright 2022, Max Base
