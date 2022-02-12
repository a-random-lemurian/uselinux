/* Documentation in docs/dig_from_json.md */

#include "ancientpkg.h"
#include <parson/parson.h>

int dig_from_json(char* filename)
{
    JSON_Value *job = json_parse_file_with_comments((const char**)filename);
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
        printf("From the command line: missing arguments.\n");
        exit(1);
    }
}
