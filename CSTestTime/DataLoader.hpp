#pragma once

#include "IDataLoader.h"
#include <string>

namespace dataloader
{

class DataLoader : public IDataLoader
{
public:
	DataLoader(std::string path);
	virtual std::map<const std::string, std::vector<double>> getData() override;
	~DataLoader() = default;
private:
	const std::string path_;
};

}