/**
 * @file main.c
 * @author Lemuria
 * @brief Command line interface for penguin spam.
 * @date 2022-02-04
 *
 * @copyright MIT License
 *
 */

#include "penguinspam.h"
#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int chartoint(char *str, int numbase);

struct args
{
    char *location;
    int penguins;
};

static struct argp_option opts[] = {
    {"location", 'l', "LOCATION", 0, "Location where penguins will be deployed"},
    {"penguins", 'p', "PENGUINS", 0,
     "Number of penguins to spam at particular location"},
    {0}};

void defaults(struct args *args)
{
    args->location = "";
    args->penguins = -1;
}

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct args *arguments = state->input;

    switch (key)
    {
    case 'l':
        arguments->location = arg;
        break;
    case 'p':
        arguments->penguins = chartoint(arg, 10);
        break;
    }
    return 0;
}

static struct argp argp = {opts, parse_opt, 0, ""};

void handle_penguin_spam_error(int rc, penguin_spam_job *job)
{
    printf("fatal: unable to prepare penguin spam, ");
    if (rc == PENGUIN_SPAM_TOO_MANY_PENGUINS)
    {
        printf("too many penguins (limited to 5000000)");
    }
    else if (rc == PENGUIN_SPAM_ERROR)
    {
        printf("general error");
    }

    printf("\n");
    printf("penguinspam: %s\n", job->__error__);

    exit(1);
}

int main(int argc, char **argv)
{
    struct args arg;
    defaults(&arg);
    argp_parse(&argp, argc, argv, 0, 0, &arg);

    penguin_spam_job job;
    int rc = mk_penguin_spam_job(&job, arg.penguins, arg.location);
    if (rc != PENGUIN_SPAM_OK)
    {
        handle_penguin_spam_error(rc, &job);
    }

    execute_penguin_spam_job(&job);
    finish_penguin_spam_job(&job);

    return 0;
}
