---
layout: docs
title:  "Encodings: Number"
---

`DOUBLE_VARINT_TUPLE`
---------------------

The encoding consists of a sequence of two integers: The signed integer that
results from concatenating the integral part and the decimal part of the
number, if any, as a ZigZag-encoded Base-128 64-bit Little Endian
variable-length unsigned integer; and the position of the decimal mark from the
last digit of the number encoded as a Base-128 64-bit Little Endian
variable-length unsigned integer.

### Options

None

### Conditions

None

### Examples

Given the input value 3.14, the encoding results in the variable-length integer
628 (the ZigZag encoding of 314) followed by the variable-length unsigned
integer 2 (the number of decimal digits in the number).

```
+------+------+------+
| 0xf4 | 0x04 | 0x02 |
+------+------+------+
```

Real numbers that represent integers are encoded with a decimal mark of zero.
Given the input value -5.0, the encoding results in the variable-length integer
9 (the ZigZag encoding of -5) followed by the variable-length unsigned integer
0.

```
+------+------+
| 0x09 | 0x00 |
+------+------+
```
