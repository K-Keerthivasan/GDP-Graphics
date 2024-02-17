 
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "cWorldConfiguration.h"

void cWorldConfiguration::DrawObject(cMesh* pCurrentMesh, glm::mat4 matModelParent, GLuint shaderProgramID)
{
    //--------------------------Calculate Matrix Model Transformation--------------------------------

    glm::mat4 matModel = matModelParent;

    glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f),
        glm::vec3(pCurrentMesh->drawPosition.x, pCurrentMesh->drawPosition.y, pCurrentMesh->drawPosition.z));

    glm::mat4 matRotation = glm::mat4(pCurrentMesh->get_qOrientation());

    glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
        glm::vec3(pCurrentMesh->drawScale.x, pCurrentMesh->drawScale.y, pCurrentMesh->drawScale.z));

    matModel = matModel * matTranslate;

    matModel = matModel * matRotation;

    matModel = matModel * matScale;

    //-------------------------Get Model Info--------------------------------------------------------

    GLint matModel_UL = glGetUniformLocation(shaderProgramID, "matModel");
    glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(matModel));

    glm::mat4 matModel_InverseTranspose = glm::inverse(glm::transpose(matModel));

    GLint matModel_IT_UL = glGetUniformLocation(shaderProgramID, "matModel_IT");
    glUniformMatrix4fv(matModel_IT_UL, 1, GL_FALSE, glm::value_ptr(matModel_InverseTranspose));

    // ---------------------Check Light and Wireframe-------------------------------------------------

    GLint bDoNotLight_UL = glGetUniformLocation(shaderProgramID, "bDoNotLight");

    if (pCurrentMesh->bIsWireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (pCurrentMesh->bDoNotLight)
        glUniform1f(bDoNotLight_UL, (GLfloat)GL_TRUE);
    else
        glUniform1f(bDoNotLight_UL, (GLfloat)GL_FALSE);

    //-------------------------Get Debug Color from Shader----------------------------------------

    GLint bUseDebugColour_UL = glGetUniformLocation(shaderProgramID, "bUseDebugColour");

    if (pCurrentMesh->bUseDebugColours)
    {
        glUniform1f(bUseDebugColour_UL, (GLfloat)GL_TRUE);

        GLint debugColourRGBA_UL = glGetUniformLocation(shaderProgramID, "debugColourRGBA");
        glUniform4f(debugColourRGBA_UL,
            pCurrentMesh->wholeObjectDebugColourRGBA.r,
            pCurrentMesh->wholeObjectDebugColourRGBA.g,
            pCurrentMesh->wholeObjectDebugColourRGBA.b,
            pCurrentMesh->wholeObjectDebugColourRGBA.a);
    }
    else
        glUniform1f(bUseDebugColour_UL, (GLfloat)GL_FALSE);

    //-------------------------Find Model Info and Draw----------------------------------------

    sModelDrawInfo modelInfo;

    if (gMeshManager->FindDrawInfoByModelName(pCurrentMesh->meshName, modelInfo))
    {
        // Found it!!!

        glBindVertexArray(modelInfo.VAO_ID);
        glDrawElements(GL_TRIANGLES,
            modelInfo.numberOfIndices,
            GL_UNSIGNED_INT,
            0);
        glBindVertexArray(0);

    }

    //-------------------------Remove Scaling----------------------------------------

    glm::mat4 matRemoveScaling = glm::scale(glm::mat4(1.0f),
        glm::vec3(1.0f / pCurrentMesh->drawScale.x, 1.0f / pCurrentMesh->drawScale.y, 1.0f / pCurrentMesh->drawScale.z));

    matModel = matModel * matRemoveScaling;


    return;

}



cMesh* cWorldConfiguration::g_pFindMeshByFriendlyName(std::string friendlyNameToFind)
{
    for (unsigned int index = 0; index != g_vec_pMeshesToDraw.size(); index++)
    {
        if (g_vec_pMeshesToDraw[index]->friendlyName == friendlyNameToFind)
        {
            return g_vec_pMeshesToDraw[index];
        }
    }

    std::cout << "Cannot find mesh model for the name provided : " << friendlyNameToFind << std::endl;

    return NULL;
}

sModelDrawInfo* cWorldConfiguration::g_pFindModelInfoByFriendlyName(std::string friendlyNameToFind)
{
    for (unsigned int index = 0; index != newMeshAdd.size(); index++)
    {
        if (newMeshAdd[index]->friendlyName == friendlyNameToFind)
        {
            return newMeshAdd[index];
        }
    }

    std::cout << "Cannot find model info for the name provided : " << friendlyNameToFind << std::endl;

    return NULL;
}


sPhysicsProperties* cWorldConfiguration::FindPhysicalModelByName(std::string modelName)
{
    for (unsigned int index = 0; index != gModelPhysicalProps.size(); index++)
    {
        if (gModelPhysicalProps[index]->modelName == modelName)
        {
            return gModelPhysicalProps[index];
        }
    }

    std::cout << "Cannot find physical mesh model for the name provided : " << modelName << std::endl;

    return NULL;
}


int cWorldConfiguration::InitializeShader()
{
    pShaderThing = new cShaderManager();

    pShaderThing->setBasePath("Assets/Shaders");

    vertexShader.fileName = "vertexShader01.glsl";

    fragmentShader.fileName = "fragmentShader01.glsl";

    if (!pShaderThing->createProgramFromFile("shader01", vertexShader, fragmentShader))
    {
        std::cout << "Error: Couldn't compile or link:" << std::endl;
        std::cout << pShaderThing->getLastError();
        return -1;
    }

    shaderProgramID = pShaderThing->getIDFromFriendlyName("shader01");

    return 0;
}
