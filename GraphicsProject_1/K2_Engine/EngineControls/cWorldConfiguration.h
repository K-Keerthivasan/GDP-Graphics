#pragma once
#include "../Models/cMesh.h"
#include "../Physics/cPhysics.h"
 
#include "../Lighting/cLightManager.h"
 
#include "../cVAOManager/cVAOManager.h"
#include "../Basic Shader Manager/cShaderManager.h"
 

class cWorldConfiguration
{
private:

    int gSelectedLight = 0;

    glm::vec3 g_cameraEye = glm::vec3(0.0, 0.0f, 0.0f);
    glm::vec3 g_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 g_upVector = glm::vec3(0.0f, 1.0f, 0.0f);

    GLuint shaderProgramID = 0;

    cShaderManager* pShaderThing = NULL;

    cVAOManager* gMeshManager = NULL;

    cPhysics* gPhysics = NULL;

    cLightManager* gTheLights = NULL;

 
    std::vector < sPhysicsProperties* > gModelPhysicalProps;

    std::vector< cMesh* > g_vec_pMeshesToDraw;

    std::vector < sModelDrawInfo* > newMeshAdd;

    cShaderManager::cShader vertexShader;

    cShaderManager::cShader fragmentShader;

    void DrawObject(cMesh* pCurrentMesh, glm::mat4 matModel, GLuint shaderProgramID);

    cMesh* g_pFindMeshByFriendlyName(std::string friendlyNameToFind);

    sModelDrawInfo* g_pFindModelInfoByFriendlyName(std::string friendlyNameToFind);

    sPhysicsProperties* FindPhysicalModelByName(std::string modelName);

    int InitializeShader();




public:

 
    // Camera-------------------------------------------------------

    void AdjustCameraPosition(float translate_x, float translate_y, float translate_z);

    void AdjustCameraTarget(float translate_x, float translate_y, float translate_z);

    glm::vec3 GetActiveCameraPosition();

    glm::vec3 GetActiveCameraTarget();

	//Mesh-Control------------------------------------------------

    void ChangeColor(std::string modelName, float r, float g, float b, bool useColor);
 
    void ResizeMesh(std::string modelModel, float scale_value);

    void TranslateMesh(std::string modelModel, float translate_x, float translate_y, float translate_z);

    glm::vec3 GetMeshLocation(std::string modelModel);

    void RotateMesh(std::string modelModel, float scalar, float rotate_x, float rotate_y, float rotate_z);
 
    void MeshVisibility(std::string modelName,
        bool isWireframe,
        bool islit,
        bool isVisible);

	//Lighting ----------------------------------------------------------------

    void CreateNewLight(int lightId, float initial_x, float initial_y, float initial_z);

    void ToggleLightState(int lightId, bool turnOff);

    void PositionLightSource(int lightId, float translate_x, float translate_y, float translate_z);

    void AdjustLightIntensity(int lightId, float linearAttentuation, float quadraticAttentuation);

    void SetLightType(int lightId, float lightType);

    void ModifyLightAngle(int lightId, float innerAngle, float outerAngle);

    void SetLightDirection(int lightId, float direction_x, float direction_y, float direction_z);
    
    void ChangeLightColor(int lightId, float color_r, float color_g, float color_b);
    
	//Physics------------------------------------------------

    void ApplyPhysics(std::string sphereModelName, std::string groundModelName, double deltaTime);

    void MoveObjectPhysics(std::string modelName, float newPositionX, float newPositionY, float newPositionZ);

    void AddPhysicsTo3DObject(std::string modelName);

    void ModifyObjectVelocity(std::string modelName, glm::vec3 velocityChange);

    void AdjustObjectAcceleration(std::string modelName, glm::vec3 accelerationChange);

    bool CheckForCollision(std::string model_1, std::string model_2);


	//Engine ----------------------------------------------------------------
       
    void Load3DModels(std::string filePath, std::string modelName, float initial_x, float initial_y, float initial_z);

    int InitializeGameEngine();

    int GameEngineMain(GLFWwindow* window);
};

