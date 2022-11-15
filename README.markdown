![JSON BinPack](./assets/banner.png)

JSON BinPack is an open-source binary JSON serialization format with a **strong
focus on space efficiency**. It supports schema-driven and schema-less modes to
encode any [JSON](https://www.json.org) document given a matching [JSON Schema
2020-12](http://json-schema.org) definition. It was awarded the Tony Hoare
prize for best examination in 2022 by the University of Oxford.

***

**This is a work-in-progress. You can watch the repository or [join the
wait-list on the official website](https://www.jsonbinpack.org) to get a
notification when the first release is out.**

In the mean-time, star the project to show your support!

***

Documentation
-------------

Refer to the project website for documentation:
[https://www.jsonbinpack.org](https://www.jsonbinpack.org).

Do you have any questions? Open a ticket on [GitHub
Discussions](https://github.com/sourcemeta/jsonbinpack/discussions)!

Building JSON BinPack
---------------------

JSON BinPack is a C++ project that makes use of the [CMake](https://cmake.org)
build system. JSON BinPack provides a set of CMake
[presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html) to
configure, build and test the project.

```sh
cmake --list-presets
```

You can configure, build and test the project using a given preset as follows:

```sh
cmake --preset <preset>
cmake --build --preset <preset>
ctest --preset <preset>
```

Once the project has been built, the JSON BinPack command-line tool can be
found at `build/<preset>/src/cli/jsonbinpack`.
