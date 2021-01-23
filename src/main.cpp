#include <iostream>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include "glm/gtc/matrix_transform.hpp"


#include "resourcesmanager.h"
#include "game/game.h"
#include "renderer.h"

// GLfloat point[] ={
//     0.0,50.0f,0.0f,
//     50.0f,-50.0f,0.0f,
//     -50.0f,-50.0f,0.0f
//  };
//     
// GLfloat textCord[]={
//     0.5f,1.0f,
//     1.0f,0.0f,
//     0.0f,0.0f,
// };
// 
// GLfloat colors[]={
//     1.0f,0.0f,0.0f,
//     0.0f,1.0f,0.0f,
//     0.0f,0.0f,1.0f
// };
glm::ivec2 g_windowsize(640,480);
Game g_game(g_windowsize);


void glfwWindowSizeCallBack(GLFWwindow *pWindow, int width, int hight);
void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode);



int main(int argc, char** argv )
{    
    GLFWwindow* pWwindow;
//     GLint nrAttributes;
//     GLint64 nrAttribs64;    
    g_windowsize = {640,480};
    
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout<<"glfwInid failed"<<std::endl;
        return -1;
    }
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    
/* Create a windowed mode window and its OpenGL context */
    pWwindow = glfwCreateWindow(g_windowsize.x, g_windowsize.x, "Hello World", nullptr, nullptr);
    if (!pWwindow)
    {
         std::cout<<"Can't create GLFW window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(pWwindow,glfwKeyCallBack);
    /* Make the window's context current */
    glfwMakeContextCurrent(pWwindow);
    glfwSetWindowSizeCallback(pWwindow,glfwWindowSizeCallBack);
    glfwSwapInterval(3); 
        
if(!gladLoadGL()){
    std::cout<<"Cant Load GLAD"<<std::endl;
    glfwTerminate();
    return -1;
}

// glGetInteger64v(GL_MAX_VERTEX_ATTRIBS, &nrAttribs64);
// std::cout<<"Renderer: "<<glGetString(GL_RENDERER)<<std::endl;
// std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;
// std::cout<< "Shader version:"<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
// std::cout<< "Max nr64 supported: "<<nrAttribs64<<std::endl;

std::cout << "Renderer:"<<RenderEngine::Renderer::getRendererStr()<<std::endl;
std::cout << "Version:"<<RenderEngine::Renderer::getVersionString()<<std::endl;


{
//ResourceManager resourcesManager(argv[0]);
ResourceManager::setExecutablePath(argv[0]);
RenderEngine::Renderer ::setClearColor(0.2f,0.3f,0.3f,1.f);     
g_game.init();

auto lastTime = std::chrono::high_resolution_clock::now();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWwindow))
    {
        /* Render here */
       
       auto currentTime = std::chrono::high_resolution_clock::now();        
       uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime-lastTime).count();
       lastTime=currentTime;
       g_game.update(duration);   
       RenderEngine::Renderer::clear();
       g_game.render();
        /* Swap front and back buffers */
        glfwSwapBuffers(pWwindow);
        /* Poll for and process events */
        glfwPollEvents();
    }
    ResourceManager::unloadAllResources();
}
    
    glfwTerminate();
    return 0;
}



void glfwWindowSizeCallBack(GLFWwindow *pWindow, int width, int hight)
{
    g_windowsize.x = width;
    g_windowsize.y = hight;
    RenderEngine::Renderer::setViewPort(width,hight);
    std::cout<<"x"<<g_windowsize.x<<" y"<<g_windowsize.y<<std::endl;
}

void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode)
{
    if (key== GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow,GL_TRUE);
    }
  g_game.setkey(key,action);
}
