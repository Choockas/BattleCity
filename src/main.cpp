//#include <iostream>
//#include <glad/gl.h>

//int main(int argc, char **argv) {
//    std::cout << "Hello, world!" << std::endl;
//    return 0;
//}
#include <main.h>
#include <shadeprogramm.h>

GLfloat point[] ={
    0.0,0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    -0.5f,-0.5f,0.0f};
    
GLfloat colors[]={
    1.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,0.0f,1.0f
    
};

const char* vertex_shader=
"#version 330\n"
"#extension GL_ARB_explicit_uniform_location : require\n"
"layout(location=0) in vec3 vertex_position;\n"
"layout(location=1) in vec3 vertex_color;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"  color= vertex_color;\n"
"  gl_Position= vec4(vertex_position,1.0);\n"
"}\0";

const char* fragment_shader=
"#version 330\n"
"in vec3 color;\n"
"out vec4 frag_color;\n"
"void main()\n"
"{\n "
"  frag_color= vec4(color,1.0);\n"
"}\n\0";



int main(void)
{
    
    /* Initialize the library */
    g_windowsize_x = 640;
    g_windowsize_y = 480;
    if (!glfwInit())
    {
        std::cout<<"glfwInid failed"<<std::endl;
        return -1;
        
    }
    
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    
/* Create a windowed mode window and its OpenGL context */
    pWwindow = glfwCreateWindow(g_windowsize_x, g_windowsize_x, "Hello World", nullptr, nullptr);
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

std::cout<<"Renderer: "<<glGetString(GL_RENDERER)<<std::endl;
std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;
std::cout<< "Shader version:"<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;


glClearColor(0.2f,0.3f,0.3f,1.0f);


std::string vertexShader(vertex_shader);
std::string fragmentShader(fragment_shader);
Renderer::ShaderProgramm shaderProgram(vertexShader,fragmentShader);

GLuint points_vbo = 0;
glGenBuffers(1,&points_vbo);
glBindBuffer(GL_ARRAY_BUFFER,points_vbo);
glBufferData(GL_ARRAY_BUFFER,sizeof(point),point,GL_STATIC_DRAW);

GLuint colors_vbo = 0;
glGenBuffers(1,&colors_vbo);
glBindBuffer(GL_ARRAY_BUFFER,colors_vbo);
glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);

GLuint vao = 0;
glGenVertexArrays(1, &vao);
glBindVertexArray(vao);

glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER,points_vbo);
glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);

glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER,colors_vbo);
glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,nullptr);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWwindow))
    {
        /* Render here */
       glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,3);
        /* Swap front and back buffers */
        glfwSwapBuffers(pWwindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
    std::cout<<"OpenGL "<<GLVersion.major<<"."<<GLVersion.minor<<"\t"<<glGetString(GL_VENDOR)<<std::endl;
    shaderProgram.clearSH();
    glfwTerminate();
    return 0;
}
