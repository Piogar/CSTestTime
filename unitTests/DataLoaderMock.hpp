#pragma once

#include "IDataLoader.h"
#include <gmock\gmock.h>

class DataLoaderMock : public dataloader::IDataLoader
{
public:
	MOCK_METHOD0(getData, dataloader::TestToTimesMap());
};
