#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


const int WIDTH = 800;
const int HEIGHT = 600;

const char *vShaderSrc = "#version 330 core\n"
                         "layout (location = 0) in vec3 vPos;\n"
                         "void main() {\n"
                            "gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0);\n"
                         "}\0\n"
;
const char *fShaderSrc = "#version 330 core\n"
                         "out vec4 FragColor;\n"
                         "void main() {\n"
                            "FragColor = vec4(0.67f, 0.1f, 0.1f, 1.0f);\n"
                         "}\0\n"
;

void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, char **argv) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "yo", NULL, NULL);
    if (window == NULL) {
        std::cout << "Couldn't create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Couldn't initialize GLAD" << std::endl;
        return -1;
    }
    
    glViewport(0, 0, 800, 600);

    double r = .53f;
    double g = .92f;
    double b = 1.0f;

    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    float vertices[] = {
        -.5f, -.5f, .0f,
        .5f, -.5f, .0f,
        .0f, .5f, .0f
    };

    // vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    // vertex shader
    unsigned int vShader;
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderSrc, NULL);
    glCompileShader(vShader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cout << "ERROR WHEN COMPILING VSHADER\n" << infoLog << std::endl;
    }
    
    // fragment shader
    unsigned int fShader;
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderSrc, NULL);
    glCompileShader(fShader);
    
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShader, 512, NULL, infoLog);
        std::cout << "ERROR WHEN COMPILING FSHADER\n" << infoLog << std::endl;
    }
    
    unsigned int shaderProg;
    shaderProg = glCreateProgram();
    glAttachShader(shaderProg, vShader);
    glAttachShader(shaderProg, fShader);
    glLinkProgram(shaderProg);
    
    glGetShaderiv(shaderProg, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShader, 512, NULL, infoLog);
        std::cout << "ERROR WHEN LINKING SHADER PROGRAM\n" << infoLog << std::endl;
    }
    
    
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    
    ////////////////////////////
    
    
    
    // vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    
    // 1
    glBindVertexArray(VAO);
    // 2
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    


    while (!glfwWindowShouldClose(window)) {

        process_input(window);

        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //finally draw the damn triangle
        glUseProgram(shaderProg);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}