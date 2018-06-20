#include "gtest\gtest.h"
#include "gmock\gmock.h"

#include <memory>
#include "DataLoaderMock.hpp"
#include "TimeLimitCounter.hpp"

class TimeLimitCounterFixture : public ::testing::Test
{
	void SetUp()
	{
		dataLoaderMock_ = std::make_shared<DataLoaderMock>();
		percentDiff_ = 0.0f;
	}

public:
	std::shared_ptr<DataLoaderMock> dataLoaderMock_;
	float percentDiff_;
};

TEST_F(TimeLimitCounterFixture, expectDataLoaderGetDataToBeCalled)
{
	TimeLimitCounter sut(dataLoaderMock_);
	
	EXPECT_CALL(*dataLoaderMock_, getData());
	EXPECT_EQ(0, sut.countTestsTimes(percentDiff_).size());
}

TEST_F(TimeLimitCounterFixture, expectMultipleTestsAndTimeWhenMultipleReturnedFromDataLoader)
{
	TimeLimitCounter sut(dataLoaderMock_);
	dataloader::TestToTimesMap ret;
	ret["test1"].push_back(10);
	ret["test2"].push_back(20);

	EXPECT_CALL(*dataLoaderMock_, getData()).WillOnce(::testing::Return(ret));
	EXPECT_EQ(2, sut.countTestsTimes(percentDiff_).size());
}

TEST_F(TimeLimitCounterFixture, expectSameValueAsAvgWhenAllTimesTheSameAndDiffPercent0)
{
	TimeLimitCounter sut(dataLoaderMock_);
	double loadedTime = 10;
	dataloader::TestToTimesMap ret;
	ret["test1"].push_back(loadedTime);
	ret["test1"].push_back(loadedTime);

	EXPECT_CALL(*dataLoaderMock_, getData()).WillOnce(::testing::Return(ret));
	auto res = sut.countTestsTimes(percentDiff_);
	EXPECT_EQ(1, res.size());
	EXPECT_EQ(loadedTime, res.front().testDuration_);
}

TEST_F(TimeLimitCounterFixture, shouldReturn0IfProblemDuringReadingDataOccured)
{
	TimeLimitCounter sut(dataLoaderMock_);
	double loadedTime = 10;
	dataloader::TestToTimesMap ret;
	ret["test1"] = std::vector<double>();

	EXPECT_CALL(*dataLoaderMock_, getData()).WillOnce(::testing::Return(ret));
	auto res = sut.countTestsTimes(percentDiff_);
	EXPECT_EQ(1, res.size());
	EXPECT_EQ(0, res.front().testDuration_);
}

TEST_F(TimeLimitCounterFixture, shouldIncreaseTimeAccordingToConfiguredPercentDiff)
{
	percentDiff_ = 50.0f;
	TimeLimitCounter sut(dataLoaderMock_);
	double loadedTime = 10;
	dataloader::TestToTimesMap ret;
	ret["test1"].push_back(10);

	EXPECT_CALL(*dataLoaderMock_, getData()).WillOnce(::testing::Return(ret));
	auto res = sut.countTestsTimes(percentDiff_);
	EXPECT_EQ(1, res.size());
	EXPECT_EQ(loadedTime * (1 + percentDiff_ / 100), res.front().testDuration_);
}