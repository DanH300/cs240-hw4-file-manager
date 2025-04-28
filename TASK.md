CS240 HOMEWORK 4

Write a C program to implement the following requirement:

Input: The program will read from the standard input multiple lines:
- First line: a number n (n < 1 000 000 000), representing the number of files.
- Next n lines: each line contains a path of file Fi :
    - Fi contains multiple lines (max 100 lines), each line is a string Sj (max 1000 characters)
- Last line: a file that contains commands to manipulate or display the content.

Requirement:
1.	Fi and Sj should be read and stored in order of appearance.
2.	Execute commands on the stored strings. Commands can be:
    - PRINT IDX :  print the file content at index IDX, separate by commas
    - PRINT_ALL : print all file contents separated by newline, strings in this file should be separated by comma.
    - PRINT_LONGEST IDX : print the first longest string in file IDX
    - PRINT_LONGEST_FILE: print the file path of the first longest file. The longest file is the file with the largest amount of strings.
    - SEARCH S: print file path of the first file that contains string S. if not found, print nothing
    - SORT IDX  : sort strings in file IDX (ascending ASCII order)
    - REMOVE S: remove all occurrences of the string S from all files.
    - APPEND IDX1 IDX2: concatenate content of file IDX2 to IDX1

Note:
- In this homework, you may only use pointers and pointer operators to interact with arrays. Submissions containing ‘[’ or ‘]’ will not be accepted.
- After each print command, you need to add a new line (‘\n’) except in case of nothing to print.

SAMPLE INPUT 1
stdin:
2
./hw4/file00.in
./hw4/file01.in
./hw4/command00.in
./hw4/file00.in:
Hello
World
123!
./hw4/file01.in
This
is
CS240
Class
./hw4/command00.in:
PRINT_LONGEST 1
PRINT_LONGEST_FILE
PRINT 0
APPEND 0 1
PRINT 0
PRINT_ALL
SAMPLE OUTPUT 1
CS240
./hw4/file01.in
Hello,World,123!
Hello,World,123!,This,is,CS240,Class
Hello,World,123!,This,is,CS240,Class
This,is,CS240,Class