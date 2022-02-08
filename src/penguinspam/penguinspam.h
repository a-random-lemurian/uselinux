/**
 * @file penguinspam.h
 * @author Lemuria
 * @brief Header file for penguin spam.
 * @date 2022-02-04
 *
 * @copyright MIT License
 *
 */

#ifndef PENGUINSPAM_H
#define PENGUINSPAM_H

/** @brief Limit on how many penguins can be sent. */
#define MAX_PENGUINS 5000000

/** @brief Operation was successful.*/
#define PENGUIN_SPAM_OK 0
/** @brief Generic error code. */
#define PENGUIN_SPAM_ERROR 1
/** @brief An attempt was made to send too many penguins.*/
#define PENGUIN_SPAM_TOO_MANY_PENGUINS 2
/** @brief Wrong kind of penguin specified. */
#define PENGUIN_SPAM_INVALID_PENGUIN 3

typedef struct penguin_food
{
    char* food;
    int qty;
} penguin_food;

typedef struct penguin_spam_job
{
    char *location;
    char *penguin_type;
    int penguins;

    penguin_food food;

    char *__error__;
} penguin_spam_job;

/**
 * @brief Prepare a penguin spam job.
 *
 * @param job Pointer to a penguin_spam_job struct.
 * @param penguins Number of penguins to send.
 * @param location Location where penguins will be sent.
 * @return int Status code of operation.
 */
int mk_penguin_spam_job(penguin_spam_job *job, int penguins, char *location,
                        char *penguin_type)
    __attribute__((warn_unused_result));
int prepare_penguin_food(char *type, penguin_food *food, int qty,
                         penguin_spam_job *job);

/**
 * @brief Execute a penguin spam job.
 *
 * @param job Pointer to a penguin_spam_job struct.
 * @return int Status code of operation.
 */
int execute_penguin_spam_job(penguin_spam_job *job);

/**
 * @brief Finish a penguin spam job.
 *
 *
 * @note You must always explicitly finish jobs (to free memory allocated by
 * penguinspam).
 *
 * @param job Pointer to a penguin_spam_job struct.
 * @return int Status code of operation.
 */
int finish_penguin_spam_job(penguin_spam_job *job);
#endif /* PENGUINSPAM_H */
