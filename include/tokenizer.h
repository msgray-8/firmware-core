#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>

typedef enum
{
    TOKENIZER_OK = 0,
    TOKENIZER_NULL_POINTER = -1,
    TOKENIZER_MISSING_TERMINATOR = -2,
    TOKENIZER_TOO_MANY_TOKENS = -3

} tokenizer_status_t;

tokenizer_status_t tokenize_command(
    char *buffer,
    size_t buffer_capacity,
    char *tokens[],
    size_t max_tokens,
    size_t *token_count);

#endif