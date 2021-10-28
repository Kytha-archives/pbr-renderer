#pragma once

#include "core.h"
#include "Event.h"
#include "Timestep.h"


class Layer
{
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    // To do when pushed/popped from layer stack
    virtual void OnAttach() {}
    virtual void OnDetach() {}

    virtual void OnUpdate(Timestep ts) {}
    // Entry point for layer-level event handling
    virtual void OnEvent(Event& e) {}
    virtual void OnImGuiRender() {}
    
    // DEBUG ONLY
    inline const std::string& GetName() const { return m_debugName; }
protected:
    std::string m_debugName;
};