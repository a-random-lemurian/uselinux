#ifndef ANCIENTPKG_H
#define ANCIENTPKG_H
#define WARN BHYEL "warning: " reset
#define ERROR BHRED "error: " reset

typedef struct Subcommand
{
    const char *cmd;
    int (*fn)(int, char **);
    const char *help;
} Subcommand;

typedef struct PackageDatingResult {
    char* package_name;
    int package_age;
    char* dating_method;
} PackageDatingResult;

typedef struct Package {
    char* name;
    char* maintainer;
    char** maintainers_ls;
    char* license;
} Package;

int cmd_dig(int argc, char** argv);
int cmd_date(int argc, char** argv);
int dig_from_json(char* filename);
int has_missing_args(char* location, int archaeologists,
               int passes, int expected_packages);
int dig_common(int archaeologists, int expected_packages,
               int verbose, int passes, char* location);
void package_shard_failure(int i, char* pkgname);

/* Packages ******************************************************************/
int validate_package(Package* self);
int create_package(Package* self, char* name, char* license);
int set_pkg_maintainer(Package* self, char* maintainer);
int set_pkg_multiple_maintainers(Package* self, char** maintainers);
#endif /* ANCIENTPKG_H */
