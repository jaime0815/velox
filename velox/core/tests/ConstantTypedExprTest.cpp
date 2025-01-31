/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <gtest/gtest.h>

#include "velox/core/Expressions.h"

namespace facebook::velox::core::test {

TEST(ConstantTypedExprTest, null) {
  auto makeNull = [](const TypePtr& type) {
    return std::make_shared<ConstantTypedExpr>(
        type, variant::null(type->kind()));
  };

  EXPECT_FALSE(*makeNull(BIGINT()) == *makeNull(DOUBLE()));
  EXPECT_FALSE(*makeNull(ARRAY(BIGINT())) == *makeNull(ARRAY(DOUBLE())));
  EXPECT_FALSE(
      *makeNull(MAP(BIGINT(), INTEGER())) ==
      *makeNull(MAP(BIGINT(), DOUBLE())));

  EXPECT_TRUE(*makeNull(DOUBLE()) == *makeNull(DOUBLE()));
  EXPECT_TRUE(*makeNull(ARRAY(DOUBLE())) == *makeNull(ARRAY(DOUBLE())));
  EXPECT_TRUE(
      *makeNull(ROW({"a", "b"}, {INTEGER(), REAL()})) ==
      *makeNull(ROW({"x", "y"}, {INTEGER(), REAL()})));
}
} // namespace facebook::velox::core::test
