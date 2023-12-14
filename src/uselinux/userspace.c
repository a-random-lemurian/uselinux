#include <common/utils.h>

#include "userspace.h"

void print_userspace_msg(const char* msg, int arg_no_typewriter)
{
    if (arg_no_typewriter == 1)
    {
        printf("%s", msg);
        return;
    }

    typewriter_randomized(msg, 2, 18);
}

void break_userspace(int arg_no_typewriter, int arg_family_friendly)
{
    printf("\n------\n");
    printf("You check the mailing list...\n");
    printf("But it seems like your kernel patch broke userspace again!\n");
    printf("New mail: 1\n\n\n");

     print_userspace_msg(arg_family_friendly
        ? WE_DO_NOT_BREAK_USERSPACE_family_friendly
        : WE_DO_NOT_BREAK_USERSPACE
        , arg_no_typewriter);


    printf("%d", randint(1, 100));

    if (randint(1, 100) >= 2)
    {
        printf("\n\nThat was tough. Just as you finish reading the\n"
               "email, you see an apparition of Linus Torvalds\n"
               "approaching you causing the program to....\n");

        segfault_or_abort(80);
    }

    exit(0);
}
