#include "PointLight.h"


PointLight::PointLight() :
    position(0.0f, 0.0f, 0.0f), position_start(position), constant(1.0f), linear(0.0f), exponent(0.0f)
{
}

PointLight::~PointLight()
{
}

void PointLight::initialize(
    std::shared_ptr<Motion> _motion,
    GLfloat red, GLfloat green, GLfloat blue,
    GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
    GLfloat x, GLfloat y, GLfloat z,
    GLfloat _constant,  GLfloat _linear, GLfloat _exponent)
{
    Light::initialize(_motion, red, green, blue, _ambientIntensity, _diffuseIntensity);
    position = glm::vec3(x, y, z);
    position_start = position;
    constant = _constant;
    linear = _linear;
    exponent = _exponent;
}

void PointLight::UseLight(
    GLuint colourLocation, GLuint ambientIntensityLocation, GLuint diffuseIntensityLocation,
    GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation)
{
    Light::UseLight(colourLocation, ambientIntensityLocation, diffuseIntensityLocation);
    glUniform3f(positionLocation, position.x, position.y, position.z);
    glUniform1f(constantLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(exponentLocation, exponent);
}

void PointLight::setPosition(glm::vec3 _position)
{
    position = _position;
}

glm::vec3 PointLight::getPosition()
{
    return position;
}

glm::vec3 PointLight::getPositionStart()
{
    return position_start;
}