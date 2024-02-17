#include "cWorldConfiguration.h"

 
//Mesh-----------------------------------------------------------------


void cWorldConfiguration::ChangeColor(std::string modelName, float r, float g, float b, bool useColor)
{
    cMesh* meshToBeScaled = g_pFindMeshByFriendlyName(modelName);
    meshToBeScaled->wholeObjectDebugColourRGBA = glm::vec4(r, g, b, 1.0);

    if (useColor)
        meshToBeScaled->bUseDebugColours = true;
    else
        meshToBeScaled->bUseDebugColours = false;

}
  
void cWorldConfiguration::ResizeMesh(std::string modelName, float scale_value)
{
    cMesh* meshToBeScaled = g_pFindMeshByFriendlyName(modelName);

    meshToBeScaled->setUniformDrawScale(scale_value);
}

void cWorldConfiguration::TranslateMesh(std::string modelName, float translate_x, float translate_y, float translate_z)
{
    cMesh* meshToBeTranslated = g_pFindMeshByFriendlyName(modelName);

    const glm::vec3& position = glm::vec3(translate_x, translate_y, translate_z);

    meshToBeTranslated->setDrawPosition(position);
}

glm::vec3 cWorldConfiguration::GetMeshLocation(std::string modelName)
{
    cMesh* meshPosition = g_pFindMeshByFriendlyName(modelName);

    return meshPosition->getDrawPosition();
}

void cWorldConfiguration::RotateMesh(std::string modelName, float scalar, float rotate_x, float rotate_y, float rotate_z)
{
    cMesh* meshToBeRotated = g_pFindMeshByFriendlyName(modelName);

    glm::vec3 rotation = glm::vec3(rotate_x, rotate_y, rotate_z);

    meshToBeRotated->setRotationFromEuler(rotation);
}
 

void cWorldConfiguration::MeshVisibility(std::string modelName, 
		bool isWireframe,
		bool islit, 
		bool isVisible)
{
	cMesh* meshVisibility = g_pFindMeshByFriendlyName(modelName);

    cMesh* mesh = g_pFindMeshByFriendlyName(modelName);

    if (isVisible) {
        mesh->bIsVisible = true;
    }
    else {
        mesh->bIsVisible = false;
    }

    if (isWireframe) {
        mesh->bIsWireframe = true;
    }
    else {
        mesh->bIsWireframe = false;
    }

    if (islit) {
        mesh->bDoNotLight = false;
    }
    else {
        mesh->bDoNotLight = true;
    }

}