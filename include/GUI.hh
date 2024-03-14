#ifndef GUI_H
#define GUI_H

#include "GLTools.hh"
#include "ResourceManager.hh"
#include "SpriteRenderer.hh"

class GUI {

    public:
        GUI();
        ~GUI();

        void Init();
        void Draw();
        void DrawGrid();

        static GUI *GetInstance();
    private:
        static GUI *fInstance;

        GLFWwindow *fWindow;

        int fGridSize;

        ResourceManager *fResourceManager;
        SpriteRenderer *fSpriteRenderer;
};

#endif