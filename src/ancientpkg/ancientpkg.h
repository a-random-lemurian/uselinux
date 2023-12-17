#ifndef ANCIENTPKG_H
#define ANCIENTPKG_H
#include <common/macros.h>
#include <common/mtwister.h>
#include <parson/parson.h>

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

    /* Always show all stats */
    int show_all_stats;

    /* Never show stats */
    int no_stats;

    /* Don't wait */
    int dry_run;

    /* Location */
    char *location;

    int force_archaeologists;
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
    int source_packages;
    int proprietary_packages_purged;

    int cursed_packages;
    int cleansing_rituals_performed;
    long double salt_used_kg;
} DigStatistics;

/**
 * @brief Set the default dig control flags in an object.
 *
 * @param dcf The object.
 * @return int An integer.
 */
int set_default_dig_control_flags(DigControlFlags *dcf);

/**
 * @brief The command line interface for the dig command.
 */
int cmd_dig(int argc, char **argv);

/**
 * @brief The command line interface for the date command.
 */
int cmd_date(int argc, char **argv);

/**
 * @brief The command line interface for the excavate command.
 */
int cmd_excavate(int argc, char **argv);

/**
 * @brief The command line interface for the install command.
 */
int cmd_install(int argc, char **argv);

/**
 * @brief Extract the packages.
 *
 * @param archaeologists Number of archaeologists
 * @param expected_packages Packages expected
 * @param passes Number of passes to make over the site
 * @param location Where to extract them
 * @param dcf Dig control flags object
 * @param dst Dig statistics object
 * @return int An integer
 */
int dig_common(int archaeologists, int expected_packages, int passes,
               char *location, DigControlFlags *dcf, DigStatistics *dst);

void package_shard_failure(DigControlFlags *dcf, int i, char *pkgname);

/**
 * @brief Launch a dig job with parameters from a JSON file
 *
 * @param filename Name of JSON file
 * @return int An integer
 */
int dig_from_json(char *filename);

/**
 * @brief Get a flag from a parson JSON object
 *
 * @param dcf_flags The parson JSON object
 * @param name The name of the flag
 * @return int The integer result code of the flag
 */
int get_flag(JSON_Object *dcf_flags, char *name);

/**
 * @brief Get the dig control flags from a parson JSON object.
 *
 * @param dcf The dig control flag object to modify
 * @param dcf_flags The parson JSON object with the dig control flags.
 */
void get_dig_control_flags_from_json(DigControlFlags *dcf,
                                     JSON_Object *dcf_flags);

/**
 * @brief Unimplemented. Performs a ritual.
 *
 * @param i Undocumented due to alien codebase.
 * @param ritual_success An integer value that the function would set if the
 * ritual worked.
 *
 * @param dst Dig statistics object
 * @param dcf Dig contol flags
 * @return long double Undocumented due to alien codebase.
 */
long double perform_ritual(int i, int *ritual_success, DigStatistics *dst,
                           DigControlFlags *dcf);

/**
 * @brief Dust a package carefully
 *
 * @return int The time spent dusting carefully
 */
int dust_carefully();

/* Package checks */
/**
 * @brief Check for curses in the packages.
 *
 * @param loops Loops to make.
 * @param dst Dig statistics object
 * @param dcf Dig control flags object
 * @return int
 */
int curse_check(int loops, DigStatistics *dst, DigControlFlags *dcf);

/**
 * @brief Check for viruses in the packages.
 *
 * @param dcf Dig control flags object
 */
void virus_check(DigControlFlags *dcf);

/**
 * @brief Extract packages
 *
 * @param location Where to extract
 * @param n Undocumented due to alien codebase.
 * @param loops Loops to make
 * @param endch Newline character
 * @param mtw Mersenne twister object
 * @param dcf Dig control flags object
 * @param dst Dig statistics object
 * @return int
 */
int extract_packages(char *location, int n, int loops, char endch, MTRand mtw,
                     DigControlFlags *dcf, DigStatistics *dst);

/**
 * @brief Deal with a broken package shard.
 *
 * @param dcf Object with flags to control the dig job.
 * @param i Shard ID
 * @param pkgname The package with the missing shard.
 */
void deal_with_broken_package_shard(DigControlFlags *dcf, int i,
                                    char *pkgname);

/**
 * @brief Find a shard, getting it from other sources
 */
void find_alternative_sources_for_shards();

/**
 * @brief Initialize a dig statistics object to its default values.
 *
 * @param dst
 */
void initialize_dig_stats(DigStatistics *dst);

/**
 * @brief Print a report of statistics during the dig.
 *
 * @param dst Dig statistics object.
 * @param dcf Object with flags to control the dig job.
 */
void print_dig_stats_report(DigStatistics *dst, DigControlFlags *dcf);

/* Packages ******************************************************************/
/**
 * @brief Validate packages for common errors, at the moment it only checks
 * for missing parameters.
 *
 * @param self The package to validate
 * @return int Whether there are missing parameters
 */
int validate_package(Package *self);

/**
 * @brief Create a package
 *
 * @param self Package object
 * @param name Name of package
 * @param license License of package
 * @return int
 */
int create_package(Package *self, char *name, char *license);

/**
 * @brief If a package has one maintainer, use this function to set the
 * package's maintainer. For a package with multiple maintainers use
 * the set_pkg_multiple_maintainers function instead.
 *
 * @param self
 * @param maintainer
 * @return int
 */
int set_pkg_maintainer(Package *self, char *maintainer);

/**
 * @brief If a package has a group of maintainers, use this function to
 * set the package's maintainers. For a package with one maintainer use the
 * set_pkg_maintainer function instead.
 *
 * @param self The package to modify
 * @param maintainers The maintainers of the package
 * @return int Result code
 */
int set_pkg_multiple_maintainers(Package *self, char **maintainers);

#endif /* ANCIENTPKG_H */
