#include "SpotLight.h"

SpotLight::SpotLight() :
    direction(0.0f, -1.0f, 0.0f), direction_start(direction), edge(0.0f), processedEdge(cosf(glm::radians(0.0f)))
{
}

SpotLight::~SpotLight()
{
}

void SpotLight::initialize(
    std::shared_ptr<Motion> _motion,
    GLfloat red, GLfloat green, GLfloat blue,
    GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
    GLfloat x, GLfloat y, GLfloat z,
    GLfloat _constant, GLfloat _linear, GLfloat _exponent,
    GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat _edge)
{
    PointLight::initialize(
        _motion,
        red, green, blue,
        _ambientIntensity, _diffuseIntensity,
        x, y, z,
        _constant, _linear, _exponent
    );

    direction = glm::vec3(xDir, yDir, zDir);
    direction_start = direction;
    edge = _edge;
    processedEdge = cosf(glm::radians(edge));
}

void SpotLight::UseLight(
    GLuint colourLocation, GLuint ambientIntensityLocation, GLuint diffuseIntensityLocation,
    GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
    GLuint directionLocation, GLuint edgeLocation)
{
    PointLight::UseLight(
        colourLocation, ambientIntensityLocation, diffuseIntensityLocation,
        positionLocation, constantLocation, linearLocation, exponentLocation
    );
    //printf("SpotLight::UseLight() direction.x = %2.4f, direction.y = %2.4f, direction.z = %2.4f\n", direction.x, direction.y, direction.z);
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(edgeLocation, edge);
}

void SpotLight::setDirection(glm::vec3 _direction)
{
    direction = _direction;
}

glm::vec3 SpotLight::getDirection()
{
    return direction;
}

glm::vec3 SpotLight::getDirectionStart()
{
    return direction_start;
}
