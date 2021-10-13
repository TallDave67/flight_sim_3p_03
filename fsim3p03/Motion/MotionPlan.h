#pragma once
#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "Motion.h"
#include "MotionSegment.h"

static const unsigned int MOTION_PLAN_TYPE_NONE     = 0x00000000;
static const unsigned int MOTION_PLAN_TYPE_FINITE   = 0x00000001;
static const unsigned int MOTION_PLAN_TYPE_INFINITE = 0x00000002;

class MotionPlan
{
public:
    MotionPlan();
    ~MotionPlan();

    void initialize(unsigned int _type);
    std::shared_ptr<MotionSegment> add_segment();

    void move();

    bool reset();
    bool next();

    std::shared_ptr<Motion> get_motion();

private:
    std::shared_ptr<Motion> motion;
    unsigned int type;
    std::vector<std::shared_ptr<MotionSegment>> segmentList;
    size_t current_segment;

};

