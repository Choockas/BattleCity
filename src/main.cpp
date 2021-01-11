//#include <iostream>
//#include <glad/gl.h>

//int main(int argc, char **argv) {
//    std::cout << "Hello, world!" << std::endl;
//    return 0;
//}
#include <main.h>
#include <resourcesmanager.h>



GLfloat point[] ={
    0.0,0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    -0.5f,-0.5f,0.0f
 };
    
GLfloat textCord[]={
    0.5f,1.0f,
    1.0f,0.0f,
    0.0f,0.0f,
};

GLfloat colors[]={
    1.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,0.0f,1.0f
};

int main(int argc, char** argv )
{
    GLint nrAttributes;
    GLint64 nrAttribs64;
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

std::cout<<"Renderer: "<<glGetString(GL_RENDERER)<<std::endl;
std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;
std::cout<< "Shader version:"<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
glGetInteger64v(GL_MAX_VERTEX_ATTRIBS, &nrAttribs64);
std::cout<< "Max nr supported: "<<nrAttributes<<std::endl;
std::cout<< "Max nr64 supported: "<<nrAttribs64<<std::endl;
glClearColor(0.2f,0.3f,0.3f,1.0f);

{
ResourceManager resourcesManager(argv[0]);

auto pDefaulShaderProgram = resourcesManager.loadShaders("Default Shader","res/shaders/vertex.txt","res/shaders/fragment.txt");
if(!pDefaulShaderProgram){
    std::cerr<< "Can't get managed resource"<<std::endl;
    glfwTerminate();
    return -1;
}
//resourcesManager.loadTexture("DefaultTexture","res/textures/map_16x16.png");
auto pTexture  = resourcesManager.loadTextures("DefaultTexture","res/textures/map_16x16.png");
if(!pTexture){
    std::cerr<< "Can't get managed textures"<<std::endl;
    glfwTerminate();
    return -1;
}



GLuint points_vbo = 0;
glGenBuffers(1,&points_vbo);
glBindBuffer(GL_ARRAY_BUFFER,points_vbo);
glBufferData(GL_ARRAY_BUFFER,sizeof(point),point,GL_STATIC_DRAW);

GLuint colors_vbo = 0;
glGenBuffers(1,&colors_vbo);
glBindBuffer(GL_ARRAY_BUFFER,colors_vbo);
glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);

GLuint textcord_vbo = 0;
glGenBuffers(1,&textcord_vbo);
glBindBuffer(GL_ARRAY_BUFFER,textcord_vbo);
glBufferData(GL_ARRAY_BUFFER,sizeof(textCord),textCord,GL_STATIC_DRAW);

GLuint vao = 0;
glGenVertexArrays(1, &vao);
glBindVertexArray(vao);

glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER,points_vbo);
glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);

glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER,colors_vbo);
glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,nullptr);


glEnableVertexAttribArray(2);
glBindBuffer(GL_ARRAY_BUFFER,textcord_vbo);
glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,nullptr);

//*********requaired to be active**************
 pDefaulShaderProgram->use(); 
 pDefaulShaderProgram->setInt("tex",0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWwindow))
    {
        /* Render here */
        
       glClear(GL_COLOR_BUFFER_BIT);
        pDefaulShaderProgram->use();
        glBindVertexArray(vao);
        pTexture->bind();
        glDrawArrays(GL_TRIANGLES,0,3);
        /* Swap front and back buffers */
        glfwSwapBuffers(pWwindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
    
    glfwTerminate();
    return 0;
}
