#pragma once
#include "Core.h"
#include "Layer.h"
#include <vector>

// A layerstack will manage a vector of layers. Insertion happens in the center to allow for overlays
// Overlays will always render ontop of every layer
class LayerStack
{
public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *overlay);
    void PopLayer(Layer *layer);
    void PopOverlay(Layer *overlay);

    std::vector<Layer *>::iterator begin() { return m_Layers.begin(); }
    std::vector<Layer *>::iterator end() { return m_Layers.end(); }

private:
    std::vector<Layer *> m_Layers;
    // Stores index to the top of the layer portion of th layerStack
    unsigned int m_LayerInsertIndex = 0;
};
