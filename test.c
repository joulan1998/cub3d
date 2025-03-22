
#include "includes/cub3d.h" // For strdup

void immegrate_map(char ***to, char ***from)
{
    int i;

    // Check if the source map is NULL
    if (!from || !*from)
    {
        *to = NULL; // Set destination to NULL
        return;
    }

    // Count the number of rows in the source map
    for (i = 0; (*from)[i]; i++)
        ;

    // Allocate memory for the destination map (rows + 1 for NULL terminator)
    *to = (char **)malloc((i + 1) * sizeof(char *));
    if (!*to)
        return; // Handle allocation failure

    // Copy each row from the source map to the destination map
    for (i = 0; (*from)[i]; i++)
    {
        (*to)[i] = strdup((*from)[i]); // Duplicate the string
        if (!(*to)[i])
        {
            // Handle allocation failure: free previously allocated memory
            while (i--)
                free((*to)[i]);
            free(*to);
            *to = NULL;
            return;
        }
    }

    // NULL-terminate the destination map
    (*to)[i] = NULL;
}