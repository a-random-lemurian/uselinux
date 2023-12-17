/* Documentation in docs/dig_from_json.md */

#include <common/ansiescapes.h>
#include <common/utils.h>
#include <parson/parson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ancientpkg.h"
#include "ancientpkg_utils.h"
#include "validate_args.h"

int validate_json_package(JSON_Object *package)
{
    const char *maintainer = json_object_get_string(package, "maintainer");
    JSON_Array *maintainers = json_object_get_array(package, "maintainers");
    const char *pkgname = json_object_get_string(package, "packageName");
    const char *license = json_object_get_string(package, "license");
    size_t number_of_maintainers = json_array_get_count(maintainers);

    char *maintainers_ls[number_of_maintainers];

    if (maintainers != NULL)
    {
        for (size_t i = 0; i < number_of_maintainers; i++)
        {
            maintainers_ls[i] = (char *)json_array_get_string(maintainers, i);
        }
    }

    Package pkg;
    create_package(&pkg, (char *)pkgname, (char *)license);

    set_pkg_maintainer(&pkg, (char *)maintainer);
    if (maintainers != NULL && !strcmp(maintainer, "multiple"))
    {
        set_pkg_multiple_maintainers(&pkg, (char **)maintainers_ls);
    }

    return validate_package(&pkg);
}

void process_single_package(DigControlFlags *dcf, JSON_Object *package,
                            size_t i)
{
    if (validate_json_package(package))
    {
        const char *pkgname = json_object_get_string(package, "packageName");
        printf("Error: missing package params. \n"
               "package %ld:\n"
               "   name: %s\n",
               i, pkgname);
        exit(1);
    }
    else
    {
        const char *pkgname = json_object_get_string(package, "packageName");
        const char *license = json_object_get_string(package, "license");
        printf("[PRIORITY] Prepare excavation of high-priority "
               "package %s (License: %s)\n",
               pkgname, license);

        int sleep = randint(500, 1000);
        ancientpkg_msleep(sleep);

        for (int i = 0; i < randint(30, 70); i++)
        {
            int pkg_delay = randint(40, 133);
            if ((randint(1, sleep)) > ((int)ceil((sleep / 100) * 94)))
            {
                package_shard_failure(dcf, i, (char *)pkgname);
            }
            else
            {
                printf("Get:%d:high-priority-packages:/%s stable (%d ms) "
                       "[200 OK]\n",
                       i, pkgname, pkg_delay);
            }
        }
    }
}

void process_multiple_packages(DigControlFlags *dcf, JSON_Array *packages)
{
    JSON_Object *package;
    for (size_t i = 0; i < json_array_get_count(packages); i++)
    {
        package = json_array_get_object(packages, i);
        if (package != NULL)
        {
            process_single_package(dcf, package, i);
        }
    }
}

int get_flag(JSON_Object *dcf_flags, char *name)
{
    int value = json_object_get_boolean(dcf_flags, name);

    return value;
}

void get_dig_control_flags_from_json(DigControlFlags *dcf,
                                     JSON_Object *dcf_flags)
{
    dcf->virus_check = get_flag(dcf_flags, "virusCheck");
    dcf->curse_check = get_flag(dcf_flags, "curseCheck");
    dcf->aggressive_diggers = get_flag(dcf_flags, "aggressiveDiggers");
    dcf->better_pickaxes = get_flag(dcf_flags, "betterPickaxes");
    dcf->ignore_broken_shards = get_flag(dcf_flags, "ignoreBrokenShards");
    dcf->dust_carefully = get_flag(dcf_flags, "dustCarefully");
    dcf->source_packages = get_flag(dcf_flags, "sourcePackages");
}

int dig_from_json(char *filename)
{
    JSON_Value *job = json_parse_file_with_comments((const char *)filename);
    JSON_Object *root = json_object(job);
    JSON_Object *flags = json_object_get_object(root, "flags");
    DigControlFlags dcf;

    set_default_dig_control_flags(&dcf);
    get_dig_control_flags_from_json(&dcf, flags);

    /* Look for the required fields. */
    char *location = NULL;
    location = (char *)json_object_get_string(root, "location");

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

               filename, location, archaeologists, passes, expected_packages);
        exit(1);
    }

    JSON_Array *packages = json_object_get_array(root, "packages");
    if (packages != NULL)
    {
        process_multiple_packages(&dcf, packages);
    }

    json_value_free(job);

    DigStatistics dst;
    initialize_dig_stats(&dst);

    dig_common(archaeologists, expected_packages, passes, location, &dcf,
               &dst);
    exit(0);
}
