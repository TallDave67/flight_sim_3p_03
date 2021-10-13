#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp> 

class Motion
{
public:
    friend class MotionPlan;

    Motion();
    ~Motion();

    void initialize();

    // Translation
    glm::vec3 get_position();
    glm::vec3 get_last_position();
    void set_position(glm::vec3 _position);
    void apply_translation(glm::mat4 & model);

    // Rotation
    void set_starting_orientation(glm::vec3 _starting_orientation);
    glm::vec3 get_starting_orientation();
    glm::tmat4x4<float> get_rotation_matrix();
    glm::tmat4x4<float> get_last_rotation_matrix();
    void set_rotation_matrix(glm::tmat4x4<float> _rotation_matrix);
    void apply_rotation(glm::mat4 & model);

    // Scaling
    float get_scaling();
    float get_last_scaling();
    void set_scaling(float _size);
    void apply_scaling(glm::mat4 & model);

    virtual void reset_motion();
private:
    glm::vec3 position;
    glm::vec3 last_position;
    glm::vec3 starting_orientation;
    glm::tmat4x4<float> rotation_matrix;
    glm::tmat4x4<float> last_rotation_matrix;
    float size;
    float last_size;
};

