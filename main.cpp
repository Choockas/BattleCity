//#include <iostream>
//#include <glad/gl.h>

//int main(int argc, char **argv) {
//    std::cout << "Hello, world!" << std::endl;
//    return 0;
//}
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
//"#extension GL_ARB_explicit_attribute_location : require\n"
"#extension GL_ARB_explicit_uniform_location : require\n"
"layout(location=0) in vec3 vertex_position;\n"
"layout(location = 0) uniform vec2 offset;\n"
"layout(location=1) in vec3 vertex_color;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"  color= vertex_color;\n"
"  gl_Position= vec4(vertex_position,1.0);\n"
"}\0";

const char* fragment_shader=
"#version 330\n"
// "#extension GL_ARB_explicit_attribute_location : require\n"
// "#extension GL_ARB_explicit_uniform_location : require\n"
"in vec3 color;\n"
"out vec4 frag_color;\n"
"void main()\n"
"{\n "
"  frag_color= vec4(color,1.0);\n"
"}\n\0";


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

int success;
char infoLog[512];

GLuint vs = glCreateShader(GL_VERTEX_SHADER) ;
glShaderSource(vs,1,&vertex_shader,nullptr);  
glCompileShader(vs);
glGetShaderiv(vs,GL_COMPILE_STATUS,&success);
if(!success){
    glGetShaderInfoLog(vs,512,NULL,infoLog);
    std::cout<<"ERRROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog<< std::endl;
}

GLuint fs = glCreateShader(GL_FRAGMENT_SHADER) ;
glShaderSource(fs,1,&fragment_shader,nullptr);  
glCompileShader(fs);
glGetShaderiv(fs,GL_COMPILE_STATUS,&success);
if(!success){
    glGetShaderInfoLog(fs,512,NULL,infoLog);
    std::cout<<"ERRROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog<< std::endl;
}

GLuint shader_program = glCreateProgram();
glAttachShader(shader_program,vs);
glAttachShader(shader_program,fs);
//glLineWidth(shader_program);
glLinkProgram(shader_program);
glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

glDeleteShader(vs);
glDeleteShader(fs);

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
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,3);
        /* Swap front and back buffers */
        glfwSwapBuffers(pWwindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
    std::cout<<"OpenGL "<<GLVersion.major<<"."<<GLVersion.minor<<"\t"<<glGetString(GL_VENDOR)<<std::endl;

    glfwTerminate();
    return 0;
}
