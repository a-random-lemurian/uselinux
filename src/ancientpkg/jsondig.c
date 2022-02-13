/* Documentation in docs/dig_from_json.md */

#include "ancientpkg.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <parson/parson.h>
#include <common/ansiescapes.h>
#include <common/utils.h>

int validate_package(JSON_Object* package)
{
    int has_missing = 0;
    const char* maintainer = json_object_get_string(package, "maintainer");
    if (maintainer == NULL)
    {
        printf(ERROR "Missing parameter \"maintainer\" in package.\n");
        has_missing = 1;
    }

    JSON_Array* maintainers = json_object_get_array(package, "maintainers");
    if (!strcmp(maintainer, "multiple"))
    {
        if (maintainers == NULL)
        {
            printf(ERROR "Missing parameter \"maintainers\" in package.\n");
            has_missing = 1;
        }
    }
    else
    {
        if (maintainers != NULL)
        {
            printf(ERROR "Both \"maintainer\" and \"maintainers\" fields "
                   "were filled in.\n");
            has_missing = 1;
        }
    }

    const char* pkgname = json_object_get_string(package, "packageName");
    if (pkgname == NULL)
    {
        printf(ERROR "Missing parameter \"packageName\" in package.\n");
        has_missing = 1;
    }

    const char* license = json_object_get_string(package, "license");
    if (license == NULL)
    {
        printf(ERROR "Missing parameter \"license\" in package.\n");
        has_missing = 1;
    }

    return has_missing;
}

void process_single_package(JSON_Object* package, size_t i)
{
    if (validate_package(package))
    {
        printf("Error: missing package params (package %ld)\n",i);
        exit(1);
    }
    else
    {
        const char* pkgname = 
                json_object_get_string(package, "packageName");
        const char* license =
                json_object_get_string(package, "license");
        printf("[PRIORITY] Prepare excavation of high-priority "
               "package %s (License: %s)\n", pkgname, license);

        int sleep = randint(500, 1000);
        msleep(sleep);

        for (int i = 0; i < randint(30, 70); i++)
        {
            int pkg_delay = randint(40,133);
            if ((randint(1, sleep)) > ((int)ceil((sleep / 100) * 94)))
            {
                printf(WARN "failed to get package shard %d %s (stable)\n",
                       i, pkgname);
                --i;

                printf("attempting to resolve the situation....\n");
                msleep(randint(100, 3000));
                for (int n = 0; n < 400; n++)
                {
                    printf("Checking package src %d.... ");
                    fflush(stdout);
                    msleep(randint(1,30));
                    if (randint(1, 100) > 20)
                    {
                        printf("shard found.\n");
                        break;
                    }
                    else
                    {
                        printf(" shard not found.\n");
                    }
                }
            }
            else
            {
                printf("Get:%d:high-priority-packages:/%s stable (%d ms) "
                       "[200 OK]\n", i, pkgname, pkg_delay);
            }

        }
    }
}

void process_multiple_packages(JSON_Array* packages)
{
    JSON_Object* package;
    for (size_t i = 0; i < json_array_get_count(packages); i++)
    {
        package = json_array_get_object(packages, i);
        if (package != NULL)
        {
            process_single_package(package, i);
        }
    }
}

int dig_from_json(char* filename)
{
    JSON_Value *job = json_parse_file_with_comments((const char*)filename);
    JSON_Object *root = json_object(job);

    /* Look for the required fields. */
    char* location = NULL;
    location = json_object_get_string(root, "location");

    int archaeologists = -1;
    archaeologists = json_object_get_number(root, "archaeologists");

    int passes = -1;
    passes = json_object_get_number(root, "passes"); 

    int expected_packages = -1;
    expected_packages = json_object_get_number(root, "expectedPackages");

    if (has_missing_args(location, archaeologists, passes, expected_packages))
    {
        printf("From JSON job file %s: missing arguments.\n"
               "location: %s\n"
               "archaeologists: %d\n"
               "passes: %d\n"
               "expected packages: %d\n",
               
               filename, location, archaeologists,
               passes, expected_packages);
        exit(1);
    }

    JSON_Array* packages = json_object_get_array(root, "packages");
    if (packages != NULL)
    {
        process_multiple_packages(packages);
    }

    json_value_free(root);
    
    dig_common(archaeologists, expected_packages, 1, passes, location);
    exit(0);
}
