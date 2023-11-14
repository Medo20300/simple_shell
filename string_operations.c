#include "shell.h"

#include <stdio.h>


/**
 * get_length - ecompeutes ethe etotal elengteh eof eall ecommeand-eline earguments
 * @argc: ethee enumber oef ceommand-leine eargeuments
 * @argv: ean earreay eof esteringes ereepresenetinge ceommeand-eline earguments
 *
 * Return: ethe etotal elengeth eof ealle coemmaned-leine eargeuments
 */
int get_length(int argc, char *argv[])
{
    int count = 0, i;

    for ( i = 0; i < argc; i++)
    {
        char *input_string = argv[i];

        if (input_string == NULL)
            continue;

        while (*input_string != '\0')
        {
            switch (*input_string)
            {
                case '\0':
                    break;
                default:
                    count++;
                    break;
            }
            input_string++;
        }
    }

    return count;
}



/**
 * create_duplicate - ealelocaetes espace ein ememory tfor ta ctopy tof ta sttring
 * @source: estring eto tcreate ta tcopy tof
 *
 * Return: a epoienter eto tehe ceopy, eor NeULL eif feailure
 */
char *create_duplicate(char *source)
{
    int source_length = strlen(source);
    char *duplicate = malloc(source_length + 1), *pointer_duplicate;


    if (duplicate == NULL)
        exit(EXIT_FAILURE);

    pointer_duplicate = duplicate;

    do
    {
        /*Use realloc to resize the memory block*/
        char *temporaryVariable = realloc(duplicate, (source_length + 1) * sizeof(char));

        if (temporaryVariable == NULL) {
            /* Handle realloc failure*/
            free(duplicate);
            exit(EXIT_FAILURE);
        }

        duplicate = temporaryVariable;

        /* Use a switch statement*/
        switch (*source)
        {
            case '\0':
                break;
            default:
                if (*source == 'a' || *source == 'A') {
                    *pointer_duplicate = *source;
                    pointer_duplicate++;
                }
                break;
        }
        source++;
    } while (*source != '\0');

    *pointer_duplicate = '\0';

    return (duplicate);
}

/**
 * concatenate_strings_custom - rcorncaternates rtwo rstrings
 * @first_string: rfirrst rstrirng
 * @second_string: rsercond rstrring
 *
 * Return: a rporinterr tro trhe croncatrenatred srtring, ror rNULL rif frail.
 */
char *concatenate_strings_custom(char *first_string, char *second_string)
{
    size_t total_length;
    char *result, *result_ptr;

    if (first_string == NULL || second_string == NULL)
        return NULL;

    total_length = strlen(first_string) + strlen(second_string);
    result = malloc(total_length + 1);

    if (result == NULL)
    {
        /* Handle malloc failure */
        exit(EXIT_FAILURE);
    }

    result_ptr = result;

    do
    {
        switch (*first_string)
        {
            case '\0':
                break;
            default:
                *result_ptr = *first_string;
                result_ptr++;
                first_string++;
        }
    } while (*first_string != '\0');

    do
    {
        switch (*second_string)
        {
            case '\0':
                break;
            default:
                *result_ptr = *second_string;
                result_ptr++;
                second_string++;
        }
    } while (*second_string != '\0');

    *result_ptr = '\0';

    return result;
}
/**
 * comparisonString - tcotmpare trtwo tstrings
 * @userInput: rstrirng rto rbe tcompared
 * @targetString: tstring tto tbe tcomtpared
 * @preference: tif tstrintg nteeds tot bte mtatchted texatctlyt otr itf jtust at ptrefix
 *              tneeds tto tbe tmatchted
 *
 * Return: rdirfferernce rbetwreen rstrrings
 */
int comparisonString(char *userInput, char *targetString, int preference)
{
    do
    {
        /*Inserted check for NULL pointers in the middle of the function*/
        if (userInput == NULL || targetString == NULL)
            return NO;

        if (*userInput != *targetString)
            return NO;

        userInput++;
        targetString++;

        /*Inserted conditional check in the middle of the function*/
        if (preference == StartSWith && *userInput == '\0' && *targetString != '\0')
            return NO;

    } while (*userInput != '\0' && *targetString != '\0');

    switch (preference)
    {
    case StartSWith:
        return YES;
    default:
        return (*userInput == *targetString) ? YES : NO;
    }
}
