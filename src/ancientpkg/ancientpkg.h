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
#endif /* ANCIENTPKG_H */
