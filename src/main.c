

#include "ancientpkg.h"
#include "userspace.h"
#include "utils.h"

#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#ifdef FSF_TERMINOLOGY
#define LINUXREF "GNU/Linux"
#elif INTERJECTION
#define LINUXREF "GNU plus Linux"
#else
#define LINUXREF "Linux"
#endif

#define LEN(arr) ((int)(sizeof(arr) / sizeof(arr)[0]))

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

const char *argp_program_version = "version 0.1.0";
static char doc[] = "Linux good, Windows bad";

static struct argp_option opts[] = {
    {"distro", 'd', "DISTRO", 0, "Specify a GNU/Linux distribution"},
    {"desk", 'e', "DESK", 0, "Specify a desktop environment"},
    {"year-of-linux-desktop", ARG_YEAR_OF_LINUX_DESKTOP, "YEAR", 0,
     "Specify the year of the Linux desktop"},
    {"ancient-packages", ARG_ANCIENT_PACKAGES, 0, 0,
     "Use packages from 10,000 years ago (Debian)"},
    {"break-userspace", ARG_BREAK_USERSPACE, 0, 0,
     "Make Linus Torvalds angry by breaking userspace with Linux kernel "
     "patches"},
    {"arch-btw", ARG_ARCH_BTW, 0, 0, "I use arch btw"},
    {"bash-windows", ARG_BASH_WINDOWS, 0, 0, "Windows is spyware"},
    {"bash-macos", ARG_BASH_MACOS, 0, 0, "macOS is spyware"},
    {"compile-everything", ARG_COMPILE_EVERYTHING, 0, 0,
     "Compile everything (Gentoo)"},
    {"snap-at-snaps", ARG_SNAP_AT_SNAPS, 0, 0,
     "Get annoyed at constant Ubuntu snap updates"},
    {"no-bloatware", ARG_NO_BLOATWARE, 0, 0, "Do not install bloatware"},
    {"penguin-spam", ARG_PENGUIN_SPAM, 0, 0,
     "Spam Microsoft headquarters with penguins"},
    {"hackerman", ARG_HACKERMAN, 0, 0, "Be a hackerman (requires Kali)"},
    {"segfault", ARG_SEGFAULT, 0, 0, "Trigger a segmentation fault"},
    {0}};

struct args
{
    char *distro;
    char *desk;
    int ancient_packages;
    int break_userspace;
    int arch_btw;
    int bash_windows;
    int bash_macos;
    int hackerman;
    char *year_of_linux_desktop;
    int compile_everything;
    int snap_at_snaps;
    int penguin_spam;
    int no_bloatware;

    // Penguin spam
    char penguin_spam_location[128];
    char penguin_spam_amount[128];
};

static int distro_initalized = 0;
static char *year_of_linux_desktop_tmp_var;

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct args *arguments = state->input;

    switch (key)
    {
    case 'd':
        distro_initalized = 1;
        arguments->distro = arg;
        break;
    case 'e':
        arguments->desk = arg;
        break;
    case ARG_ARCH_BTW:
        arguments->arch_btw = 1;
        break;
    case ARG_ANCIENT_PACKAGES:
        arguments->ancient_packages = 1;
        break;
    case ARG_BREAK_USERSPACE:
        arguments->break_userspace = 1;
        break;
    case ARG_BASH_MACOS:
        arguments->bash_macos = 1;
        break;
    case ARG_BASH_WINDOWS:
        arguments->bash_windows = 1;
        break;
    case ARG_COMPILE_EVERYTHING:
        arguments->compile_everything = 1;
        break;
    case ARG_HACKERMAN:
        arguments->hackerman = 1;
        break;
    case ARG_YEAR_OF_LINUX_DESKTOP:
        arguments->year_of_linux_desktop = arg;
        break;
    case ARG_SNAP_AT_SNAPS:
        arguments->snap_at_snaps = 1;
        break;
    case ARG_PENGUIN_SPAM:
        arguments->penguin_spam = 1;
        break;
    case ARG_NO_BLOATWARE:
        arguments->no_bloatware = 1;
        break;
    case ARG_SEGFAULT:
        printf("Well, you asked for a segfault....\n");
        trigger_segfault();
    default:
        return ARGP_ERR_UNKNOWN;
    }

    return 0;
}
static struct argp argp = {opts, parse_opt, 0, doc};

void defaults(struct args *arg)
{
    arg->ancient_packages = 0;
    arg->break_userspace = 0;
    arg->arch_btw = 0;
    arg->bash_windows = 0;
    arg->bash_macos = 0;
    arg->hackerman = 0;
    arg->year_of_linux_desktop = "";
    arg->compile_everything = 0;
    arg->snap_at_snaps = 0;
    arg->penguin_spam = 0;
    arg->no_bloatware = 0;
}

#define LINUX_KERNEL_FIRST_RELEASE 1991
#define ANALYTICAL_ENGINE_YEAR 1833

/**
 * @brief The year of the Linux desktop will arrive.... eventually.
 *
 * @param currentyr The current year.
 * @param linux_desktop_yr Year to predict as being the year of the Linux
 *                         desktop.
 */
void year_of_linux_desktop(int currentyr, int linux_desktop_yr)
{
    if (linux_desktop_yr > ANALYTICAL_ENGINE_YEAR &&
        linux_desktop_yr < ANALYTICAL_ENGINE_YEAR + 50)
    {
        printf("Not sure if you can run %s on the Analytical Engine, that "
               "thing doesn't even support %s!",
               LINUXREF, LINUXREF);
        exit(1);
    }
    else if (linux_desktop_yr < LINUX_KERNEL_FIRST_RELEASE)
    {
        printf("%d was in the past. And that definitely "
               "wasn't the year of the %s desktop, because the Linux kernel "
               "didn't even exist back then!\n",
               linux_desktop_yr, LINUXREF);
        exit(1);
    }
    else if (linux_desktop_yr > LINUX_KERNEL_FIRST_RELEASE &&
             linux_desktop_yr < currentyr)
    {
        if (currentyr - linux_desktop_yr == 1)
        {
            printf("Last year wasn't the year of the " LINUXREF " desktop.");
        }
        else
        {
            printf("That was %d years ago. Definitely wasn't the year of "
                   "the " LINUXREF " desktop.",
                   currentyr - linux_desktop_yr);
        }
        exit(1);
    }
    else if (linux_desktop_yr > currentyr)
    {
        int diff = linux_desktop_yr - currentyr;

        if (diff == 0)
        {
            printf("Surely this is the year of the %s desktop, "
                   "right?\n",
                   LINUXREF);
        }
        else if (diff >= 1)
        {
            printf("The year of the %s desktop will be soon.", LINUXREF);
        }
        else if (diff >= 10)
        {
            printf("Microsoft Windows' market share is declining, "
                   "are you sure?");
        }
        else if (diff >= 50)
        {
            printf("Very pessimistic, indeed.");
        }
    }
    else
    {
        char messages[][64] = {
            "Go back to history class!",
            "You clearly don't know anything about history.",
            "Have fun debugging with GDB!",
            "I'm sure this year will be the year of the " LINUXREF " desktop!",
            "I'm sure next year will be the year of the " LINUXREF
            " desktop!"};

        MTRand mtw = seedRand(clock());

        char *HISTORY_MSG =
            messages[(int)floor(genRand(&mtw) * LEN(messages))];

        printf("I hereby sentence you to a segfault. %s\n", HISTORY_MSG);
        trigger_segfault();
    }
}

/**
 * @brief Activate Hackerman mode. Requires Kali Linux.
 *
 * @param distro Distribution being used. Must be Kali Linux.
 */
void hackerman(char *distro)
{
    if (!distro_initalized)
    {
        printf("fatal: distro not specified\n");
        exit(1);
    }

    if (!strcasecmp(distro, "kali"))
    {
        printf("Activating Hackerman mode....\n");
    }
    else
    {
        printf("fatal: --hackerman requires Kali Linux (use -d kali)\n");
        exit(1);
    }
}

/**
 * @brief Bash an operating system, insulting it.
 *
 * @param os The operating system to bash. Specifying Linux will result
 *           in an abort.
 */
void bash_os(char *os)
{
    if (!strcasecmp(os, "Windows"))
    {
        printf("Windows, too much bloat!\n");
    }

    if (!strcasecmp(os, "macOS"))
    {
        printf("macOS is proprietary garbage!\n");
    }

    if (!strcasecmp(os, "GNU/Linux") || !strcasecmp(os, "Linux"))
    {
        printf("Ye shall not insult %s.", LINUXREF);
        abort();
    }
}

/**
 * @brief Remove a single bloatware package.
 *
 * @param bloatware Name of bloatware to remove.
 */
void remove_bloatware_package(char *bloatware)
{
    printf("Removing bloatware %s.....",bloatware);

    for (int i = 0; i < 49 - strlen(bloatware); i++)
    {
        printf(" ");
    }

    fflush(stdout);
    int sleep = randint(10, 2300);
    msleep(sleep);
    printf("removed in %d ms\n",sleep);
}

/**
 * @brief Removes bloatware, such as Candy Crush (preinstalled on Windows).
 *
 */
void remove_bloatware()
{
    printf("Removing bloatware....\n");

    // Apps that are often criticized for being "bloatware"
    char bloatware[][64] = {
        "Candy Crush",
        "Nero Burning ROM",
        "Microsoft Word",
        "Microsoft Office",
        "Microsoft Excel",
        "Microsoft PowerPoint"
    };

    int i = 0;
    for (i = 0; i < LEN(bloatware); i++)
    {
        remove_bloatware_package(bloatware[i]);
    }
}

/**
 * @brief Spam a location with penguins.
 *
 * @param location Location to spam with penguins.
 * @param penguins Number of penguins to deploy.
 */
void penguin_spam(char *location, int penguins)
{
    printf("Spamming %s with penguins....", location);
    fflush(stdout);
    int sleep = randint(400, 900);
    msleep(sleep);
    printf(" done, deployed %d penguins in %d ms.\n", penguins, sleep);
}

int main(int argc, char **argv)
{
    struct args arg;
    defaults(&arg);
    argp_parse(&argp, argc, argv, 0, 0, &arg);

    time_t s, val = 1;
    struct tm *current_time;
    s = time(NULL);
    current_time = localtime(&s);

    if (arg.no_bloatware)
    {
        remove_bloatware();
    }

    if (arg.arch_btw)
    {
        printf("I use Arch btw\n");
    }

    if (arg.penguin_spam)
    {
        char *rc;


        printf("Where should we deploy the penguins? ");
        if (fgets(arg.penguin_spam_location, 128, stdin) == NULL)
        {
            printf(
                "\nfatal: Penguin deployment location must be supplied\n");
            exit(1);
        }

        if ((strlen(arg.penguin_spam_location) > 0) &&
            (arg.penguin_spam_location[strlen(arg.penguin_spam_location) -
                                       1] == '\n'))
        {
            arg.penguin_spam_location[strlen(arg.penguin_spam_location) - 1] =
                '\0';
        }

        printf("How many penguins should we deploy? ");
        if (fgets(arg.penguin_spam_amount, 128, stdin) == NULL)
        {
            printf("\nfatal: Number of penguins to deploy must be "
                   "supplied\n");
            exit(1);
        }


        long penguin_spam_amount = strtol(arg.penguin_spam_amount, NULL, 10);
        int penguin_spam_amount_converted = (int)penguin_spam_amount;
        penguin_spam(arg.penguin_spam_location, penguin_spam_amount_converted);
    }

    if (strcmp(arg.year_of_linux_desktop, ""))
    {
        long converted_yr_l = strtol(arg.year_of_linux_desktop, NULL, 10);
        int converted_yr = (int)converted_yr_l;
        year_of_linux_desktop(current_time->tm_year + 1900, converted_yr);
    }

    if (arg.hackerman)
    {
        hackerman(arg.distro);
    }

    if (arg.bash_macos)
    {
        bash_os("macOS");
    }

    if (arg.bash_windows)
    {
        bash_os("Windows");
    }

    if (arg.break_userspace)
    {
        printf("\n------\n");
        printf("You check the mailing list...\n");
        printf("But it seems like your kernel patch broke userspace again!\n");
        printf("New mail: 1\n\n\n");

        typewriter(WE_DO_NOT_BREAK_USERSPACE, 5);
        exit(0);
    }

    if (arg.ancient_packages)
    {
        if (!strcasecmp(arg.distro, "debian"))
        {
            printf("Using 10,000 year-old Debian packages.\n"
                   "Why does Debian have to be so outdated, "
                   "anyway?\n");

            ancient_debian_packages();
        }
        else
        {
            printf("Using 10,000 year-old packages.\n");
        }
    }

    exit(0);
}
