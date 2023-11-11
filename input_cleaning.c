include "shell.h"
#include <stdio.h>
int status;

int line_num;

char *shell_name;

/**
 * custom_sanitized_input - Sanitizes input string
 * @input_str: Pointer to the input string
 * @output_str_size: Pointer to the size of the output string
 *kfhfhdhsjnn
 * Returns: Pointer to the sanitized buffer or NULL on error
 */
char *custom_sanitized_input(char *input_str, size_t *output_str_size) {
    char *sanitized_buffer;
    char *sanitized_pointer;
    char *input_pointer;

    /* Allocate memory for the sanitized buffer */
    sanitized_buffer = malloc(*output_str_size * 3);

    /* Check if memory allocation was successful */
    if (sanitized_buffer == NULL) {
        return NULL;
    }

    /* Initialize pointers */
    sanitized_pointer = sanitized_buffer;
    input_pointer = input_str;

    /* Loop through the input string */
    while (*input_pointer != '\0') {
        /* Skip leading spaces */
        for (; *input_pointer == ' '; input_pointer++);

        /* Copy non-special characters to sanitized buffer */
        while (*input_pointer != ' ' && *input_pointer != ';' &&
               *input_pointer != '|' && *input_pointer != '&' &&
               *input_pointer != '\0') {
            *sanitized_pointer = *input_pointer;
            sanitized_pointer++;
            input_pointer++;
        }

        /* Skip trailing spaces */
        for (; *input_pointer == ' '; input_pointer++);

        /* Add space if not at the beginning and not at end of input */
        if (sanitized_pointer != sanitized_buffer && *input_pointer != '\0') {
            *sanitized_pointer = ' ';
            sanitized_pointer++;
        }

        /* Handle special characters */
        if (*input_pointer == ';' || *input_pointer == '|' || *input_pointer == '&') {
            if (analyze_input(input_pointer) == NO) {
                *output_str_size = 0;
                free(sanitized_buffer); /* Free memory on error */
                return NULL;
            }
            *sanitized_pointer = *input_pointer;

            /* Add space after semicolon */
            if (*input_pointer == ';') {
                sanitized_pointer++;
                *sanitized_pointer = ' ';
            }

            /* Handle repeated special characters */
            else if (*(input_pointer + 1) == *input_pointer) {
                if (sanitized_pointer == sanitized_buffer) {
                        handle_error(input_pointer, NULL);
                    *output_str_size = 0;
                    free(sanitized_buffer); /* Free memory on error */
                    return NULL;
                }
                sanitized_pointer++;
                *sanitized_pointer = *input_pointer;
                sanitized_pointer++;
                *sanitized_pointer = ' ';
                input_pointer++;
            }
            sanitized_pointer++;
            input_pointer++;
        }
    }

    /* Add null terminator to the sanitized buffer */
    *sanitized_pointer = '\0';

    /* Free the original input string as it's no longer needed */
    free(input_str);

    return sanitized_buffer;
}

/**
 * analyze_input - function to scrutinize input for unexpected characters
 * @input_string: pointer to the input string that needs to be checked
 *
 * This function checks the input_string for unexpected characters and
 * provides an error message if necessary.
 *
 * Return: 1 if no error, 0 if error
 */
int analyze_input(char *input_string)
{
    char *iter = input_string;

    iter++;

    switch (*input_string) {
        case ';':
            if (*iter == *input_string) {
                handle_error(input_string, NULL);
                return 0;
            }
            break;
        case '|':
        case '&':
            if (*iter == *input_string) {
                handle_error(iter, NULL);
                return 0;
            }
            break;
        default:
            break;
    }

    while (*iter == ' ')
        iter++;

    switch (*iter) {
        case ';':
        case '|':
        case '&':
            handle_error(iter, NULL);
            return 0;
        default:
            return 1;
    }
}
/**
 * handle_error - prints error messages and sets status
 * @command: command that is causing error
 * @argument: first argument to command
 */

void handle_error(char *command, char *argument)
{
    char *line_number_strings = my_custom_function_for_integer_to_string(line_num);

    fprintf(stderr, "%s: %d", shell_name, line_num);

    switch (*command) {
        case ' ':
        case '\t':
        case '\n':
        case '\r':
        case '\f':
        case '\v':
            fprintf(stderr, "?");
            break;
        case 'c':
            if (comparisonString("cd", command, ComPareString) == YES)
            {
                    status = 2;
                    fprintf(stderr, ": cd: can't cd to %s\n", argument);
            }
            break;
        case 'e':
            if (comparisonString("exit", command, ComPareString) == YES)
            {
                    fprintf(stderr, ": exit: Illegal number: %s\n", argument);
            }
            break;
        case ';':
        case '|':
        case '&':
            status = 2;
            fprintf(stderr, ": Syntax error: \"%c", *command);
            if (*command == *(command + 1))
                fprintf(stderr, "%c", *command);
            fprintf(stderr, "\" unexpected\n");
            break;
        default:
            status = 127;
            fprintf(stderr, ": %s: not found\n", command);
            break;
    }

    free(line_number_strings);
}
/**
 * evaluate_variables - Evaluates variables in the provided argument.
 * @argument: The argument to be evaluated.
 *
 * Returns: A pointer to the evaluated argument (either new or an altered clone).
 */
char *evaluate_variables(char *argument)
{
    char *duplicate = NULL;
    char *current_pointer = argument;
    char *next_pointer;
    char *temporary;
    char *buff;
    int is_variable;
    int index;

    do
    {
        switch (*current_pointer)
        {
            case '$':
                if (duplicate == NULL)
                {
                    duplicate = strdup(argument);
                    index = current_pointer - argument;
                    current_pointer = duplicate + index;
                }
                next_pointer = current_pointer + 1;
                do
                {
                    next_pointer++;
                } while (*next_pointer != '\0' && *next_pointer != '$' && *next_pointer != '#');

                if (*next_pointer == '$' && next_pointer > current_pointer + 1)
                    is_variable = YES;
                else if (*next_pointer == '#')
                    is_variable = NOT_APPLICABLE;
                else
                    is_variable = NO;

                *next_pointer = '\0';

                if (comparisonString("$?", current_pointer, ComPareString) == YES)
                    temporary = my_custom_function_for_integer_to_string(status);
                else if (comparisonString("$$", current_pointer, ComPareString) == YES)
                    temporary = my_custom_function_for_integer_to_string(getpid());
                else
                {
                    char *result = my_new_function(environ, current_pointer + 1);
                    if (result == NULL)
                        temporary = strdup("");
                    else
                    {
                        buff = concatenate_strings_custom(current_pointer + 1, "=");
                        temporary = strdup(result + strlen(buff));
                        free(buff);
                    }
                }

                *current_pointer = '\0';
                current_pointer = concatenate_strings_custom(duplicate, temporary);
                free(temporary);

                if (is_variable == NO)
                {
                    free(duplicate);
                    duplicate = current_pointer;
                    break;
                }

                if (is_variable == YES)
                    *next_pointer = '$';
                else if (is_variable == NOT_APPLICABLE)
                    *next_pointer = '#';

                temporary = concatenate_strings_custom(current_pointer, next_pointer);
                free(current_pointer);
                current_pointer = temporary;
                free(duplicate);
                duplicate = current_pointer;

                if (is_variable == NOT_APPLICABLE)
                {
                    do
                    {
                        current_pointer++;
                    } while (*current_pointer != '#');
                }

                break;
        }

        current_pointer++;
    } while (*current_pointer != '\0');

    if (duplicate != NULL)
        return duplicate;

    return argument;
}
