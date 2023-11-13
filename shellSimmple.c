#include "shell.h"

int status = 0;
int line_num = 1;
char *shell_name = NULL;

/**
 * main - executes commands from the terminal
 * @argc: number of inputs from main
 * @argv: array of inputs from main
 *
 * Return: 0, or another number if desired
 */
int main(int argc, char **argv)
{
int numbytesRead, is_command_separated = NO;
    size_t buffer_size = 1;
char *input_buffer = NULL, *buffer_pointer, *temporary_buffer, **command_arguments = NULL;

    int i; /* Move the declaration here */

    (void)argc;
    shell_name = strdup(*argv);

    environ = my_updated_array_copy(environ, my_new_list_length(environ, NULL));

    signal(SIGINT, SIG_IGN);

    input_buffer = malloc(buffer_size);
    if (input_buffer == NULL)
        exit(EXIT_FAILURE);

    for (;;)
    {
        if (is_command_separated == NO)
        {
            if (isatty(STDIN_FILENO) == 1)
                printf(" $ ");

            numbytesRead = getline(&input_buffer, &buffer_size, stdin);

            if (numbytesRead == -1)
                break;
            if (numbytesRead == 1)
            {
                line_num++;
                continue;
            }
            input_buffer[numbytesRead - 1] = '\0';
            input_buffer = custom_sanitized_input(input_buffer, &buffer_size);
            if (buffer_size == 0)
            {
                line_num++;
                continue;
            }
            buffer_pointer = input_buffer;
        }
        else
            buffer_pointer = temporary_buffer;

        temporary_buffer = NULL;
        command_arguments = my_new_function_name(buffer_pointer, ' ', &temporary_buffer);
        if (temporary_buffer != NULL)
            is_command_separated = YES;
        else
            is_command_separated = NO;

        i = process_commands(command_arguments); /* Now use i */

        free(command_arguments);

        if (is_command_separated == NO)
            line_num++;

        if (i == TERminalShell)
            break;
    }

    free(input_buffer);
    handle_command_aliases(NULL, YES);
    my_deallocate_array(environ);
    free(shell_name);

    return (status);
}
