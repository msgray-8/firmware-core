#include <stddef.h>

#include "tokenizer.h"

tokenizer_status_t tokenize_command(
    char *buffer,
    size_t buffer_capacity,
    char *tokens[],
    size_t max_tokens,
    size_t *token_count)
{
    if ((buffer == NULL) ||
        (tokens == NULL) ||
        (token_count == NULL))
    {
        return TOKENIZER_NULL_POINTER;
    }

    *token_count = 0U;

    size_t terminator_index = 0U;

    while ((terminator_index < buffer_capacity) &&
           (buffer[terminator_index] != '\0'))
    {
        terminator_index++;
    }

    if (terminator_index == buffer_capacity)
    {
        return TOKENIZER_MISSING_TERMINATOR;
    }

    size_t i = 0U;

    while (i < terminator_index)
    {
        while ((i < terminator_index) &&
               (buffer[i] == ' '))
        {
            buffer[i] = '\0';
            i++;
        }

        if (i >= terminator_index)
        {
            break;
        }

        if (*token_count >= max_tokens)
        {
            return TOKENIZER_TOO_MANY_TOKENS;
        }

        tokens[*token_count] = &buffer[i];
        (*token_count)++;

        while ((i < terminator_index) &&
               (buffer[i] != ' '))
        {
            i++;
        }

        if (i < terminator_index)
        {
            buffer[i] = '\0';
            i++;
        }
    }

    return TOKENIZER_OK;
}