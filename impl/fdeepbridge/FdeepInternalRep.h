#ifndef FDEEPINTERNALREP_H
#define FDEEPINTERNALREP_H

#include <LayerInterface.h>
#include <fdeep/node.hpp>

class FdeepInternalRep : public ModelBridge::InternalLayerRep
{
public:
    FdeepInternalRep(const fdeep::internal::layer_ptr& layer)
        : m_ptr(layer)
    {

    }

    fdeep::internal::layer_ptr getLayerPtr() const
    {
        return m_ptr;
    }

private:
    fdeep::internal::layer_ptr m_ptr;
};

#endif // FDEEPINTERNALREP_H
