#include "shell.h"

int status;

char *shell_name;
/**
 * process_commands - processes a series of commands, handling logical operators
 * @commands: command and arguments
 *
 * Return: TRUE if all commands succeed, FALSE if any command fails, or EXIT_SHELL if the user wants to exit the shell
 */
int process_commands(char **commands)
{
    char **current_command = commands;
    int previous_evaluation = NOT_APPLICABLE;
    int success = YES;
    char previous_operator = 'c';
    char next_operator = 'c';
    int result;

    do
    {
        do
        {
            current_command++;
        } while (*current_command != NULL && **current_command != '&' && **current_command != '|');

        if (comparisonString(*current_command, "||", ComPareString) == YES)
        {
            *current_command = NULL;
            current_command++;
            next_operator = '|';
        }
        if (comparisonString(*current_command, "&&", ComPareString) == YES)
        {
            *current_command = NULL;
            current_command++;
            next_operator = '&';
        }
        if (next_operator == 'c')
        {
            break;
        }

        previous_evaluation = evaluate_logical_operator(commands, previous_operator, previous_evaluation);

        if (previous_evaluation == NO)
        {
            success = NO;
        }

        previous_operator = next_operator;
        commands = current_command;
    } while (*current_command != NULL && previous_evaluation != TERminalShell);

    if (next_operator == 'c')
    {
        result = process_directive(commands);

        if (result == TERminalShell)
        {
            return TERminalShell;
        }
    }

    if (success == NO || result == NO)
    {
        return NO;
    }

    return YES;
}


/**
 * check_if_builtin - checks if a command is a built-in or a shell-specific operation
 * @commands: command and arguments
 *
 * Return:
 *   - SKIP_FORK if the command is a shell-specific operation,
 *   - DO_EXECVE if not a built-in,
 *   - EXIT_SHELL if the command is for exiting the shell,
 *   - EXIT_SHELL_CODE if exiting with a particular code
 */
int check_if_builtin(char **commands)
{
    char **current_command = commands;
    int built_in_result;

    do
    {
        if (**current_command == '#')
        {
            *current_command = NULL;
            break;
        }
        if (comparisonString("~", *current_command, ComPareString) == YES
            && my_new_function(environ, "HOME="))
        {
            *current_command = strdup(my_new_function(environ, "HOME=") + 5);
            continue;
        }
        if (comparisonString("~/", *current_command, StartSWith) == YES
            && my_new_function(environ, "HOME="))
        {
            *current_command = concatenate_strings_custom(my_new_function(environ, "HOME=") + 5, *current_command + 1);
        }
        *current_command = evaluate_variables(*current_command);

        current_command++;
    } while (*current_command);

    if (!*commands)
        return ByPassFork;

    built_in_result = handle_command_aliases(commands, NO);
    if (built_in_result == ExecuteCommand || built_in_result == ByPassFork)
        return built_in_result;

    if (comparisonString("exit", *commands,  ComPareString) == YES)
    {
        if (commands[1])
        {
            status = my_custom_function_for_string_to_integer(commands[1]);
            if (status < 0)
            {
                status = 2;
                handle_error(commands[0], commands[1]);
                return ByPassFork;
            }
        }
        return TERminalShell;
    }
    else if (comparisonString("setenv", *commands, ComPareString) == YES && commands[1] && commands[2])
        return setenv(commands[1], commands[2], 1); /* Assuming 'replace' parameter is set to 1*/
    else if (comparisonString("unsetenv", *commands, ComPareString) == YES && commands[1])
        return unsetenv(commands[1]);
    else if (comparisonString("cd", *commands, ComPareString) == YES)
        return change_current_directory(commands[1]);
    else if (comparisonString("env", *commands, ComPareString) == YES)
        return print_environment();

    return ExecuteCommand;
}
/**
 * evaluate_logical_operator - evaluates the logical operator between commands
 * @commands: command and arguments
 * @eXcute: first char of logical operator
 * @final_eval: if last command in logic evaluated to true or false
 *
 * Return: if this command evaluates to true or false
 */
int evaluate_logical_operator(char **commands, char eXcute, int final_eval)
{
    int result;

    if (final_eval == NOT_APPLICABLE)
    {
        result = process_directive(commands);
        if (result == TERminalShell)
            return TERminalShell;
        else if (result == YES)
            return YES;
        else
            return NO;
    }
    else if (final_eval == YES && eXcute == '&')
    {
        result = process_directive(commands);
        if (result == TERminalShell)
            return TERminalShell;
        else if (result == YES)
            return YES;
        else
            return NO;
    }
    else if (final_eval == NO && eXcute == '|')
    {
        result = process_directive(commands);
        if (result == TERminalShell)
            return TERminalShell;
        else if (result == YES)
            return YES;
        else
            return NO;
    }
    else if (final_eval == YES && eXcute == '|')
         return YES;
    else
        return YES;
}

/**
 * find_executable_path - Finds the full path of an executable in the given arguments and system PATH
 * @input_arguments: Array of command and arguments
 *
 * Return: Full path of the executable if found, NULL otherwise
 */
char *find_executable_path(char **input_arguments)
{
    char *cMd_buffer;
    char *tOtal_buffer;
    char *lOcationString = NULL;
    char *pathWay_pointer;
    char *temporary_path;
    char **var_directory = NULL;
    char **var_directory_pointer;

    if (access(input_arguments[0], X_OK) == 0) {
        return (strdup(input_arguments[0]));
    }

    if (my_new_function(environ, "PATH=") != NULL) {
        lOcationString = strdup(my_new_function(environ, "PATH=") + 5);
    }

    pathWay_pointer = lOcationString;

    if (lOcationString != NULL) {
        do {
            if (*pathWay_pointer == ':' && *(pathWay_pointer + 1) == ':') {
                *(pathWay_pointer + 1) = '\0';
                temporary_path = (concatenate_strings_custom(lOcationString, ".:"));
                pathWay_pointer = concatenate_strings_custom(temporary_path, pathWay_pointer + 2);
                free(lOcationString);
                free(temporary_path);
                lOcationString = pathWay_pointer;
            }
            pathWay_pointer++;
        } while (*pathWay_pointer != '\0');
    }

    if (lOcationString != NULL) {
        var_directory = my_new_function_name(lOcationString, ':', NULL);
    }

    var_directory_pointer = var_directory;

    cMd_buffer = concatenate_strings_custom("/", input_arguments[0]);

    tOtal_buffer = strdup(cMd_buffer);

    if (var_directory != NULL) {
        do {
            if (access(tOtal_buffer, X_OK) == 0) {
                break;
            }
            free(tOtal_buffer);
            tOtal_buffer = concatenate_strings_custom(*var_directory_pointer, cMd_buffer);
            var_directory_pointer++;
        } while (*var_directory_pointer != NULL);
    }

    free(cMd_buffer);
    free(lOcationString);
    free(var_directory);

    if (access(tOtal_buffer, X_OK) != 0) {
        handle_error(input_arguments[0], NULL);
        free(tOtal_buffer);
        return (NULL);
    } else {
        return (tOtal_buffer);
    }
}

/**
 * process_directive - handles the execution of a command
 * @command_arguments: array of command and arguments
 *
 * Returns: TRUE if successful, EXIT_SHELL if shell should exit
 */
int process_directive(char **command_arguments)
{
    char *buffer_pointer = *command_arguments;
    char *executable_name;
    pid_t process_id;
    int operation_type = check_if_builtin(command_arguments);

    if (operation_type == ExecuteCommand)
    {
        executable_name = find_executable_path(command_arguments);
        if (executable_name == NULL)
            return (NO);

        process_id = fork();
        if (process_id == -1)
        {
            exit(EXIT_FAILURE);
        }
        if (process_id == 0)
        {
            execve(executable_name, command_arguments, environ);
            exit(EXIT_FAILURE);
        }
        wait(&status);
        free(executable_name);
        fflush(stdin);
        if (status != 0)
            status = 2;
    }

    if (comparisonString("false", *command_arguments, ComPareString) == YES)
        status = 1;

    if (*command_arguments != buffer_pointer)
        free(*command_arguments);
    command_arguments++;

    while (*command_arguments != NULL)
    {
        while (*buffer_pointer != '\0')
        {
            buffer_pointer++;
        }
        buffer_pointer++;

        if (*command_arguments != buffer_pointer)
            free(*command_arguments);

        command_arguments++;
    }

    if (operation_type == TERminalShell)
        return (TERminalShell);

    if (status != 0)
        return (NO);

    return (YES);
}
