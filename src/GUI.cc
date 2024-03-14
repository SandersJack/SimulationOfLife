#include "GUI.hh"
#include "SimManager.hh"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

static const uint SCR_WIDTH = 1000;
static const uint SCR_HEIGHT = 1000;

static const int GRID_SIZE = 32;

static GLuint VAO, modelLocation, colorLocation;

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

    glfwMakeContextCurrent(fWindow);
    glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		exit(3);
	}

    // Make the window's context current
    glfwMakeContextCurrent(fWindow);

    glfwMakeContextCurrent(fWindow);
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
    
    std::cout << "Res Start" << std::endl;
    fResourceManager = ResourceManager::GetInstance();
    std::cout << "Res Start0" << std::endl;
    fSpriteRenderer = SpriteRenderer::GetInstance();
    std::cout << "Res Start10" << std::endl;

    fResourceManager->LoadShader("shaders/sprite.vs", "shaders/sprite.fs", "sprite");
    std::cout << "Res Start11" << std::endl;

    std::cout << "Res Start1" << std::endl;
    Matrix4 modelMatrix1 = Matrix4(1.0f);
    fResourceManager->GetShader("sprite").Use().SetInteger("image", 0);
    fResourceManager->GetShader("sprite").SetMatrix4("model", modelMatrix1);

    fSpriteRenderer->SetShader(fResourceManager->GetShader("sprite"));
    fSpriteRenderer->initRenderData();
    // load textures
    fResourceManager->LoadTexture("textures/org.png", true, "face");

    std::cout << "Res Start2" << std::endl;
    modelLocation = glGetUniformLocation(fResourceManager->GetShader("sprite").GetID(), "model");
    colorLocation = glGetUniformLocation(fResourceManager->GetShader("sprite").GetID(), "color");

    // Set initial model matrix and color uniforms
    Matrix4 modelMatrix = Matrix4(1.0f);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelMatrix[0][0]);

    Vector3 sliderColor = Vector3(0.2f, 0.2f, 0.8f);
    glUniform3fv(colorLocation, 1, &sliderColor[0]);

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

    
    
    std::cout << "INIT DONE" << std::endl;
}

void GUI::DrawGrid() {

}

void GUI::Draw() {
    glfwMakeContextCurrent(fWindow); // Make the OpenGL context current
    DrawGrid();

    const Texture2D &textureRef = fResourceManager->GetTexture("face");
    Vector3 Color = Vector3(1.f, 1.f, 1.f);
    fSpriteRenderer->DrawSprite(textureRef, Vector2(0.5,0.5), Vector2(.25 / 4,.25 / 4), 0.0, Color);

    glfwSwapBuffers(fWindow);
    glfwPollEvents();
}