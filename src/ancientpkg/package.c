#include <ancientpkg.h>
#include <common/ansiescapes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int validate_package(Package *self)
{
    int has_missing = 0;
    if (self->maintainer == NULL)
    {
        printf(ERROR "Missing parameter \"maintainer\" in package.\n");
        has_missing = 1;
    }
    if (!strcmp(self->maintainer, "multiple"))
    {
        if (self->maintainers_ls == NULL)
        {
            printf(ERROR "Missing parameter \"maintainers\" in package.\n");
            has_missing = 1;
        }
    }
    else
    {
        if (self->maintainers_ls != NULL)
        {
            printf(ERROR "Both \"maintainer\" and \"maintainers\" fields "
                         "were filled in.\n");
            has_missing = 1;
        }
    }
    if (self->name == NULL)
    {
        printf(ERROR "Missing parameter \"packageName\" in package.\n");
        has_missing = 1;
    }
    if (self->license == NULL)
    {
        printf(ERROR "Missing parameter \"license\" in package.\n");
        has_missing = 1;
    }

    return has_missing;
}

int create_package(Package *self, char *name, char *license)
{
    self->name = name;
    self->license = license;
    return 0;
}

int set_pkg_maintainer(Package *self, char *maintainer)
{
    self->maintainer = maintainer;
    self->maintainers_ls = NULL;
    return 0;
}

int set_pkg_multiple_maintainers(Package *self, char **maintainers)
{
    self->maintainer = "multiple";
    self->maintainers_ls = maintainers;
    return 0;
}
