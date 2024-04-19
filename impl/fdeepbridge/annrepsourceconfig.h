#ifndef ANNREPSOURCECONFIG_H
#define ANNREPSOURCECONFIG_H

#include "abstractrepsourceconfig.h"

#include <string>

class ANNRepSourceConfig : public AbstractRepSourceConfig
{
public:
    std::string hd5_path;
};

#endif // ANNREPSOURCECONFIG_H
