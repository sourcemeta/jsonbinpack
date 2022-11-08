---
layout: docs
title:  "Encodings: String"
---

`UTF8_STRING_NO_LENGTH`
-----------------------

The encoding consist in the UTF-8 encoding of the input string.

### Options

| Option | Type   | Description                  |
|--------|--------|------------------------------|
| `size` | `uint` | The string UTF-8 byte-length |

### Conditions

| Condition            | Description                                               |
|----------------------|-----------------------------------------------------------|
| `len(value) == size` | The input string must have the declared UTF-8 byte-length |

### Examples

Given the input value "foo bar" with a corresponding size of 7, the encoding
results in:

```
+------+------+------+------+------+------+------+
| 0x66 | 0x6f | 0x6f | 0x20 | 0x62 | 0x61 | 0x72 |
+------+------+------+------+------+------+------+
  f      o      o             b      a      r
```
