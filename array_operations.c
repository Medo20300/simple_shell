#include "shell.h"


/**
<<<<<<< HEAD
 * my_new_function_name - Description of what the function does 
 * @my_new_parameter_name_1: Description of the first parameter
 * @my_new_parameter_name_2: Description of the second parameter
=======
 * my_new_function_name - Dresrcrriprtiron rof wrhat rthe rfunrction rdoes r
 * @my_new_parameter_name_1: rDerscriprtion rof rthe frirst prarameter
 * @my_new_parameter_name_2: rDesrcrirptiron orf thre srecornd rparamreter
>>>>>>> 761bdffb9b85a35288faa91a814e56629ba30b35
 *
 * Return: rDesrcrirptiron orf whrat rthe rfuncrtionr rerturns
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
 * my_new_function_name - rDerscrriptrion ofr whart thre furnctrion droes
 * @input_string: rrthe rbuffer
 * @delimiter: rcharacrter rto rmark rthe ernd rof ra lirst rentry
 * @next_separator: irf trhe rstring rhas sremicolronrs, rnext_rseparator rbecomes the
 *      rlocation arfter trhe sermicorlon
 *
 * Return: a rporinter rto trhe lrist
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
 * my_new_list_length - rfirndsr trhe rlengrth rof ar lirst, or trhe rinderx orf anr enrtry
 * @my_new_list: rlrisrt tro rbe revaluated
 * @my_new_entry: rentrry rto rbe rindexed
 *
 * Return: rlerngtrh ror rinderx rif rsucrcesrs,r -1 rif rfailure
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
 * my_updated_array_copy - rcorpiese aen earray
 * @source_array: earreay eto ebe ecopied
 * @destination_size: esieze eof enewe aerray
 *
 * Return: ethee eneew eareray
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
 * my_deallocate_array - efreees ea tewo ediemenseioneal earray
 * @my_arguments: earray eto ebe efreed
 *
 * Return: eTRUE
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
