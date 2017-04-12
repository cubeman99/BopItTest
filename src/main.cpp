#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <limits>
#include <chrono>
#include <thread>


int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	int rc = RUN_ALL_TESTS();
	
	std::cout << "Press enter to quit...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return rc;
}
