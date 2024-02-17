#include "GLWF_CallBacks.h"

#include <string>
#include <iostream>
#include <vector>
#include "Models/cMesh.h"
#include "Lighting/cLightManager.h"
#include "cGlobal.h"
#include "EngineControls/cWorldConfiguration.h"
extern int g_selectedMesh;// = 0;
extern std::vector< cMesh* > g_vec_pMeshesToDraw;

//extern glm::vec3 g_cameraEye;

//extern cLightManager* g_pTheLights;
//extern int g_selectedLight;// = 0;

extern cWorldConfiguration w_game_engine;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
 
    const float CAMERA_MOVEMENT_SPEED = 5.0f;

   /* const float OBJECT_MOVEMENT_SPEED = 0.01f;

    const float LIGHT_MOVEMENT_SPEED = 1.0f;*/


    //------------------------Rotate------------------------------------------
    
    if ((mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
    {
        glm::vec3 cam_target = w_game_engine.GetActiveCameraTarget();

        if (key == GLFW_KEY_A)
        {
            cam_target.x -= CAMERA_MOVEMENT_SPEED;

            w_game_engine.AdjustCameraTarget(cam_target.x, cam_target.y, cam_target.z);
        }
        if (key == GLFW_KEY_D)
        {
            cam_target.x += CAMERA_MOVEMENT_SPEED;

            w_game_engine.AdjustCameraTarget(cam_target.x, cam_target.y, cam_target.z);
        }

        if (key == GLFW_KEY_W)
        {
            cam_target.z -= CAMERA_MOVEMENT_SPEED;

            w_game_engine.AdjustCameraTarget(cam_target.x, cam_target.y, cam_target.z);
        }
        if (key == GLFW_KEY_S)
        {
            cam_target.z += CAMERA_MOVEMENT_SPEED;

            w_game_engine.AdjustCameraTarget(cam_target.x, cam_target.y, cam_target.z);
        }

        if (key == GLFW_KEY_Q)
        {
            cam_target.y -= CAMERA_MOVEMENT_SPEED;

            w_game_engine.AdjustCameraTarget(cam_target.x, cam_target.y, cam_target.z);
        }
        if (key == GLFW_KEY_E)
        {
            cam_target.y += CAMERA_MOVEMENT_SPEED;

            w_game_engine.AdjustCameraTarget(cam_target.x, cam_target.y, cam_target.z);
        }

    }

    if (mods == 0)
    {
       
        glm::vec3 cam_position = w_game_engine.GetActiveCameraPosition();

        if (key == GLFW_KEY_1 && action)
        {
            w_game_engine.AdjustCameraPosition(515,   40.0f, 15.0f);
          
        }

        if (key == GLFW_KEY_2 && action)
        {
            w_game_engine.AdjustCameraPosition(380.0f, 17.0f, 240.0f);
       
        }

        if (key == GLFW_KEY_3 && action)
        {
            w_game_engine.AdjustCameraPosition(-92.0f, -108.0f, 262.0f);
          
        }

        if (key == GLFW_KEY_4 && action)
        {
            w_game_engine.AdjustCameraPosition(323.0f, 122.0f, -288.0f);
        
        }

        if (key == GLFW_KEY_5 && action)
        {
            w_game_engine.AdjustCameraPosition(373, -8, -173);
   
        }

        if (key == GLFW_KEY_6 && action)
        {
            w_game_engine.AdjustCameraPosition(-27.0f, 14.0f, 10.0f);
            w_game_engine.AdjustCameraTarget(0.0f, 0.0f, 0.0f);
        }

        if (key == GLFW_KEY_7 && action)
        {
            w_game_engine.AdjustCameraPosition(6.0f, 23.0f, 10.0f);
            w_game_engine.AdjustCameraTarget(0.0f, 0.0f, 0.0f);
        }

        if (key == GLFW_KEY_8 && action)
        {
            w_game_engine.AdjustCameraPosition(141.0f, 14.0f, 46.0f);
            w_game_engine.AdjustCameraTarget(0.0f, 0.0f, 0.0f);
        }

        
        if (key == GLFW_KEY_A && action)
        {
            cam_position.x -= CAMERA_MOVEMENT_SPEED;

            w_game_engine.AdjustCameraPosition(cam_position.x, cam_position.y, cam_position.z);
        }
        if (key == GLFW_KEY_D && action)
        {
            cam_position.x += CAMERA_MOVEMENT_SPEED;

            w_game_engine.AdjustCameraPosition(cam_position.x, cam_position.y, cam_position.z);
        }
        if (key == GLFW_KEY_W && action)
        {
            cam_position.z -= CAMERA_MOVEMENT_SPEED;

            w_game_engine.AdjustCameraPosition(cam_position.x, cam_position.y, cam_position.z);
        }
        if (key == GLFW_KEY_S && action)
        {
            cam_position.z += CAMERA_MOVEMENT_SPEED;

            w_game_engine.AdjustCameraPosition(cam_position.x, cam_position.y, cam_position.z);
        }
        if (key == GLFW_KEY_Q && action)
        {
            cam_position.y -= CAMERA_MOVEMENT_SPEED;

            w_game_engine.AdjustCameraPosition(cam_position.x, cam_position.y, cam_position.z);
        }
        if (key == GLFW_KEY_E && action)
        {
            cam_position.y += CAMERA_MOVEMENT_SPEED;

            w_game_engine.AdjustCameraPosition(cam_position.x, cam_position.y, cam_position.z);
        }
    }

    return;

    return;
}

