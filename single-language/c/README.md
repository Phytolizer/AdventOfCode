# Pure C solutions

The folder structure here is simple: `<year>/<day>/src/main.c` holds the implementation.

As a challenge to myself, I am not using much advanced tooling besides AddressSanitizer and the built-in warning flags.
I am restricted to editing in Vim and using GNU `make` to build.

The code can be built by  running `make`, or `make all-2022` to build only 2022 (for example).

The state of the code can be verified by running `make test`, or `make test-<year>` for a specific year.

