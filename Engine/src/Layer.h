#pragma once

#include <string>

namespace Engine
{

class Layer
{
public: 
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach() {}    
    virtual void OnDetach() {}    
    virtual void OnUpdate() {}    

    inline const std::string& GetName() const { return _debugName; }

protected:
    std::string _debugName;
};

}