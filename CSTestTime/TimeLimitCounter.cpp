#include "stdafx.h"

#include <iostream>
#include <numeric>
#include "TimeLimitCounter.hpp"
#include "IDataLoader.h"


TimeLimitCounter::TimeLimitCounter(std::shared_ptr<dataloader::IDataLoader> dataLoader) :
	dataLoader_(dataLoader)
{
}

TestsTimes TimeLimitCounter::countTestsTimes(float timeDiffPercent)
{
	auto data = dataLoader_->getData();
	TestsTimes allTestsTimes;

	for (const auto & testData : data)
	{
		TestTimeItem item(testData.first);
		std::cout << "Data for " << item.testName_ << std::endl;
		if (testData.second.empty())
		{
			item.testDuration_ = 0; // In case of problems returning 0 as clearly incorrect value
			std::cout << "Durations for " << item.testName_ << " is empty" << std::endl;
		}

		double avgTime = 0;
		for (const auto & time : testData.second)
		{
			avgTime += (time / testData.second.size()); // adding smaller numbers to avoid overflow
		}

		item.testDuration_ = avgTime * (1 + timeDiffPercent/100);
		allTestsTimes.push_back(item);
		std::cout << "Avg duration of " << item.testName_ << " is " << item.testDuration_ << std::endl;
	}
	
	return allTestsTimes;
}
