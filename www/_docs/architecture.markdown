---
layout: docs
title:  "The Architecture of JSON BinPack"
---

JSON BinPack consists of three software modules: the Canonicalizer, the Encoder
and the Mapper.

![JSON BinPack C4 Container Diagram]({{ site.url }}/assets/images/c4-jsonbinpack-container.png)

The core goal of JSON BinPack is to **unambiguously and bi-directionally map
the high-level data types provided by JSON and JSON Schema to low-level
space-efficient counterparts**.

In order to provide these mappings, JSON BinPack statically analyses the input
JSON Schema definition to derive encoding and decoding rules. We may think of
this process as a *schema refinement* phase that takes a high-level schema
definition that describes an abstract data type and augments it to produce a
new schema definition, referred to as the *encoding schema*, that more
precisely describes how to represent such abstract data type as a bit-string.
The presence of an encoding schema definition for the input data is not enough
by itself to perform serialization and deserialization. To complement schema
refinement, we introduce an *encoder* phase that makes use of an encoding
schema definition to guide the serialization and deserialization processes.

In terms of the phases introduced in this section, the schema refinement phase
is concerned with the high-level schema definition while the encoder is
concerned with the input data instance and the encoding schema definition.
Schema-driven serialization specifications typically exploit this separation of
concerns to optimize for runtime-efficiency by performing the phases that do
not involve the input data at build time. Given the expressiveness of JSON
Schema, the JSON BinPack schema refinement phase is computationally-expensive
yet crucial to achieve space-efficiency.  JSON BinPack exploits this separation
of concerns by allocating unbounded build time resources to the schema
refinement phase and its static analysis process to derive space-efficient
encoding rules.  The schema-refinement phase is performed once per schema
rather than once per input data instance, reducing the amount of computation
required to serialize and deserialize multiple input data instances described
by the same schema definition to a minimum.

Canonicalizer
-------------

See {{ siet.url }}/api/group__canonicalizer.html.

Encode
-------

JSON BinPack implements a diverse set of encodings that are space-efficient in
different scenarios. The *Encoder* component consists of a set of parameterized
serialization and deserialization procedures targetting data types given
different sets of contrains.  The set of serialization and deserialization
procedures defined in the *Encoder* component are bounded by the JSON data
model. However, the set of serialization and deserialization procedures are
agnostic to the schema language used to validate and describe the input data.

![JSON BinPack C4 Encoder Diagram]({{ site.url }}/assets/images/c4-jsonbinpack-encoder.png)

The *Encoder* defines a proxy serialization procedure that given a JSON
document and a matching *Encoding Schema*, serializes the JSON document into a
bit-string using the specific encoding implementation declared by the *Encoding
Schema*. The deserialization process mirrors the serialization process through
a proxy deserialization procedure that deserializes a bit-string into a JSON
document using the specific encoding implementation declared by the Encoding
Schema.

Mapper
------

The *Mapper* component is the bridge between a *Canonical JSON Schema* produced
by the *Canonicalizer* component and an *Encoding Schema* consumed by the
*Encoder* component. The Mapper statically analyses the input *Canonical JSON
Schema* and deterministically computes which encodings and respective encoding
parameters defined by the Encoder are likely to produce the most
space-efficient bit-strings for any JSON instance that successfully validates
against the given schema.

![JSON BinPack C4 Mapper Diagram]({{ site.url }}/assets/images/c4-jsonbinpack-mapper.png)
