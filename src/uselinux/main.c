

#include "ancientpkg.h"
#include "bloatrm.h"
#include "uselinuxcommon.h"
#include "userspace.h"
#include "utils.h"
#include "yearoflinuxdesktop.h"

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

const char *argp_program_version = "version 0.1.0";
static char doc[] = "Linux good, Windows bad";

static struct argp_option opts[] = {
    {"distro", 'd', "DISTRO", 0, "Specify a " LINUXREF " distribution"},
    {"desk", 'e', "DESK", 0, "Specify a desktop environment"},
    {"year-of-linux-desktop", ARG_YEAR_OF_LINUX_DESKTOP, "YEAR", 0,
     "Specify the year of the Linux desktop"},
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
    {"get-yold", ARG_GET_YOLD, 0, 0, "Print the year of the Linux desktop"},
    {"no-bloatware", ARG_NO_BLOATWARE, 0, 0, "Do not install bloatware"},
    {"hackerman", ARG_HACKERMAN, 0, 0, "Be a hackerman (requires Kali)"},
    {"segfault", ARG_SEGFAULT, 0, 0, "Trigger a segmentation fault"},
    {0, 0, 0, 0, "Ancient Debian packages"},
    {"ancient-packages", ARG_ANCIENT_PACKAGES, 0, 0,
     "Use packages from 10,000 years ago (Debian), v1"},
    {"ancient-packages-v2", ARG_ANCIENT_DEBIAN_PACKAGES_USE_V2, 0, 0,
     "Use Debian packages from 11,000 years ago"},
    {"ap-limit-locations", ARG_AP_LIMIT_LOCS, "LOCS", 0,
     "Limit locations to exacavate packages at"},
    {"ap-limit-sites", ARG_AP_LIMIT_SITES, "SITES", 0,
     "Limit digsites per location"},
    {0, 0, 0, 0, "Other options"},
    {"no-typewriter", ARG_NO_TYPEWRITER, 0, 0,
     "Do not print messages with typewriter effect"},
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
    int no_bloatware;
    int no_typewriter;
    int get_yold;

    int ancient_debian_packages_v2;

    char *ap_limit_locs;
    char *ap_limit_sites;

    // Penguin spam
    char penguin_spam_location[128];
    char penguin_spam_amount[128];
};

void defaults(struct args *arg)
{
    arg->ancient_packages = 0;
    arg->break_userspace = 0;
    arg->arch_btw = 0;
    arg->bash_windows = 0;
    arg->bash_macos = 0;
    arg->hackerman = 0;
    arg->distro = "";
    arg->desk = "";
    arg->year_of_linux_desktop = "";
    arg->compile_everything = 0;
    arg->snap_at_snaps = 0;
    arg->no_bloatware = 0;
    arg->no_typewriter = 0;
    arg->get_yold = 0;
    arg->ancient_debian_packages_v2 = 0;

    arg->ap_limit_locs = "";
    arg->ap_limit_sites = "";
}

static int distro_initalized = 0;

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
    case ARG_NO_BLOATWARE:
        arguments->no_bloatware = 1;
        break;
    case ARG_SEGFAULT:
        printf("Well, you asked for a segfault....\n");
        trigger_segfault();
    case ARG_NO_TYPEWRITER:
        arguments->no_typewriter = 1;
        break;
    case ARG_ANCIENT_DEBIAN_PACKAGES_USE_V2:
        arguments->ancient_debian_packages_v2 = 1;
        break;
    case ARG_AP_LIMIT_LOCS:
        arguments->ap_limit_locs = arg;
        break;
    case ARG_AP_LIMIT_SITES:
        arguments->ap_limit_sites = arg;
        break;
    case ARG_GET_YOLD:
        arguments->get_yold = 1;
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }

    return 0;
}
static struct argp argp = {opts, parse_opt, 0, doc};


int main(int argc, char **argv)
{
    struct args arg;
    defaults(&arg);
    argp_parse(&argp, argc, argv, 0, 0, &arg);

    time_t s = 1;
    struct tm *current_time;
    s = time(NULL);
    current_time = localtime(&s);

    if (arg.get_yold)
    {
        int yr = get_year_of_linux_desktop();
        printf("%d", yr);
    }

    if (arg.no_bloatware)
    {
        remove_bloatware();
    }

    if (arg.snap_at_snaps)
    {
        snap_at_snaps(arg.distro);
    }

    if (arg.arch_btw)
    {
        printf("I use Arch btw\n");
    }

    if (strcmp(arg.year_of_linux_desktop, ""))
    {
        long converted_yr_l = strtol(arg.year_of_linux_desktop, NULL, 10);
        int converted_yr = (int)converted_yr_l;
        year_of_linux_desktop(current_time->tm_year + 1900, converted_yr);
    }

    if (arg.hackerman)
    {
        if (!distro_initalized)
        {
            printf("fatal: distro must be specified\n");
            exit(1);
        }

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

        if (arg.no_typewriter)
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

    if (arg.ancient_debian_packages_v2)
    {
        if (strcasecmp(arg.distro, "debian"))
        {
            printf("fatal: to dig for ancient packages, you must specify"
                   " debian as the distro");
            exit(1);
        }

        pkg_dig_job_control pkgdigctl;

        pdjctl_set_defaults(&pkgdigctl);

        if (strcmp(arg.ap_limit_locs, ""))
        {
            long converted_l = strtol(arg.ap_limit_locs, NULL, 10);
            int ap_limit_locs_i = (int)converted_l;
            pkgdigctl.max_locs = ap_limit_locs_i;
        }

        if (strcmp(arg.ap_limit_sites, ""))
        {
            long converted_l = strtol(arg.ap_limit_sites, NULL, 10);
            int ap_limit_sites_i = (int)converted_l;
            pkgdigctl.max_sites = ap_limit_sites_i;
        }

        ancient_debian_packages_v2(&pkgdigctl);
    }

    if (arg.ancient_packages)
    {
        if (!strcasecmp(arg.distro, "debian"))
        {
            printf("Warning: --ancient-packages is deprecated.\n"
                   "Please use --ancient-packages-v2 instead.\n");
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
