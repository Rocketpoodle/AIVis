#ifndef DATALOADERINTERFACE_H
#define DATALOADERINTERFACE_H

#include "DataInterface.h"
// #include <list>

namespace ModelBridge {

using DataPtr = std::shared_ptr<DataInterface>;

class DataLoaderInterface
{
public:

    /*! \note eventually we may want to load data from file */
    // virtual DataPtr loadDataFromFile(const std::string& filePath) const = 0;

    // virtual std::list<std::string> getModelFileFilters() const = 0;

    virtual DataPtr createBlankData() const = 0;
};

}
#endif // DATALOADERINTERFACE_H
