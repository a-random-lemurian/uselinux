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
    int ignore_broken_shards;


    /* Don't wait */
    int dry_run;
} DigControlFlags;

typedef struct Package
{
    char *name;
    char *maintainer;
    char **maintainers_ls;
    char *license;
} Package;

typedef struct DigStatistics
{
    int packages;
    int broken_shards;
    int missing_shards;

    int cursed_packages;
    int cleansing_rituals_performed;
    long double salt_used_kg;
} DigStatistics;

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
               int passes, char *location, DigControlFlags *dcf,
               DigStatistics* dst);
void package_shard_failure(DigControlFlags *dcf, int i, char *pkgname);
int get_flag(JSON_Object *dcf_flags, char *name);
void get_dig_control_flags_from_json(DigControlFlags *dcf,
                                     JSON_Object *dcf_flags);
long double perform_ritual(int i, int *ritual_success, DigStatistics* dst, 
                           DigControlFlags* dcf);
int dust_carefully();
int curse_check(int loops, DigStatistics *dst, DigControlFlags *dcf);
void virus_check(DigControlFlags *dcf);
int extract_packages(char *location, int n,
                     int loops, char endch, MTRand mtw, DigControlFlags *dcf,
                     DigStatistics* dst);
void deal_with_broken_package_shard(DigControlFlags* dcf, int i, char* pkgname);
void find_alternative_sources_for_shards();
void initialize_dig_stats(DigStatistics *dst);
void print_dig_stats_report(DigStatistics *dst);
/* Packages ******************************************************************/
int validate_package(Package *self);
int create_package(Package *self, char *name, char *license);
int set_pkg_maintainer(Package *self, char *maintainer);
int set_pkg_multiple_maintainers(Package *self, char **maintainers);
#endif /* ANCIENTPKG_H */
