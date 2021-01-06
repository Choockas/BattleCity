#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>



int g_windowsize_x ;
int g_windowsize_y ;
GLFWwindow* pWwindow;

void glfwWindowSizeCallBack(GLFWwindow *pWindow, int width, int hight)
{
    g_windowsize_x = width;
    g_windowsize_y = hight;

    glViewport(0,0, g_windowsize_x,g_windowsize_y); 
    std::cout<<"x"<<g_windowsize_x<<" y"<<g_windowsize_y<<std::endl;
}

void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode)
{
    if (key== GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow,GL_TRUE);
    }
}
