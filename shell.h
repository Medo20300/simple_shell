#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <signal.h>

#define NO  0
#define YES  1
#define NOT_APPLICABLE  2
#define ComPareString 0
#define StartSWith  4
#define TERminalShell  5
#define ByPassFork  6
#define ExecuteCommand 2

/**
 * struct Alias - singly linked list
 * @name: name of alias
 * @value: command that alias calls
 * @next: points to next node
 */

typedef struct NewName {
    char *name;
    char *value;
    struct NewName *next;
} NewName;




extern int condition;
extern int lineIndex;
extern char *command_shell;
extern char **environ;

/*** execution.c ***/
int process_commands(char **commands);
int check_if_builtin(char **commands);
int evaluate_logical_operator(char **commands, char eXcute, int final_eval);
char *find_executable_path(char **input_arguments);
int process_directive(char **command_arguments);


/***** input_correction.c ***********/

char *custom_sanitized_input(char *input_str, size_t *output_str_size);
int analyze_input(char *input_string);
void handle_error(char *command, char *argument);
char *evaluate_variables(char *argument);


/************/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _getline(char **line_ptr, size_t *n, int file);


/**** string *******/
int get_length(int argc, char *argv[]);
char *create_duplicate(char *source);
char *concatenate_strings_custom(char *first_string, char *second_string);
int comparisonString(char *userInput, char *targetString, int preference);

/*** array_mmanip.c ***/
char *my_new_function(char **my_new_parameter_name_1, char *my_new_parameter_name_2);
char **my_new_function_name(char *input_string, char delimiter, char **next_separator);
int my_new_list_length(char **my_new_list, char *my_new_entry);
char **my_updated_array_copy(char **source_array, int destination_size);
int my_deallocate_array(char **my_arguments);

/*****  built  ********/
int set_environment_variable(const char *gold_Name, const char *nEw_result);
int unset_environment_variable(const char *new_name);
int change_current_directory(char *new_path);
int handle_command_aliases(char **new_args, int to_free);
int print_environment(void);

/**1 **/
int deallocate_aliases(NewName *new_name_ptr);
int process_alias_check(char **arguments, NewName *newName_pointer);
int display_all_aliases(NewName *newName_pointer);
int display_alias_value(char *arguments, NewName *newName_pointer);
int update_alias_value(char *arguments, NewName *newName_pointer, char *newName_value);



/***** math_funcs.c *********/
char *my_custom_function_for_integer_to_string(int quantity);
int my_custom_function_for_string_to_integer(char *string);



#endif
