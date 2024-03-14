#ifndef GUI_H
#define GUI_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

class GUI {

    public:
        GUI();
        ~GUI();

        void Init();
        void Draw();

        static GUI *GetInstance();
    private:
        static GUI *fInstance;

        GLFWwindow *fWindow;
};

#endif