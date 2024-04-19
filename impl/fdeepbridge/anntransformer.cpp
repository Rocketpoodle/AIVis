#include "anntransformer.h"

ANNTransformer::ANNTransformer() {}

void ANNTransformer::transform(std::shared_ptr<AbstractRepSourceConfig> inputconfig)
{
    m_error = TransformError();



    m_representation.reset();
}
