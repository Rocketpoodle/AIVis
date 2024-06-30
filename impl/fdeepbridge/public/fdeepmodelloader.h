#ifndef FDEEPMODELLOADER_H
#define FDEEPMODELLOADER_H

#include <ModelLoaderInterface.h>

class FdeepModelLoader : public ModelBridge::ModelLoaderInterface
{
public:
    FdeepModelLoader();

    virtual ModelBridge::ModelPtr loadModelFromFile(const std::string& filePath) const override;

    virtual std::list<std::string> getModelFileFilters() const override;
};

#endif // FDEEPMODELLOADER_H
