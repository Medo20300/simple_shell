#include "shell.h"

/**
 * my_new_function_name - Description of what the function does
 * @my_new_parameter_name_1: Description of the first parameter
 * @my_new_parameter_name_2: Description of the second parameter
 *
 * Return: Description of what the function returns
*/

char *my_new_function(char **my_new_parameter_name_1,char *my_new_parameter_name_2)
{
	do 
	{
		if (comparisonString(*my_new_parameter_name_1, my_new_parameter_name_2, StartSWith) == YES)
			return (*my_new_parameter_name_1);

		my_new_parameter_name_1++;
	} 
	while (*my_new_parameter_name_1 != NULL)
	return (NULL);
}

/**
 * my_new_function_name - Description of what the function does
 * @input_string: the buffer
 * @delimiter: character to mark the end of a list entry
 * @next_separator: if the string has semicolons, next_separator becomes the
 * location after the semicolon
 *
 * Return: a pointer to the list
*/
char **my_new_function_name(char *input_string, char delimiter, char **next_separator)
{
	char *string_ptr = input_string;
	unsigned int i = 2;
	char **result_array = NULL;


	do
	{
		if (*string_ptr == ';')
			break;
		if (*string_ptr == delimiter && *(string_ptr + 1) != '\0')
			i++;

		string_ptr++;
	}
	while (*string_ptr != '\0');

	result_array = malloc(i * sizeof(char **));
	if (result_array == NULL)
		exit(EXIT_FAILURE);

	result_array[0] = input_string;
	string_ptr = input_string;
	i = 1;
	
	do
	{
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
	}
	while (*string_ptr != '\0');

	result_array[i] = NULL;

	return (result_array);
}
