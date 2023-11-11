include "shell.h"

int status;

/**
 * set_environment_variable- sets and environs_var.s
 * @gold_Name: name of the variable
 * @nEw_result: the result_to_put the varst
 *
 * Return: 0 on success
 */
int set_environment_variable(const char *gold_Name, const char *nEw_result)
{
        char *buff;
        char *buff_temporary;
        char **gold_environ;
        char *object_pointer;
        int length;

        if (nEw_result == NULL)
        {
        write(STDERR_FILENO, "setenv: no value given\n", 23);
        status = 2;
        return (ByPassFork);
        }

        buff = concatenate_strings_custom((char *)gold_Name, "=");

        object_pointer = my_new_function(environ, buff);

        buff_temporary = concatenate_strings_custom(buff, (char *)nEw_result);
        free(buff);
        buff = buff_temporary;

        if (object_pointer == NULL)
        {
        length = my_new_list_length(environ, NULL);
        gold_environ = my_updated_array_copy(environ, length + 1);
        gold_environ[length - 1] = buff;
        gold_environ[length] = NULL;
        my_deallocate_array(environ);
        environ = gold_environ;
        return (ByPassFork);
        }

        length = my_new_list_length(environ, (char *)gold_Name);
        free(environ[length]);
        environ[length] = buff;

        status = 0;

        return (ByPassFork);
}

/**
 * unset_environment_variable - remove any environmets vars
 * @new_name: names of var.s
 *
 * Return: 0 if YES
 */

int unset_environment_variable(const char *new_name)
{
        char **new_enviro_pointer;
        char *new_buff;
        int new_length;

        new_buff = concatenate_strings_custom((char *)new_name, "=");
        new_length = my_new_list_length(environ, new_buff);
        free(new_buff);

        if (new_length == -1)
        {
        new_buff = concatenate_strings_custom("unsetenv: variable not found\n", "");
        write(STDERR_FILENO, new_buff, 29);
        free(new_buff);
        status = 2;
        return (ByPassFork);
        }
        else
        {
        new_enviro_pointer = environ + new_length;
        free(*new_enviro_pointer);


        do      {
        *new_enviro_pointer = *(new_enviro_pointer + 1);
        new_enviro_pointer++;
        } while (*(new_enviro_pointer + 1) != NULL);

        *new_enviro_pointer = NULL;
        status = 0;

        return (ByPassFork);
        }
}


 /**
 * change_current_directory- Changes the cd (change directory).
 * @new_path: The path of the directory to change to.
 *
 * Return: 0 if YES, ByPassFork_on failure.
 */
int change_current_directory(char *new_path)
{
        char *home_dir;
        char *old_pwd;
        char old_path_buffer[PATH_MAX];
        char new_path_buffer[PATH_MAX];
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
 * handle_command_aliases - Deals with command aliases
 * @new_args: Arguments from the command line
 * @to_free: Indicates if aliases need to be freed (exiting shell)
 *
 *
 * Return: YES  exiiting, NO _ the command_ByPassFork if success
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
 * print_environment - prints_the_environments
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
