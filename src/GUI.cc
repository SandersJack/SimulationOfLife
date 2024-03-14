#include "GUI.hh"
#include "SimManager.hh"

GUI::GUI(){
}

GUI::~GUI(){
}

GUI *GUI::fInstance = nullptr;

GUI *GUI::GetInstance(){
    if(!fInstance){
        fInstance = new GUI();
    }   
    return fInstance;
}

void GUI::Init(){
    glfwInit();
    fWindow = glfwCreateWindow(800, 600, "World Visualization", nullptr, nullptr);
    glfwMakeContextCurrent(fWindow);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(fWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void GUI::Draw(){
    glfwPollEvents();

    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Create ImGui window
    ImGui::Begin("Grid Visualization");

    // Draw grid
    const int gridSize = SimManager::GetInstance()->GetGridSize();
    const float cellSize = 30.0f;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            ImGui::GetWindowDrawList()->AddRect(ImGui::GetCursorScreenPos(),
                                                    ImVec2(ImGui::GetCursorScreenPos().x + cellSize,
                                                        ImGui::GetCursorScreenPos().y + cellSize),
                                                    IM_COL32(255, 255, 255, 255));
            ImGui::Dummy(ImVec2(cellSize, cellSize));
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }

    // End ImGui window
    ImGui::End();

    // Rendering
    int display_w, display_h;
    glfwGetFramebufferSize(fWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(fWindow);
}