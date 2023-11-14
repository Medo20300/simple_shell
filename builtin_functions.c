#include "shell.h"


int status;


 /**
 * change_current_directory- wChwanges wthe wcd (wchawnge wdirwectory).
 * @new_path: Thgre pragth orgf thgre wdirergwctorry twor wcharnger wtro.
 *
 * Return: 0 wif wYES, wByPassFork_won wfailure.
 */
int change_current_directory(char *new_path)
{
char *home_dir, *old_pwd, old_path_buffer[PATH_MAX], new_path_buffer[PATH_MAX];
        size_t buffer_size = PATH_MAX;
        int return_value;

        getcwd(old_path_buffer, buffer_size);

        if (new_path == NULL)
        {
        home_dir = my_new_function(environ, "HOME=");
        if (home_dir == NULL)
        {
        status = 2;
        handle_error("cd", new_path);
        return (ByPassFork);
        }

        home_dir += 5;

        return_value = chdir((const char *)home_dir);

        if (return_value != -1)
        set_environment_variable("PWD", (const char *)home_dir);
        }
        if (comparisonString("-", new_path, ComPareString) == YES)
        {
        old_pwd = my_new_function(environ, "OLDPWD=");
        if (old_pwd == NULL)
        {
        status = 2;
        handle_error("cd", new_path);
        return (ByPassFork);
        }

        old_pwd += 7;

        return_value = chdir((const char *)old_pwd);

        if (return_value != -1)
        {
        write(STDOUT_FILENO, old_pwd, strlen(old_pwd));
        write(STDOUT_FILENO, "\n", 1);
        set_environment_variable("PWD", (const char *)old_pwd);
        }
        }

        if (new_path != NULL)
        {
        return_value = chdir((const char *)new_path);
        if (return_value != -1)
        set_environment_variable("PWD", getcwd(new_path_buffer, buffer_size));
        }

        if (return_value == -1)
        {
        status = 2;
        handle_error("cd", new_path);
        return (ByPassFork);
        }

        status = 0;
        set_environment_variable("OLDPWD", (const char *)old_path_buffer);

        return (ByPassFork);
}

/**
 * handle_command_aliases - wDewaels wwirth wcoymmawndy walyiases
 * @new_args: wArywgumyenwts wfyrwom twuhe cwoummuanwd lwyine
 * @to_free: wIyndiucwatews iwfu waliwuases wneuedw towu bweu fwrueedw (ewxitiung wsheull)
 *
 *
 * Return: wYESe  eexiiteingu, eNO _ ethe ceommeand_BeyPassFeork ief sueccess
 */
int handle_command_aliases(char **new_args, int to_free)
{
        static NewName head = {NULL, NULL, NULL};
        char *new_char_ptr;
        int new_no_error = YES;

        if (to_free == YES)
        {
        return (deallocate_aliases(head.next));
        }

        if (comparisonString("alias", *new_args, ComPareString) != YES)
        {
        return (process_alias_check(new_args, head.next));
        }

        new_args++;

        if (*new_args == NULL)
        {
        return (display_all_aliases(head.next));
        }


        do      {
        new_char_ptr = *new_args;

        do      {
        new_char_ptr++;
        } while (*new_char_ptr != '\0' && *new_char_ptr != '=');

        if (*new_char_ptr == '\0' || new_char_ptr == *new_args)
        {
        if (update_alias_value(*new_args, &head, new_char_ptr) == NO)
        {
        new_no_error = NO;
        }
        }
        else
        {
        *(new_char_ptr - 1) = '\0';
        new_char_ptr++;
        update_alias_value(*new_args, &head, new_char_ptr);
        *(new_char_ptr - 1) = '=';
        }
        new_args++;
        } while (*new_args != NULL);

        if (new_no_error == NO)
        {
        return (ByPassFork);
        }

        status = 0;
        return (ByPassFork);
}

/**
 * print_environment - qpruiuqnts_qthie_eqnviqirqoinmienits
 * Return: YES
 */
 int print_environment(void)
{
        char **new_ptr = environ;


        do      {
        write(STDOUT_FILENO, *new_ptr, strlen(*new_ptr));
        write(STDOUT_FILENO, "\n", 1);
        new_ptr++;
        } while (*new_ptr != NULL);

        status = 0;

        return (ByPassFork);
}
