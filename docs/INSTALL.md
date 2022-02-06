# uselinux Install
[Home](/README.md)

Installing `uselinux` requires CMake. `uselinux` **does not support Windows and is not designed with Windows compatibilty in mind**. This program is mostly developed on Ubuntu 20.04.

```
mkdir build
cd build
cmake ..
make
```

There will be a `bin` directory in the build directory, containing the executables. Supply `--help` to those executables to get help information.


## Generating Documentation

Run `doxygen` in the project's root directory.
