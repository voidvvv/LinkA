#include "Shader.h"

ShaderProgram::ShaderProgram(const char *vertPath, const char *fragpath)
{
    std::string vertexSourceCoded;
    std::string fragmentSourceCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertPath);
        fShaderFile.open(fragpath);
        std::stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();

        vertexSourceCoded = vShaderStream.str();
        fragmentSourceCode = fShaderStream.str();

        const char *vShaderCode = vertexSourceCoded.c_str();
        const char *fShaderCode = fragmentSourceCode.c_str();
        
        this->parseToProgram(vShaderCode, fShaderCode);
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "error" << std::endl;
    }
}

ShaderProgram::ShaderProgram(const char *vertSource, const char *fragSource, int)
{
    this->parseToProgram(vertSource, fragSource);
}

void ShaderProgram::use()
{
    glUseProgram(ID);
}

void ShaderProgram::setUniformMat4(const char *name, glm::mat4 m4)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(m4)); // 注意，这里应该用 glm::value_ptr(mat4)
}

void ShaderProgram::setUniformMat3(const char *name, glm::mat3 m3)
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(m3)); // 注意，这里应该用 glm::value_ptr(mat4)
}

void ShaderProgram::setUniformInt(const char *name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void ShaderProgram::setUniformFloat(const char *name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name), value);
}

void ShaderProgram::setUniformFloat3(const char *name, float * value)
{
    glUniform3fv(glGetUniformLocation(ID, name), 1,value);
}

void ShaderProgram::setUniformFloat3(const char *name, float a, float b, float c)
{
    glUniform3f(glGetUniformLocation(ID, name), a,b,c);
}

void ShaderProgram::parseToProgram(const char *vertSource, const char *fragSource)
{
    if (ID != 0)
    {
        return;
    }
    std::cout<< "vertSource: " << vertSource<< std::endl;
        std::cout<< "fragSource: " << fragSource<< std::endl;

    int success;
    char infoLog[512];
    ID = glCreateProgram();
    GLuint vertextShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertextShader, 1, &vertSource, NULL);
    glCompileShader(vertextShader);
    glGetShaderiv(vertextShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertextShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::fragShader::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    glAttachShader(ID, vertextShader);
    glAttachShader(ID, fragShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::program::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertextShader);
    glDeleteShader(fragShader);
}
