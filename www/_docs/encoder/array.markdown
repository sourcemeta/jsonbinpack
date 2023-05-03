---
layout: docs
title:  "Encodings: Array"
---

`FIXED_TYPED_ARRAY`
-------------------

The encoding consists of the elements of the fixed array encoded in order. The
encoding of the element at index `i` is either `prefixEncodings[i]` if set, or
`encoding`.

### Options

| Option            | Type         | Description          |
|-------------------|--------------|----------------------|
| `size`            | `uint`       | The array length     |
| `prefixEncodings` | `encoding[]` | Positional encodings |
| `encoding`        | `encoding`   | Element encoding     |

### Conditions

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

`BOUNDED_8BITS_TYPED_ARRAY`
---------------------------

The encoding consists of the length of the array minus `minimum` encoded as an
8-bit fixed-length unsigned integer followed by the elements of the array
encoded in order. The encoding of the element at index `i` is either
`prefixEncodings[i]` if set, or `encoding`.

### Options

| Option            | Type         | Description                     |
|-------------------|--------------|---------------------------------|
| `minimum`         | `uint`       | The minimum length of the array |
| `maximum`         | `uint`       | The maximum length of the array |
| `prefixEncodings` | `encoding[]` | Positional encodings            |
| `encoding`        | `encoding`   | Element encoding                |

### Conditions

| Condition                              | Description                                                                           |
|----------------------------------------|---------------------------------------------------------------------------------------|
| `len(value) >= minimum`                | The length of the array must be greater than or equal to the minimum                  |
| `len(value) <= maximum`                | The length of the array must be less than or equal to the maximum                     |
| `len(prefixEncodings) <= maximum`      | The number of prefix encodings must be less than or equal to the maximum array length |
| `len(maximum) - len(minimum) < 2 ** 8` | The array length must be representable in 8 bits                                      |

### Examples

Given the array `[ true, false, 5 ]` where the minimum is 1 and the maximum is
3, the `prefixEncodings` corresponds to [`BYTE_CHOICE_INDEX`](./enum) with
choices `[ false, true ]` and [`BYTE_CHOICE_INDEX`](./enum) with choices `[
false, true ]` and `encoding` corresponds to
[`BOUNDED_MULTIPLE_8BITS_ENUM_FIXED`](./integer) with minimum 0 and maximum
255, the encoding results in:

```
+------+------+------+------+
| 0x02 | 0x01 | 0x00 | 0x05 |
+------+------+------+------+
  size   true   false  5
```


`BOUNDED_TYPED_ARRAY`
---------------------

The encoding consists of the length of the array minus `minimum` encoded as a
Base-128 64-bit Little Endian variable-length unsigned integer followed by the
elements of the array encoded in order. The encoding of the element at index
`i` is either `prefixEncodings[i]` if set, or `encoding`.

### Options

| Option            | Type         | Description                     |
|-------------------|--------------|---------------------------------|
| `minimum`         | `uint`       | The minimum length of the array |
| `maximum`         | `uint`       | The maximum length of the array |
| `prefixEncodings` | `encoding[]` | Positional encodings            |
| `encoding`        | `encoding`   | Element encoding                |

### Conditions

| Condition                         | Description                                                                           |
|-----------------------------------|---------------------------------------------------------------------------------------|
| `len(value) >= minimum`           | The length of the array must be greater than or equal to the minimum                  |
| `len(value) <= maximum`           | The length of the array must be less than or equal to the maximum                     |
| `len(prefixEncodings) <= maximum` | The number of prefix encodings must be less than or equal to the maximum array length |

### Examples

Given the array `[ true, false, 5 ]` where the minimum is 1 and the maximum is
3, the `prefixEncodings` corresponds to [`BYTE_CHOICE_INDEX`](./enum) with
choices `[ false, true ]` and [`BYTE_CHOICE_INDEX`](./enum) with choices `[
false, true ]` and `encoding` corresponds to
[`BOUNDED_MULTIPLE_8BITS_ENUM_FIXED`](./integer) with minimum 0 and maximum
255, the encoding results in:

```
+------+------+------+------+
| 0x02 | 0x01 | 0x00 | 0x05 |
+------+------+------+------+
  size   true   false  5
```
