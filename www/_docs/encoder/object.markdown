---
layout: docs
title:  "Encodings: Object"
---

`FIXED_TYPED_ARBITRARY_OBJECT`
------------------------------

The encoding consists of each pair encoded as the key followed by the value
according to `keyEncoding` and `encoding`. The order in which pairs are encoded
is undefined.

### Options

| Option        | Type       | Description     |
|---------------|------------|-----------------|
| `size`        | `uint`     | The object size |
| `keyEncoding` | `encoding` | Key encoding    |
| `encoding`    | `encoding` | Value encoding  |

### Conditions

| Condition            | Description                                               |
|----------------------|-----------------------------------------------------------|
| `len(value) == size` | The input object must have the declared amount of entries |

### Examples

Given the array `{ "foo": 1, "bar": 2 }` where `keyEncoding` corresponds to
[`UTF8_STRING_NO_LENGTH`](./string) (size 3) and `encoding` corresponds to
[`BOUNDED_MULTIPLE_8BITS_ENUM_FIXED`](./integer) (minimum 0, maximum 10,
multiplier 1), the encoding results in:

```
+------+------+------+------+------+------+------+------+
| 0x66 | 0x6f | 0x6f | 0x01 | 0x62 | 0x61 | 0x72 | 0x02 |
+------+------+------+------+------+------+------+------+
  f      o      o      1      b      a      r      2
```

Or:

```
+------+------+------+------+------+------+------+------+
| 0x62 | 0x61 | 0x72 | 0x02 | 0x66 | 0x6f | 0x6f | 0x01 |
+------+------+------+------+------+------+------+------+
  b      a      r      2      f      o      o      1
```

`VARINT_TYPED_ARBITRARY_OBJECT`
-------------------------------

The encoding consists of the number of key-value pairs in the input object as a
Base-128 64-bit Little Endian variable-length unsigned integer followed by each
pair encoded as the key followed by the value according to `keyEncoding` and
`encoding`. The order in which pairs are encoded is undefined.

### Options

| Option        | Type       | Description    |
|---------------|------------|----------------|
| `keyEncoding` | `encoding` | Key encoding   |
| `encoding`    | `encoding` | Value encoding |

### Examples

Given the array `{ "foo": 1, "bar": 2 }` where `keyEncoding` corresponds to
[`UTF8_STRING_NO_LENGTH`](./string) (size 3) and `encoding` corresponds to
[`BOUNDED_MULTIPLE_8BITS_ENUM_FIXED`](./integer) (minimum 0, maximum 10,
multiplier 1), the encoding results in:

```
+------+------+------+------+------+------+------+------+------+
| 0x02 | 0x66 | 0x6f | 0x6f | 0x01 | 0x62 | 0x61 | 0x72 | 0x02 |
+------+------+------+------+------+------+------+------+------+
  2      f      o      o      1      b      a      r      2
```

Or:

```
+------+------+------+------+------+------+------+------+------+
| 0x02 | 0x62 | 0x61 | 0x72 | 0x02 | 0x66 | 0x6f | 0x6f | 0x01 |
+------+------+------+------+------+------+------+------+------+
  2      b      a      r      2      f      o      o      1
```
