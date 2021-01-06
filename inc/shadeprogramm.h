#pragma once
#include <string>


namespace Renderer {
    const char* vertex_shader;
    class ShaderProgramm{
        
    public:
        ShaderProgramm(const std::string &vertexShader, const std::string &fragmentShader);
        ~ShaderProgramm();
        ShaderProgramm() = delete;
        
        
        ShaderProgramm& operator = (const ShaderProgramm&)=delete;
        
        ShaderProgramm& operator = (ShaderProgramm&& shaderProgramm) noexcept;
        ShaderProgramm(ShaderProgramm&& shaderProgramm) noexcept;
        ShaderProgramm(ShaderProgramm&)= delete;
        bool isCompiled() const {return m_isCompiled;}
        void use() const;
        void clearSH();
    private:
       bool CreateShader(const std::string& source,const GLenum shaderType, GLuint& shaderID);
        GLint m_isCompiled=false;
        GLuint m_ID;
        
    };
    
    
    ShaderProgramm::ShaderProgramm(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLuint vertexShaderID, fragmentShaderID;
    if(!CreateShader(vertexShader,GL_VERTEX_SHADER, vertexShaderID)){
        std::cerr<<"VERTEX SHADER compile time error"<<std::endl;
        return;  
    }

    if(!CreateShader(fragmentShader,GL_FRAGMENT_SHADER, fragmentShaderID)){
        std::cerr<<"FRAGMENT SHADER compile time error"<<std::endl;
        glDeleteShader(vertexShaderID);
        return;  
    } 
   m_ID = glCreateProgram();
    glAttachShader(m_ID,vertexShaderID);
    glAttachShader(m_ID,fragmentShaderID);
    glLinkProgram(m_ID);
    glGetProgramiv(m_ID, GL_LINK_STATUS, &m_isCompiled);
    if (!m_isCompiled) {
        GLchar infolog[1024];
        glGetProgramInfoLog(m_ID, 512, NULL, infolog);
        std::cout << "ERROR::SHADER: Link time error\n" << infolog << std::endl;
    }
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    
}

bool ShaderProgramm::CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
{
    GLint success=0;
    shaderID= glCreateShader(shaderType);
    const char*  code = source.c_str();
     glShaderSource(shaderID,1, &code, nullptr);
     glCompileShader(shaderID);
     glGetShaderiv(shaderID,GL_COMPILE_STATUS,&success);
     if (!success){
         GLchar infolog[1024];
         glGetShaderInfoLog(shaderID,1024,nullptr,infolog);
         std::cerr<<"ERROR::SHADER:Compile time error:\n"<<infolog<<std::endl;
         return false;
    }
         
    return true;
}
    
  ShaderProgramm::~ShaderProgramm()
{
    //glDeleteProgram(m_ID);
    
}

void ShaderProgramm::clearSH()
{
     glDeleteProgram(m_ID);
}

    
void ShaderProgramm::use() const {
        glUseProgram(m_ID);
        
    }    
    
ShaderProgramm::ShaderProgramm(ShaderProgramm && shaderProgramm) noexcept
{
    m_ID=shaderProgramm.m_ID;
    m_isCompiled = shaderProgramm.m_isCompiled;
    shaderProgramm.m_ID = 0;
    shaderProgramm.m_isCompiled = false;
}
 
ShaderProgramm & ShaderProgramm::operator=(ShaderProgramm && shaderProgramm) noexcept
{
    glDeleteProgram(m_ID);
    m_ID=shaderProgramm.m_ID;
    m_isCompiled = shaderProgramm.m_isCompiled;
    shaderProgramm.m_ID = 0;
    shaderProgramm.m_isCompiled = false;
    return *this;
}
 
    
}
