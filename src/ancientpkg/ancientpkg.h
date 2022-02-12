#ifndef ANCIENTPKG_H
#define ANCIENTPKG_H
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

int cmd_dig(int argc, char** argv);
int cmd_date(int argc, char** argv);
int dig_from_json(char* filename);
int has_missing_args(char* location, int archaeologists,
               int passes, int expected_packages);
int dig_common(int archaeologists, int expected_packages,
               int verbose, int passes, char* location)
#endif /* ANCIENTPKG_H */
