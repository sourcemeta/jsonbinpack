---
layout: docs
title:  "Encodings: Enum"
---

`BYTE_CHOICE_INDEX`
-------------------

The encoding consists of an index to the enumeration choices encoded as an
8-bit fixed-length unsigned integer.

### Options

| Option    | Type    | Description              |
|-----------|---------|--------------------------|
| `choices` | `any[]` | The set of choice values |

### Conditions

| Condition                | Description                                            |
|--------------------------|--------------------------------------------------------|
| `len(choices) > 0`       | The choices array must not be empty                    |
| `len(choices) <  2 ** 8` | The number of choices must be representable in 8 bits  |
| `value in choices`       | The input value must be included in the set of choices |

### Examples

Given an enumeration `[ "foo", "bar", "baz" ]` and an input value `"bar"`, the
encoding results in the unsigned 8 bit integer 1:

```
+------+
| 0x01 |
+------+
```

Given an enumeration `[ "foo", "bar", "baz" ]` and an input value `"foo"`, the
encoding results in the unsigned 8 bit integer 0:

```
+------+
| 0x00 |
+------+
```
