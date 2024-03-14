#include "ResourceManager.hh"
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ResourceManager *ResourceManager::fInstance = nullptr;

ResourceManager *ResourceManager::GetInstance() {
    if(!fInstance)
        fInstance = new ResourceManager();
    return fInstance;
}


ResourceManager::ResourceManager(){
}

Shader ResourceManager::LoadShader(const char * vertex_file_path,const char * fragment_file_path, std::string name){
    Shader nShader = Shader();
    std::cout << "1" << std::endl;
    nShader.Compile(vertex_file_path, fragment_file_path);
    std::cout << "2" << std::endl;
    fShaders[name] = nShader;
    std::cout << "3" << std::endl;
    return fShaders[name];
}

Texture2D ResourceManager::LoadTexture(const char *file, bool alpha, std::string name){
    fTextures[name] = LoadTextureFromFile(file, alpha);

    return fTextures[name];
}


Texture2D ResourceManager::LoadTextureFromFile(const char *file, bool alpha) {
    // create texture object
    Texture2D texture;
    if (alpha)
    {
        texture.SetInternal_Format(GL_RGBA);
        texture.SetImage_Format(GL_RGBA);
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    texture.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
}



void ResourceManager::Clear()
{
    // (properly) delete all shaders	
    for (auto iter : fShaders)
        glDeleteProgram(iter.second.GetID());
    // (properly) delete all textures
    for (auto iter : fTextures)
        glDeleteTextures(1, iter.second.value_ptr());
}