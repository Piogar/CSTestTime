#pragma once

#include <memory>
#include <string>
#include <vector>

struct TestTimeItem
{
	std::string testName_;
	double testDuration_;
	TestTimeItem(const std::string &name) : testName_(name) {}
};

using TestsTimes = std::vector<TestTimeItem>;

class ITimeLimitCounter
{
public:
	virtual TestsTimes countTestsTimes(float timeDiffPercent) = 0;
	virtual ~ITimeLimitCounter() = default;
};