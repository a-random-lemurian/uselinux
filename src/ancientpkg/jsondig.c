/* Documentation in docs/dig_from_json.md */

#include "ancientpkg.h"
#include <string.h>
#include <stdlib.h>
#include <parson/parson.h>

int has_missing_package_params(JSON_Object* package)
{
    const char* maintainer = json_object_get_string(package, "maintainer");
    if (maintainer == NULL)
    {
        return 1;
    }
    if (!strcmp(maintainer, "multiple"))
    {
        JSON_Array* maintainers = json_object_get_array(package,
                                                        "maintainers");
        if (maintainers == NULL)
        {
            return 1;
        }
    }

    const char* pkgname = json_object_get_string(package, "packageName");
    if (pkgname == NULL)
    {
        return 1;
    }

    const char* license = json_object_get_string(package, "license");
    if (license == NULL)
    {
        return 1;
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
        printf("From JSON job file %s: missing arguments.\n", filename);
        exit(1);
    }

    JSON_Array* packages = json_object_get_array(root, "packages");
    JSON_Object* package;
    if (packages != NULL)
    {
        for (size_t i = 0; i < json_array_get_count(packages); i++)
        {
            package = json_array_get_object(packages, i);
            if (package != NULL)
            {
                if (has_missing_package_params(package))
                {
                    printf("Error: missing package params (package %ld)\n",i);
                }
                else
                {
                    const char* pkgname = 
                            json_object_get_string(package, "packageName");
                    const char* license =
                            json_object_get_string(package, "license");
                    printf("[PRIORITY] Prepare excavation of high-priority "
                           "package %s (License: %s)", pkgname, license);
                }
            }
        }
    }

    json_value_free(root);
}
