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

`FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED`
----------------------------------------

The encoding consists of the byte-length of the string minus `minimum` plus 1
as a Base-128 64-bit Little Endian variable-length unsigned integer followed by
the UTF-8 encoding of the input value.

Optionally, if the input string has already been encoded to the buffer using
UTF-8, the encoding may consist of the byte constant `0x00` followed by the
byte-length of the string minus `minimum` plus 1 as a Base-128 64-bit Little
Endian variable-length unsigned integer, followed by the current offset minus
the offset to the start of the UTF-8 string value in the buffer encoded as a
Base-128 64-bit Little Endian variable-length unsigned integer.

#### Options

| Option    | Type   | Description                                    |
|-----------|--------|------------------------------------------------|
| `minimum` | `uint` | The inclusive minimum string UTF-8 byte-length |

#### Conditions

| Condition               | Description                                                          |
|-------------------------|----------------------------------------------------------------------|
| `len(value) >= minimum` | The input string byte-length is equal to or greater than the minimum |

#### Examples

Given the input string `foo` with a minimum 3 where the string has not been
previously encoded, the encoding results in:

```
+------+------+------+------+
| 0x01 | 0x66 | 0x6f | 0x6f |
+------+------+------+------+
         f      o      o
```

Given the encoding of `foo` with a minimum of 0 followed by the encoding of
`foo` with a minimum of 3, the encoding may result in:

```
0      1      2      3      4      5      6
^      ^      ^      ^      ^      ^      ^
+------+------+------+------+------+------+------+
| 0x04 | 0x66 | 0x6f | 0x6f | 0x00 | 0x01 | 0x05 |
+------+------+------+------+------+------+------+
         f      o      o                    6 - 1
```

`ROOF_VARINT_PREFIX_UTF8_STRING_SHARED`
---------------------------------------

The encoding consists of `maximum` minus the byte-length of the string plus 1
as a Base-128 64-bit Little Endian variable-length unsigned integer followed by
the UTF-8 encoding of the input value.

Optionally, if the input string has already been encoded to the buffer using
UTF-8, the encoding may consist of the byte constant `0x00` followed by
`maximum` minus the byte-length of the string plus 1 as a Base-128 64-bit
Little Endian variable-length unsigned integer, followed by the current offset
minus the offset to the start of the UTF-8 string value in the buffer encoded
as a Base-128 64-bit Little Endian variable-length unsigned integer.

#### Options

| Option    | Type   | Description                                    |
|-----------|--------|------------------------------------------------|
| `maximum` | `uint` | The inclusive maximum string UTF-8 byte-length |

#### Conditions

| Condition               | Description                                                       |
|-------------------------|-------------------------------------------------------------------|
| `len(value) <= maximum` | The input string byte-length is equal to or less than the maximum |

#### Examples

Given the input string `foo` with a maximum 4 where the string has not been
previously encoded, the encoding results in:

```
+------+------+------+------+
| 0x02 | 0x66 | 0x6f | 0x6f |
+------+------+------+------+
         f      o      o
```

Given the encoding of `foo` with a maximum of 3 followed by the encoding of
`foo` with a maximum of 5, the encoding may result in:

```
0      1      2      3      4      5      6
^      ^      ^      ^      ^      ^      ^
+------+------+------+------+------+------+------+
| 0x01 | 0x66 | 0x6f | 0x6f | 0x00 | 0x03 | 0x05 |
+------+------+------+------+------+------+------+
         f      o      o                    6 - 1
```
