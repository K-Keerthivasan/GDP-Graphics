#include "cWorldConfiguration.h"
#include "../cVAOManager/cVAOManager.h"
#include "../Basic Shader Manager/cShaderManager.h"
#include "../GLWF_CallBacks.h"
#include "../Models/cMesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <sstream>
 

//Private------------------------------------------------------------------------------------


//Public Functions-----------------------------------------------------------------------
 
 
void cWorldConfiguration::Load3DModels(std::string filePath, std::string modelName, float initial_x, float initial_y, float initial_z)
{
    sModelDrawInfo* newModel = new sModelDrawInfo;

    cMesh* newMesh = new cMesh();

    bool result = gMeshManager->LoadModelIntoVAO(modelName, filePath, *newModel, shaderProgramID);

    if (!result)
    {
        std::cout << "Cannot load model - " << modelName << std::endl;
        return;
    }

    newMeshAdd.push_back(newModel);

    newMesh->meshName = filePath;

    newMesh->friendlyName = modelName;

    newMesh->drawPosition = glm::vec3(initial_x, initial_y, initial_z);

    std::cout << "Loaded: " << newMesh->friendlyName << " | Vertices : " << newModel->numberOfVertices << std::endl;

    g_vec_pMeshesToDraw.push_back(newMesh);
}

int cWorldConfiguration::InitializeGameEngine()
{
   

    int result = InitializeShader();

    if (result != 0)
        return -1;

 

    gMeshManager = new cVAOManager();

    gMeshManager->setBasePath("Assets/Models");

    gPhysics = new cPhysics();

    gPhysics->setVAOManager(gMeshManager);

 

    gTheLights = new cLightManager();

   // CreateNewLight(0);

    return 0;
}

int cWorldConfiguration::GameEngineMain(GLFWwindow* window)
{

  /*  glm::vec3 modelPosition = g_vec_pMeshesToDraw[0]->getDrawPosition();  

    MoveObjectPhysics("Asteroid", modelPosition.x, modelPosition.y, modelPosition.z);*/

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glUseProgram(shaderProgramID);

        glfwGetFramebufferSize(window, &width, &height);

        ratio = width / (float)height;

        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        glCullFace(GL_BACK);

   

        gTheLights->UpdateUniformValues(shaderProgramID);
 

        GLint eyeLocation_UL = glGetUniformLocation(shaderProgramID, "eyeLocation");
        glUniform4f(eyeLocation_UL,
            g_cameraEye.x, g_cameraEye.y, g_cameraEye.z, 1.0f);

        glm::mat4 matProjection = glm::perspective(0.6f, ratio, 0.1f, 1000.0f);

        glm::mat4 matView = glm::lookAt(g_cameraEye, g_cameraTarget, g_upVector);

        GLint matProjection_UL = glGetUniformLocation(shaderProgramID, "matProjection");
        glUniformMatrix4fv(matProjection_UL, 1, GL_FALSE, glm::value_ptr(matProjection));

        GLint matView_UL = glGetUniformLocation(shaderProgramID, "matView");
        glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(matView));

   
            
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;

 
        
        lastTime = currentTime;

        //ApplyPhysics("Asteroid", "SpaceShip", deltaTime);
 

        for (unsigned int index = 0; index != g_vec_pMeshesToDraw.size(); index++)
        {
            cMesh* pCurrentMesh = g_vec_pMeshesToDraw[index];

            if (pCurrentMesh->bIsVisible)
            {
                glm::mat4 matModel = glm::mat4(1.0f);




                DrawObject(pCurrentMesh, matModel, shaderProgramID);
            }
        }
 
        std::stringstream ssTitle;

        ssTitle << "Camera Eye(x,y,z): "
            << g_cameraEye.x << ", "
            << g_cameraEye.y << ", "
            << g_cameraEye.z << ") | "
            << "Camera Target(x,y,z): "
            << g_cameraTarget.x << ", "
            << g_cameraTarget.y << ", "
            << g_cameraTarget.z << ")";

        std::string theTitle = ssTitle.str();

        glfwSwapBuffers(window);

        glfwPollEvents();

        glfwSetWindowTitle(window, theTitle.c_str());
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    exit(EXIT_SUCCESS);
}
