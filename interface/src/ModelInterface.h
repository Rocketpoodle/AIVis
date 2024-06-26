#ifndef MODELINTERFACE_H
#define MODELINTERFACE_H

#include "LayerInterface.h"
#include "DataInterface.h"

#include <algorithm>
#include <map>
#include <memory>
#include <numeric>
#include <vector>
#include <string>

namespace ModelBridge
{

using LayerPtr = std::shared_ptr<LayerInterface>;
using DataPtr = std::shared_ptr<DataInterface>;

// Layer graph
struct LayerGraphNode;

/*!
 * \brief The LayerGraphNode class
 */
struct LayerGraphNode
{
    LayerGraphNode(const LayerPtr& layer) : layer(layer) {}
    LayerPtr layer;
    std::vector<LayerGraphNode*> inputs;
    std::vector<LayerGraphNode*> outputs;
};

using LayerGraphNodePtr = std::shared_ptr<LayerGraphNode>;

class ModelInterface
{
public:
    /*!
     * \brief initialize
     * \details initializes the model interface, building the layer graph
     */
    void initialize()
    {
        m_layer_graph.clear();
        m_id_to_index_map.clear();

        // get list of layers from the model
        auto layers = getLayers();
        // transform the list into graph nodes
        std::for_each(layers.cbegin(), layers.cend(), [this](const LayerPtr& a){
            m_layer_graph.emplace_back(std::make_shared<LayerGraphNode>(a));
        });
        // build the graph nodes based upon connections
        std::for_each(m_layer_graph.begin(), m_layer_graph.end(), [this](LayerGraphNodePtr& a){
            // build input graph connections
            for (const auto& input : getIncomingLayers(a->layer)) {
                auto inputToLayer = std::find_if(m_layer_graph.cbegin(), m_layer_graph.cend(), [&input](const LayerGraphNodePtr& b){
                    return b->layer == input;
                });
                // if input was found, assing input for current layer and output for the found input
                if (inputToLayer != m_layer_graph.cend()) {
                    a->inputs.push_back(inputToLayer->get());
                    inputToLayer->get()->outputs.push_back(a.get());
                }
            }
        });
        // sort layers so they are in order from input to output
        // this assumes all layers returned are connected (no floating layers)
        std::function<int(const LayerGraphNode*, int)> getDistanceToInput = [&getDistanceToInput](const LayerGraphNode* node, int distance) -> int {
            int maxDistanceToInput = distance + 1;
            for (const auto& input : node->inputs){
                maxDistanceToInput = std::max(maxDistanceToInput, getDistanceToInput(input, distance));
            }
            return maxDistanceToInput;
        };
        std::sort(m_layer_graph.begin(), m_layer_graph.end(), [&getDistanceToInput](const LayerGraphNodePtr& a, const LayerGraphNodePtr& b){
            return getDistanceToInput(a.get(), 0) < getDistanceToInput(b.get(), 0);
        });
        // build id to index map
        for(int i = 0; i < m_layer_graph.size(); i++) {
            m_id_to_index_map.insert({m_layer_graph.at(i)->layer->getId(), i});
        }
    }

    /*!
     * \brief apply
     * \details runs model on given data
     * \param data object to apply model to and store results in
     */
    void apply(DataPtr& data) const
    {
        auto inputShapes = getInputShape();
        int expectedInputSize = std::accumulate(inputShapes.begin(),
                                                inputShapes.end(),
                                                1,
                                                [](const int&a, const int&b){
                                                    return a * b;
                                                });

        if (expectedInputSize != data->getInputs().size()) {
            data->setError("Input size given doesn't match input layer size");
            return;
        }

        apply_impl(data);
    }

    /*!
     * \brief getLayer
     * \param layerId string id for the layer to retrieve
     * \return layer pointer for the given layerId, nullptr if not found
     */
    inline LayerPtr getLayer(const std::string& layerId) const
    {
        if (m_id_to_index_map.count(layerId) < 1) {
            return nullptr;
        }
        return m_layer_graph.at(m_id_to_index_map.at(layerId))->layer;
    }

    /*!
     * \brief getLayerCount
     * \return number of layers in model
     */
    inline int getLayerCount() const
    {
        return m_layer_graph.size();
    }

    /*!
     * \brief getLayerGraph
     * \return vector of layer graph nodes
     */
    inline const std::vector<LayerGraphNodePtr>& getLayerGraph() const
    {
        return m_layer_graph;
    }

    /*!
     * \brief hasLayer
     * \param layer to check for
     * \return true if model contains the given layer
     */
    inline bool hasLayer(const LayerPtr& layer)
    {
        return layer && (getLayer(layer->getId()) == layer);
    }

    /*!
     * \brief getInputShape
     * \return dimensions of input vector
     */
    virtual std::vector<int> getInputShape() const = 0;

    /*!
     * \brief getOutputShape
     * \return dimensions of output vector
     */
    virtual std::vector<int> getOutputShape() const = 0;

protected:
    // model representation specific implementation to apply to given data
    virtual void apply_impl(DataPtr& data) const = 0;

    // gets list of layers from the underlying model representation
    virtual const std::vector<LayerPtr>& getLayers() const = 0;

    // gets the inputs for the given layer
    virtual std::vector<LayerPtr> getIncomingLayers(const LayerPtr& layer) const = 0;

    std::vector<LayerGraphNodePtr> m_layer_graph;
    std::unordered_map<std::string, int> m_id_to_index_map;
};
}

#endif // MODELINTERFACE_H
