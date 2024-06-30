#ifndef MODELLOADERINTERFACE_H
#define MODELLOADERINTERFACE_H

#include "ModelInterface.h"
#include <list>

namespace ModelBridge {

using ModelPtr = std::shared_ptr<ModelInterface>;

class ModelLoaderInterface
{
public:
    virtual ModelPtr loadModelFromFile(const std::string& filePath) const = 0;

    virtual std::list<std::string> getModelFileFilters() const = 0;
};

}

#endif // MODELLOADERINTERFACE_H
