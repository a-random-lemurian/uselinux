#ifndef ANCIENTPKG_H
#define ANCIENTPKG_H
#include <common/mtwister.h>
#include <parson/parson.h>
#define WARN BHYEL "warning: " reset
#define ERROR BHRED "error: " reset

typedef struct Subcommand
{
    const char *cmd;
    int (*fn)(int, char **);
    const char *help;
} Subcommand;

typedef struct PackageDatingResult
{
    char *package_name;
    int package_age;
    char *dating_method;
} PackageDatingResult;

typedef struct DigControlFlags
{
    int aggressive_diggers;
    int better_pickaxes;
    int dust_carefully;
    int source_packages;
    int no_proprietary_packages;
    int virus_check;
    int curse_check;
    int ignore_missing_shards;
} DigControlFlags;

typedef struct Package
{
    char *name;
    char *maintainer;
    char **maintainers_ls;
    char *license;
} Package;

int set_dig_control_flags(DigControlFlags *dcf, int aggressive_diggers,
                          int better_pickaxes, int dust_carefully,
                          int source_packages, int no_proprietary_packages,
                          int virus_check, int curse_check);
int cmd_dig(int argc, char **argv);
int cmd_date(int argc, char **argv);
int dig_from_json(char *filename);
int set_default_dig_control_flags(DigControlFlags *dcf);
int has_missing_args(char *location, int archaeologists, int passes,
                     int expected_packages);
int dig_common(int archaeologists, int expected_packages, int verbose,
               int passes, char *location, DigControlFlags* dcf);
void package_shard_failure(int i, char *pkgname);
int get_flag(JSON_Object* dcf_flags, char* name);
void get_dig_control_flags_from_json(DigControlFlags *dcf,
                                     JSON_Object *dcf_flags);
void perform_ritual(int i, int *ritual_success);
void curse_check(int loops);
void virus_check();
int extract_packages(char *location, int n, int verbose, int *packages, int loops, char endch, MTRand mtw, DigControlFlags *dcf);

/* Packages ******************************************************************/
int validate_package(Package *self);
int create_package(Package *self, char *name, char *license);
int set_pkg_maintainer(Package *self, char *maintainer);
int set_pkg_multiple_maintainers(Package *self, char **maintainers);
#endif /* ANCIENTPKG_H */
