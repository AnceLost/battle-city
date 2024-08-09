#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const std::string& execubalePath) {
	size_t found = execubalePath.find_last_of("/\\");
	m_path = execubalePath.substr(0, found);
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath) const{
	std::ifstream f;
	f.open(m_path + "/" + relativeFilePath.c_str(), std::ios::binary);
	if (!f.is_open()) {
		std::cerr << "Failed to open file" << relativeFilePath << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaderProgram(
	const std::string& shaderName,
	const std::string& vertexPath,
	const std::string& fragmentPath
) {
	std::string vertexString = getFileString(vertexPath);
	
	if (vertexString.empty()) {
		std::cerr << "No vertex shader!" << std::endl;
		return nullptr;
	}

	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty()) {
		std::cerr << "No fragment shader!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>& newShader = m_shader_programs.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString,fragmentString)).first -> second;
	if (newShader->isCompiled()) {
		return newShader;
	}
	std::cerr << "Can't load shader program:\n"
		<< "Vertex: " << vertexPath << "\n"
		<< "Fragment: " << fragmentPath << std::endl;

	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName) {
	ShaderProgramsMap::const_iterator it = m_shader_programs.find(shaderName);
	if (it != m_shader_programs.end()) {
		return it->second;
	}
	std::cerr << "Can't find the shader: " << shaderName << std::endl;
	return nullptr;
}