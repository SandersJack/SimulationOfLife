#include "GUI.hh"
#include "SimManager.hh"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <ctime>
#include <thread>
#include <algorithm>

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

void GUI::Init(const uint SCR_WIDTH, const uint SCR_HEIGHT) {
    // Set GLFW error callback
    glfwSetErrorCallback(errorCallback);

    fGRID_SIZE = SimManager::GetInstance()->GetGridSize();

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
    glClear(GL_COLOR_BUFFER_BIT);
    DrawGrid();

    fResourceManager = ResourceManager::GetInstance();
    fSpriteRenderer = SpriteRenderer::GetInstance();

    fResourceManager->LoadShader("shaders/sprite.vs", "shaders/sprite.fs", "sprite");

    Matrix4 modelMatrix1 = Matrix4(1.0f);
    fResourceManager->GetShader("sprite").Use().SetInteger("image", 0);
    fResourceManager->GetShader("sprite").SetMatrix4("model", modelMatrix1);

    fSpriteRenderer->SetShader(fResourceManager->GetShader("sprite"));
    fSpriteRenderer->initRenderData();
    // load textures
    fResourceManager->LoadTexture("textures/org.png", true, "face");

    modelLocation = glGetUniformLocation(fResourceManager->GetShader("sprite").GetID(), "model");
    colorLocation = glGetUniformLocation(fResourceManager->GetShader("sprite").GetID(), "color");

    // Set the viewport and projection matrix
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    
    // Set line width
    glLineWidth(1.0);

}

void GUI::DrawGrid() {

    // Draw horizontal lines
    glColor3f(1.0, 1.0, 1.0); // Set color to black
    glBegin(GL_LINES);
    for (int i = -fGRID_SIZE / 2; i <= fGRID_SIZE / 2; ++i) {
        glVertex2f(-1.0, 2.0 * i / fGRID_SIZE);
        glVertex2f(1.0, 2.0 * i / fGRID_SIZE);
    }
    glEnd();

    // Draw vertical lines
    glBegin(GL_LINES);
    for (int i = -fGRID_SIZE / 2; i <= fGRID_SIZE / 2; ++i) {
        glVertex2f(2.0 * i / fGRID_SIZE, -1.0);
        glVertex2f(2.0 * i / fGRID_SIZE, 1.0);
    }
    glEnd();
}

void GUI::Draw() {
    glfwMakeContextCurrent(fWindow); // Make the OpenGL context current
    glClear(GL_COLOR_BUFFER_BIT);
    DrawGrid();

    const Texture2D &textureRef = fResourceManager->GetTexture("face");
    Vector3 Color = Vector3(1.f, 1.f, 1.f);

    double width = (static_cast<float>(fGRID_SIZE) - 1.) / 2;

    std::vector<Organism*> orgs = SimManager::GetInstance()->GetOrganisms();
    for(auto o: orgs){
        int y = o->GetX();
        int x = o->GetY();

        double gui_x = -width + x;
        double gui_y = width - y;

        fSpriteRenderer->DrawSprite(textureRef, Vector2(gui_x, gui_y), Vector2(.25 / 4,.25 / 4), 0.0, Color);
    }
    glfwSwapBuffers(fWindow);
    glfwPollEvents();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

}