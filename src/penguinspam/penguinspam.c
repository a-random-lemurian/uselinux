/**
 * @file penguinspam.c
 * @author Lemuria
 * @brief Implementation file for penguin spam.
 * @date 2022-02-04
 *
 * @copyright MIT License
 *
 */

#include "penguinspam.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void free_psj_mem(penguin_spam_job *job)
{
    free(job->__error__);
}

int mk_penguin_spam_job(penguin_spam_job *job, int penguins, char *location)
{
    job->__error__ = malloc(512);


    if (!strcmp(location, ""))
    {
        sprintf(job->__error__,"Error: Location cannot be an empty string");
        return PENGUIN_SPAM_ERROR;
    }
    if (penguins > MAX_PENGUINS)
    {
        sprintf(job->__error__,"Error: Too many penguins (limit is %d, "
                 "tried to send %d)",
                  MAX_PENGUINS, penguins);
        return PENGUIN_SPAM_TOO_MANY_PENGUINS;
    }
    if (penguins <= 0)
    {
        sprintf(job->__error__,
            "Error: penguins must be a positive number (tried to send %d)",
             penguins);
        return PENGUIN_SPAM_ERROR;
    }

    job->location = location;
    job->penguins = penguins;

    return PENGUIN_SPAM_OK;
}

int execute_penguin_spam_job(penguin_spam_job *job)
{
    printf("Acquired penguins.\n");
    printf("Sending %d penguins to %s, done.\n", job->penguins, job->location);
    printf("Successfully spammed penguins.\n");

    return PENGUIN_SPAM_OK;
};

int finish_penguin_spam_job(penguin_spam_job *job)
{
    free(job->__error__);
    return PENGUIN_SPAM_OK;
}
