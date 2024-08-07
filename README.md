<h1 align="center">
	📄 get_next_line
</h1>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/jose5556/get_next_line?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/jose5556/get_next_line?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/jose5556/get_next_line?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/jose5556/get_next_line?color=green" />
</p>

## 💡 About the project

This is the get_next_line project, completed during my studies at School 42. The goal of this project is to create a function that reads a line from a file descriptor, one at a time, regardless of how many read calls are required.

## Overview

In this project, I have implemented a function that reads a line from a file descriptor. The function dynamically allocates memory to handle lines of arbitrary length and manages buffer overflow efficiently. It is designed to work seamlessly with different file descriptors including standard input, files, and network sockets.

For more detailed information about the implementation, please refer to the project files and documentation.

## 🛠️ Usage

### Requirements

The function is written in C language and therefore requires the **`cc`** compiler to be executed.

### Instructions

**1. Compiling the library**

To compile the project files, run the following command in the project directory:

```shell
$ cc -Wall -Wextra -Werror -D BUFFER_SIZE=<number you want> -c get_next_line.c get_next_line_utils.c
```
**2.  Using it in your code**

To use the get_next_line function in your code, include its header:

```shell
#include "get_next_line.h"
```
Then, you can call the function get_next_line by passing a valid file descriptor:

```shell
int fd = open("file.txt", O_RDONLY);
char *line;
while ((line = get_next_line(fd)))
{
    printf("%s\n", line);
    free(line);
}
close(fd);
```

## Note

Please ensure that you define BUFFER_SIZE before compilation as it determines the buffer's size used in the function. 
You can adjust it based on your needs, but if you are unsure what value to put in, ignore that part because the code already has a standard number, which is 42.

Feel free to explore the get_next_line.h header file for documentation on the implemented function and helper utilities.
