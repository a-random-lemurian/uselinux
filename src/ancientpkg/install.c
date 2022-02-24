#include <common/ansiescapes.h>
#include <common/argparse.h>
#include <common/mtwister.h>
#include <common/utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int install_package(char *name)
{
    MTRand mtw = seedRand(clock());

    int n = (int)ceil(genRand(&mtw) * 500) + 200;

    for (int i = 0; i < n; i++)
    {
        printf("Scanning site %d for package %s.\n", i, name);
        msleep(randint(40, 70));
    }

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
