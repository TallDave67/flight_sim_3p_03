#include <stdio.h>
#include <string.h>
#include <memory>
#include <vector>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Constants.h"
#include "Screen.h"
#include "EntityManager.h"
#include "LightManager.h"
#include "ShaderManager.h"

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Motion.h"

#include "Camera.h"
#include "FrameRate.h"
#include "VideoStreamer.h"

#include "Utility.h"

// Managers
EntityManager entityManager;
LightManager lightManager;
ShaderManager shaderManager;

// Camera
Camera camera;

int main()
{
    // Our screen to which we draw our graphics
    std::shared_ptr<Screen> screen = std::make_shared<Screen>();
    if (!screen)
    {
        return 1;
    }
    int ret = screen->initialize(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (ret != 0)
    {
        return ret;
    }

    // Initialize our Managers
    std::shared_ptr<EntityManager> entityManager = std::make_shared<EntityManager>();
    std::shared_ptr<LightManager> lightManager = std::make_shared<LightManager>();
    std::shared_ptr<ShaderManager> shaderManager = std::make_shared<ShaderManager>();
    if (!(entityManager && lightManager && shaderManager))
    {
        return 1;
    }
    //
    entityManager->initialize();
    lightManager->initialize(entityManager);
    shaderManager->initialize();
    if (!shaderManager->getShader(0))
    {
        return 1;
    }

    // Initiliaze our camera
    camera.initialize(screen, glm::vec3(0.0f, 0.0f, TRANSLATION_MAX_OFFSET), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 
        static_cast<GLfloat>(CAMERA_TRANSLATION_INCREMENT), static_cast<GLfloat>(CAMERA_ROTATION_INCREMENT));

    // Create a perspective projection so we can live in a 3d world
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), static_cast<GLfloat>(screen->getBufferWidth())/static_cast<GLfloat>(screen->getBufferHeight()), 0.1f, 150.0f);

    // Set a reasonable frame rate
    FrameRate fr(FPS_SCREEN);

    // Video Streaming
    VideoStreamer video_streamer(FPS_MP4);
    video_streamer.prepare(screen->getWidth(), screen->getHeight());

    // Loop until screen closed
    while (!screen->shouldClose())
    {
        // Do we render to the screen?
        if (!fr.is_frame_due())
        {
            continue;
        }

        // Get + Handle user input events
        glfwPollEvents();
        camera.handleKeyEvent();

        // Clear screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set our shader
        shaderManager->useShader(0);
    
        // Projection
        glUniformMatrix4fv(shaderManager->getShader(0)->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));

        // Camera (View)
        glUniformMatrix4fv(shaderManager->getShader(0)->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera.getView()));

        // Eye
        glUniform3f(shaderManager->getShader(0)->GetEyeLocation(), camera.getCameraEye().x, camera.getCameraEye().y, camera.getCameraEye().z);
        
        // Lights
        lightManager->moveLights();
        lightManager->setLights(shaderManager->getShader(0));

        // Render
        entityManager->moveEntities();
        entityManager->renderEntities(shaderManager->getShader(0));

        glUseProgram(0);

        // stream before rendering
        video_streamer.stream();

        // render
        screen->swapBuffers();
    }

    // finish streaming
    video_streamer.finish();

    // report the number of frames rendered
    printf("rendered %u frames\n", fr.get_next_frame() - 1);

    return 0;
}