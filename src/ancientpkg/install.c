#include <common/ansiescapes.h>
#include <common/argparse.h>
#include <common/mtwister.h>
#include <common/utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ancientpkg_utils.h"

void install_files()
{
    int files = randint(5400, 8044);
    int files_done;
    for (files_done = 0; files_done < files; files_done++) {
        printf("Installing files: [%d/%d]", files_done, files);
        repeat(' ', 40);
        if (randint(1,100) > 85) {
            fflush(stdout);
        }
        ancientpkg_msleep((randint(1,100) < 30) ? randint(1, 3) : 0);
        printf("\r");
    }
}

int install_package(char *name)
{
    MTRand mtw = seed_rand(clock());

    int n = (int)ceil(gen_rand(&mtw) * 500) + 200;

    int i;
    for (i = 0; i < n; i++)
    {
        printf("Scanning site %d for package %s.\n", i, name);
        ancientpkg_msleep(randint(40, 70));
    }
    printf("Found package %s at site %d. Installing..\n", name, i);

    install_files();

    printf("\n");
    printf("Installed package %s.\n", name);
}

int cmd_install(int argc, char **argv)
{
    char *package_name = NULL;

    struct argparse ap;
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_STRING('p', "package-name", &package_name, "Name of package"),
        OPT_END()};

    argparse_init(&ap, options, NULL, 0);
    argparse_parse(&ap, argc, (const char **)argv);

    if (package_name == NULL)
    {
        printf(BHRED "error:" reset " need to specify a package name.\n");
    }

    install_package(package_name);
}
