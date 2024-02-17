/*
#include "cMesh.h"
//#include "sPhsyicsProperties.h"
#include "../cVAOManager/cVAOManager.h"
 
#include "../Physics/cPhysics.h"
#include <vector>

extern std::vector< cMesh* > g_vec_pMeshesToDraw;
//extern std::vector< sPhsyicsProperties* > g_vec_pPhysicalProps;
extern cPhysics* g_pPhysics;    //

extern cMesh* g_pDebugSphereMesh;

extern cVAOManager* g_pMeshManager;

float getRandomFloat(float a, float b);

bool LoadModels(void)
{

    /*
    cMesh* pCube = new cMesh();
    pCube->meshFileName = "Cube_1x1x1_xyz_n_rgba.ply";
    pCube->friendlyName = "cube";
    //   pBathtub->bDoNotLight = true;
    pCube->drawPosition = glm::vec3(0.0f, -30.0f, 100.0f);
    //bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
    ::g_vec_pMeshesToDraw.push_back(pCube);


    //Robot Meshes

    cMesh* pRobot_Eye_Centre = new cMesh();
    pRobot_Eye_Centre->meshFileName = "Robot_Eye_Centre.ply";
    pRobot_Eye_Centre->friendlyName = "robot_eye_centre";
    //   pBathtub->bDoNotLight = true;
    pRobot_Eye_Centre->drawPosition = glm::vec3(0.0f, 0.0f, 100.0f);
    pRobot_Eye_Centre->setUniformDrawScale(0.1f);
    ::g_vec_pMeshesToDraw.push_back(pRobot_Eye_Centre);


    cMesh* pRobot_Eye_Far_Left = new cMesh();
    pRobot_Eye_Far_Left->meshFileName = "Robot_Eye_Far_Left.ply";
    pRobot_Eye_Far_Left->friendlyName = "pRobot_Eye_Far_Left";
    //   pBathtub->bDoNotLight = true;
    pRobot_Eye_Far_Left->drawPosition = glm::vec3(10.0f, 10.0f, 100.0f);
    pRobot_Eye_Far_Left->setUniformDrawScale(0.1f);
::g_vec_pMeshesToDraw.push_back(pRobot_Eye_Far_Left);


     cMesh* cRobot_Eye_Far_Right = new cMesh();
     cRobot_Eye_Far_Right->meshFileName = "Robot_Eye_Far_Right.ply";
     cRobot_Eye_Far_Right->friendlyName = "cRobot_Eye_Far_Right";
     //   pBathtub->bDoNotLight = true;
     cRobot_Eye_Far_Right->drawPosition = glm::vec3(0.0f, 20.0f, 100.0f);
     //bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
             pRobot_Eye_Centre->setUniformDrawScale(0.1f);

::g_vec_pMeshesToDraw.push_back(cRobot_Eye_Far_Right);

     cMesh* cRobot_Eye_Right = new cMesh();
     cRobot_Eye_Right->meshFileName = "Robot_Eye_Right.ply";
     cRobot_Eye_Right->friendlyName = "cRobot_Eye_Right";
     //   pBathtub->bDoNotLight = true;
     cRobot_Eye_Right->drawPosition = glm::vec3(0.0f, -30.0f, 100.0f);
     //bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
     cRobot_Eye_Right->setUniformDrawScale(0.1f);
     ::g_vec_pMeshesToDraw.push_back(cRobot_Eye_Right);

      cMesh* cRobot_Eye_Left = new cMesh();
     cRobot_Eye_Left->meshFileName = "Robot_Eye_Left.ply";
     cRobot_Eye_Left->friendlyName = "cRobot_Eye_Left";
     //   pBathtub->bDoNotLight = true;
     cRobot_Eye_Left->drawPosition = glm::vec3(0.0f, -10.0f, 100.0f);
     //bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
     cRobot_Eye_Left->setUniformDrawScale(0.1f);
     ::g_vec_pMeshesToDraw.push_back(cRobot_Eye_Left);


     const float CUBE_SPACING = 5.0f;  // Adjust the spacing between cubes
     const unsigned int NUMBER_OF_CUBES = 10;
     for (unsigned int count = 0; count < NUMBER_OF_CUBES; count++)
        {
            cMesh* pDrawCubes = new cMesh();
            pCube->meshFileName = "Cube_1x1x1_xyz_n_rgba.ply";

            pDrawCubes->friendlyName = "drawCube";

            pDrawCubes->setUniformDrawScale(1.0f);  // Adjust the scale as needed

            // Calculate the position of each cube in the sequence
            float xPos = count * CUBE_SPACING;
            float yPos = 0.0f;
            float zPos = 0.0f;
            //float zPos = 0.0f;

            pDrawCubes->drawPosition.x = xPos;
            pDrawCubes->drawPosition.y = yPos;
            pDrawCubes->drawPosition.z = zPos;


            // Add drawing mesh to the things to draw
            ::g_vec_pMeshesToDraw.push_back(pDrawCubes);
     }
     #1#



    return true;
}
*/
