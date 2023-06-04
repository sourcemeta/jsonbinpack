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

`BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED`
----------------------------------------

The encoding consists of the byte-length of the string minus `minimum` plus 1
as an 8-bit fixed-length unsigned integer followed by the UTF-8 encoding of the
input value.

Optionally, if the input string has already been encoded to the buffer using
UTF-8, the encoding may consist of the byte constant `0x00` followed by the
byte-length of the string minus `minimum` plus 1 as an 8-bit fixed-length
unsigned integer, followed by the current offset minus the offset to the start
of the UTF-8 string value in the buffer encoded as a Base-128 64-bit Little
Endian variable-length unsigned integer.

The byte-length of the string is encoded even if `maximum` equals `minimum` in
order to disambiguate between shared and non-shared fixed strings.

#### Options

| Option    | Type   | Description                                    |
|-----------|--------|------------------------------------------------|
| `minimum` | `uint` | The inclusive minimum string UTF-8 byte-length |
| `maximum` | `uint` | The inclusive maximum string UTF-8 byte-length |

#### Conditions

| Condition                        | Description                                                          |
|----------------------------------|----------------------------------------------------------------------|
| `len(value) >= minimum`          | The input string byte-length is equal to or greater than the minimum |
| `len(value) <= maximum`          | The input string byte-length is equal to or less than the maximum    |
| `maximum - minimum < 2 ** 8 - 1` | The range minus 1 must be representable in 8 bits                    |

#### Examples

Given the input string `foo` with a minimum 3 and a maximum 5 where the string
has not been previously encoded, the encoding results in:

```
+------+------+------+------+
| 0x01 | 0x66 | 0x6f | 0x6f |
+------+------+------+------+
         f      o      o
```

Given the encoding of `foo` with a minimum of 0 and a maximum of 6 followed by
the encoding of `foo` with a minimum of 3 and a maximum of 100, the encoding
may result in:

```
0      1      2      3      4      5      6
^      ^      ^      ^      ^      ^      ^
+------+------+------+------+------+------+------+
| 0x04 | 0x66 | 0x6f | 0x6f | 0x00 | 0x01 | 0x05 |
+------+------+------+------+------+------+------+
         f      o      o                    6 - 1
```

`RFC3339_DATE_INTEGER_TRIPLET`
------------------------------

The encoding consists of an implementation of
[RFC3339](https://datatracker.ietf.org/doc/html/rfc3339) date expressions as
the sequence of 3 integers: the year as a 16-bit fixed-length Little Endian
unsigned integer, the month as an 8-bit fixed-length unsigned integer, and the
day as an 8-bit fixed-length unsigned integer.

#### Options

None

#### Conditions

| Condition            | Description                                                 |
|----------------------|-------------------------------------------------------------|
| `len(value) == 10`   | The input string consists of 10 characters                  |
| `value[0:4] >= 0`    | The year is greater than or equal to 0                      |
| `value[0:4] <= 9999` | The year is less than or equal to 9999 as stated by RFC3339 |
| `value[4] == '-'`    | The year and the month are divided by a hyphen              |
| `value[5:7] >= 1`    | The month is greater than or equal to 1                     |
| `value[5:7] <= 12`   | The month is less than or equal to 12                       |
| `value[7] == '-'`    | The month and the day are divided by a hyphen               |
| `value[8:10] >= 1`   | The day is greater than or equal to 1                       |
| `value[8:10] <= 31`  | The day is less than or equal to 31                         |

#### Examples

Given the input string `2014-10-01`, the encoding results in:

```
+------+------+------+------+
| 0xde | 0x07 | 0x0a | 0x01 |
+------+------+------+------+
  year   ...    month  day
```

`PREFIX_VARINT_LENGTH_STRING_SHARED`
------------------------------------

The encoding consists of the byte-length of the string plus 1 as a Base-128
64-bit Little Endian variable-length unsigned integer followed by the UTF-8
encoding of the input value.

Optionally, if the input string has already been encoded to the buffer using
this encoding the encoding may consist of the byte constant `0x00` followed by
the current offset minus the offset to the start of the string as a Base-128
64-bit Little Endian variable-length unsigned integer.  It is permissible to
point to another instance of the string that is a pointer itself.

### Options

None

### Conditions

None

### Examples

Given the input string `foo` where the string has not been previously encoded,
the encoding results in:

```
+------+------+------+------+
| 0x04 | 0x66 | 0x6f | 0x6f |
+------+------+------+------+
         f      o      o
```

Given the encoding of `foo` repeated 3 times, the encoding may result in:

```
0      1      2      3      4      5      6      7
^      ^      ^      ^      ^      ^      ^      ^
+------+------+------+------+------+------+------+------+
| 0x04 | 0x66 | 0x6f | 0x6f | 0x00 | 0x05 | 0x00 | 0x03 |
+------+------+------+------+------+------+------+------+
         f      o      o             5 - 0         7 - 4
```
