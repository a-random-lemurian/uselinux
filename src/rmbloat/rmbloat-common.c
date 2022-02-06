#include <stdio.h>
#include <stdlib.h>

void handle_bad_arg(char* offending_arg)
{
    if (offending_arg[0] == '-')
    {
        if (offending_arg[1] == '-')
        {
            fprintf(stderr, "fatal: unrecognized long "
                            "flag %s", offending_arg);
        }
        else
        {
            fprintf(stderr, "fatal: unrecognized short "
                            "flag %s", offending_arg);
        }
    }
    else
    {
        fprintf(stderr, "fatal: unrecognized argument or "
                    "subcommand %s", offending_arg);
    }

    fprintf(stderr, "\n");
    exit(1);
}
