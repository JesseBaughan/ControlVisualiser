#include <algorithm>

#include "LayerStack.h"

namespace Engine
{

LayerStack::LayerStack()
{
    _layerInsert = _layers.begin();
}

LayerStack::~LayerStack()
{
    for(Layer* layer : _layers)
    {
        delete layer;
    }
}

// Layers are pushed to front half of the layer stack
void LayerStack::PushLayer(Layer* layer)
{
    _layerInsert = _layers.emplace(_layerInsert, layer);
}

// Overlays are pushed to back half of layer stack
void LayerStack::PushOverlay(Layer* overlay)
{
    _layers.emplace_back(overlay);
}

void LayerStack::PopLayer(Layer* layer)
{
    auto it = std::find(_layers.begin(), _layers.end(), layer);
    if(it != _layers.end())
    {
        _layers.erase(it);
        _layerInsert--;
    }
}

void LayerStack::PopOverlay(Layer* overlay)
{
    auto it = std::find(_layers.begin(), _layers.end(), overlay);
    if(it != _layers.end())
    {
        _layers.erase(it);
    }
}

}