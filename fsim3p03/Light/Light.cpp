#include "Light.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

Light::Light() :
    motion(nullptr), colour(1.0f, 1.0f, 1.0f), ambientIntensity(1.0),  diffuseIntensity(0.0f)
{
}

Light::~Light()
{
}

void Light::initialize(
    std::shared_ptr<Motion> _motion,
    GLfloat red, GLfloat green, GLfloat blue,
    GLfloat _ambientIntensity, GLfloat _diffuseIntensity)
{
    motion = _motion;
    colour = glm::vec3(red, green, blue);
    ambientIntensity = _ambientIntensity;
    diffuseIntensity = _diffuseIntensity;
}

bool Light::getNewPosition(glm::vec3 old_position, glm::vec3& new_position)
{
    bool got = false;
    if (motion)
    {
        // get position from the motion and add it to
        // the old_position (the relative position_start)
        new_position = old_position + motion->get_position();
        got = true;
    }
    return got;
}

bool Light::getNewDirection(glm::vec3 old_direction, glm::vec3 & new_direction)
{
    bool got = false;
    if (motion)
    {
        // get quaternion from the motion's rotation matrix and use it to rotate 
        // the old_direction vector (the absolute direction_start)
        glm::quat quaternion = glm::quat_cast(motion->get_rotation_matrix());
        new_direction = quaternion * old_direction;
        got = true;
    }
    return got;
}

void Light::UseLight(GLuint colourLocation, GLuint ambientIntensityLocation, GLuint diffuseIntensityLocation)
{
    glUniform3f(colourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}
