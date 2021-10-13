#include "MotionSegment.h"

#include "Constants.h"

MotionSegment::MotionSegment() :
    translation(nullptr), rotation(nullptr), scaling(nullptr), duration(0.0f)
{
}

MotionSegment::~MotionSegment()
{
}

bool MotionSegment::initialize()
{
    translation = std::make_shared<MotionChange>();
    if (!translation)
    {
        return false;
    }
    translation->set_category(MOTION_CHANGE_CATEGORY_TRANSLATION);
    //
    rotation = std::make_shared<MotionChange>();
    if (!rotation)
    {
        return false;
    }
    rotation->set_category(MOTION_CHANGE_CATEGORY_ROTATION);
    //
    scaling = std::make_shared<MotionChange>();
    if (!scaling)
    {
        return false;
    }
    scaling->set_category(MOTION_CHANGE_CATEGORY_SCALING);
    return true;
}

std::shared_ptr<MotionChange> MotionSegment::get_translation()
{
    return translation;
}

std::shared_ptr<MotionChange> MotionSegment::get_rotation()
{
    return rotation;
}

std::shared_ptr<MotionChange> MotionSegment::get_scaling()
{
    return scaling;
}

bool MotionSegment::set_duration(float _duration)
{
    duration = _duration;

    //pass along to our motion children
    bool set_translation = false;
    bool set_rotation = false;
    bool set_scaling = false;
    //
    unsigned int num_frames = 0;
    if (translation->get_temporality() != MOTION_CHANGE_TEMPORALITY_NONE)
    {
        set_translation = translation->compute_num_frames(duration, num_frames);
        if (set_translation)
        {
            translation->set_num_frames(num_frames);
        }
    }
    if (rotation->get_temporality() != MOTION_CHANGE_TEMPORALITY_NONE)
    {
        if (set_translation)
        {
             rotation->set_num_frames(num_frames);
        }
        else
        {
            set_rotation = rotation->compute_num_frames(duration, num_frames);
            if (set_rotation)
            {
                rotation->set_num_frames(num_frames);
            }
        }
    }
    if (scaling->get_temporality() != MOTION_CHANGE_TEMPORALITY_NONE)
    {
        if (set_translation || set_rotation)
        {
             scaling->set_num_frames(num_frames);
        }
        else
        {
            set_scaling = scaling->compute_num_frames(duration, num_frames);
            if (set_scaling)
            {
                scaling->set_num_frames(num_frames);
            }
        }
    }
    return (set_translation || set_rotation || set_scaling);
}

bool MotionSegment::set_num_frames(unsigned int _num_frames)
{
    //pass along to our motion children
    bool set_translation = false;
    bool set_rotation = false;
    bool set_scaling = false;
    if (translation->get_temporality() != MOTION_CHANGE_TEMPORALITY_NONE)
    {
        set_translation = translation->set_num_frames(_num_frames);
    }
    if (rotation->get_temporality() != MOTION_CHANGE_TEMPORALITY_NONE)
    {
        set_rotation = rotation->set_num_frames(_num_frames);
    }
    if (scaling->get_temporality() != MOTION_CHANGE_TEMPORALITY_NONE)
    {
        set_scaling = scaling->set_num_frames(_num_frames);
    }
    return (set_translation || set_rotation || set_scaling);
}

unsigned int MotionSegment::get_num_frames()
{
    unsigned int num_frames = 0;
    if (translation->get_temporality() != MOTION_CHANGE_TEMPORALITY_NONE)
    {
        num_frames = translation->get_num_frames();
    }
    else if (rotation->get_temporality() != MOTION_CHANGE_TEMPORALITY_NONE)
    {
        num_frames = rotation->get_num_frames();
    }
    else if (scaling->get_temporality() != MOTION_CHANGE_TEMPORALITY_NONE)
    {
        num_frames = scaling->get_num_frames();
    }
    return num_frames;
}

unsigned int MotionSegment::reset()
{
    translation->reset();
    rotation->reset();
    scaling->reset();
    return get_num_frames();
}

bool MotionSegment::next(std::shared_ptr<Motion> motion)
{
    bool next_translation = false;
    bool next_rotation = false;
    bool next_scaling = false;
    //
    if (translation->get_temporality() != MOTION_CHANGE_TEMPORALITY_NONE)
    {
        next_translation = translation->get_next_change(motion);
    }
    if (rotation->get_temporality() != MOTION_CHANGE_TEMPORALITY_NONE)
    {
        next_rotation = rotation->get_next_change(motion);
    }
    if (scaling->get_temporality() != MOTION_CHANGE_TEMPORALITY_NONE)
    {
        next_scaling = scaling->get_next_change(motion);
    }
    return (next_translation || next_rotation || next_scaling);
}
