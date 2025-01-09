#include "Log.h"
#include "Shader.h"
#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader(const std::string&  filepath)
    :m_Filepath(filepath)
{
    auto [vertex_source, fragment_source] = ParseShader(filepath);
    m_RendererId = CreateShader(vertex_source, fragment_source);

}

Shader::~Shader()
{
    GLLOGCALL(glDeleteProgram(m_RendererId));
}

std::pair<std::string, std::string> Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[static_cast<int>(type)] << line << "\n";
        }
    }

    return std::make_pair(ss[0].str(), ss[1].str());
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    // initialize a shader of given type, return a unique idetifier to it for future reference.
    unsigned int id = glCreateShader(type);
    // create a pointer to point to the first position of our source code.
    const char* src = source.c_str();
    // attach the source code to our newly created shader.
    GLLOGCALL(glShaderSource(id, 1, &src, nullptr));
    // compile the source code for that shader.
    GLLOGCALL(glCompileShader(id));
    // declare an int type variable to store the compile status
    int result;
    // query the compile status of shader "id", and store that info at &result
    GLLOGCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    // check if compiled succesfully
    if (result == GL_FALSE)
        // if result == gl_false, compiled unsucessfuly, get error message.
    {
        // length variable where mark the length of the log info
        int length;
        // query the length of log info of the shader "id", and store it at &length
        GLLOGCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        // manually allocate memory on stack to create a char array of length (buffer)
        char* message = static_cast<char*>(alloca(length * sizeof(char)));
        // store log info in the buffer
        GLLOGCALL(glGetShaderInfoLog(id, length, &length, message));
        // print out error message
        std::cout << "Fail to Compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment")
            << std::endl;
        std::cout << message << std::endl;
        // delete the shader because it is not compiled sucessfully.
        GLLOGCALL(glDeleteShader(id));
        // return 0 as a failure flag;
        return 0;
    }
    // return the unique identifier for the shader created.
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // create a program, a container where we compile and link the two shaders given.
    GLLOGCALL(unsigned int program = glCreateProgram());
    // compile the vertex shader using the helper function: CompileShader.
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    // compile the fragment shader using the helper function: CompileShader.
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    // attach the vertex shader to the program.
    GLLOGCALL(glAttachShader(program, vs));
    // attach the fragment shader to the program.
    GLLOGCALL(glAttachShader(program, fs));
    // generate the executables that will run on corresponding processors.
    GLLOGCALL(glLinkProgram(program));
    // checks to see whether the executables contained in program can execute given the current OpenGL state
    GLLOGCALL(glValidateProgram(program));

    // flag the two shaders as ready to be deleted once after it is not attached to any program
    GLLOGCALL(glDeleteShader(vs));
    // flag the two shaders as ready to be deleted once after it is not attached to any program
    GLLOGCALL(glDeleteShader(fs));
    return program;
}

void Shader::Bind() const
{
    GLLOGCALL(glUseProgram(m_RendererId));
}

void Shader::UnBind() const
{
    GLLOGCALL(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLLOGCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1i(const std::string& name, int v0)
{
    GLLOGCALL(glUniform1i(GetUniformLocation(name), v0));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformCache.find(name) != m_UniformCache.end())
    {
        return m_UniformCache[name];
    }

    GLLOGCALL(int location = glGetUniformLocation(m_RendererId, name.c_str()));
    if (location == -1)
    {
        std::cout << "Warning: uniform " << name << " does not exist! " << std::endl;
    }
    m_UniformCache[name] = location;
    
    return location;
}
