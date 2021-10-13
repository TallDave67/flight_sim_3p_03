#include "Motion.h"

#include <glm/gtc/matrix_transform.hpp>

Motion::Motion() :
    starting_orientation(0.0f, 0.0f, 0.0f)
{
    reset_motion();
}

Motion::~Motion()
{
}

void Motion::initialize()
{
}

// Translation
glm::vec3 Motion::get_position()
{
    return position;
}

glm::vec3 Motion::get_last_position()
{
    return last_position;
}

void Motion::set_position(glm::vec3 _position)
{
    last_position = position;
    position = _position;
}

void Motion::apply_translation(glm::mat4& model)
{
    model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
}

// Rotation
void Motion::set_starting_orientation(glm::vec3 _starting_orientation)
{
    starting_orientation = _starting_orientation;
}

glm::vec3 Motion::get_starting_orientation()
{
    return starting_orientation;
}

glm::tmat4x4<float> Motion::get_rotation_matrix()
{
    return rotation_matrix;
}

glm::tmat4x4<float> Motion::get_last_rotation_matrix()
{
    return last_rotation_matrix;
}

void Motion::set_rotation_matrix(glm::tmat4x4<float> _rotation_matrix)
{
    last_rotation_matrix = rotation_matrix;
    rotation_matrix = _rotation_matrix;
}

void  Motion::apply_rotation(glm::mat4& model)
{
    model *= rotation_matrix;
}

// Scaling
float Motion::get_scaling()
{
    return size;
}
  
float Motion::get_last_scaling()
{
    return last_size;
}

void Motion::set_scaling(float _size)
{
    last_size = size;
    size = _size;
}

void Motion::apply_scaling(glm::mat4& model)
{
    // only uniform scaling for now
    model = glm::scale(model, glm::vec3(size, size, size));
}

void Motion::reset_motion()
{ 
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    last_position = position;
    rotation_matrix = glm::eulerAngleYZX(0.0f, 0.0f, 0.0f);
    last_rotation_matrix = rotation_matrix;
    size = 0.0f;
    last_size = size;
}