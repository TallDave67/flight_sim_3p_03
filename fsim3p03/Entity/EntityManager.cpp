#include "EntityManager.h"

#include "Constants.h"
#include "MotionSegment.h"
#include "MotionChange.h"

// Motion
EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
}

void EntityManager::initialize()
{
    // Create Materials

    // *** Shiny
    std::shared_ptr<Material> shinyMaterial = addMaterial();
    shinyMaterial->initialize(1.0f, 32.0f);

    // *** Dull
    std::shared_ptr<Material> dullMaterial = addMaterial();
    dullMaterial->initialize(0.2f, 4.0f);

    // Create Entities

    // *** Flyer
    std::shared_ptr<Entity> flyer_entity = addEntity();
    if (flyer_entity)
    {
        flyer_entity->initialize(shinyMaterial);
        //
        std::string flyer_data = std::string("Viper-mk-IV-fighter");
        std::shared_ptr<Model> flyer_model = flyer_entity->getModel();
        if (flyer_model)
        {
            flyer_model->initialize(flyer_data.c_str());
            flyer_model->LoadModel();
        }
        //
        std::shared_ptr<MotionPlan> flyerMotionPlan = flyer_entity->getMotionPlan();
        if (flyerMotionPlan)
        {
            flyerMotionPlan->initialize(MOTION_PLAN_TYPE_INFINITE);
            std::shared_ptr<Motion> motion = flyerMotionPlan->get_motion();
            if (motion)
            {
                motion->set_starting_orientation(glm::vec3(-1.0f, 0.0f, 0.0f));
            }
            //
            std::shared_ptr<MotionSegment> motionStart = flyerMotionPlan->add_segment();
            if (motionStart)
            {
                if (motionStart->initialize())
                {
                    motionStart->get_translation()->set_change(
                        MOTION_CHANGE_TEMPORALITY_ONCE, MOTION_CHANGE_CAUSE_ASSIGN,
                        28.0f, 8.0f, 0.0f,
                        0.0f,  0.0f, 0.0f
                    );
                    motionStart->get_rotation()->set_change(
                        MOTION_CHANGE_TEMPORALITY_ONCE, MOTION_CHANGE_CAUSE_ASSIGN,
                        0.0f, 55.0f, -10.0f,
                        0.0f,  0.0f, 0.0f
                    );
                    motionStart->get_scaling()->set_change(
                        MOTION_CHANGE_TEMPORALITY_ONCE, MOTION_CHANGE_CAUSE_ASSIGN,
                        0.2f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f
                    );
                    motionStart->set_num_frames(1);
                }
            }
            //
            std::shared_ptr<MotionSegment> motionFly = flyerMotionPlan->add_segment();
            if (motionFly)
            {
                if (motionFly->initialize())
                {
                    motionFly->get_translation()->set_change(
                        MOTION_CHANGE_TEMPORALITY_FINTE, MOTION_CHANGE_CAUSE_FUNCTION,
                        0.0f, 0.0f, 0.0f,
                        0.5f, DEGREES_IN_QUARTER_CIRCLE, DEGREES_IN_CIRCLE + DEGREES_IN_QUARTER_CIRCLE
                    );
                    motionFly->get_translation()->set_motion_function(
                        [](float t)
                        {
                            float radius = 6.0f;
                            float y = radius * sinf(glm::radians(t)) + 2.0f;
                            float z = radius * cosf(glm::radians(t));
                            float x = static_cast<float>(pow(y, 2)) + static_cast<float>(pow(z, 2)) - 36.0f;
                            return glm::vec3(x, y, z);
                        }
                    );
                    //
                    motionFly->get_rotation()->set_change(
                        MOTION_CHANGE_TEMPORALITY_FINTE, MOTION_CHANGE_CAUSE_TRANSLATION,
                        0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f
                    );
                    //
                    motionFly->set_duration(12.0f);
                }
            }
        }
    }

    // *** Floater
    std::shared_ptr<Entity> floater_entity = addEntity();
    if (floater_entity)
    {
        floater_entity->initialize(dullMaterial);
        //
        std::string floater_data = std::string("UHFSatcom");
        std::shared_ptr<Model> floater_model = floater_entity->getModel();
        if (floater_model)
        {
            floater_model->initialize(floater_data.c_str());
            floater_model->LoadModel();
        }
        //
        std::shared_ptr<MotionPlan> floaterMotionPlan = floater_entity->getMotionPlan();
        if (floaterMotionPlan)
        {
            floaterMotionPlan->initialize(MOTION_PLAN_TYPE_FINITE);
            std::shared_ptr<MotionSegment> motionStart = floaterMotionPlan->add_segment();
            if (motionStart)
            {
                if (motionStart->initialize())
                {
                    motionStart->get_translation()->set_change(
                        MOTION_CHANGE_TEMPORALITY_ONCE, MOTION_CHANGE_CAUSE_ASSIGN,
                        -2.3f, 1.0f, -4.7f,
                        0.0f, 0.0f, 0.0f
                    );
                    motionStart->get_rotation()->set_change(
                        MOTION_CHANGE_TEMPORALITY_ONCE, MOTION_CHANGE_CAUSE_ASSIGN,
                        0.0f, 0.0f, 45.0f,
                        0.0f, 0.0f, 0.0f
                    );
                    motionStart->get_scaling()->set_change(
                        MOTION_CHANGE_TEMPORALITY_ONCE, MOTION_CHANGE_CAUSE_ASSIGN,
                        0.75f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f
                    );
                    motionStart->set_num_frames(1);
                }
            }
            //
            std::shared_ptr<MotionSegment> motionFloat = floaterMotionPlan->add_segment();
            if (motionFloat)
            {
                if (motionFloat->initialize())
                {
                    motionFloat->get_rotation()->set_change(
                        MOTION_CHANGE_TEMPORALITY_INFINITE, MOTION_CHANGE_CAUSE_INCREMENT,
                        -1.0f, 1.0f, 0.0f,
                        0.75f, 0.0f, 0.0f
                    );
                    motionFloat->set_num_frames(1);
                }
            }
        }
    }

    // *** Planet
    std::shared_ptr<Entity> planet_entity = addEntity();
    if (planet_entity)
    {
        planet_entity->initialize(dullMaterial);
        //
        std::string planet_data = std::string("Mercury");
        std::shared_ptr<Model> planet_model = planet_entity->getModel();
        if (planet_model)
        {
            planet_model->initialize(planet_data.c_str());
            planet_model->LoadModel();
        }
        //
        std::shared_ptr<MotionPlan> planetMotionPlan = planet_entity->getMotionPlan();
        if (planetMotionPlan)
        {
            planetMotionPlan->initialize(MOTION_PLAN_TYPE_FINITE);
            std::shared_ptr<MotionSegment> motionStart = planetMotionPlan->add_segment();
            if (motionStart)
            {
                if (motionStart->initialize())
                {
                    motionStart->get_translation()->set_change(
                        MOTION_CHANGE_TEMPORALITY_ONCE, MOTION_CHANGE_CAUSE_ASSIGN,
                        0.0f, -34.0f, 0.0f,
                        0.0f, 0.0f, 0.0f
                    );
                    motionStart->get_scaling()->set_change(
                        MOTION_CHANGE_TEMPORALITY_ONCE, MOTION_CHANGE_CAUSE_ASSIGN,
                        9.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f
                    );
                    motionStart->set_num_frames(1);
                }
            }
        }
    }
}

void EntityManager::moveEntities()
{
    std::vector<std::shared_ptr<Entity>>::iterator itr = entityList.begin();
    for (; itr != entityList.end(); itr++)
    {
        (*itr)->moveEntity();
    }
}

void EntityManager::renderEntities(std::shared_ptr<Shader> shader)
{
    std::vector<std::shared_ptr<Entity>>::iterator itr = entityList.begin();
    for (; itr != entityList.end(); itr++)
    {
        (*itr)->renderEntity(shader);
    }
}

std::shared_ptr<Entity> EntityManager::addEntity()
{
    entityList.push_back(std::make_shared<Entity>());
    return entityList[entityList.size() - 1];
}

std::shared_ptr<Entity> EntityManager::getEntity(size_t index)
{
    std::shared_ptr<Entity> entity = nullptr;
    if (index < entityList.size())
    {
        entity = entityList[index];
    }
    return entity;
}

std::shared_ptr<Motion> EntityManager::getEntityMotion(size_t index)
{
    std::shared_ptr<Motion> motion = nullptr;
    std::shared_ptr<Entity> entity = getEntity(index);
    if (entity)
    {
        std::shared_ptr<MotionPlan> motionPlan = entity->getMotionPlan();
        if (motionPlan)
        {
            motion = motionPlan->get_motion();
        }
    }
    return motion;
}

std::shared_ptr<Material> EntityManager::addMaterial()
{
    materialList.push_back(std::make_shared<Material>());
    return materialList[materialList.size() - 1];
}

std::shared_ptr<Material> EntityManager::getMaterial(size_t index)
{
    std::shared_ptr<Material> material = nullptr;
    if (index < materialList.size())
    {
        material = materialList[index];
    }
    return material;
}