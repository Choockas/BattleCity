#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/vec2.hpp>
#include <iostream>




glm::ivec2 g_windowsize;

GLFWwindow* pWwindow;

void glfwWindowSizeCallBack(GLFWwindow *pWindow, int width, int hight)
{
    g_windowsize.x = width;
    g_windowsize.y = hight;

    glViewport(0,0, g_windowsize.x,g_windowsize.y); 
    std::cout<<"x"<<g_windowsize.x<<" y"<<g_windowsize.y<<std::endl;
}

void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode)
{
    if (key== GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow,GL_TRUE);
    }
}
