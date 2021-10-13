#pragma once
#include<memory>

#include <glm/glm.hpp>

#include "Motion.h"
#include "MotionChange.h"

class MotionSegment
{
public:
    friend class MotionPlan;

    MotionSegment();
    ~MotionSegment();

    bool initialize();
        
    std::shared_ptr<MotionChange> get_translation();
    std::shared_ptr<MotionChange> get_rotation();
    std::shared_ptr<MotionChange> get_scaling();

    bool set_duration(float _duration);
    bool set_num_frames(unsigned int _num_frames);
    unsigned int get_num_frames();

    unsigned int reset();
    bool next(std::shared_ptr<Motion> motion);

private:
    // The 3 forms of motion
    std::shared_ptr<MotionChange> translation;
    std::shared_ptr<MotionChange> rotation;
    std::shared_ptr<MotionChange> scaling;

    // Duration
    float duration;
};

