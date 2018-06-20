#pragma once

#include "ITimeLimitCounter.hpp"
#include "IDataLoader.h"
#include <memory>

class TimeLimitCounter : public ITimeLimitCounter
{
public:
	TimeLimitCounter(std::shared_ptr<dataloader::IDataLoader> dataLoader);
	~TimeLimitCounter() = default;
	TestsTimes countTestsTimes(float timeDiffPercent) override;

private:
	std::shared_ptr<dataloader::IDataLoader> dataLoader_;
};

