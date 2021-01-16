
#include <main.h>
#include "texture2D.h"
#include "shadeprogramm.h"
#include "sprite.h"

#include "resourcesmanager.h"




GLfloat point[] ={
    0.0,50.0f,0.0f,
    50.0f,-50.0f,0.0f,
    -50.0f,-50.0f,0.0f
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

auto pSpriteShaderProgram = resourcesManager.loadShaders("Sprite Shader","res/shaders/vsprite.txt","res/shaders/fsprite.txt");
if(!pSpriteShaderProgram){
    std::cerr<< "Can't get managed resource"<<std::endl;
    glfwTerminate();
    return -1;
}


auto pTexture  = resourcesManager.loadTextures("DefaultTexture","res/textures/map_16x16.png");
if(!pTexture){
    std::cerr<< "Can't get managed textures"<<std::endl;
    glfwTerminate();
    return -1;
}

std::vector<std::string> subTexturesNames ={"block","topBlock","bootomBlock","leftBlock","rightBlock","topLeftBlock", "topRightBlock","bottomLeftBlock","bottomRightBlock","beton"};
auto pTextureAtlas = resourcesManager.loadTextureAtlas ( "DefaultTextureAtlas","res/textures/map_16x16.png",std::move(subTexturesNames),16,16);     

auto pSprite = resourcesManager.loadSprites("NewSprite", "DefaultTextureAtlas", "Sprite Shader",100,100,"beton");

pSprite->setPosition(glm::vec2(300,100));     


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
 
 glm::mat4 modeMatrix_1 = glm::mat4(1.0f);
 modeMatrix_1 = glm::translate(modeMatrix_1,glm::vec3(200.0f,50.0f,0.0f));
 
 glm::mat4 modeMatrix_2 = glm::mat4(1.0f);
 modeMatrix_2 = glm::translate(modeMatrix_2,glm::vec3(440.0f,50.0f,0.0f));
 
glm::mat4 projectionMatrix = glm::ortho (0.0f, static_cast<float>(g_windowsize.x),0.0f,static_cast<float>( g_windowsize.y),-100.0f,100.0f);
pDefaulShaderProgram->setMatrix4("projectionMat", projectionMatrix);

pSpriteShaderProgram->use(); 
pSpriteShaderProgram->setInt("tex",0);
pSpriteShaderProgram -> setMatrix4("projectionMat", projectionMatrix);;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWwindow))
    {
        /* Render here */
        
       glClear(GL_COLOR_BUFFER_BIT);
        pDefaulShaderProgram->use();
        glBindVertexArray(vao);
        pTexture->bind();
        
        pDefaulShaderProgram->setMatrix4("modelMat", modeMatrix_1);
        glDrawArrays(GL_TRIANGLES,0,3);
        pDefaulShaderProgram->setMatrix4("modelMat", modeMatrix_2);
        glDrawArrays(GL_TRIANGLES,0,3);
        pSprite->render();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(pWwindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
    
    glfwTerminate();
    return 0;
}
