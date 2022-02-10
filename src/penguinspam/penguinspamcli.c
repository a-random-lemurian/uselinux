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
#include <argparse.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int chartoint(char *str, int numbase);

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
    else if (rc == PENGUIN_SPAM_INVALID_PENGUIN)
    {
        printf("invalid type of penguin");
    }

    printf("\n");
    printf("penguinspam: %s\n", job->__error__);

    exit(1);
}

int main(int argc, char **argv)
{
    char *arg_location = "";
    int arg_penguins = -1;
    char *arg_penguin_type = "";

    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_STRING('l', "location", &arg_location,
                   "Location of penguin spam job"),
        OPT_STRING('p', "penguins", &arg_penguins,
                   "Number of penguins to send"),
        OPT_STRING('t', "penguin-type", &arg_penguin_type, "Type of penguin"),
        OPT_END()};

    penguin_spam_job job;
    int rc = mk_penguin_spam_job(&job, arg_penguins, arg_location,
                                 arg_penguin_type);
    if (rc != PENGUIN_SPAM_OK)
    {
        handle_penguin_spam_error(rc, &job);
    }

    execute_penguin_spam_job(&job);
    finish_penguin_spam_job(&job);

    return 0;
}
