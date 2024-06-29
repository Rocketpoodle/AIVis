#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H

#include <memory>
#include <vector>
#include <string>

namespace ModelBridge {

class LayerInterface;
using LayerPtr = std::shared_ptr<LayerInterface>;

/*!
 * \brief The DataInterface class
 * \details Interface between ViewModel and underlying representation of run data.
 *          It gives access to all of the layer outputs for a given input
 * \note This interface returns vectors of data, not by reference. This is not ideal
 *       from a performance aspect, but is done to remove coupling between the
 *       underlying model representation and the ViewModels.
 */
class DataInterface
{
public:

    DataInterface()
        : m_has_error(false)
    {

    }

    /*!
     * \brief hasValidOutput
     * \return true if run produced valid output
     */
    inline bool hasValidOutput() const
    {
        return !m_has_error && hasValidOutput_impl();
    }

    /*!
     * \brief setInputs
     * \details sets the input data for the given run
     * \param inputs array of input data to model
     */
    inline void setInputs(const std::vector<double>& inputs)
    {
        m_inputs = inputs;
    }

    /*!
     * \brief getLayerOutput
     * \param layer gets the output data vector for the output of the given layer
     * \return vector of output data
     */
    inline std::vector<double> getLayerOutput(const LayerPtr& layer)
    {
        if(!hasValidOutput()) {
            return m_inputs;
        }

        return getLayerOutput_impl(layer);
    }

    /*!
     * \brief getInputs
     * \return vector of input data
     */
    inline const std::vector<double>& getInputs() const
    {
        return m_inputs;
    }

    /*!
     * \brief hasError
     * \return true if there was an error processing the data
     */
    inline bool hasError() const
    {
        return m_has_error;
    };

    /*!
     * \brief getErrorString
     * \return description of the error that occured
     */
    inline std::string getErrorString() const
    {
        return m_error_string;
    }

    /*!
     * \brief setError
     * \details sets the error string for the data
     * \param errorString description of error that occured
     */
    inline void setError(const std::string& errorString)
    {
        m_error_string = errorString;
        m_has_error = true;
    }

    /*!
     * \brief resetError
     * \details resets any error that is currently set
     */
    inline void resetError()
    {
        m_error_string = "";
        m_has_error = false;
    }

protected:
    // model representation specific check for valid output data
    virtual bool hasValidOutput_impl() const = 0;
    // model representation specific clearing of valid output
    virtual void clearValidOutput_impl() = 0;
    // model representation specific implementation for getting the output data from the given layer
    virtual std::vector<double> getLayerOutput_impl(const LayerPtr& layer) const = 0;

    std::vector<double> m_inputs;

    std::string m_error_string;
    bool m_has_error;
};
}
#endif // DATAINTERFACE_H
