// Copyright (c) 2021 Juan Cruz Viotti. All rights reserved.

#include <gtest/gtest.h>

#include "jsonbinpack/stream/base.h"

TEST(MagicTest, BasicAssertions) {
  EXPECT_EQ(jsonbinpack::stream::sum(4, 2), 6);
}
