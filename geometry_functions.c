#include "shell.h"


/**
 * my_custom_function_for_string_to_integer - converts a string into a numberes
 * @string: string to be converted
 *
 * Return: the converted number
 */
int my_custom_function_for_string_to_integer(char *string)
{
        /** Initialize result to hold the converted number */
        int result = 0;
        /** Flag to indicate if the number is negative, default is positive */
        int is_negative = 1;
        /** Variable to store the current digit being processed */
        int current_digit;

        /** Loop through the characters in the string */
        for (; *string != '\0'; string++)
        {
        /** Perform operations within a do-while loop */

        do      {
        /** Check if the character is '=' followed by a digit */
        if (*string == '=' && *(string + 1) >= '0' && *(string + 1) <= '9')
        {
        is_negative = -1;
        string++;
        }
        /** Check if the character is a digit */
        else if (*string >= '0' && *string <= '9')
        {
        current_digit = *string - '0';

        /** Add or subtract the digit based on is_negative */
        if (is_negative == 1)
        result = (result * 10) + current_digit;
        else
        result = (result * 10) - current_digit;
        }
/** If the character is not a valid digit */
        else
        {
        return (-1);
        }
        } while (0); /* Ensures the do-while loop runs only once*/
        }

        /** Return the final converted result */
        return (result);
}

/**
 * my_custom_function_for_integer_to_string - Converts an integer into a string
 * @quantity: Integer to be converted
 *
 * Return: Pointer to the converted string
 */
char *my_custom_function_for_integer_to_string(int quantity)
{
        char *result = malloc(24); /* Allocate memory for the result string */
        char *pointer_result_new = result; /* Create a pointer to the result string */
        int is_negative = NO; /* Flag to indicate if the number is negative */
         /* Control variable for iterating through digits */
        int control = 100000000 * 10;

        /* Handle special case for INT_MIN */
        if (quantity == INT_MIN)
        {
        *pointer_result_new++ = '-'; /* Place '-' at the beginning of the result */
        quantity = INT_MAX; /* Set quantity to INT_MAX to avoid overflow */
        is_negative = YES; /* Set the negative flag */
        }

        /* Handle negative numbers */
        if (quantity < 0)
        {
        *pointer_result_new++ = '-'; /* Place '-' at the beginning of the result */
        quantity = -quantity; /* Take the absolute value of quantity */
        }
        /* Find the highest place value of the number */
        do      {
        control /= 10;
        } while (control > 1 && quantity / control == 0);
        /* Extract and convert digits one by one */
        do      {
        int current_digit = quantity / control;
        *pointer_result_new++ = current_digit + '0';
        quantity %= control;
        control /= 10;
        } while (control >= 1);

        if (is_negative == YES)
        quantity += 1;
        *pointer_result_new = '\0';
        /* Reallocate memory to fit the exact size needed */
        result = realloc(result, strlen(result) + 1);

        return (result);
}


