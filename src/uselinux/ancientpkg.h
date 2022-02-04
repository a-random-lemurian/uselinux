
#ifndef ANCIENTPKG_H
#define ANCIENTPKG_H

/**
 * @brief A job struct for excavating ancient Debian packages.
 */
typedef struct pkg_dig_job
{
    /// Location of archaeological site to extract packages from.
    char *location;

    /// How thorough the dig process will be.
    int dig_coverage;
} pkg_dig_job;

/**
 * @brief A control struct containing values that will affect the
 * operation of a package digging job.
 */
typedef struct pkg_dig_job_control
{
    /// Maximum number of locations to dig for packages at.
    int max_locs;

    /// Maximum number of sites per location.
    int max_sites;
} pkg_dig_job_control;

/**
 * @brief Set the values of a pkg_dig_job_control struct to their default
 * values.
 */
void pdjctl_set_defaults(pkg_dig_job_control *ctl);

/**
 * @brief Create a package digging job. It is recommended to use this function
 * to create package jobs. Direct modification of the struct is not
 * recommended.
 *
 * @param location Location of archaeological site.
 * @param dig_coverage Thoroughness of digging. Higher values will result in
 * more packages being found, but will incur a significant cost.
 * @param job A pointer to an existing package dig job struct.
 *
 * @return pkg_dig_job A newly created package excavation job.
 */
int mk_pdj_safe(char *location, int dig_coverage, pkg_dig_job *job);

/**
 * @brief Execute a package dig job.
 *
 * @param job The package dig job.
 * @param sanity Whether to perform a sanity check.
 */
void package_dig_job(pkg_dig_job *job, int sanity, pkg_dig_job_control *ctl);

/**
 * @brief Perform a sanity check on a package digging job.
 *
 * @param job The `pkg_dig_job` struct.
 * @return int A return code. If 0 is returned, the sanity check passed.
 */
int pkg_dig_job_sanity_check(pkg_dig_job *job);

/**
 * @brief Dig up ancient Debian packages. This function automatically
 * calls check_digsite() to check digsites for ancient Debian
 * packages.
 *
 * This function excavates digsites around the world. In a future version
 * of uselinux, more precise control over the geographic distribution of
 * digsites chosen may be provided.
 *
 * @deprecated This function is deprecated.
 * Please use ancient_debian_packages_v2() instead.
 */
void ancient_debian_packages();

/**
 * @brief Dig up ancient Debian packages. This function allows for more
 * precise control over the geographic distribution of digsites at
 * compilation time. This function is the successor to the deprecated
 * ancient_debian_packages().
 */
void ancient_debian_packages_v2(pkg_dig_job_control *ctl);

/**
 * @brief Look for ancient Debian packages at a digsite.
 *
 * @param i Digsite's numerical identifier.
 *
 * @return int, Amount of Debian packages found at the digsite.
 */
int check_digsite(int i);

#endif /* ANCIENTPKG_H */
