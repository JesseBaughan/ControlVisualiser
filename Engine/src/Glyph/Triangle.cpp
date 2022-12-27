#include "Triangle.h"

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
    TriangleGlyph::TriangleGlyph()
    {
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
    }

    void TriangleGlyph::Insert(Glyph* glyph, int id)
    {

    }

    void TriangleGlyph::Remove(Glyph* glyph)
    {

    }
}