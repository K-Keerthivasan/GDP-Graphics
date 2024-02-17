#include "cWorldConfiguration.h"
#include <iostream>
 
//Lighting---------------------------------------------------------------------------------------------

void cWorldConfiguration::CreateNewLight(int lightId, float initial_x, float initial_y, float initial_z)
{
    if (lightId > 15)
    {
        std::cout << "Light Id is more than 15 ! Cannot create light !" << std::endl;
        return;
    }
    std::cout << "Light : " << lightId << " Created !" << std::endl;

    gTheLights->SetUniformLocations(shaderProgramID, lightId);

    gTheLights->theLights[lightId].param2.x = 1.0f; // Turn on

    gTheLights->theLights[lightId].param1.x = 2.0f;   // 0 = point light , 1 = spot light , 2 = directional light

    gTheLights->theLights[lightId].param1.y = 50.0f; // inner angle

    gTheLights->theLights[lightId].param1.z = 50.0f; // outer angle

    gTheLights->theLights[lightId].position.x = initial_x;

    gTheLights->theLights[lightId].position.y = initial_y;

    gTheLights->theLights[lightId].position.z = initial_z;

    gTheLights->theLights[lightId].direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);

    gTheLights->theLights[lightId].atten.x = 0.0f;        // Constant attenuation

    gTheLights->theLights[lightId].atten.y = 0.1f;        // Linear attenuation

    gTheLights->theLights[lightId].atten.z = 0.0f;        // Quadratic attenuation
}

void cWorldConfiguration::ToggleLightState(int lightId, bool turnOff)
{
    if (turnOff)
        gTheLights->theLights[lightId].param2.x = 0.0f;
    else
        gTheLights->theLights[lightId].param2.x = 1.0f;
}

void cWorldConfiguration::PositionLightSource(int lightId, float translate_x, float translate_y, float translate_z)
{
    gTheLights->theLights[lightId].position.x = translate_x;

    gTheLights->theLights[lightId].position.y = translate_y;

    gTheLights->theLights[lightId].position.z = translate_z;
}

void cWorldConfiguration::AdjustLightIntensity(int lightId, float linearAttentuation, float quadraticAttentuation)
{
    gTheLights->theLights[lightId].atten.y = linearAttentuation;

    gTheLights->theLights[lightId].atten.z = quadraticAttentuation;
}

void cWorldConfiguration::SetLightType(int lightId, float lightType)
{
    gTheLights->theLights[lightId].param1.x = lightType;
}

void cWorldConfiguration::ModifyLightAngle(int lightId, float innerAngle, float outerAngle)
{
    gTheLights->theLights[lightId].param1.y = innerAngle; // inner angle

    gTheLights->theLights[lightId].param1.z = outerAngle; // outer angle
}

void cWorldConfiguration::SetLightDirection(int lightId, float direction_x, float direction_y, float direction_z)
{
    gTheLights->theLights[lightId].direction = glm::vec4(direction_x, direction_y, direction_z, 1.0f);

}

void cWorldConfiguration::ChangeLightColor(int lightId, float color_r, float color_g, float color_b)
{
    gTheLights->theLights[lightId].diffuse = glm::vec4(color_r, color_g, color_b, 1.0f);
}
