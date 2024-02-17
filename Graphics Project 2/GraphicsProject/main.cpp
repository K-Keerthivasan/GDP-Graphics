
#include "Engine.h"
#include "Random.h"
#include <iostream>

extern Camera* camera;
int keyHit = 0;
int action = 0;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        //   std::cout << "Hit" << key << std::endl;
        keyHit = key;
        action = action;
    }

}

int main(void)
{
    Engine engine;
    if (!engine.Initialize())
    {
        return 1;
    }


#pragma region Game Audio
    //Just some Audio Stuff
    sAudio* someAmbience = engine.audioManager->AddAudioToPlaylist("Can You Hear The Music.mp3",
        false,
        false);

    //play audio
    engine.audioManager->PlayAudio("Can You Hear The Music.mp3", true);
    //add filter
    someAmbience->Channel->setVolume(2.0f);
#pragma endregion

#pragma region GameTextures
    //Loading all the textures

    //Common Textures
    engine.meshManager->LoadTexture("Water_Texture_01.bmp");
    engine.meshManager->LoadTexture("PaletteV1.bmp");
    engine.meshManager->LoadTexture("IcePack.bmp");
    engine.meshManager->LoadTexture("ice_texture.bmp");
    engine.meshManager->LoadTexture("ice_texture_plain.bmp");
    engine.meshManager->LoadTexture("BillboardTexture.bmp");
    engine.meshManager->LoadTexture("SomeGround.bmp");
    engine.meshManager->LoadTexture("Graffiti.bmp");
    engine.meshManager->LoadTexture("RandomBuildingTexture.bmp");
    engine.meshManager->LoadTexture("RandomBuildingTextureWGraffitti.bmp");
    engine.meshManager->LoadTexture("JokerMask.bmp");
    engine.meshManager->LoadTexture("EmptyMask.bmp");
 

    //Car Textures
    engine.meshManager->LoadTexture("npc_car_1_with_rust.bmp");
    engine.meshManager->LoadTexture("npc_car_1.bmp");
    engine.meshManager->LoadTexture("npc_car_2.bmp");
    engine.meshManager->LoadTexture("npc_car_3.bmp");
    engine.meshManager->LoadTexture("npc_car_4.bmp");
    engine.meshManager->LoadTexture("npc_car_5.bmp");



    //Skybox Textures
    bool loaded = engine.meshManager->LoadCubeMap("space",
        "CubeMaps/SpaceBox_right1_posX.bmp",
        "CubeMaps/SpaceBox_left2_negX.bmp",
        "CubeMaps/SpaceBox_top3_posY.bmp",
        "CubeMaps/SpaceBox_bottom4_negY.bmp",
        "CubeMaps/SpaceBox_front5_posZ.bmp",
        "CubeMaps/SpaceBox_back6_negZ.bmp",
        true);

#pragma endregion

#pragma region GameMeshes
    //Loading all the mest starts from here ----

    cMesh* skyBoxMesh = engine.LoadMesh("Sphere_1_unit_Radius_UV.ply", "skybox");
    skyBoxMesh->isSkyBox = true;
    skyBoxMesh->setUniformDrawScale(5000.0f);

    cMesh* groundPlane = engine.LoadMesh("Plane.fbx", "groundPlane");
    groundPlane->transperancy = 1.0f;
    groundPlane->bDoNotLight = false;
	groundPlane->color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    groundPlane->texture[0] = "SomeGround.bmp";
    groundPlane->texture[1] = "ice_texture.bmp";
    groundPlane->textureRatio[0] = 0.5f;
    groundPlane->textureRatio[1] = 0.5f;
    groundPlane->drawPosition = glm::vec3(-20.0, -5.0f, 0.0f);
    groundPlane->drawScale = glm::vec3(5.0, 1.0f, 5.0);

 
 
#pragma region RoadMeshes
    //Loop For the Roads

    float roadGap;
    for (int i=0;i< 2; i++)
    {
         roadGap = i * 8;

        cMesh* roadStraightRight = engine.LoadMesh("RoadDoubleBase.fbx", "roadStraightRight " + std::to_string(i));
        roadStraightRight->transperancy = 1.0f;
        roadStraightRight->bDoNotLight = false;
        roadStraightRight->texture[0] = "PaletteV1.bmp";
        roadStraightRight->textureRatio[0] = 1.0f;
        roadStraightRight->drawScale = glm::vec3(1.0f, 1.0f, 1.05f);
        roadStraightRight->drawPosition = glm::vec3(63.0, 0.0f, -3.95f+ roadGap);

    }

    for (int i = 0; i < 2; i++)
    {
        roadGap = i * 8.6;

        cMesh* roadStraightLeft = engine.LoadMesh("RoadDoubleBase.fbx", "roadStraightLeft " + std::to_string(i));
        roadStraightLeft->transperancy = 1.0f;
        roadStraightLeft->bDoNotLight = false;
        roadStraightLeft->texture[0] = "PaletteV1.bmp";
        roadStraightLeft->textureRatio[0] = 1.0f;
        roadStraightLeft->drawPosition = glm::vec3(-41, 0.0f, -4.3f + roadGap);
        roadStraightLeft->drawScale = glm::vec3(1.0f, 1.0f, 1.2f);
    }

    for (int i = 0; i < 10; i++)
    {
        roadGap = i * 8;

        cMesh* roadStraightUp = engine.LoadMesh("RoadDoubleBase.fbx", "roadStraightUp " + std::to_string(i));
        roadStraightUp->transperancy = 1.0f;
        roadStraightUp->bDoNotLight = false;
        roadStraightUp->texture[0] = "PaletteV1.bmp";
        roadStraightUp->textureRatio[0] = 1.0f;
        roadStraightUp->drawPosition = glm::vec3(-25 + roadGap, 0.0f, -20.0f );
        roadStraightUp->setRotationFromEuler(glm::vec3(0.0f, 1.56f, 0.0f));
    }

    for (int i = 0; i < 10; i++)
    {
        roadGap = i * 8;

        cMesh* roadStraightDown = engine.LoadMesh("RoadDoubleBase.fbx", "roadStraightDown " + std::to_string(i));
        roadStraightDown->transperancy = 1.0f;
        roadStraightDown->bDoNotLight = false;
        roadStraightDown->texture[0] = "PaletteV1.bmp";
        roadStraightDown->textureRatio[0] = 1.0f;
        roadStraightDown->drawPosition = glm::vec3(-25 + roadGap, 0.0f, 20.0f);
        roadStraightDown->setRotationFromEuler(glm::vec3(0.0f, 1.56f, 0.0f));
    }

    //Roads Ends
    cMesh* roadTurnLeft = engine.LoadMesh("RoadDoubleTurnLeft.fbx", "roadTurnLeft");
    roadTurnLeft->transperancy = 1.0f;
    roadTurnLeft->bDoNotLight = false;
    roadTurnLeft->texture[0] = "PaletteV1.bmp";
    roadTurnLeft->textureRatio[0] = 1.0f;
    roadTurnLeft->drawPosition = glm::vec3(58.4f, 0.0f, -15.4f);


    cMesh* roadTurnLeftI = engine.LoadMesh("RoadDoubleTurnRight.fbx", "roadTurnLeftI");
    roadTurnLeftI->transperancy = 1.0f;
    roadTurnLeftI->bDoNotLight = false;
    roadTurnLeftI->texture[0] = "PaletteV1.bmp";
    roadTurnLeftI->textureRatio[0] = 1.0f;
    roadTurnLeftI->drawPosition = glm::vec3(-36.0f, 0.0f, 16.0f);
    roadTurnLeftI->setRotationFromEuler(glm::vec3(0.0f, 1.64f, 0.0f));


    cMesh* roadTurnRight = engine.LoadMesh("RoadDoubleTurnRight.fbx", "roadTurnRight");
    roadTurnRight->transperancy = 1.0f;
    roadTurnRight->bDoNotLight = false;
    roadTurnRight->texture[0] = "PaletteV1.bmp";
    roadTurnRight->textureRatio[0] = 1.0f;
    roadTurnRight->drawPosition = glm::vec3(-36.0f, 0.0f, -16.0f);
    roadTurnRight->setRotationFromEuler(glm::vec3(0.0f, -0.06f, 0.0f));

    cMesh* roadTurnRightI = engine.LoadMesh("RoadDoubleTurnRight.fbx", "roadTurnRightI");
    roadTurnRightI->transperancy = 1.0f;
    roadTurnRightI->bDoNotLight = false;
    roadTurnRightI->texture[0] = "PaletteV1.bmp";
    roadTurnRightI->textureRatio[0] = 1.0f;
    roadTurnRightI->drawPosition = glm::vec3(58.4, 0.0f, 15.6f);
    roadTurnRightI->drawScale = glm::vec3(1.0f, 1.0f, 1.0f);
    roadTurnRightI->setRotationFromEuler(glm::vec3(0.0f, 3.12f, 0.0f));

    
#pragma endregion

#pragma region CarMeshes
    //Loading all the cars first
    
    cMesh* car1 = engine.LoadMesh("npc_car_1.fbx", "car1");
    car1->transperancy = 1.0f;
    car1->bDoNotLight = false;
    car1->texture[0] = "npc_car_1.bmp";
    car1->texture[1] = "npc_car_1_with_rust.bmp";
    car1->textureRatio[0] = 0.5f;
    car1->textureRatio[1] = 0.5f;
    car1->drawPosition = glm::vec3(65.0f, 0.0f, 5.0f);
    car1->setUniformDrawScale(0.1f);

    cMesh*car2 = engine.LoadMesh("npc_car_2.fbx", "car2");
    car2->transperancy = 1.0f;
    car2->bDoNotLight = false;
    car2->texture[0] = "npc_car_2.bmp";
    car2->textureRatio[0] = 1.0f;
    car2->drawPosition = glm::vec3(61.0f, 0.0f, 5.0f);
    car2->setUniformDrawScale(0.1f);

    cMesh*car3 = engine.LoadMesh("npc_car_3.fbx", "car3");
    car3->transperancy = 1.0f;
    car3->bDoNotLight = false;
    car3->texture[0] = "npc_car_3.bmp";
    car3->textureRatio[0] = 1.0f;
    car3->drawPosition = glm::vec3(65.0f, 0.0f, 0.0f);
    car3->setUniformDrawScale(0.1f);

    cMesh*car4 = engine.LoadMesh("npc_car_4.fbx", "car4");
    car4->transperancy = 1.0f;
    car4->bDoNotLight = false;
    car4->texture[0] = "npc_car_4.bmp";
    car4->textureRatio[0] = 1.0f;
    car4->drawPosition = glm::vec3(61.0f, 0.0f, 0.0f);
    car4->setUniformDrawScale(0.1f);

#pragma endregion

#pragma region Buildingss 
    //Loading all the House

#pragma region HouseMeshes
    cMesh* house1 = engine.LoadMesh("House01.fbx", "house1");
    house1->transperancy = 1.0f;
    house1->bDoNotLight = false;
    house1->texture[0] = "PaletteV1.bmp";
    house1->textureRatio[0] = 1.0f;
    house1->drawPosition = glm::vec3(-25.0f, 0.0f, -30.0f);

    cMesh* house2 = engine.LoadMesh("House02.fbx", "house2");
    house2->transperancy = 1.0f;
    house2->bDoNotLight = false;
    house2->texture[0] = "PaletteV1.bmp";
    house2->textureRatio[0] = 1.0f;
    house2->drawPosition = glm::vec3(-5.0f, 0.0f, -30.0f);

    cMesh* house3 = engine.LoadMesh("House03.fbx", "house3");
    house3->transperancy = 1.0f;
    house3->bDoNotLight = false;
    house3->texture[0] = "PaletteV1.bmp";
    house3->textureRatio[0] = 1.0f;
    house3->drawPosition = glm::vec3(10.0f, 0.0f, -30.0f);

    cMesh* house4 = engine.LoadMesh("House04.fbx", "house4");
    house4->transperancy = 1.0f;
    house4->bDoNotLight = false;
    house4->texture[0] = "PaletteV1.bmp";
    house4->textureRatio[0] = 1.0f;
    house4->drawPosition = glm::vec3(30.0f, 0.0f, -30.0f);

    cMesh* house5 = engine.LoadMesh("House05.fbx", "house5");
    house5->transperancy = 1.0f;
    house5->bDoNotLight = false;
    house5->texture[0] = "PaletteV1.bmp";
    house5->textureRatio[0] = 1.0f;
    house5->drawPosition = glm::vec3(50.0f, 0.0f, -30.0f);

#pragma endregion
    //Loading all the buildings

#pragma region BuildingMeshes
    cMesh* billboard = engine.LoadMesh("BillboardCylinder.fbx", "billboard");
    billboard->transperancy = 1.0f;
    billboard->bDoNotLight = true;
    billboard->texture[0] = "BillboardTexture.bmp";
    billboard->textureRatio[0] = 1.0f;
    billboard->drawPosition = glm::vec3(-21.0, 20.0f, 0.0);

 
    cMesh* building1 = engine.LoadMesh("Building01.fbx", "building1");
    building1->transperancy = 1.0f;
    building1->bDoNotLight = false;
    building1->texture[0] = "PaletteV1.bmp";
    building1->textureRatio[0] = 1.0f;
    building1->drawPosition = glm::vec3(-25.0f, 0.0f, 35.0f);


    cMesh* building2 = engine.LoadMesh("Building02.fbx", "building2");
    building2->transperancy = 1.0f;
    building2->bDoNotLight = false;
    building2->texture[0] = "PaletteV1.bmp";
    building2->textureRatio[0] = 1.0f;
    building2->drawPosition = glm::vec3(0.0f, 0.0f, 35.0f);

    cMesh* building3 = engine.LoadMesh("Building03.fbx", "building3");
    building3->transperancy = 1.0f;
    building3->bDoNotLight = false;
    building3->texture[0] = "PaletteV1.bmp";
    building3->textureRatio[0] = 1.0f;
    building3->drawPosition = glm::vec3(50, 0.0f, 35.0f);

    cMesh* building4 = engine.LoadMesh("Building04.fbx", "building4");
    building4->transperancy = 1.0f;
    building4->bDoNotLight = false;
    building4->texture[0] = "PaletteV1.bmp";
    building4->textureRatio[0] = 1.0f;
    building4->drawPosition = glm::vec3(25.0f, 0.0f, 35.0f);

    cMesh* building5 = engine.LoadMesh("Building05.fbx", "building5");
    building5->transperancy = 1.0f;
    building5->bDoNotLight = false;
    building5->texture[0] = "PaletteV1.bmp";
    building5->textureRatio[0] = 1.0f;
    building5->drawPosition = glm::vec3(-21.0f, 0.0f, 0.0f);


    cMesh* building6 = engine.LoadMesh("RandomBuilding.fbx", "building6");
    building6->transperancy = 1.0f;
    building6->bDoNotLight = false;
    building6->texture[0] = "RandomBuildingTexture.bmp";
    building6->texture[1] = "RandomBuildingTextureWGraffitti.bmp";
    building6->maskTexture = "JokerMask.bmp";
    building6->textureRatio[0] = 0.3f;
    building6->textureRatio[1] = 0.7f;
    building6->drawScale = glm::vec3(0.2f, 0.2f, 0.2f);
    building6->drawPosition = glm::vec3(77.0f, 0.0f, 0.0f);

#pragma endregion


    //GroundStuff Meshes
#pragma region GroundMeshes

    for (int i = 0; i < 5; i++)
    {
        roadGap = i * 20;

        cMesh* l_housing = engine.LoadMesh("L_Housing01.fbx", "l_housing" + std::to_string(i));
        l_housing->transperancy = 1.0f;
        l_housing->bDoNotLight = false;
        l_housing->texture[0] = "PaletteV1.bmp";
        l_housing->textureRatio[0] = 1.0f;
        l_housing->drawPosition = glm::vec3(-25.0f+roadGap, 0.0f, -34.0f);
    }


    for (int i = 0; i < 5; i++)
    {
        roadGap = i * 20;

        cMesh* l_construction = engine.LoadMesh("L_Urban02.fbx", "l_urban" + std::to_string(i));
        l_construction->transperancy = 1.0f;
        l_construction->bDoNotLight = false;
        l_construction->texture[0] = "PaletteV1.bmp";
        l_construction->textureRatio[0] = 1.0f;
        l_construction->drawPosition = glm::vec3(-25.0f + roadGap, 0.0f, 36.0f);

    }


    cMesh* l_construction = engine.LoadMesh("L_Urban01.fbx", "l_urban");
    l_construction->transperancy = 1.0f;
    l_construction->bDoNotLight = false;
    l_construction->texture[0] = "PaletteV1.bmp";
    l_construction->textureRatio[0] = 1.0f;
    l_construction->drawPosition = glm::vec3(-20.0f, 0.0f, 0.0);
    l_construction->drawScale = glm::vec3(1.0f, 1.0f, 1.3f);

 
    //Loading all the background meshes Starting from the park

    cMesh* park01 = engine.LoadMesh("Park01.fbx", "park01");
    park01->transperancy = 1.0f;
    park01->bDoNotLight = false;
    park01->texture[0] = "PaletteV1.bmp";
    park01->textureRatio[0] = 1.0f;
    park01->drawPosition = glm::vec3(0.0f, 0.0f, -8.0f);

    cMesh* park02 = engine.LoadMesh("Park01.fbx", "park02");
    park02->transperancy = 1.0f;
    park02->bDoNotLight = false;
    park02->texture[0] = "PaletteV1.bmp";
    park02->textureRatio[0] = 1.0f;
    park02->drawPosition = glm::vec3(0.0f, 0.0f, 8.0f);


    cMesh* park03 = engine.LoadMesh("Park02.fbx", "park03");
    park03->transperancy = 1.0f;
    park03->bDoNotLight = false;
    park03->texture[0] = "PaletteV1.bmp";
    park03->textureRatio[0] = 1.0f;
    park03->drawPosition = glm::vec3(24, 0.0f, 0.0f);

    cMesh* park04 = engine.LoadMesh("Park03.fbx", "park04");
    park04->transperancy = 1.0f;
    park04->bDoNotLight = false;
    park04->texture[0] = "PaletteV1.bmp";
    park04->textureRatio[0] = 1.0f;
    park04->drawScale = glm::vec3(0.65, 0.65f, 0.65f);
    park04->drawPosition = glm::vec3(47.60, 0.0f, -8.20f);

    cMesh* park05 = engine.LoadMesh("Park03.fbx", "park05");
    park05->transperancy = 1.0f;
    park05->bDoNotLight = false;
    park05->texture[0] = "PaletteV1.bmp";
    park05->textureRatio[0] = 1.0f;
    park05->drawScale = glm::vec3(0.65, 0.65f, 0.65f);
    park05->drawPosition = glm::vec3(47.60, 0.0f, 7.6f);
#pragma endregion

#pragma endregion

#pragma region IceMeshes
    //Ice Meshes

    cMesh* ice03 = engine.LoadMesh("Ice_03.fbx", "ice03");
    ice03->transperancy = 1.0f;
    ice03->bDoNotLight = false;
    ice03->texture[0] = "ice_texture.bmp";
    ice03->texture[1] = "ice_texture_plain.bmp";
    ice03->textureRatio[0] = 0.5f;
    ice03->textureRatio[1] = 0.5f;
    ice03->drawPosition = glm::vec3(-80.0, 0.0f, 0.0);
    ice03->drawScale = glm::vec3(1.5f, 1.5f, 1.5f);


    cMesh* ice04 = engine.LoadMesh("Ice_04.fbx", "ice04");
    ice04->transperancy = 1.0f;
    ice04->bDoNotLight = false;
    ice04->texture[0] = "ice_texture.bmp";
    ice04->texture[1] = "ice_texture_plain.bmp";
    ice04->textureRatio[0] = 0.5f;
    ice04->textureRatio[1] = 0.5f;
    ice04->drawPosition = glm::vec3(-75.0f, 0.0f, -25.0f);

   cMesh* ice02 = engine.LoadMesh("Ice_02.fbx", "ice02");
    ice02->transperancy = 0.7f;
    ice02->bDoNotLight = false;
    ice02->texture[0] = "ice_texture.bmp";
    ice02->texture[1] = "ice_texture_plain.bmp";
    ice02->textureRatio[0] = 0.5f;
    ice02->textureRatio[1] = 0.5f;
    ice02->drawPosition = glm::vec3(-70.0, 15.0f, 23.0f);

    cMesh* ice01 = engine.LoadMesh("Ice_01.fbx", "ice01");
    ice01->transperancy = 0.7f;
    ice01->bDoNotLight = false;
    ice01->texture[0] = "ice_texture.bmp";
    ice01->texture[1] = "ice_texture_plain.bmp";
    ice01->textureRatio[0] = 0.5f;
    ice01->textureRatio[1] = 0.5f;
    ice01->drawPosition = glm::vec3(-120.0f, 20.0f, 1.0f);


    cMesh* ice05 = engine.LoadMesh("Ice_01.fbx", "ice05");
    ice05->transperancy = 0.7f;
    ice05->bDoNotLight = false;
    ice05->texture[0] = "ice_texture.bmp";
    ice05->texture[1] = "ice_texture_plain.bmp";
    ice05->textureRatio[0] = 0.5f;
    ice05->textureRatio[1] = 0.5f;
    ice05->drawPosition = glm::vec3(23.5f, 2.0f, 0.0f);
    ice05->drawScale = glm::vec3(0.1f, 0.1f, 0.1f);

#pragma endregion

 //Lets Starts with props
    //With the lights
    
#pragma region Props
    for (int i = 0; i < 2; i++)
    {
        roadGap = i * 8;

        cMesh* p_lightRight = engine.LoadMesh("P_Light03.fbx", "p_lightRight " + std::to_string(i));
        p_lightRight->transperancy = 1.0f;
        p_lightRight->bDoNotLight = false;
        p_lightRight->texture[0] = "PaletteV1.bmp";
        p_lightRight->textureRatio[0] = 1.0f;
        p_lightRight->drawPosition = glm::vec3(66.0, 0.0f, -5.0f + roadGap);
    }


    for (int i = 0; i < 2; i++)
    {
        roadGap = i * 8.6;

        cMesh* p_lightLeft = engine.LoadMesh("P_Light03.fbx", "p_lightLeft " + std::to_string(i));
        p_lightLeft->transperancy = 1.0f;
        p_lightLeft->bDoNotLight = false;
        p_lightLeft->texture[0] = "PaletteV1.bmp";
        p_lightLeft->textureRatio[0] = 1.0f;
        p_lightLeft->drawPosition = glm::vec3(-46, 0.0f, -4.3f + roadGap);
        p_lightLeft->drawScale = glm::vec3(1.0f, 1.0f, 1.2f);
        p_lightLeft->setRotationFromEuler(glm::vec3(0.0f, 3.1f, 0.0f));
    }

    for (int i = 0; i < 8; i++)
    {
        roadGap = i * 10;

        cMesh* p_lightUp = engine.LoadMesh("P_Light03.fbx", "p_lightUp " + std::to_string(i));
        p_lightUp->transperancy = 1.0f;
        p_lightUp->bDoNotLight = false;
        p_lightUp->texture[0] = "PaletteV1.bmp";
        p_lightUp->textureRatio[0] = 1.0f;
        p_lightUp->drawPosition = glm::vec3(-25 + roadGap, 0.0f, -24.0f);
        p_lightUp->setRotationFromEuler(glm::vec3(0.0f, 1.56f, 0.0f));
    }

    for (int i = 0; i < 8; i++)
    {
        roadGap = i * 10;

        cMesh* p_lightDown = engine.LoadMesh("P_Light03.fbx", "p_lightDown " + std::to_string(i));
        p_lightDown->transperancy = 1.0f;
        p_lightDown->bDoNotLight = false;
        p_lightDown->texture[0] = "PaletteV1.bmp";
        p_lightDown->textureRatio[0] = 1.0f;
        p_lightDown->drawPosition = glm::vec3(-25 + roadGap, 0.0f, 23.0f);
        p_lightDown->setRotationFromEuler(glm::vec3(0.0f, -1.56f, 0.0f));
    }
  

#pragma endregion
#pragma endregion

#pragma region GameLights
    //Loading all the lights

    //Base night light
    engine.lightManager->theLights[0]->param2.x = 1; //on
    engine.lightManager->theLights[0]->param1.x = 0; //po
    engine.lightManager->theLights[0]->position = glm::vec4(10.0f, 100.0f, 60.0f, 1.0f);
    engine.lightManager->theLights[0]->atten.x = 1.0f; //constant
    engine.lightManager->theLights[0]->atten.y = 0.014f; //linear
    engine.lightManager->theLights[0]->atten.z = 0.0007f; //quadratic
    engine.lightManager->theLights[0]->direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);


    //Base Light for the streets
#pragma region StreetLights
    //Spot Light For street lights

 
    float lightGap;

    //Light Upper
    for (int i = 1; i < 9; i++)
    {
        lightGap = i * 10.0;

    engine.lightManager->theLights[i]->param2.x = 1; //on
    engine.lightManager->theLights[i]->param1.x = 1; //spot
	engine.lightManager->theLights[i]->param1.y = 20; //inner angle
	engine.lightManager->theLights[i]->param1.z = 45; //Outer angle
    engine.lightManager->theLights[i]->position = glm::vec4(-35.0f + lightGap, 7.0, -21, 1.0f);

    engine.lightManager->theLights[i]->atten.x = 1.0f; //constant
    engine.lightManager->theLights[i]->atten.y = 0.14f; //linear
    engine.lightManager->theLights[i]->atten.z = 0.07f; //quadratic
    engine.lightManager->theLights[i]->direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);

    }

	//Light Down

    for (int i = 10; i < 18; i++)
    {
        float adjustedIndex = i - 9;

        lightGap = 10 * adjustedIndex;

        engine.lightManager->theLights[i]->param2.x = 1; //on
        engine.lightManager->theLights[i]->param1.x = 1; //spot
        engine.lightManager->theLights[i]->param1.y = 20; //inner angle
        engine.lightManager->theLights[i]->param1.z = 45; //Outer angle
        engine.lightManager->theLights[i]->position = glm::vec4(-35.0f + lightGap, 7.0, 20, 1.0f);

        engine.lightManager->theLights[i]->atten.x = 1.0f; //constant
        engine.lightManager->theLights[i]->atten.y = 0.14f; //linear
        engine.lightManager->theLights[i]->atten.z = 0.07f; //quadratic
        engine.lightManager->theLights[i]->direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);

    }

	//Light Right

    for (int i = 18; i < 20; i++)
    {
        float adjustedIndex = i - 17;

        lightGap = 10 * adjustedIndex;

        engine.lightManager->theLights[i]->param2.x = 1; //on
        engine.lightManager->theLights[i]->param1.x = 1; //spot
        engine.lightManager->theLights[i]->param1.y = 20; //inner angle
        engine.lightManager->theLights[i]->param1.z = 45; //Outer angle
        engine.lightManager->theLights[i]->position = glm::vec4(65, 7.0, -15 +lightGap, 1.0f);

        engine.lightManager->theLights[i]->atten.x = 1.0f; //constant
        engine.lightManager->theLights[i]->atten.y = 0.14f; //linear
        engine.lightManager->theLights[i]->atten.z = 0.07f; //quadratic
        engine.lightManager->theLights[i]->direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);

    }

    //Light Left
    for (int i = 20; i < 22; i++)
    {
        float adjustedIndex = i - 19;

        lightGap = 10 * adjustedIndex;

        engine.lightManager->theLights[i]->param2.x = 1; //on
        engine.lightManager->theLights[i]->param1.x = 1; //spot
        engine.lightManager->theLights[i]->param1.y = 20; //inner angle
        engine.lightManager->theLights[i]->param1.z = 45; //Outer angle
        engine.lightManager->theLights[i]->position = glm::vec4(-41, 7.0, -15 +lightGap, 1.0f);

        engine.lightManager->theLights[i]->atten.x = 1.0f; //constant
        engine.lightManager->theLights[i]->atten.y = 0.14f; //linear
        engine.lightManager->theLights[i]->atten.z = 0.07f; //quadratic
        engine.lightManager->theLights[i]->direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);

    }
#pragma endregion

#pragma region MainBuildingLights

    engine.lightManager->theLights[22]->param2.x = 1; //on
    engine.lightManager->theLights[22]->param1.x = 1; //spot
    engine.lightManager->theLights[22]->param1.y = 15; //inner angle
    engine.lightManager->theLights[22]->param1.z = 45; //Outer angle
    engine.lightManager->theLights[22]->position = glm::vec4(-20, 20, 0, 1.0f);
    engine.lightManager->theLights[22]->diffuse = glm::vec4(1.0f, 0.0f, 0.5f, 1.0f);
    engine.lightManager->theLights[22]->specular = glm::vec4(1.0f, 0.0f, 0.5f, 1.0f);

    engine.lightManager->theLights[22]->atten.x = 1.0f; //constant
    engine.lightManager->theLights[22]->atten.y = 0.14f; //linear
    engine.lightManager->theLights[22]->atten.z = 0.007f; //quadratic
    engine.lightManager->theLights[22]->direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);


    //for the buildings
    for (int i = 23; i < 27; i++)
    {
        float adjustedIndex = i - 22;

        lightGap = 25 * adjustedIndex;

        engine.lightManager->theLights[i]->param2.x = 1; //on
        engine.lightManager->theLights[i]->param1.x = 1; //spot
        engine.lightManager->theLights[i]->param1.y = 20; //inner angle
        engine.lightManager->theLights[i]->param1.z = 45; //Outer angle
        engine.lightManager->theLights[i]->position = glm::vec4(-50+ lightGap, 20.0, 35, 1.0f);
        engine.lightManager->theLights[i]->diffuse = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);
        engine.lightManager->theLights[i]->specular = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);

        engine.lightManager->theLights[i]->atten.x = 1.0f; //constant
        engine.lightManager->theLights[i]->atten.y = 0.14f; //linear
        engine.lightManager->theLights[i]->atten.z = 0.007f; //quadratic
        engine.lightManager->theLights[i]->direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);
        
	}
    //for the houses
    for (int i = 27; i < 33; i++)
    {
        float adjustedIndex = i - 26;

        lightGap = 25 * adjustedIndex;

        engine.lightManager->theLights[i]->param2.x = 1; //on
        engine.lightManager->theLights[i]->param1.x = 0; //point
        engine.lightManager->theLights[i]->position = glm::vec4(-50 + lightGap, 15, -35, 1.0f);
		engine.lightManager->theLights[i]->atten.x = 1.0f; //constant
        engine.lightManager->theLights[i]->atten.y = 0.1f; //linear
        engine.lightManager->theLights[i]->atten.z = 0.05f; //quadratic
        engine.lightManager->theLights[i]->direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);

    }

    //for the park
    for (int i = 33; i < 35; i++)
    {
        float adjustedIndex = i - 32;

        lightGap = 25 * adjustedIndex;

        engine.lightManager->theLights[i]->param2.x = 1; //on
        engine.lightManager->theLights[i]->param1.x = 0; //point
        engine.lightManager->theLights[i]->position = glm::vec4(-15 + lightGap, 15, -5, 1.0f);
        engine.lightManager->theLights[i]->diffuse = glm::vec4(0.7f, 1.0f, 0.5f, 1.0f);
        engine.lightManager->theLights[i]->diffuse = glm::vec4(0.7f, 1.0f, 0.5f, 1.0f);
        engine.lightManager->theLights[i]->atten.x = 1.0f; //constant
        engine.lightManager->theLights[i]->atten.y = 0.1f; //linear
        engine.lightManager->theLights[i]->atten.z = 0.04f; //quadratic
        engine.lightManager->theLights[i]->direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);

    }

    //For the ice
    engine.lightManager->theLights[35]->param2.x = 1; //on
    engine.lightManager->theLights[35]->param1.x = 0; //spot
    engine.lightManager->theLights[35]->param1.y = 15; //inner angle
    engine.lightManager->theLights[35]->param1.z = 45; //Outer angle
    engine.lightManager->theLights[35]->position = glm::vec4(-100, 40, 0, 1.0f);
    engine.lightManager->theLights[35]->diffuse = glm::vec4(0.0, 0.5f, 0.7f, 1.0f);
    engine.lightManager->theLights[35]->specular = glm::vec4(0.0f, 0.5f, 0.7f, 1.0f);

    engine.lightManager->theLights[35]->atten.x = 1.0f; //constant
    engine.lightManager->theLights[35]->atten.y = 0.014f; //linear
    engine.lightManager->theLights[35]->atten.z = 0.0007f; //quadratic
    engine.lightManager->theLights[35]->direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);
 
#pragma endregion

#pragma region Extra Lights

    //Extra Lights
    engine.lightManager->theLights[36]->param2.x = 1; //on
    engine.lightManager->theLights[36]->param1.x = 0; //spot
    engine.lightManager->theLights[36]->param1.y = 15; //inner angle
    engine.lightManager->theLights[36]->param1.z = 45; //Outer angle
    engine.lightManager->theLights[36]->position = glm::vec4(-20, 37, 0, 1.0f);
    engine.lightManager->theLights[36]->diffuse = glm::vec4(0.0, 0.5f, 0.7f, 1.0f);
    engine.lightManager->theLights[36]->specular = glm::vec4(0.5f, 0.0f, 0.7f, 1.0f);

    engine.lightManager->theLights[36]->atten.x = 1.0f; //constant
    engine.lightManager->theLights[36]->atten.y = 0.14f; //linear
    engine.lightManager->theLights[36]->atten.z = 0.007f; //quadratic
    engine.lightManager->theLights[36]->direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);

    engine.lightManager->theLights[37]->param2.x = 1; //on
    engine.lightManager->theLights[37]->param1.x = 0; //point
    engine.lightManager->theLights[37]->position = glm::vec4(80.0f , 10.f, -12.0f, 1.0f);
    engine.lightManager->theLights[37]->diffuse = glm::vec4(0.7f, 1.0f, 0.5f, 1.0f);
    engine.lightManager->theLights[37]->diffuse = glm::vec4(0.7f, 1.0f, 0.5f, 1.0f);
    engine.lightManager->theLights[37]->atten.x = 1.0f; //constant
    engine.lightManager->theLights[37]->atten.y = 0.1f; //linear
    engine.lightManager->theLights[37]->atten.z = 0.001f; //quadratic
    engine.lightManager->theLights[37]->direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);



#pragma endregion
#pragma endregion

 
    while (!glfwWindowShouldClose(engine.window))
    {
        engine.Update();
        skyBoxMesh->drawPosition = camera->cameraEye;

        if (billboard->UV_Offset.x >= 1.0f)
        {
            billboard->UV_Offset.x = 0.0f;
        }

        billboard->UV_Offset.x += 0.01f;

    }

    engine.ShutDown();
}
