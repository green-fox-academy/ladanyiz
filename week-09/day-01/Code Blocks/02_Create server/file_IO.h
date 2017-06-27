/**
    File_IO
    Purpose: Add functions to help working with I/O in C

    @author Marton Lorinczi
    @version 1.0 17/06/17
*/


#ifndef FILE_IO_H_INCLUDED
#define FILE_IO_H_INCLUDED

#define ROW_LENGTH 255
#define PATH_LENGTH 255


//---------------FILE I/O FUNCTIONS-------------------

/**
*   Name: file_print
*   Job: Prints all lines from a txt file.
*   input: char *path It's maximum size is PATH_LENGTH.
*   returns: 0 if there was no problem 1 if something went wrong.
*   Error handling: wrong path, empty file.
*/
int file_print(char *path);

/**
*   Name: file_print_delay
*   Job: Prints all lines from a txt file. There is delay [ms] between printing of each line.
*   input: char *path It's maximum size is PATH_LENGTH.
*   input: int delay This is the delay between the prints, it is given with milliseconds.
*   returns: 0 if there was no problem 1 if something went wrong.
*   Error handling: wrong path, empty file.
*/

int file_print_delay(char *path, int delay);

/**
*   Name: file_write_single_line
*   Job: Write a single line to the target txt file.
*   input: char *path It's maximum size is PATH_LENGTH.
*   input: char *mode. "w" or "a".
*   input: char *line It's maximum size is ROW_LENGTH.
*   returns: 0 if there was no problem 1 if something went wrong.
*   Error handling: wrong path, too big line.
*   If file doesn't exist it asks would you like to make a new one (y/n).
*/
int file_write_single_line(char *path, char *mode, char *line);

/**
*   Name: file_write_multiple_lines
*   Job: Write multiple lines to the target txt file.
*   input: char *path - It's maximum size is PATH_LENGTH.
*   input: char *mode - "w" or "a".
*   input: char **str_arr - array of strings.
*   input: int len - This must be the length of str_arr.
*   returns: 0 if there was no problem 1 if something went wrong.
*   Error handling: wrong path
*   If file doesn't exist it asks would you like to make a new one (y/n).
*/
int file_write_multiple_lines(char *path, char *mode, char **str_arr, int len);

/**
*   Name: file_read_single_line
*   Job: Reads the n-th line from a file, then it copies it to var line.
*   input: char *path - It's maximum size is PATH_LENGTH.
*   input: int number - Its the target lines number. 1- is first line.
*   input: char *line - This is the pointer for a char, the result will be there.
*   returns: 0 if there was no problem 1 if something went wrong.
*   Error handling: wrong path, empty file, if number is greater than the numbers of lines in file.
*/
int file_read_single_line(char *path, int number, char *line);

/**
*   Name: file_read_multiple_lines
*   Job: Read lines from a txt file and make an array of strings from them.
*   input: char *path - It's maximum size is PATH_LENGTH.
*   input: int from - From which line would you like to read.
*   input: int how many lines would you like to read.
*   returns: A pointer for the array of strings (Its a char matrix)
*   Error handling: wrong path, empty file, you want to read more than the number of lines exist.
*   (Error handling is not completed, and at the future I will add a mode to it, to read all the lines from the file)
*/

char** file_read_multiple_lines(char *path, int from, int how_many);

//---------------INSIDE FUNCTIONS TESTS-------------------


/**
*   Name: path_test
*   Job: Decide the given path ends ".txt" or not.
*   input: char *path
*   returns: 0 if it ends ".txt". Returns 1 if it doesn't end ".txt".
*   It prints out the problem if there is any.
*/
int path_test(char *path);

/**
*   Name: is_file_empty
*   Job: Decide the pointed file is empty or not ends ".txt" or not.
*   input: char *path
*   returns: 0 if its not empty ends. Returns 1 if it empty.
*   If its empty it prints out a warning.
*/
int is_file_empty(char *path);

/**
*   Name: opened_file_write_line_logging_mode
*   Job: Write a single line to an opened file with "a" mode. And it adds the current time.
*   Yes you have to OPEN the file before use this function, and don't forget to close it after.
*   This mode is recommended when the data comes fast, like in a while loop.
*   input: char *path
*   input: char *line the line you want to log
*   input: FILE *fw the opened file's name
*   returns: 0 if its not empty ends. Returns 1 if it empty.
*   If its empty it prints out a warning.
*/
int opened_file_write_line_logging_mode(char *line, FILE *fw);

/**
*   Name: file_write_line_logging_mode
*   Job: Write a single line to a file with "a" mode. And it adds the current time.
*   input: char *path
*   input: char *line the line you want to log
*   returns: 0 if its not empty ends. Returns 1 if it empty.
*   If its empty it prints out a warning.
*/
int file_write_line_logging_mode(char *path, char *line);



#endif // FILE_IO_H_INCLUDED
