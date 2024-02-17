#include "cWorldConfiguration.h"



//Camera----------------------------------------------------------------

void cWorldConfiguration::AdjustCameraPosition(float translate_x, float translate_y, float translate_z)
{
    g_cameraEye = glm::vec3(translate_x, translate_y, translate_z);
}

void cWorldConfiguration::AdjustCameraTarget(float translate_x, float translate_y, float translate_z)
{
    g_cameraTarget = glm::vec3(translate_x, translate_y, translate_z);
}

glm::vec3 cWorldConfiguration::GetActiveCameraPosition()
{
    return g_cameraEye;
}

glm::vec3 cWorldConfiguration::GetActiveCameraTarget()
{
    return g_cameraTarget;
}

