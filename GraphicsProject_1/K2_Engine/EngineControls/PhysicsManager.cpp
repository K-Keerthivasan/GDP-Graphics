#include "cWorldConfiguration.h"


//Physics-----------------------------------------------------------------------------------------------------

void cWorldConfiguration::ApplyPhysics(std::string sphereModelName, std::string groundModelName, double deltaTime)
{
    sPhysicsProperties* spherePhysicalModel = FindPhysicalModelByName(sphereModelName);

    glm::vec3 velocityChange = spherePhysicalModel->acceleration * (float)deltaTime;

    spherePhysicalModel->velocity += velocityChange;

    glm::vec3 positionChange = spherePhysicalModel->velocity * (float)deltaTime;

    spherePhysicalModel->position.x += positionChange.x;
    spherePhysicalModel->position.y += positionChange.y;
    spherePhysicalModel->position.z += positionChange.z;

    g_vec_pMeshesToDraw[0]->setDrawPosition(spherePhysicalModel->position);

    glm::vec3 groundPos = g_vec_pMeshesToDraw[1]->getDrawPosition();

    /* if (physicalModelFound->position.y - 5 <= groundPos.y)
         physicalModelFound->velocity.y = fabs(physicalModelFound->velocity.y);*/

    cMesh* groundMesh = g_pFindMeshByFriendlyName(groundModelName);

    sModelDrawInfo* modelInfo = g_pFindModelInfoByFriendlyName(groundModelName);

    gPhysics->CheckForCollision(gMeshManager, modelInfo->meshFileName, modelInfo, spherePhysicalModel->position, 5.0f, groundMesh, spherePhysicalModel);


}

bool cWorldConfiguration::CheckForCollision(std::string model_1, std::string model_2)
{
    return true;
}

void cWorldConfiguration::MoveObjectPhysics(std::string modelName, float newPositionX, float newPositionY, float newPositionZ)
{
    sPhysicsProperties* physicalModelFound = FindPhysicalModelByName(modelName);

    physicalModelFound->position.x = newPositionX;
    physicalModelFound->position.y = newPositionY;
    physicalModelFound->position.z = newPositionZ;
}

void cWorldConfiguration::AddPhysicsTo3DObject(std::string modelName)
{
    sPhysicsProperties* newPhysicsModel = new sPhysicsProperties();

    newPhysicsModel->modelName = modelName;

    gModelPhysicalProps.push_back(newPhysicsModel);
}

void cWorldConfiguration::ModifyObjectVelocity(std::string modelName, glm::vec3 velocityChange)
{
    sPhysicsProperties* physicalModelFound = FindPhysicalModelByName(modelName);

    physicalModelFound->velocity = velocityChange;
}

void cWorldConfiguration::AdjustObjectAcceleration(std::string modelName, glm::vec3 accelerationChange)
{
    sPhysicsProperties* physicalModelFound = FindPhysicalModelByName(modelName);

    physicalModelFound->acceleration = accelerationChange;
}