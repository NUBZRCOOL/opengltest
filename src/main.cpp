#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


const int WIDTH = 1920;
const int HEIGHT = 1080;

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

    double rIncrement = 0.01f;
    double gIncrement = 0.01f;
    double bIncrement = 0.01f;

    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    while (!glfwWindowShouldClose(window)) {

        process_input(window);

        if (r >= 1.0f || r <= 0.0f) rIncrement = -rIncrement; 
        if (g >= 1.0f || g <= 0.0f) gIncrement = -gIncrement; 
        if (b >= 1.0f || b <= 0.0f) bIncrement = - bIncrement;

        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        r += rIncrement;
        g += gIncrement;
        b += bIncrement;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}