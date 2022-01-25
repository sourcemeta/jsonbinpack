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

Once the project has been built, the JSON BinPack command-line tool can be
executed through the `bin/jsonbinpack` utility script:

```sh
./bin/jsonbinpack version
```

License
-------

Copyright (C) Juan Cruz Viotti - All Rights Reserved.
