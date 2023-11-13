#include "shell.h"


/**
 * my_new_function_name - Description of what the function does r
 * @my_new_parameter_name_1: Description of the first parameter
 * @my_new_parameter_name_2: Description of the second parameter
 *
 * Return: Description of what the function returns
 */
char *my_new_function(char **my_new_parameter_name_1,
                char *my_new_parameter_name_2)
{
        do {
        if (comparisonString(*my_new_parameter_name_1, my_new_parameter_name_2, StartSWith) == YES)
        return (*my_new_parameter_name_1);

        my_new_parameter_name_1++;
        } while (*my_new_parameter_name_1 != NULL);

        return (NULL);
}

/**
 * my_new_function_name - Description of what the function does
 * @input_string: the buffer
 * @delimiter: character to mark the end of a list entry
 * @next_separator: if the string has semicolons, next_separator becomes the
 *      location after the semicolon
 *
 * Return: a pointer to the list
 */
char **my_new_function_name(char *input_string, char delimiter, char **next_separator)
{
        char *string_ptr = input_string;
        unsigned int i = 2;
        char **result_array = NULL;


        do      {
        if (*string_ptr == ';')
        break;
        if (*string_ptr == delimiter && *(string_ptr + 1) != '\0')
        i++;

        string_ptr++;
        } while (*string_ptr != '\0');

        result_array = malloc(i * sizeof(char **));
        if (result_array == NULL)
        exit(EXIT_FAILURE);

        result_array[0] = input_string;
        string_ptr = input_string;
        i = 1;


        do      {
        if (*string_ptr == delimiter)
        {
        *string_ptr = '\0';
        string_ptr++;
        if (*string_ptr == ';')
        {
        result_array[i] = NULL;
        if (*(string_ptr + 1) != '\0' && *(string_ptr + 2) != '\0')
        *next_separator = string_ptr + 2;
        break;
        }
        if (*string_ptr != '\0')
        {
        result_array[i] = string_ptr;
        i++;
        }
        }
        string_ptr++;
        } while (*string_ptr != '\0');

        result_array[i] = NULL;

        return (result_array);
}

/**
 * my_new_list_length - finds the length of a list, or the index of an entry
 * @my_new_list: list to be evaluated
 * @my_new_entry: entry to be indexed
 *
 * Return: length or index if success, -1 if failure
 */
int my_new_list_length(char **my_new_list, char *my_new_entry)
{
        int count = 0;

        if (my_new_entry == NULL)
        {

        do      {
        count++;
        my_new_list++;
        } while (*my_new_list != NULL);

        count++;
        return (count);
        }
        else
        {

        do      {
        if (comparisonString(*my_new_list, my_new_entry, StartSWith) == YES)
        return (count);

        count++;
        my_new_list++;
        } while (*my_new_list != NULL);
        }

        return (-1);
}

/**
 * my_updated_array_copy - copies an array
 * @source_array: array to be copied
 * @destination_size: size of new array
 *
 * Return: the new array
 */
char **my_updated_array_copy(char **source_array, int destination_size)
{
        char **modern_Array = NULL;
        char **pointer_Array;

        modern_Array = malloc(sizeof(char **) * destination_size);

        if (modern_Array == NULL)
        exit(EXIT_FAILURE);

        pointer_Array = modern_Array;


        do      {
        *pointer_Array = strdup(*source_array);
        pointer_Array++;
        source_array++;
        } while (*source_array != NULL);

        *pointer_Array = NULL;

        return (modern_Array);
}

/**
 * my_deallocate_array - frees a two dimensional array
 * @my_arguments: array to be freed
 *
 * Return: TRUE
 */
int my_deallocate_array(char **my_arguments)
{
        char **m_pointer = my_arguments;


        do      {
        free(*m_pointer);
        m_pointer++;
        } while (*m_pointer != NULL);

        free(my_arguments);

        return (YES);
}
