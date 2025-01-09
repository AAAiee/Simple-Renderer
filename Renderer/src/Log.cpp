#include<Log.h>
#include<iostream>

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
