#include "GUI.hh"
#include "SimManager.hh"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

static const uint SCR_WIDTH = 1000;
static const uint SCR_HEIGHT = 1000;

static const int GRID_SIZE = 32;

GUI::GUI() : fWindow(nullptr) {}

GUI::~GUI() {
    if (fWindow) {
        glfwDestroyWindow(fWindow);
        glfwTerminate();
    }
}

GUI* GUI::fInstance = nullptr;

GUI* GUI::GetInstance() {
    if (!fInstance) {
        fInstance = new GUI();
    }
    return fInstance;
}

static void errorCallback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void GUI::Init() {
    // Set GLFW error callback
    glfwSetErrorCallback(errorCallback);

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Create a windowed mode window and its OpenGL context
    fWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Grid Example", NULL, NULL);
    if (!fWindow) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    // Make the window's context current
    glfwMakeContextCurrent(fWindow);

    // Set framebuffer size callback
    glfwSetFramebufferSizeCallback(fWindow, framebuffer_size_callback);

    // Set the viewport and projection matrix
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.1, 1.1, -1.1, 1.1, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    // Set line width
    glLineWidth(1.0);

    
}

void GUI::DrawGrid() {
    std::cout << "Drawing Grid" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw horizontal lines
    glColor3f(1.0, 1.0, 1.0); // Set color to black
    glBegin(GL_LINES);
    for (int i = -GRID_SIZE / 2; i <= GRID_SIZE / 2; ++i) {
        glVertex2f(-1.0, 2.0 * i / GRID_SIZE);
        glVertex2f(1.0, 2.0 * i / GRID_SIZE);
    }
    glEnd();

    // Draw vertical lines
    glBegin(GL_LINES);
    for (int i = -GRID_SIZE / 2; i <= GRID_SIZE / 2; ++i) {
        glVertex2f(2.0 * i / GRID_SIZE, -1.0);
        glVertex2f(2.0 * i / GRID_SIZE, 1.0);
    }
    glEnd();

    glfwSwapBuffers(fWindow);
    glfwPollEvents();
}

void GUI::Draw() {
    glfwMakeContextCurrent(fWindow); // Make the OpenGL context current
    DrawGrid();
}