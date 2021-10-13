#include "MotionChange.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Constants.h"
#include "quaternion_utils.hpp"

MotionChange::MotionChange() :
    category(MOTION_CHANGE_CATEGORY_NONE), temporality(MOTION_CHANGE_TEMPORALITY_NONE), cause(MOTION_CHANGE_CAUSE_NONE),
    x(0.0f), y(0.0f), z(0.0f), speed(0.0f), t1(0.0f), t2(0.0f),
    num_frames(0), current_frame(0), t_increment(0.0f), t_current(0.0f)
{
    mo_ftn = [](float t)
    {
        printf ("generic motion function\n");
        return glm::vec3(0.0f, 0.0f, 0.0f);
    };
}

MotionChange::~MotionChange()
{
}

void  MotionChange::set_category(unsigned int _category)
{
    category = _category;
}

void MotionChange::set_change(
    unsigned int _temporality, unsigned int _cause,
    float _x, float _y, float _z,
    float _speed, float _t1, float _t2
)
{
    temporality = _temporality;
    cause = _cause;
    x = _x;
    y = _y;
    z = _z;
    speed = _speed;
    t1 = _t1;
    t2 = _t2;
}

void MotionChange::set_motion_function(std::function<glm::vec3(float)> _mo_ftn)
{
    mo_ftn = _mo_ftn;
}

unsigned int MotionChange::get_temporality()
{
    return temporality;
}

unsigned int MotionChange::get_num_frames()
{
    return num_frames;
}

bool MotionChange::compute_num_frames(float duration, unsigned int & _num_frames)
{
    bool computed = false;
    if (temporality == MOTION_CHANGE_TEMPORALITY_FINTE)
    {
        _num_frames = static_cast<unsigned int>(static_cast<float>(FPS_SCREEN) * duration / speed);
        computed = true;
    }
    return computed;
}

bool MotionChange::set_num_frames(unsigned int _num_frames)
{
    num_frames = _num_frames;
    if (temporality == MOTION_CHANGE_TEMPORALITY_FINTE)
    {
        if (num_frames != 0)
        {
            t_increment = (t2 - t1) / static_cast<float>(num_frames);
        }
    }
    return true;
}

bool MotionChange::get_next_change(std::shared_ptr<Motion> motion)
{
    current_frame++;
    bool gotten = false;
    if (current_frame <= num_frames)
    {
        if (category == MOTION_CHANGE_CATEGORY_TRANSLATION)
        {
            if (temporality == MOTION_CHANGE_TEMPORALITY_ONCE)
            {
                if (cause == MOTION_CHANGE_CAUSE_ASSIGN)
                {
                    set_translation(motion, x, y, z);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_INCREMENT)
                {
                    compute_incremental_translation(motion, x, y, z);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_FUNCTION)
                {
                    function_translation(motion);
                    gotten = true;
                }
            }
            else if (temporality == MOTION_CHANGE_TEMPORALITY_FINTE)
            {
                if (cause == MOTION_CHANGE_CAUSE_INCREMENT)
                {
                    compute_incremental_translation(motion, x, y, z);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_FUNCTION)
                {
                    function_translation(motion);
                    gotten = true;
                }
            }
            else if (temporality == MOTION_CHANGE_TEMPORALITY_INFINITE)
            {
                --current_frame; //no frame counting for infinite motion
                if (cause == MOTION_CHANGE_CAUSE_INCREMENT)
                {
                    compute_incremental_translation(motion, x, y, z);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_FUNCTION)
                {
                    function_translation(motion);
                    gotten = true;
                }
            }
        }
        else if (category == MOTION_CHANGE_CATEGORY_ROTATION)
        {
            if (temporality == MOTION_CHANGE_TEMPORALITY_ONCE)
            {
                if (cause == MOTION_CHANGE_CAUSE_ASSIGN)
                {
                    set_rotation(motion, x, y, z);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_INCREMENT)
                {
                    compute_incremental_rotation(motion, x, y, z);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_FUNCTION)
                {
                    function_rotation(motion);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_TRANSLATION)
                {
                    translation_rotation(motion);
                    gotten = true;
                }
            }
            else if (temporality == MOTION_CHANGE_TEMPORALITY_FINTE)
            {
                if (cause == MOTION_CHANGE_CAUSE_INCREMENT)
                {
                    compute_incremental_rotation(motion, x, y, z);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_FUNCTION)
                {
                    function_rotation(motion);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_TRANSLATION)
                {
                    translation_rotation(motion);
                    gotten = true;
                }
            }
            else if (temporality == MOTION_CHANGE_TEMPORALITY_INFINITE)
            {
                --current_frame; //no frame counting for infinite motion
                if (cause == MOTION_CHANGE_CAUSE_INCREMENT)
                {
                    compute_incremental_rotation(motion, x, y, z);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_FUNCTION)
                {
                    function_rotation(motion);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_TRANSLATION)
                {
                    translation_rotation(motion);
                    gotten = true;
                }
            }
        }
        else if (category == MOTION_CHANGE_CATEGORY_SCALING)
        {
            if (temporality == MOTION_CHANGE_TEMPORALITY_ONCE)
            {
                if (cause == MOTION_CHANGE_CAUSE_ASSIGN)
                {
                    set_scaling(motion, x);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_INCREMENT)
                {
                    compute_incremental_scaling(motion, x);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_FUNCTION)
                {
                    function_scaling(motion);
                    gotten = true;
                }
            }
            else if (temporality == MOTION_CHANGE_TEMPORALITY_FINTE)
            {
                if (cause == MOTION_CHANGE_CAUSE_INCREMENT)
                {
                    compute_incremental_scaling(motion, x);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_FUNCTION)
                {
                    function_scaling(motion);
                    gotten = true;
                }
            }
            else if (temporality == MOTION_CHANGE_TEMPORALITY_INFINITE)
            {
                --current_frame; //no frame counting for infinite motion
                if (cause == MOTION_CHANGE_CAUSE_INCREMENT)
                {
                    compute_incremental_scaling(motion, x);
                    gotten = true;
                }
                else if (cause == MOTION_CHANGE_CAUSE_FUNCTION)
                {
                    function_scaling(motion);
                    gotten = true;
                }
            }
        }
    }
    return gotten;
}

void MotionChange::reset()
{
    current_frame = 0;
    t_current = 0.0f;
}

// Translation
void MotionChange::set_translation(std::shared_ptr<Motion> motion, float x, float y, float z)
{
    glm::vec3 position = motion->get_position();
    position.x += x;
    position.y += y;
    position.z += z;
    motion->set_position(position);
}

void MotionChange::function_translation(std::shared_ptr<Motion> motion)
{
    map_frame_to_t();
    glm::vec3 position = mo_ftn(t_current);
    motion->set_position(position);
}

void MotionChange::compute_incremental_translation(std::shared_ptr<Motion> motion, float factor_x, float factor_y, float factor_z)
{
    float x = compute_translation_distance(factor_x);
    float y = compute_translation_distance(factor_y);
    float z = compute_translation_distance(factor_z);
    set_translation(motion, x, y, z);
}

float MotionChange::compute_translation_distance(float factor)
{
    float distance = factor*TRANSLATION_INCREMENT*speed;
    if (distance > TRANSLATION_MAX_OFFSET)
    {
        distance = TRANSLATION_MAX_OFFSET;
    }
    else if (distance < (-TRANSLATION_MAX_OFFSET))
    {
        distance = -TRANSLATION_MAX_OFFSET;
    }
    return distance;
}

// Rotation
void MotionChange::set_rotation(std::shared_ptr<Motion> motion, float angle_x, float angle_y, float angle_z)
{
    glm::tmat4x4<float> next_rotation_matrix = glm::eulerAngleYZX(glm::radians(angle_y), glm::radians(angle_z), glm::radians(angle_x));
    glm::tmat4x4<float> rotation_matrix = motion->get_rotation_matrix();
    rotation_matrix = next_rotation_matrix * rotation_matrix;
    motion->set_rotation_matrix(rotation_matrix);
}

void MotionChange::function_rotation(std::shared_ptr<Motion> motion)
{
    glm::vec3 starting_orientation = glm::normalize(get_starting_orientation(motion));
    map_frame_to_t();
    glm::vec3 current_orientation = mo_ftn(t_current);
    glm::quat quaternion = RotationBetweenVectors(starting_orientation, current_orientation);
    motion->set_rotation_matrix(glm::toMat4(quaternion));
}

void MotionChange::compute_incremental_rotation(std::shared_ptr<Motion> motion, float factor_x, float factor_y, float factor_z)
{
    float angle_x = compute_rotation_angle(factor_x);
    float angle_y = compute_rotation_angle(factor_y);
    float angle_z = compute_rotation_angle(factor_z);
    set_rotation(motion, angle_x, angle_y, angle_z);
}

float MotionChange::compute_rotation_angle(float factor)
{
    float angle = factor*ROTATION_INCREMENT*speed;
    if (angle > ROTATION_MAX_ANGLE)
    {
        angle -= ROTATION_MAX_ANGLE;
    }
    else if (angle < (-ROTATION_MAX_ANGLE))
    {
        angle += ROTATION_MAX_ANGLE;
    }
    return angle;
}

void MotionChange::translation_rotation(std::shared_ptr<Motion> motion)
{
    glm::vec3 starting_orientation = glm::normalize(get_starting_orientation(motion));
    glm::vec3 current_orientation = glm::normalize(compute_current_orientation(motion));
    glm::quat quaternion = RotationBetweenVectors(starting_orientation, current_orientation);
    motion->set_rotation_matrix(glm::toMat4(quaternion));
}

// Scaling
void MotionChange::set_scaling(std::shared_ptr<Motion> motion, float _size)
{
    float size = motion->get_scaling();
    size += _size;
    motion->set_scaling(size);
}

void MotionChange::function_scaling(std::shared_ptr<Motion> motion)
{
    map_frame_to_t();
    glm::vec3 scaling = mo_ftn(t_current);
    float x = scaling.x;
    set_scaling(motion, x);
}

void MotionChange::compute_incremental_scaling(std::shared_ptr<Motion> motion, float factor)
{
    float _size = compute_scaling_size(factor);
    set_scaling(motion, _size);
}

float MotionChange::compute_scaling_size(float factor)
{
    float _size = factor*SCALING_INCREMENT*speed;
    if (_size > SCALING_MAX_SIZE)
    {
        _size = SCALING_MAX_SIZE;
    }
    else if (_size < SCALING_MIN_SIZE)
    {
        _size = SCALING_MIN_SIZE;
    }
    return _size;
}

// Orientation
glm::vec3 MotionChange::get_starting_orientation(std::shared_ptr<Motion> motion)
{
    return motion->get_starting_orientation();
}

glm::vec3 MotionChange::compute_current_orientation(std::shared_ptr<Motion> motion)
{
    return (motion->get_position() - motion->get_last_position());
}

// Run
void MotionChange::map_frame_to_t()
{
    if (current_frame == num_frames)
    {
        // it's possible our number of frames which is an unsigned int
        // is not cleanly divisible by our period t2 - t1
        // so if we are done we should be on t2
        t_current = t2;
    }
    else
    {
        t_current = t1 + current_frame * t_increment;
    }  
}