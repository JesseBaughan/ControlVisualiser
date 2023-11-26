#include "Renderer.h"
#include "Shader.h"

namespace Engine
{
Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData();

void Renderer::BeginScene(OrthographicCamera& camera)
{
    Renderer::_sceneData->_vpMatrix = camera.getViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
{
    shader->Bind();
    shader->SetUniformMat4f("u_ViewProjection", _sceneData->_vpMatrix);
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

}
