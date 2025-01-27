**This is a work-in-progress. Please consider starring or watching the repository
to stay up to date.**

***

![JSON BinPack](./assets/banner.png)

JSON BinPack is an open-source binary JSON serialization format with a **strong
focus on space efficiency**. It supports schema-driven and schema-less modes to
encode any [JSON](https://www.json.org) document given a matching [JSON Schema
2020-12](http://json-schema.org) definition.

![](./assets/example.png)

- **Highly Space-efficient**: A reproducible benchmark study has proven JSON
  BinPack to be space-efficient in comparison to 12 alternative binary
  serialization formats in every considered case. Additionally, JSON BinPack
  typically provides higher average size reduction than general purpose
  compressors such as GZIP, LZMA and LZ4 with the highest compression levels.

    [Take a look at the benchmark](https://benchmark.sourcemeta.com)

- **Based on JSON Schema**: JSON BinPack adopts the industry-standard schema
  language for JSON documents. Re-use the same schemas you already have in your
  OpenAPI, AsyncAPI, RAML or other specifications. No need to learn more
  domain-specific schema languages or attempt to translate between them.

    [Learn more about JSON Schema](https://json-schema.org/)

- **Optional Schema**: JSON BinPack is a hybrid serialization format that runs
  in both schema-driven and schema-less modes. Thanks to JSON Schema, JSON
  BinPack allows you to be as loose or specific as your use case demands, even
  within the same document, without having to use different serialization
  technologies.

    [Read more about JSON Schema as a constraint system](https://modern-json-schema.com/json-schema-is-a-constraint-system)

Documentation
-------------

Refer to the project website for reference documentation:
[https://jsonbinpack.sourcemeta.com](https://jsonbinpack.sourcemeta.com).

Do you have any questions? Open a ticket on [GitHub
Discussions](https://github.com/sourcemeta/jsonbinpack/discussions)!

Frequently Asked Questions
--------------------------

### How does JSON BinPack compare to compression formats like GZIP?

Our [reproducible benchmark study](https://benchmark.sourcemeta.com) shows that
the semantic information provided by detailed schema definitions enables a
serialization format such as JSON BinPack to often outperform general-purpose
compressors configured with even their highest supported compression levels,
specially for small and medium-sized JSON documents. For large JSON documents,
you can experiment combining JSON BinPack with a compression format to
potentially achieve greater space-efficiency.

### JSON BinPack is space-efficient, but what about runtime-efficiency?

When transmitting data over the Internet, time is the bottleneck, making
computation much cheaper in comparison. Leaving extremely low-powered devices
aside, trading more CPU cycles for better compression is a sensible choice.
JSON BinPack particularly excels at improving network performance when
transmitting data through unreliable and low-bandwidth connections on mobile
and IoT systems, and it is still optimized to deliver the best runtime
efficiency possible.

If your use-case demands extreme runtime-efficiency or zero-copy serialization,
such as in the case of intra-service or inter-process communication, we suggest
you consider alternative serialization formats such as
[FlatBuffers](https://google.github.io/flatbuffers/) and [Cap'n
Proto](https://capnproto.org/).

### How does JSON BinPack handle unknown fields?

JSON BinPack serializes any instance that matches its JSON Schema definition.
JSON Schema is an expressive constrain-based language that permits
schema-writers to be as strict or loose on defining data as they wish. As a
consequence of adopting JSON Schema, JSON BinPack elegantly supports encoding
free-form data and unknown fields as long as the corresponding JSON Schema
definition successfully validates the data.

However, deserializing data that does not match the given JSON Schema
definition is undefined behavior and will likely result in an exception being
thrown.

### How does JSON BinPack compare to [alternative]?

We maintain a [live benchmark](https://benchmark.sourcemeta.com/) comparing
JSON BinPack to various popular alternatives, including Protocol Buffers, CBOR,
MessagePack, Apache Avro, and more. We also published an [academic
paper](https://arxiv.org/abs/2211.12799) discussing the benchmark results in
more detail. In summary, you can expect JSON BinPack to be as or more
space-efficient than every alternative in every tested case.

### How does JSON BinPack support schema evolution?

In comparison to schema-driven alternatives like Protocol Buffers and Apache
Avro that invented their own specialized schema language, JSON BinPack adopts a
popular and industry-standard one: [JSON Schema](https://json-schema.org/).
This means that you can use JSON BinPack alongside any schema evolution tooling
or approach from the wider JSON Schema ecosystem. A popular one from the
decentralised systems world is
[Cambria](https://www.inkandswitch.com/cambria/).

***

Do you have further questions or feedback? Don't hesitate in reaching out on
[GitHub
Discussions](https://github.com/sourcemeta/jsonbinpack/discussions)!

Research
--------

JSON BinPack is the result of extensive binary serialization research at the
Department of Computer Science of University of Oxford. The project is led by
Juan Cruz Viotti, a computer scientist with first-hand exposure to the problem
of space-efficient network communication in the context of IoT and APIs, under
the supervision of Mital Kinderkhedia.

- [JSON BinPack: A space-efficient schema-driven and schema-less binary
serialization specification based on JSON
Schema](https://www.jviotti.com/dissertation.pdf)

    - Awarded the 2022 CAR Hoare Prize for the best performance on the project
      in the MSc in Software Engineering
    - Awarded the 2022 CAR Hoare Prize for the best performance in the
      examination by coursework in the MSc in Software Engineering

- [Benchmarking JSON BinPack](https://arxiv.org/abs/2211.12799)
- [A benchmark of JSON-compatible binary serialization
  specifications](https://arxiv.org/abs/2201.03051)
- [A survey of JSON-compatible binary serialization
  specification](https://arxiv.org/abs/2201.02089)
