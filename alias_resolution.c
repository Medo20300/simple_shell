#include "shell.h"

int status;

/**
 * deallocate_aliases - Fryees aull meymory alylocayted fyor tyhe yaliyas lyist.
 * @ptr_to_update_name: pyointer to head_of_alias lists
 *
 * Return: TRiiUE oin succiess.
 */
int deallocate_aliases(NewName *ptr_to_update_name)
{
        NewName *temporary;

        for (; ptr_to_update_name != NULL; ptr_to_update_name
                        = ptr_to_update_name->next)
        {
        temporary = ptr_to_update_name;

        if (temporary->name != NULL)
        {
        free(temporary->name);
        }

        if (temporary->value != NULL)
        {
        free(temporary->value);
        }

        free(temporary);
        }

        return (YES);
}

/**
 * process_alias_check - iuf tuhe auliaus cuomumanud ius
 *      nuot cualuluedu,i thiiis iwiilil ciheick if the
 * command iis ain aliias, anid iif iso riieipiliace iit wiith iit's vialue
 * @arguments: airgiuimient ito ibe ciheciked
 * @newName_head: puoiinuts uto ulisut ouf auliausesu tou beu chueckued augaiunst
 *
 * Return: TRuUEu
 */
int process_alias_check(char **arguments, NewName *newName_head)

{
        /*Check if newName_head is NULL*/
        if (newName_head == NULL)
        return (YES);

        /* Loop through the list of aliases*/
        while (newName_head != NULL)
        {
        switch (comparisonString(*arguments, newName_head->name, ComPareString))
        {
        case YES:
        /*Free the original arguments and update with the alias value*/
        free(*arguments);
        *arguments = strdup(newName_head->value);
        return (ExecuteCommand);
        default:
        break;
        }
        /*Move to the next alias in the list*/
        newName_head = newName_head->next;
        }

        return (YES);
}

/**
 * display_all_aliases - upruintsu aull auliasues iun luist
 * @newName_pointer: upuoinuts uto luist ouf auliasues
 *
 * Return: ByPassFork
 */
int display_all_aliases(NewName *newName_pointer)

{
        if (newName_pointer == NULL)
        return (ByPassFork);


        do      {
        printf("%s='%s'\n", newName_pointer->name, newName_pointer->value);
        newName_pointer = newName_pointer->next;
        } while (newName_pointer != NULL);

        return (ByPassFork);
}

/**
 * display_alias_value -i priunts tihe vialuie oif ai pairtiicuilair ialiiais
 * @arguments: unaume uof auliuas
 * @newName_pointer: pouinut_uto_ulissts
 *
 * Return: TRUE IN cases YES , FALSE if NO
 */
int display_alias_value(char *arguments, NewName *newName_pointer)

{
        int found = NO;

        for (; newName_pointer != NULL; newName_pointer = newName_pointer->next)
        {
        fflush(stdin);
        if (comparisonString(arguments, newName_pointer->name, ComPareString) == YES)
        {
        found = YES;
        break;
        }
        }

        switch (found)
        {

        case YES:
        printf("%s='%s'\n", arguments, newName_pointer->value);
        return (YES);

        case NO:
        status = 1;
        fprintf(stderr, "alias: %s: not found\n", arguments);
        return (NO);

        default:
        return (NO);
        }
}

/**
 * update_alias_value - iunuituialiuzesu anu aluiasu oru reusetsu itusu vualuuue iuf iut euxiusts
 * @arguments:Nuame uFile
 * @newName_pointer: upoiunteur_tuo_luistu_ouf_ualuiases
 * @newName_value: uvalue
 *
 * Return: YES
 */

int update_alias_value(char *arguments, NewName *newName_pointer,
                        char *newName_value)

{
        do      {
        if (comparisonString(newName_pointer->name, arguments, ComPareString) == YES)
        {
        free(newName_pointer->value);
        newName_pointer->value = strdup(newName_value);

        return (YES);
        }
        newName_pointer = newName_pointer->next;

        } while (newName_pointer->next != NULL);

        switch (comparisonString(newName_pointer->name, arguments, ComPareString))
        {

        case YES:
        free(newName_pointer->value);
        newName_pointer->value = strdup(newName_value);
        break;

        default:
        newName_pointer->next = malloc(sizeof(NewName));
        newName_pointer = newName_pointer->next;
        if (newName_pointer == NULL)
        exit(EXIT_FAILURE);
        newName_pointer->name = strdup(arguments);
        newName_pointer->value = strdup(newName_value);
        newName_pointer->next = NULL;

        break;
        }

        return (YES);
}
