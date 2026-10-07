#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "tokenizer.h"

static int test_normal_command(void)
{
    char command[] = "SET LED ON";
    char *tokens[3];
    size_t token_count = 0U;

    tokenizer_status_t status =
        tokenize_command(
            command,
            sizeof(command),
            tokens,
            3U,
            &token_count);

    if (status != TOKENIZER_OK)
    {
        printf("FAIL: normal command returned error\n");
        return 1;
    }

    if (token_count != 3U)
    {
        printf("FAIL: expected 3 tokens\n");
        return 1;
    }

    if ((strcmp(tokens[0], "SET") != 0) ||
        (strcmp(tokens[1], "LED") != 0) ||
        (strcmp(tokens[2], "ON") != 0))
    {
        printf("FAIL: normal command tokens incorrect\n");
        return 1;
    }

    printf("PASS: normal command\n");
    return 0;
}

static int test_empty_input(void)
{
    char command[] = "";
    char *tokens[1];
    size_t token_count = 99U;

    tokenizer_status_t status =
        tokenize_command(
            command,
            sizeof(command),
            tokens,
            1U,
            &token_count);

    if ((status != TOKENIZER_OK) ||
        (token_count != 0U))
    {
        printf("FAIL: empty input\n");
        return 1;
    }

    printf("PASS: empty input\n");
    return 0;
}

static int test_multiple_spaces(void)
{
    char command[] = "SET   LED   ON";
    char *tokens[3];
    size_t token_count = 0U;

    tokenizer_status_t status =
        tokenize_command(
            command,
            sizeof(command),
            tokens,
            3U,
            &token_count);

    if ((status != TOKENIZER_OK) ||
        (token_count != 3U))
    {
        printf("FAIL: multiple spaces\n");
        return 1;
    }

    if ((strcmp(tokens[0], "SET") != 0) ||
        (strcmp(tokens[1], "LED") != 0) ||
        (strcmp(tokens[2], "ON") != 0))
    {
        printf("FAIL: multiple-space tokens incorrect\n");
        return 1;
    }

    printf("PASS: multiple spaces\n");
    return 0;
}

static int test_too_many_tokens(void)
{
    char command[] = "SET LED ON NOW";
    char *tokens[3];
    size_t token_count = 0U;

    tokenizer_status_t status =
        tokenize_command(
            command,
            sizeof(command),
            tokens,
            3U,
            &token_count);

    if (status != TOKENIZER_TOO_MANY_TOKENS)
    {
        printf("FAIL: too many tokens not detected\n");
        return 1;
    }

    printf("PASS: too many tokens rejected\n");
    return 0;
}

static int test_missing_terminator(void)
{
    char command[4] = {'T', 'E', 'S', 'T'};
    char *tokens[2];
    size_t token_count = 0U;

    tokenizer_status_t status =
        tokenize_command(
            command,
            sizeof(command),
            tokens,
            2U,
            &token_count);

    if (status != TOKENIZER_MISSING_TERMINATOR)
    {
        printf("FAIL: missing terminator not detected\n");
        return 1;
    }

    printf("PASS: missing terminator rejected\n");
    return 0;
}

static int test_null_buffer(void)
{
    char *tokens[2];
    size_t token_count = 0U;

    tokenizer_status_t status =
        tokenize_command(
            NULL,
            0U,
            tokens,
            2U,
            &token_count);

    if (status != TOKENIZER_NULL_POINTER)
    {
        printf("FAIL: NULL buffer not rejected\n");
        return 1;
    }

    printf("PASS: NULL buffer rejected\n");
    return 0;
}

static int test_leading_and_trailing_spaces(void)
{
    char command[] = "  SET LED  ";
    char *tokens[2];
    size_t token_count = 0U;

    tokenizer_status_t status =
        tokenize_command(
            command,
            sizeof(command),
            tokens,
            2U,
            &token_count);

    if ((status != TOKENIZER_OK) ||
        (token_count != 2U))
    {
        printf("FAIL: leading/trailing spaces\n");
        return 1;
    }

    if ((strcmp(tokens[0], "SET") != 0) ||
        (strcmp(tokens[1], "LED") != 0))
    {
        printf("FAIL: leading/trailing-space tokens incorrect\n");
        return 1;
    }

    printf("PASS: leading/trailing spaces\n");
    return 0;
}

int main(void)
{
    int failures = 0;

    failures += test_normal_command();
    failures += test_empty_input();
    failures += test_multiple_spaces();
    failures += test_too_many_tokens();
    failures += test_missing_terminator();
    failures += test_null_buffer();
    failures += test_leading_and_trailing_spaces();

    if (failures == 0)
    {
        printf("All tokenizer tests passed\n");
        return 0;
    }

    printf("%d tokenizer test(s) failed\n", failures);
    return 1;
}