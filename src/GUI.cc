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
    int SCR_WIDTH = 1024;
    int SCR_HEIGHT = 768;

	OGLManager *oglM = OGLManager::GetInstance();
	oglM->Init(SCR_WIDTH, SCR_HEIGHT);

    fWindow = oglM->GetWindow();
}

void GUI::Draw(){
    glfwPollEvents();
    
}