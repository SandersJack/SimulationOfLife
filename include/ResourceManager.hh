#ifndef ResourceManager_HPP
#define ResourceManager_HPP

#include <map>
#include <string>

#include "Texture2D.hh"
#include "Shader.hh"

class ResourceManager {

    public:
        ResourceManager();
        ~ResourceManager();

        static ResourceManager *GetInstance();

        Shader LoadShader(const char * vertex_file_path,const char * fragment_file_path, std::string name);
        Texture2D LoadTexture(const char *file, bool alpha, std::string name);
        Texture2D LoadTextureFromFile(const char *file, bool alpha);

        Shader GetShader(std::string name){ return fShaders[name];}
        Texture2D GetTexture(std::string name){ return fTextures[name];}
        void Clear();

    private:

        static ResourceManager *fInstance;

        std::map<std::string, Texture2D> fTextures;
        std::map<std::string, Shader> fShaders;
};

#endif