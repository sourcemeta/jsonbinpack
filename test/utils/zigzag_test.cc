// Copyright (c) 2021 Juan Cruz Viotti. All rights reserved.

#include "jsonbinpack/utils/zigzag.h"

#include <gtest/gtest.h>

TEST(ZigZag, EncodeMinus2) {
  EXPECT_EQ(jsonbinpack::utils::ZigzagEncode(-2), 3);
}

TEST(ZigZag, EncodeMinus1) {
  EXPECT_EQ(jsonbinpack::utils::ZigzagEncode(-1), 1);
}

TEST(ZigZag, Encode0) { EXPECT_EQ(jsonbinpack::utils::ZigzagEncode(0), 0); }

TEST(ZigZag, Encode1) { EXPECT_EQ(jsonbinpack::utils::ZigzagEncode(1), 2); }

TEST(ZigZag, Encode2) { EXPECT_EQ(jsonbinpack::utils::ZigzagEncode(2), 4); }
