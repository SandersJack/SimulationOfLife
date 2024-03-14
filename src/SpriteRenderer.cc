#include "SpriteRenderer.hh"

#include "MathGL.hh"
#include "MatrixTransform.hh"

#include "Shape2D.hh"


SpriteRenderer *SpriteRenderer::fInstance = nullptr;

SpriteRenderer *SpriteRenderer::GetInstance() {
    if(!fInstance)
        fInstance = new SpriteRenderer();
    return fInstance;
}

SpriteRenderer::SpriteRenderer() {

}

void SpriteRenderer::DrawSprite(const Texture2D& texture, Vector2 position, Vector2 size, float rotate, Vector3 color){
    Shape2D *shape = Shape2D::GetInstance();
    Matrix4 projection = Matrix4(1.0);

    projection = projection.scale(Vector3(size, 1));

    projection = Rotate(projection, ToRadians(rotate), Vector3(0.0f, 0.0f, 1.0f));
    shape->render2DShape(fShader, texture, fQuadVAO, projection, position, 4*4, color);

}

void SpriteRenderer::initRenderData(){
    // configure VAO/VBO

    GLfloat vertices[] = {
        /// Vertex ////   Tex ///
        -0.5f, -0.5f, 0.0f, 0.0f,   // Bottom-left
        0.5f, -0.5f, 1.0f, 0.0f,    // Bottom-right
        0.5f, 0.5f, 1.0f, 1.0f,     // Top-right
        -0.5f, 0.5f, 0.0f, 1.0f
    };

    glGenVertexArrays(1, &fQuadVAO);
    glBindVertexArray(fQuadVAO);
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}