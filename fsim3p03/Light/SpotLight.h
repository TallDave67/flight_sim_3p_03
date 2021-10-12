#pragma once

#include "PointLight.h"

class SpotLight : public PointLight
{
public:
    SpotLight();
    ~SpotLight();

    void initialize(
        std::shared_ptr<Motion> _motion,
        GLfloat red, GLfloat green, GLfloat blue,
        GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
        GLfloat x, GLfloat y, GLfloat z,
        GLfloat _constant,  GLfloat _linear, GLfloat _exponent,
        GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat _edge);

    void UseLight(
        GLuint colourLocation, GLuint ambientIntensityLocation, GLuint diffuseIntensityLocation,
        GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
        GLuint directionLocation, GLuint edgeLocation);

    void setDirection(glm::vec3 _direction);
    glm::vec3 getDirection();
    glm::vec3 getDirectionStart();

private:
    glm::vec3 direction;
    glm::vec3 direction_start;
    GLfloat edge;
    GLfloat processedEdge;
};

