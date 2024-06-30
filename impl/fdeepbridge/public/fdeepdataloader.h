#ifndef FDEEPDATALOADER_H
#define FDEEPDATALOADER_H

#include <DataLoaderInterface.h>

class FdeepDataLoader : public ModelBridge::DataLoaderInterface
{
public:
    FdeepDataLoader();

    virtual ModelBridge::DataPtr createBlankData() const override;
};

#endif // FDEEPDATALOADER_H
