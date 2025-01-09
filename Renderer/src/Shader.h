#pragma once
#include "string"
#include <unordered_map>
class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();


	std::pair<std::string, std::string> ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	void Bind() const;
	void UnBind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1i(const std::string& name, int v0);
	int GetUniformLocation(const std::string& name);


private:
	std::unordered_map<std::string, int> m_UniformCache;
	unsigned int m_RendererId;
	std::string m_Filepath;
};

