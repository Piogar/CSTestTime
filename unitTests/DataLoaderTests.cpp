#include "gtest\gtest.h"
#include "gmock\gmock.h"

#include <stdio.h>
#include <memory>
#include <vector>
#include <fstream>
#include "DataLoader.hpp"

class DataLoaderFixture : public ::testing::Test
{
public:
	void SetUp()
	{
		test1Name_ = "testNo1";
		test2Name_ = "testNo2";
		lines_.push_back(test1Name_ + "	23.1\n");
		lines_.push_back(test2Name_ + "	51.0\n");
		lines_.push_back(test1Name_ + "	20.0\n");
		path_ = "data.txt";

		saveSomeLinesToFile(path_);
	}

	void TearDown()
	{
		std::remove(path_.c_str());
	}

	void saveSomeLinesToFile(const std::string &path)
	{
		std::ofstream file(path);
		for (const auto & line : lines_)
			file << line;

		file.close();
	}

public:
	std::string path_;
	std::string test1Name_;
	std::string test2Name_;
	std::vector<std::string> lines_;
};

TEST_F(DataLoaderFixture, expect2TestsReadIf2InFile)
{
	dataloader::DataLoader sut(path_);
	EXPECT_EQ(2, sut.getData().size());
}

TEST_F(DataLoaderFixture, expectCorrectNumberOfExecTimesToBeRead)
{
	dataloader::DataLoader sut(path_);
	auto ret = sut.getData();
	EXPECT_EQ(2, ret[test1Name_].size());
	EXPECT_EQ(1, ret[test2Name_].size());
}
