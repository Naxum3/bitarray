#include "../include/BitArray.h"
#include <gtest/gtest.h>
using namespace std;


TEST(Array, Main) {
	// SET/RESET/INITIALIZE

	BitArray b = BitArray(); // Init 32 bits with 0 only val
	ASSERT_TRUE(!b.empty());
	ASSERT_TRUE(b.none()); // not have any true bits
	// invalid sizes check

	// same for |, &, ^
}

int main() {
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
