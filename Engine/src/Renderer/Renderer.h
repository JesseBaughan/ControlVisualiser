#pragma once

#include "RenderCommand.h"
#include "Core/OrthographicCamera.h"
#include "Shader.h"
#include <glm/glm.hpp>

namespace Engine 
{

class Renderer
{
public:
    static void BeginScene(OrthographicCamera& camera);
    static void EndScene();

    static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

    inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
private:
    struct SceneData
    {
        glm::mat4 _vpMatrix;
    };

    static SceneData* _sceneData;
};

}