# DSCEngine 

## How to build

1. Select the build mode.

    - For the normal distribution of DSC (compiles into `libdscengine.a`):

        `set_build normal`

    - For the DSC build that activates test modules (compiles into `libdscengine_testmod.a`, _dev only_):

        `set_build testmod`

2.  Make it

    `make clean & make -f Makefile`

## Using DSCEngine to compile other dependent projects

1. Add `%DSCENGINE%` to your environment variables. Use this automatic script that loads `%DSCENGINE%` to the user variables.

    `setenv`

2. Go to the project's path and type `make`.

    **Warning!** Make sure you use the correct library build to compile your project. Testmodules need a DSCEngine version that
    was compiled with the `TESTMOD` flag.



## Related

- Documentation: https://ds-creator-dev.github.io/docs/dsc-engine/index.html

    See [DOCS.md](DOCS.md) for old docs.

- Examples: https://github.com/DS-Creator-Dev/DSCEngine-Examples

- Tests: https://github.com/DS-Creator-Dev/DSCEngine-Tests

