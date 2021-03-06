#pragma once

#include <map>
#include <string>
#include <vector>

namespace dataloadersssss
{

using TestToTimesMap = std::map<const std::string, std::vector<double>>;

class IDataLoader
{
public:
	virtual TestToTimesMap getData() = 0;
	virtual ~IDataLoader() = default;
};

}