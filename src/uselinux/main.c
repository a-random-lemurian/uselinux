

#include "ancientpkg.h"
#include "deskenv.h"
#include "uselinuxcommon.h"
#include "userspace.h"
#include "yearoflinuxdesktop.h"


#include <common/utils.h>
#include <common/argparse.h>


#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

// Long-only options
#define ARG_ARCH_BTW 1000
#define ARG_ANCIENT_PACKAGES 1001
#define ARG_BREAK_USERSPACE 1002
#define ARG_BASH_WINDOWS 1003
#define ARG_BASH_MACOS 1004
#define ARG_COMPILE_EVERYTHING 1005
#define ARG_SNAP_AT_SNAPS 1006
#define ARG_NO_BLOATWARE 1007
#define ARG_PENGUIN_SPAM 1008
#define ARG_HACKERMAN 1009
#define ARG_YEAR_OF_LINUX_DESKTOP 1010
#define ARG_SEGFAULT 1011
#define ARG_NO_TYPEWRITER 1012
#define ARG_ANCIENT_DEBIAN_PACKAGES_USE_V2 1013
#define ARG_AP_LIMIT_LOCS 1014
#define ARG_AP_LIMIT_SITES 1015
#define ARG_GET_YOLD 1016

#define PROGNAME "uselinux"
static const char *cmd_doc_footer =
    "\n"
    "\n"
    "uselinux -- compiled "__TIME__
    " " __DATE__ "\n"
    "Copyright (c) 2022 Lemuria, licensed under MIT";
static const char *cmd_doc = "Linux good, Windows bad";
static const char *const usage[] = {PROGNAME " --year-of-linux-desktop 2023",
                                    PROGNAME " --arch-btw", NULL};

int main(int argc, const char **argv)
{

    int arg_ancient_packages = -100;
    int arg_break_userspace = -100;
    int arg_arch_btw = -100;
    int arg_bash_windows = -100;
    int arg_bash_macos = -100;
    int arg_hackerman = -100;
    char *arg_distro = "";
    char *arg_desk = "";
    int arg_year_of_linux_desktop = -100;
    int arg_compile_everything = -100;
    int arg_no_typewriter = -100;
    int arg_get_yold = -100;
    int arg_ancient_debian_packages_v2 = -100;
    int arg_ap_limit_locs = -100;
    int arg_ap_limit_sites = -100;
    int arg_segfault = -100;

    struct argparse_option opts[] = {
        OPT_HELP(),

        OPT_GROUP("Basic options"),
        OPT_STRING('d', "distro", &arg_distro,
                   "Specify a " LINUXREF " distribution"),
        OPT_STRING('e', "desk", &arg_desk, "Specify a desktop environment"),
        OPT_BOOLEAN(0, "break-userspace", &arg_break_userspace,
                    "Make Linus Torvalds angry by breaking userspace with "
                    "Linux kernel "
                    "patches"),
        OPT_BOOLEAN(0, "arch-btw", &arg_arch_btw, "I use arch btw"),
        OPT_BOOLEAN(0, "bash-windows", &arg_bash_windows,
                    "Windows is spyware"),
        OPT_BOOLEAN(0, "bash-macos", &arg_bash_macos, "macOS is spyware"),
        OPT_BOOLEAN(0, "compile-everything", &arg_compile_everything,
                    "Compile everything (Gentoo)"),
        OPT_BOOLEAN(0, "get-yold", &arg_get_yold,
                    "Print the year of the Linux desktop"),
        OPT_BOOLEAN(0, "hackerman", &arg_hackerman,
                    "Be a hackerman (requires Kali)"),
        OPT_BOOLEAN(0, "segfault", &arg_segfault,
                    "Trigger a segmentation fault"),

        OPT_GROUP("Other options"),
        OPT_BOOLEAN(0, "no-typewriter", &arg_no_typewriter,
                    "Do not print messages with typewriter effect"),
        OPT_END()
    };

    struct argparse argparse;
    argparse_init(&argparse, opts, usage, 0);
    argparse_describe(&argparse, cmd_doc, cmd_doc_footer);

    if (argc == 1)
    {
        printf("Error: no arguments specified\n");
        argparse_help_cb(&argparse, opts);
        exit(1);
    }

    argc = argparse_parse(&argparse, argc, argv);

    time_t s = 1;
    struct tm *current_time;
    s = time(NULL);
    current_time = localtime(&s);

    if (arg_segfault == 1)
    {
        trigger_segfault();
    }

    if (strcmp("", arg_desk))
    {
        desktop_environments(arg_desk);
    }

    if (arg_get_yold == 1)
    {
        int yr = get_year_of_linux_desktop();
        printf("%d", yr);
    }

    if (arg_arch_btw == 1)
    {
        printf("I use Arch btw\n");
    }

    if (arg_year_of_linux_desktop != -100)
    {
        year_of_linux_desktop(current_time->tm_year + 1900,
                              arg_year_of_linux_desktop);
    }

    if (arg_hackerman == 1)
    {
        if (!strcmp(arg_distro, ""))
        {
            printf("fatal: distro must be specified\n");
            exit(1);
        }

        hackerman(arg_distro);
    }

    if (arg_bash_macos == 1)
    {
        bash_os("macOS");
    }

    if (arg_bash_windows == 1)
    {
        bash_os("Windows");
    }

    if (arg_break_userspace == 1)
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

    exit(0);
}
