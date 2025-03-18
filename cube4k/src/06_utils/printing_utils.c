#include "../../headers/cub3d.h"

/**
 * @brief Prints a formatted message with a detail to the standard output.
 *
 * This function takes a message and a detail string, and prints them
 * in the format "message: detail" followed by a newline character.
 *
 * @param message The main message to be printed.
 * @param detail The detail to be printed alongside the message.
 */
void    print_message(const char *message, const char *detail)
{
    printf("%s: %s\n", message, detail);
}
