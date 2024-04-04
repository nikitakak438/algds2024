#include "pch.h"
#include "C:\Users\nikib\source\repos\tests1\Test1\Algos1lab\countNumbers.c"

TEST(TestCountNumbers, Test1_1_res1) {
  EXPECT_EQ(1, countNumbers(1, 1));
  EXPECT_TRUE(true);
}

TEST(TestCountNumbers, Test1_10_res0) {
	EXPECT_EQ(0, countNumbers(1, 10));
	EXPECT_TRUE(true);
}

TEST(TestCountNumbers, Test10_1_res10) {
	EXPECT_EQ(10, countNumbers(10, 1));
	EXPECT_TRUE(true);
}

TEST(TestCountNumbers, Test4_4_res35) {
	EXPECT_EQ(35, countNumbers(4, 4));
	EXPECT_TRUE(true);
}