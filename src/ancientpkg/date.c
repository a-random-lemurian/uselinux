#include "ancientpkg.h"
#include <common/ansiescapes.h>
#include <common/argparse.h>
#include <common/mtwister.h>
#include <math.h>
#include <parson/parson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *valid_dating_methods[] = {"radiocarbon", "carbon", "uranium–lead",
                                "uranium–thorium", "uranium–uranium"};

#define ARRSZ(x) sizeof(x) / sizeof(x[0])

int is_valid_dating_method(char *method)
{
    for (int i = 0; i < ARRSZ(valid_dating_methods); i++)
    {
        if (!strcasecmp(method, valid_dating_methods[i]))
        {
            return 1;
        }
    }
    return 0;
}

int cmd_date(int argc, char **argv)
{
    int flag_help = 0;
    char *pkg = NULL;
    char *method = NULL;
    char *json_file = NULL;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_STRING('m', "method", &method,
                   "Dating method to use for determining package age"),
        OPT_STRING('p', "package", &pkg, "Package to check age of"),
        OPT_STRING(0, "write-to-json", &json_file,
                   "Write results to JSON file"),
        OPT_END()};
    const char *usages[] = {"ancientpkg date --package=PKG --method=METHOD",
                            NULL};
    argparse_init(&argparse, options, usages, 0);
    argc = argparse_parse(&argparse, argc, (const char **)argv);

    if (pkg == NULL || method == NULL)
    {
        if (pkg == NULL)
        {
            printf(BHRED "error:" reset " Package not specified\n");
        }
        if (method == NULL)
        {
            printf(BHRED "error:" reset " Method of dating package "
                         "not specified\n");
        }
        exit(1);
    }

    if (is_valid_dating_method(method) == 0)
    {
        printf(BHRED "error: " reset "\"%s\" is not a valid dating method",
               method);
        exit(1);
    }

    PackageDatingResult pdr;
    MTRand mtw = seedRand(clock());

    int pkg_age = (int)ceil((genRand(&mtw) * 200000) + 10000);

    int chance = 1;

    if (!strcasecmp(method, "radiocarbon"))
    {
        if (pkg_age > 40000)
        {
            chance += (int)ceil((pkg_age - 40000) / 4000);
        }
    }

    int odds = (int)ceil((genRand(&mtw) * chance));

    if (odds < 16)
    {
        printf("%d\n",odds);
        if (json_file != NULL)
        {
            FILE *fp = fopen(json_file, "w");
            JSON_Value *root = json_value_init_object();
            JSON_Object *rootobj = json_value_get_object(root);
            char *serialized_string = NULL;
            json_object_set_string(rootobj, "packageName", pkg);
            json_object_set_number(rootobj, "packageAge", pkg_age);
            json_object_dotset_string(rootobj, "datingMethod", method);
            json_serialize_to_file(root, json_file);
        }
        else
        {
            printf("Package " HWHT "%s" reset
                   " is %d years old (dated with %s)\n",
                   pkg, pkg_age, method);
            
            if (pkg_age < 200)
            {
                printf("That's a very young package. How rare, indeed.\n");
            }
            else if (pkg_age > 4200 && pkg_age < 4500)
            {
                printf("It seems like this package was released "
                       "during the construction of the Great "
                       "Pyramids of Giza.\n");
            }
            else
            {
                printf(BHYEL"warning:"reset" No historical context for %s.",
                       pkg);
            }
            exit(0);
        }
    }
    else
    {
        printf(BHRED "error: " reset "unable to determine age of %s", pkg);
        exit(1);
    }
}
