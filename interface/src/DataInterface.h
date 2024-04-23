#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H

#include <memory>
#include <vector>
#include <string>

namespace ModelBridge {

class LayerInterface;
using LayerPtr = std::shared_ptr<LayerInterface>;

class DataInterface
{
public:

    inline bool hasValidOutput() const {
        return !m_has_error && hasValidOutput_impl();
    }

    inline void setInputs(const std::vector<double>& inputs)
    {
        m_inputs = inputs;
    }

    inline std::vector<double> getLayerOutput(const LayerPtr& layer)
    {
        if(!hasValidOutput()) {
            return m_inputs;
        }

        return getLayerOutput_impl(layer);
    }

    inline const std::vector<double>& getInputs() const
    {
        return m_inputs;
    }

    inline bool hasError() const
    {
        return m_has_error;
    };
    inline std::string getErrorString() const
    {
        return m_error_string;
    }

    inline void setError(const std::string& errorString)
    {
        m_error_string = errorString;
        m_has_error = true;
    }

    inline void resetError()
    {
        m_error_string = "";
        m_has_error = false;
    }

protected:
    virtual bool hasValidOutput_impl() const = 0;
    virtual void clearValidOutput_impl() = 0;
    virtual std::vector<double> getLayerOutput_impl(const LayerPtr& layer) const = 0;

    std::vector<double> m_inputs;

    std::string m_error_string;
    bool m_has_error;
};
}
#endif // DATAINTERFACE_H
