#include "../../src/Model.h"
#include "gtest/gtest.h"

TEST(ModelTest, Select) {
  Model model;
  EXPECT_EQ(std::nullopt, model.selectedSampleIndex());
}
