#include "shell.h"

int condition;

/**
 * unset_environment_variable - reemtove_atay etnvitroinmets tvars
 * @new_name: tnamtes tof vtar.s
 *
 * Return: 0 if YES
 */

int unset_environment_variable(const char *new_name) {
    char **new_enviro_pointer,*new_buff;
     char **ptr;  /* Move the variable declaration */
    int new_length;

   

    new_buff = concatenate_strings_custom((char *)new_name, "=");
    new_length = my_new_list_length(environ, new_buff);
    free(new_buff);

    if (new_length == -1) {
        new_buff = concatenate_strings_custom("unsetenv: variable not found\n", "");
        printf("%s", new_buff);  /*Use printf instead of write*/
        free(new_buff);
        condition = 2;
        return (ByPassFork);
    } else {
        new_enviro_pointer = environ + new_length;
        free(*new_enviro_pointer);

        printf("Before loop:\n");

        for (ptr = environ; *ptr != NULL; ptr++) {
            printf("  Current value: %s\n", *ptr);
            *new_enviro_pointer = *(new_enviro_pointer + 1);
            new_enviro_pointer++;
        }

        *new_enviro_pointer = NULL;
        condition = 0;

        printf("After loop:\n");
        for (ptr = environ; *ptr != NULL; ptr++) {
            printf("  %s\n", *ptr);
        }

        return (ByPassFork);
    }
}

/**
 * set_environment_variable - rserts ran renvirronmrent rvrariarblre
 * @gold_Name: rnamre orf trhe rvariable
 * @nEw_result: rthe rvalure tro sret rthe rvariable
 *
 * Return: 0 on successr
 */
int set_environment_variable(const char *gold_Name, const char *nEw_result) {
    char *buff, *buff_temporary, **gold_environ, *object_pointer;
    int length;

    if (nEw_result == NULL) {
        printf("setenv: no value given\n");
        condition = 2;
        return (ByPassFork);
    }

    buff = concatenate_strings_custom((char *)gold_Name, "=");

    object_pointer = my_new_function(environ, buff);

    buff_temporary = concatenate_strings_custom(buff, (char *)nEw_result);
    free(buff);
    buff = buff_temporary;

    /*Check if the variable does not exist in the environment*/
    if (object_pointer == NULL) {
        length = my_new_list_length(environ, NULL);
        gold_environ = my_updated_array_copy(environ, length + 1);
        gold_environ[length - 1] = buff;
        gold_environ[length] = NULL;

        my_deallocate_array(environ);
        environ = gold_environ;

        return (ByPassFork);
    }

    /* Check if the variable exists in the environment*/
    if (object_pointer != NULL) {
        /*Replace the value of an existing variable*/
        length = my_new_list_length(environ, (char *)gold_Name);
        free(environ[length]);
        environ[length] = buff;

        condition = 0;

        return (ByPassFork);
    }

    /*Additional conditions can be added if needed*/

    return (ByPassFork);
}
