#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include "../../headers/ogl/ogl.h"

Engine::_ogl_Shader::_ogl_Shader(){

}
Engine::_ogl_Shader::~_ogl_Shader(){

}

void Engine::_ogl_Shader::GLcheckCompileErrors(unsigned int shader, const char* type, const char* filepath){
    GLint success;
    GLchar infoLog[1024];
    if (strcmp(type, "PROGRAM"))
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);

            if (filepath != nullptr)
                printf("%s :\n", filepath);

            std::cout << type << " Shader compilation error! " << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);

            std::cout << "Shader program compilation error! " << infoLog << std::endl;
        }
    }
}

bool Engine::_ogl_Shader::readShaderFile(const char* path, char* result){
    std::string res_data;
    std::ifstream stream;

    stream.exceptions(std::ifstream::badbit);

    try
    {
        stream.open(path);// Open file
        std::stringstream css;
        css << stream.rdbuf();

        stream.close();//close file stream
        res_data = css.str();
        strcpy(result, res_data.c_str());
    }
    catch (std::ifstream::failure e)
    {
        return false;
    }
    return true;
}

bool Engine::_ogl_Shader::compileFromFile(std::string VSpath, std::string FSpath){
    std::cout << "OGL: Compiling shader " << VSpath << " " << FSpath << std::endl;

    GLchar vs_data[SHADER_STR_LEN];
    GLchar fs_data[SHADER_STR_LEN];

    const GLchar* vs = &vs_data[0];
    const GLchar* fs = &fs_data[0];
    //read shader files
    readShaderFile(VSpath.c_str(), &vs_data[0]);
    readShaderFile(FSpath.c_str(), &fs_data[0]);
    //init opengl shaders
    this->shader_id = glCreateProgram();

    unsigned int VS = glCreateShader(GL_VERTEX_SHADER);
    unsigned int FS = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(VS, 1, &vs, nullptr); //Setting shader code text on vs
    glShaderSource(FS, 1, &fs, nullptr); //Setting shader code text on fs

    glCompileShader(VS); //Compile VS shader code
    GLcheckCompileErrors(VS, "VERTEX", VSpath.c_str()); //Check vertex errors
    glCompileShader(FS); //Compile FS shader code
    GLcheckCompileErrors(FS, "FRAGMENT", FSpath.c_str()); //Check fragment compile errors

    glAttachShader(this->shader_id, VS);
    glAttachShader(this->shader_id, FS);

    glLinkProgram(this->shader_id);
    GLcheckCompileErrors(shader_id, "PROGRAM");
    //Clear shaders, we don't need them anymore
    glDeleteShader(VS);
    glDeleteShader(FS);

}
void Engine::_ogl_Shader::Destroy(){
    glDeleteProgram(this->shader_id);
}
void Engine::_ogl_Shader::Use(){
    glUseProgram(this->shader_id);
}
