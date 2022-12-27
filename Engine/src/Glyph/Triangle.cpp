#include "Triangle.h"
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

namespace Engine
{
    TriangleGlyph::TriangleGlyph()
    {
        /*
        float vehicle_vertices[] = {
            -0.1f, -0.3f, 0.0f, //0
            0.1f, -0.3f, 0.0f,  //1
            0.0f,  0.3f, 0.0f   //2
        };

        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
        };  

        _va = new VertexArray();
        _vb = new VertexBuffer(vehicle_vertices, 9 * sizeof(float));

        _layout = new VertexBufferLayout();
        _layout->Push<float>(3);
        _va->AddBuffer(*_vb, *_layout);

        _ib = new IndexBuffer(indices, 3);
        _shader = new Shader("../res/shaders/Basic.shader");
        _shader->Bind();

        _renderer = new Renderer();
        */
    }

    TriangleGlyph::~TriangleGlyph()
    {
    }

    void TriangleGlyph::Draw(Window* window) 
    {
        // Rendering of ImGui
        int display_w = 0;
        int display_h = 0;
        glClearColor(0.45f,  0.55f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        GLFWwindow* _window = static_cast<GLFWwindow*>(window->GetNativeWindow());
        glfwGetFramebufferSize(_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        //*********OPENGL DRAWING***********
        // Rendering of ImGui
        /*
        //Rendering of test triangle
        _shader->Bind();
        //Rotate 90degrees about z-axis
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); 
        //Translate by some X/Y amount
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 
        glm::mat4 transformation = translation * rotate;
        float aspect = (float)display_w/display_h;
        //Ensure our shape is being kept at the right scaling even with window size changing
        glm::mat4 proj = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
        //Re-scale for window size change to keep proper shape proportions
        transformation = proj * transformation; 
        _shader->SetUniformMat4f("u_MVP", transformation);
        _renderer->Draw(*_va, *_ib, *_shader);
        _shader->Unbind();
        */
    }

    void TriangleGlyph::Insert(Glyph* glyph, int id)
    {

    }

    void TriangleGlyph::Remove(Glyph* glyph)
    {

    }
}