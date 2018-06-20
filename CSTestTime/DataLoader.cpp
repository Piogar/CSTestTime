#include "stdafx.h"
#include "DataLoader.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace dataloader
{

DataLoader::DataLoader(std::string path) :
	path_(path)
{
}

TestToTimesMap DataLoader::getData()
{
	std::ifstream file(path_);
	if (!file.is_open())
	{
		std::cout << "Error opening file" << std::endl;
		return{};
	}

	std::cout << "File loaded" << std::endl;
	std::string line;
	TestToTimesMap retMap_;
	std::string testName;
	double duration;

	while (std::getline(file, line))
	{
		if (line.length() == 0)
			continue;

		std::istringstream ss(line);
		ss >> testName;
		ss >> duration;
		if (duration > -1)
		{
			std::cout << "name " << testName << ", duration: " << duration << std::endl;
		}
		else
		{
			std::cout << "error reading duration in " << line << std::endl;
			continue;
		}

		retMap_[testName].push_back(duration);
		duration = -1;
	}

	std::cout << "total tests: " << retMap_.size() << std::endl;
	file.close();
	return retMap_;
}

}