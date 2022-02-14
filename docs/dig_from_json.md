# JSON Dig Job
For greater control over your Debian package digging, you can specify a
JSON file to read a dig job from.


```json
{
    "archaeologists": 900,
    "expectedPackages": 6500,
    "passes": 5,
    "location": "Egypt",
    "flags": {
        "aggressiveDiggers": null,
        "betterPickaxes": null,
        "dustCarefully": null,
        "sourcePackages": null,
        "noProprietaryPackage": null,
        "virusCheck": null,
        "curseCheck": null
    }
    "packages": [
        // Package syntax
    ]
}
```

The `archaeologists` parameter is the number of archaeologists to send on the
digging expedition. Be mindful of labor costs, and provide enough space
for the archaeologists to take breaks, and deposit their Debian package finds.

The `expectedPackages` parameter is the number of packages that are expected
to be retrieved while digging for Debian packages.

The `passes` parameter is the number of passes to be performed, in essence
repeating the dig jobs to hopefully extract more Debian packages.

The first three parameters must be a number between 1 and the 32-bit signed
integer limit, which is approximately 2.1 billion.

The `location` parameter is the location where the Debian packages will be
excavated from. While not enforced by the application yet, the location
must be on Earth. Latitude/longtitude coordinates are not supported as
arguments to this parameter.

The `packages` parameter is a list of package objects, whose syntax is
described in the below **Packages** section.

The `flags` object contains several flags, described in the **Flags**
section.

The command line has support for the above 4 parameters. Their command-line
equivalent flags are `--archaeologists`, `--expected-pkgs`, `--passes`,
and `--location`, respectively.

All of the above parameters, except `packages` are mandatory.

## Packages

During the course of a dig job, there may be certain high-priority packages
that should be excavated from the dig site.

```json
{
    "packageName": "libhomosapiens",
    "license": "MIT",
    "maintainer": "Natural evolution",
    "maintainers": [

    ]
}
```

The `packageName` parameter is the name of the package.

The `license` parameter is the copyright license that the package has been
placed under.

The `maintainer` field is the maintainer of the package. Should the package
have multiple maintainers, the `maintainer` field must be set to `multiple`
(case sensitive), and a list of maintainers specified in the `maintainers`
parameter. The name of the most significant maintainer must be the first
item of the `maintainers` array. Other than the first item, the list of
other maintainers may be unordered.

All three fields are mandatory (`maintainers` is mandatory if `maintainer`
is "multiple").

## Flags

```json
{
        "aggressiveDiggers": null,
        "betterPickaxes": null,
        "dustCarefully": null,
        "sourcePackages": null,
        "noProprietaryPackage": null,
        "virusCheck": null,
        "curseCheck": null
}
```

Only the `virusCheck` flag is implemented. When the `virusCheck` flag is
specified, each package will undergo several malware scans to prevent
the re-emergence of ancient viruses that may still be on these Debian
packages.
