//#include <iostream>
//#include <glad/gl.h>

//int main(int argc, char **argv) {
//    std::cout << "Hello, world!" << std::endl;
//    return 0;
//}
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int g_windowsize_x = 640;
int g_windowsize_y = 480;

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

int main(void)
{
    GLFWwindow* pWwindow;

    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout<<"glfwInid failed"<<std::endl;
        return -1;
        
    }
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
//glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    pWwindow = glfwCreateWindow(g_windowsize_x, g_windowsize_x, "Hello World", nullptr, nullptr);
    if (!pWwindow)
    {
         std::cout<<"Can't create window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwSetWindowSizeCallback(pWwindow,glfwWindowSizeCallBack);
    glfwSetKeyCallback(pWwindow,glfwKeyCallBack);
    
    /* Make the window's context current */
    glfwMakeContextCurrent(pWwindow);
    glfwSwapInterval(3);    
if(!gladLoadGL()){
    std::cout<<"Cant Load GLAD"<<std::endl;
    glfwTerminate();
    return -1;
}
std::cout<<"Renderer: "<<glGetString(GL_RENDERER)<<std::endl;
std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;
glClearColor(0,1,0,1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWwindow))
    {
        /* Render here */
       glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWwindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
    std::cout<<"OpenGL "<<GLVersion.major<<"."<<GLVersion.minor<<"\t"<<glGetString(GL_VENDOR)<<std::endl;

    glfwTerminate();
    return 0;
}
