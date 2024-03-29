#include "Triangle.h"
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{

TriangleGlyph::TriangleGlyph()
{
    _vb.reset(VertexBuffer::Create(vehicle_vertices, 9 * sizeof(float)));

    BufferLayout layout = { ShaderDataType::Float3, "a_Position" };
    //_va.AddBuffer(_vb.get(), _layout);

    _ib.reset(IndexBuffer::Create(indices, 3));
    _shader.reset(new Shader("../res/shaders/Basic.shader"));
}

void TriangleGlyph::Draw(Window* window) 
{
    //Rendering of test triangle
    _shader->Bind();
    //Rotate 90degrees about z-axis
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); 
    //Translate by some X/Y amount
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 
    glm::mat4 transformation = translation * rotate;
    float aspect = window->GetWidth()/window->GetHeight();
    //Ensure our shape is being kept at the right scaling even with window size changing
    glm::mat4 proj = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    //Re-scale for window size change to keep proper shape proportions
    transformation = proj * transformation; 
    _shader->SetUniformMat4f("u_MVP", transformation);
    _renderer.Draw(_va, _ib.get(), _shader.get());
    _shader->Unbind();
}

void TriangleGlyph::Insert(Glyph* glyph, int id)
{
}

void TriangleGlyph::Remove(Glyph* glyph)
{
}

}