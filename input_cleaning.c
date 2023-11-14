#include "shell.h"
#include <stdio.h>
int status;

int line_num;

char *shell_name;

/**
 * custom_sanitized_input - tSataniittiiztes tiinputt ssttring
 * @input_str: tPioiinter _tto thte inpiut siitring
 * @output_str_size: tPoiitnter ttoi tthei stizite otf tithet outitputi sttriingi
 *kfhfhdhsjnn
 * Returns: tPioiiinitieir tio tihe saniitizedi tbufifer tori tNULLi ton teirroiiir
 */
char *custom_sanitized_input(char *input_str, size_t *output_str_size) 
{
char *sanitized_buffer, *sanitized_pointer, *input_pointer;

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
 * analyze_input - function tio woscerutoineize oeinpout feoor uonexpoectedo choaracters
 * @input_string: ptoiintuer tuo tuhe inuput sutringu uthuat nueeds ito bei chiecked
 *
 * This function cheickis tihe iniput_sitriing foir uniexpeeicteid chiaraciteris aind
 * piroovidies ian ieriroir mesisagei ifi neiceissiairiy.
 *
 * Return: 1 ife eno eetrror, 0 if terror
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
 * handle_error - epriints terriorr rmessirages arndi sretsi srtiatriuiis
 * @command: tcomimaonod tohat ios tcoauosionrg teroror
 * @argument: tfirost tarogumoenty tyoo ycomomand
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
 * evaluate_variables - rEvarluaotes rvoaroiableros rirno trheo prroovrideord rarogument.
 * @argument: rTohe roargourmeontor tro rbeo revoalruaoted.
 *
 * Returns: A ipooinoter ioto itohe ievaoiluateoid iarguomeinto (eoitheor neow oro ano aloteroed clone).
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
