#pragma once
#include <memory>
#include <functional>

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp> 

#include "Motion.h"

static const unsigned int MOTION_CHANGE_CATEGORY_NONE           = 0x00000000;
static const unsigned int MOTION_CHANGE_CATEGORY_TRANSLATION    = 0x00000001;
static const unsigned int MOTION_CHANGE_CATEGORY_ROTATION       = 0x00000002;
static const unsigned int MOTION_CHANGE_CATEGORY_SCALING        = 0x00000004;

static const unsigned int MOTION_CHANGE_TEMPORALITY_NONE        = 0x00000000;
static const unsigned int MOTION_CHANGE_TEMPORALITY_ONCE        = 0x00000001;
static const unsigned int MOTION_CHANGE_TEMPORALITY_FINTE       = 0x00000002;
static const unsigned int MOTION_CHANGE_TEMPORALITY_INFINITE    = 0x00000004;

static const unsigned int MOTION_CHANGE_CAUSE_NONE              = 0x00000000;
static const unsigned int MOTION_CHANGE_CAUSE_ASSIGN            = 0x00000001;
static const unsigned int MOTION_CHANGE_CAUSE_INCREMENT         = 0x00000002;
static const unsigned int MOTION_CHANGE_CAUSE_FUNCTION          = 0x00000004;
static const unsigned int MOTION_CHANGE_CAUSE_TRANSLATION       = 0x00000008;

class MotionChange
{
public:
    friend class MotionPlan;

    MotionChange();
    ~MotionChange();

    void set_category(unsigned int _category);
    void set_change(
        unsigned int _temporality, unsigned int _cause,
        float _x, float _y, float _z,
        float _speed, float _t1, float _t2 
    );
    void set_motion_function(std::function<glm::vec3(float)> _mo_ftn);

    unsigned int get_temporality();
    unsigned int get_num_frames();

    bool compute_num_frames(float duration, unsigned int & _num_frames);
    bool set_num_frames(unsigned int _num_frames);
    bool get_next_change(std::shared_ptr<Motion> motion);

    void reset();
private:
    // Configuration
    unsigned int category;
    unsigned int temporality;
    unsigned int cause;
    //
    float x;
    float y;
    float z;
    //
    float speed;
    //
    std::function<glm::vec3(float)> mo_ftn;
    float t1;
    float t2;

    // Run
    unsigned int num_frames;
    unsigned int current_frame;
    float t_increment;
    float t_current;

private:
    // Translation
    void set_translation(std::shared_ptr<Motion> motion, float x, float y, float z);
    void function_translation(std::shared_ptr<Motion> motion);
    void compute_incremental_translation(std::shared_ptr<Motion> motion, float factor_x, float factor_y, float factor_z);
    float compute_translation_distance(float factor);

    // Rotation
    void set_rotation(std::shared_ptr<Motion> motion, float angle_x, float angle_y, float angle_z);
    void function_rotation(std::shared_ptr<Motion> motion);
    void compute_incremental_rotation(std::shared_ptr<Motion> motion, float factor_x, float factor_y, float factor_z);
    float compute_rotation_angle(float factor);
    void translation_rotation(std::shared_ptr<Motion> motion);

    // Scaling
    void set_scaling(std::shared_ptr<Motion> motion, float _size);
    void function_scaling(std::shared_ptr<Motion> motion);
    void compute_incremental_scaling(std::shared_ptr<Motion> motion, float factor);
    float compute_scaling_size(float factor);

    // Orientation
    glm::vec3 get_starting_orientation(std::shared_ptr<Motion> motion);
    glm::vec3 compute_current_orientation(std::shared_ptr<Motion> motion);

    // Run
    void map_frame_to_t();
};

