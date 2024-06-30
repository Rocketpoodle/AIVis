#include "public/fdeepdataloader.h"
#include "fdeepdata.h"

FdeepDataLoader::FdeepDataLoader() {}

ModelBridge::DataPtr FdeepDataLoader::createBlankData() const
{
    return std::make_shared<FdeepBridge::Data>();
}
