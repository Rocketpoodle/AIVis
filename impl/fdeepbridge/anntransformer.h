#ifndef ANNTRANSFORMER_H
#define ANNTRANSFORMER_H

#include "abstractaitransformer.h"

class ANNTransformer : public AbstractAiTransformer
{
public:
    ANNTransformer();

    virtual void transform(std::shared_ptr<AbstractRepSourceConfig> inputConfig);
};

#endif // ANNTRANSFORMER_H
