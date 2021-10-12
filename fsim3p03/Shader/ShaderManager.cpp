#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::initialize()
{
    vertex_code_path = std::string(PATH_INPUT) + std::string(PATH_SHADERS) + std::string("shader.vert");
    fragment_code_path =  std::string(PATH_INPUT) + std::string(PATH_SHADERS) + std::string("shader.frag");

    shaderList.push_back(std::make_shared<Shader>());
    shaderList[0]->CreateFromFile(vertex_code_path.c_str() , fragment_code_path.c_str());
}

void ShaderManager::useShader(size_t index)
{
    if (index < shaderList.size())
    {
        shaderList[index]->UseShader();
    }
}

std::shared_ptr<Shader> ShaderManager::getShader(size_t index)
{
    std::shared_ptr<Shader> shader = nullptr;
    if (index < shaderList.size())
    {
        shader = shaderList[index];
    }
    return shader;
}
