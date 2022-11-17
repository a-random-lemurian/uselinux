#include <common/utils.h>

#include "userspace.h"

void break_userspace(int arg_no_typewriter)
{
    printf("\n------\n");
    printf("You check the mailing list...\n");
    printf("But it seems like your kernel patch broke userspace again!\n");
    printf("New mail: 1\n\n\n");


    if (arg_no_typewriter == 1)
    {
        printf("%s", WE_DO_NOT_BREAK_USERSPACE);
    }
    else
    {
        typewriter_randomized(WE_DO_NOT_BREAK_USERSPACE, 2, 18);
    }

    printf("%d", randint(1, 100));

    if (randint(1, 100) >= 2)
    {
        printf("\n\nThat was tough. Just as you finish reading the\n"
               "email, you see an apparition of Linus Torvalds\n"
               "approaching you causing the program to....\n");

        segfault_or_abort(80);
    }
    else
    {
        exit(0);
    }
}
