// CSTestTime.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "DataLoader.hpp"
#include "TimeLimitCounter.hpp"

void saveOutput(const TestsTimes &times) // Results expected to be in XML, so saving them would be moved to separate class
{
	std::ofstream file("output.txt");
	if (!file.is_open())
	{
		std::cout << "Problem saving file" << std::endl;
		return;
	}
	for (const auto & test : times)
		file << test.testName_ << "\t" << test.testDuration_ << "\n";

	file.close();
}


int main()
{
	auto loader = std::make_shared<dataloader::DataLoader>("Executions3.txt");
	// Path to file with test data. In real environment XML formatted to fit test invironment is expected, here is simple
	// file with test name and test time. Depending on environemnt path for in and out could be input from user. 

	TimeLimitCounter counter(loader);
	float allowedPercentDiffToAvg = 10.0f;	// defined by user value which by which average time should be increased to
											// calculate new max time for tests. Value could be passed by user as input 
	auto testsTimes = counter.countTestsTimes(allowedPercentDiffToAvg);

	saveOutput(testsTimes);

    return 0;
}

