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

    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    while (!glfwWindowShouldClose(window)) {

        process_input(window);

        glClearColor(.529f, .808f, .922f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}