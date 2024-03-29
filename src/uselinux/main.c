#include "deskenv.h"
#include "hackerman.h"
#include "uselinuxcommon.h"
#include "userspace.h"
#include "yearoflinuxdesktop.h"

#include <common/argparse.h>
#include <common/utils.h>

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
#define ARG_FAMILY_FRIENDLY 1017

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

static int arg_ancient_packages = -100;
static int arg_break_userspace = -100;
static int arg_arch_btw = -100;
static int arg_bash_windows = -100;
static int arg_bash_macos = -100;
static int arg_hackerman = -100;
static char *arg_distro = "";
static char *arg_desk = "";
static int arg_year_of_linux_desktop = NULL;
static int arg_compile_everything = -100;
static int arg_no_typewriter = -100;
static int arg_get_yold = -100;
static int arg_ancient_debian_packages_v2 = -100;
static int arg_ap_limit_locs = -100;
static int arg_ap_limit_sites = -100;
static int arg_segfault = -100;
static int arg_family_friendly = -100;

int main(int argc, const char **argv)
{

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
        OPT_INTEGER(0, "predict-yold", &arg_year_of_linux_desktop,
                    "Predict the year of the Linux desktop"),
        OPT_INTEGER(0, "year-of-linux-desktop", &arg_year_of_linux_desktop,
                    "Same as --predict-yold"),
        OPT_BOOLEAN(0, "segfault", &arg_segfault,
                    "Trigger a segmentation fault"),

        OPT_GROUP("Other options"),
        OPT_BOOLEAN(0, "no-typewriter", &arg_no_typewriter,
                    "Do not print messages with typewriter effect"),
        OPT_BOOLEAN(0, "family-friendly", &arg_family_friendly,
                    "Don't use strong language"),
        OPT_END()};

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

    if (arg_segfault == 0)
    {
        trigger_segfault();
    }

    if (strcmp("", arg_desk))
    {
        desktop_environments(arg_desk);
    }

    if (arg_get_yold == 0)
    {
        int yr = get_year_of_linux_desktop();
        printf("%d", yr);
    }

    if (arg_arch_btw == 0)
    {
        printf("I use Arch btw\n");
    }

    if (arg_year_of_linux_desktop != NULL)
    {
        year_of_linux_desktop(current_time->tm_year + 1900,
                              arg_year_of_linux_desktop);
    }

    if (arg_hackerman == 0)
    {
        if (!strcmp(arg_distro, ""))
        {
            printf("fatal: distro must be specified\n");
            exit(1);
        }

        hackerman(arg_distro);
    }

    if (arg_bash_macos == 0)
    {
        bash_os("macOS");
    }

    if (arg_bash_windows == 0)
    {
        bash_os("Windows");
    }

    if (arg_break_userspace == 0)
    {
        break_userspace(arg_no_typewriter, arg_family_friendly);
    }

    exit(0);
}
