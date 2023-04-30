---
layout: docs
title:  "Encodings: Array"
---

`FIXED_TYPED_ARRAY`
-------------------

The encoding consists of the elements of the fixed array encoded in order. The
encoding of the element at index `i` is either `prefixEncodings[i]` if set, or
`encoding`.

#### Options

| Option            | Type         | Description          |
|-------------------|--------------|----------------------|
| `size`            | `uint`       | The array length     |
| `prefixEncodings` | `encoding[]` | Positional encodings |
| `encoding`        | `encoding`   | Element encoding     |

#### Conditions

| Condition                      | Description                                                           |
|--------------------------------|-----------------------------------------------------------------------|
| `len(prefixEncodings) <= size` | The number of prefix encodings must be less than or equal to the size |
| `len(value) == size`           | The input array must have the declared size                           |

### Examples

Given the array `[ 1, 2, true ]` where the `prefixEncodings` corresponds to
[`BOUNDED_MULTIPLE_8BITS_ENUM_FIXED`](./integer) (minimum 0, maximum 10,
multiplier 1) and [`BOUNDED_MULTIPLE_8BITS_ENUM_FIXED`](./integer) (minimum 0,
maximum 10, multiplier 1) and `encoding` corresponds to
[`BYTE_CHOICE_INDEX`](./enum) with choices `[ false, true ]`, the encoding
results in:

```
+------+------+------+
| 0x00 | 0x01 | 0x01 |
+------+------+------+
  1      2      true
```
