#include<iostream>
#include "Log.h"
#include "Renderer.h"


void ClearError()
{
    while (glGetError());
}

bool PullError(const char* func_name, const int& line_number, const char* file)
{
    if (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ")" << " from: " << file << " " << line_number << " " << func_name << std::endl;
        return false;
    }
    return true;
} 

void Renderer::Clear() const
{
    GLLOGCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();
    GLLOGCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
