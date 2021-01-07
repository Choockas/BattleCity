#pragma once
#include <string>
#include <memory>
#include <map>
#include <shadeprogramm.h>
#include <sstream>
#include <fstream>


//using namespace Renderer;

class ResourceManager{
    public:
        ResourceManager(const std::string& executablePath);
        ~ResourceManager() = default;
        ResourceManager(const ResourceManager& ) = delete;
        ResourceManager& operator = (const ResourceManager&) = delete;
        ResourceManager& operator = (ResourceManager&&) = delete;
        ResourceManager(ResourceManager&&) = delete;
        std::shared_ptr<Renderer::ShaderProgramm> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath );
       std::shared_ptr<Renderer::ShaderProgramm> getShaderProgram(const std::string& shaderName);
        
private:
    std::string getFileString(const std::string& relativePath);
    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgramm>> ShaderProgramsMap;
    ShaderProgramsMap m_shaderPrograms;
    std::string m_path;
};


ResourceManager::ResourceManager(const std::string& executablePath)
{
    size_t found = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0,found); 
    std::cout<< "resurse manager is created, "<<"looked for"<<m_path<<std::endl;
}

std::string ResourceManager::getFileString(const std::string& relativePath)
{
    std::ifstream f;
    f.open(m_path+"/"+relativePath,std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        std::cerr<<"Failed to open "<< relativePath<<std::endl;
        return std::string();
    }
    std::stringstream buffer;
    buffer<<f.rdbuf();
    std::cout<< "getting string from "<< relativePath<<std::endl;
    return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgramm> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexString = getFileString(vertexPath);
    if (vertexString.empty()){
        std::cerr<<"No vertex shader!"<< std::endl;
    }
    std::string fragmentString = getFileString(fragmentPath);
    if (fragmentString.empty()){
        std::cerr<<"No fragment shader!"<< std::endl;
    }
    
    std::shared_ptr<Renderer::ShaderProgramm>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgramm>(vertexString,fragmentString)).first->second;
    if (!newShader->isCompiled()){
        std::cerr<< "Can't load shader program:"<<"\n"
        <<"Vertex: " << vertexPath<< "\n" 
        <<"Fragment: " <<fragmentPath
        <<std::endl;
        return nullptr;
    }
    std::cout<<"shader programm loaded right"<<std::endl;
     return newShader;
    
}
std::shared_ptr<Renderer::ShaderProgramm> ResourceManager::getShaderProgram(const std::string& shaderName)
{
    ShaderProgramsMap::const_iterator it=m_shaderPrograms.find(shaderName);
    if(it!=m_shaderPrograms.end()){
        return it->second;
    }
    std::cerr<<"Can't find the shader program"
    <<shaderName
    <<std::endl;
    return nullptr;
}
