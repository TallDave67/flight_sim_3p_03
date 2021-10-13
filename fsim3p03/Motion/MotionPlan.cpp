#include "MotionPlan.h"

#include "Constants.h"

MotionPlan::MotionPlan() :
    motion(nullptr), type(MOTION_PLAN_TYPE_NONE), current_segment(0)
{
}

MotionPlan::~MotionPlan()
{
}

void MotionPlan::initialize(unsigned int _type)
{
    motion = std::make_shared<Motion>();
    if (motion)
    {
        motion->initialize();
    }

    type =_type;
}
   
std::shared_ptr<MotionSegment> MotionPlan::add_segment()
{
    segmentList.push_back(std::make_shared<MotionSegment>());
    return segmentList[segmentList.size() - 1];
}

void MotionPlan::move()
{
    if (!next())
    {
        if (type & MOTION_PLAN_TYPE_INFINITE)
        {
            if (reset())
            {
                move();
            }
        }
    }
}

bool MotionPlan::reset()
{
    if (motion)
    {
        motion->reset_motion();
    }

    current_segment = 0;
    unsigned int num_frames = 0;
    std::vector<std::shared_ptr<MotionSegment>>::iterator itr_seg = segmentList.begin();
    for (; itr_seg != segmentList.end(); itr_seg++)
    {
        num_frames += (*itr_seg)->reset();
    }

    return (num_frames > 0);
}

bool MotionPlan::next()
{
    bool n = false;
    while (current_segment < segmentList.size())
    {
        if (!(segmentList[current_segment]->next(motion)))
        {
            current_segment++;
        }
        else
        {
            n = true;
            break;
        }
    }
    return n;
}

std::shared_ptr<Motion> MotionPlan::get_motion()
{
    return motion;
}
