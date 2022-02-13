/* Documentation in docs/dig_from_json.md */

#include "ancientpkg.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <parson/parson.h>
#include <common/ansiescapes.h>
#include <common/utils.h>

int validate_json_package(JSON_Object* package)
{
    const char* maintainer = json_object_get_string(package, "maintainer");
    JSON_Array* maintainers = json_object_get_array(package, "maintainers");
    const char* pkgname = json_object_get_string(package, "packageName");
    const char* license = json_object_get_string(package, "license");
    size_t number_of_maintainers = json_array_get_count(maintainers);

    char* maintainers_ls[number_of_maintainers];

    if (maintainers != NULL)
    {
        for (size_t i = 0; i < number_of_maintainers; i++)
        {
            maintainers_ls[i] = json_array_get_string(maintainers, i);
        }
    }

    Package pkg;
    create_package(&pkg, pkgname, license);

    set_pkg_maintainer(&pkg, maintainer);
    if (maintainers != NULL && !strcmp(maintainer, "multiple"))
    {
        set_pkg_multiple_maintainers(&pkg, (char**)maintainers_ls);
    }

    return validate_package(&pkg);
}

void package_shard_failure(int i, char* pkgname)
{
    printf(WARN "failed to get package shard %d %s (stable)\n",
       i, pkgname);

    printf("attempting to resolve the situation....\n");
    msleep(randint(100, 3000));
    for (int n = 0; n < 400; n++)
    {
        printf("Checking package src %d.... ", n);
        fflush(stdout);
        msleep(randint(1,300));
        if (randint(1, 100) > 90)
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

void process_single_package(JSON_Object* package, size_t i)
{
    if (validate_json_package(package))
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
                package_shard_failure(i, pkgname);
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
