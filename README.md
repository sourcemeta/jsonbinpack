JSON BinPack
============

JSON BinPack is an open-source binary JSON serialization format with a **strong
focus on space efficiency**. It supports schema-driven and schema-less modes to
encode any [JSON](https://www.json.org) document given a matching [JSON Schema
2020-12](http://json-schema.org) definition.

Building JSON BinPack
---------------------

JSON BinPack is a C++ project that makes use of the [CMake](https://cmake.org)
build system. You can build the project using the standard CMake flow:

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

For convenience, the project also provides an Autotools-like [GNU
Make](https://www.gnu.org/software/make/) integration with simple-to-use
targets. Run the following commands to build JSON BinPack from source:

```sh
./configure
make
```

Contributing
------------

Developing JSON BinPack typically involves running the following set of
targets:

```sh
# Run the tests
make test
# Run the linter
make lint
# Format code changes
make format
```

License
-------

Copyright (C) Juan Cruz Viotti - All Rights Reserved.
