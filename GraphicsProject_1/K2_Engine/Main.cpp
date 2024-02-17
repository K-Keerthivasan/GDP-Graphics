#include <fstream>

#include "EngineControls/cWorldConfiguration.h"
#include "GLWF_CallBacks.h"
#include "InputHandling.h"
 

//GetRandom FLoat
float getRandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

 

GLFWwindow* window;
cWorldConfiguration w_game_engine;

void LoadModelsFromTextFile(const std::string& filename, cWorldConfiguration& w_game_engine)

{
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	std::map<std::string, bool> loadedModels;

	std::string addingNewModel;
	float translateX, translateY, translateZ;//For position
	float rotatex, rotatey, rotatez;//For rotation
	float red, green, blue;//For Colour
	float scale;
	int rgbToggle;
 
	

	//Fstream read file loop
			while(file >> addingNewModel >>translateX>>translateY>>translateZ>>rotatex>>rotatey>>rotatez>>red>>green>>blue>>scale>> rgbToggle)
	{
			if (!loadedModels[addingNewModel]) {
				std::string modelFileName;

				//Asteroid Props
				if(addingNewModel =="AsteroidExtra1")
				{
					modelFileName = "Asteroid_015_x10_flatshaded_xyz_n_rgba.ply";
				}
				else if(addingNewModel=="Asteroid2Extra2")
				{
					modelFileName = "Asteroid_011_x10_flatshaded_xyz_n_rgba.ply";
				}


				if (addingNewModel == "AsteroidExtra3")
				{
					modelFileName = "Asteroid_015_x10_flatshaded_xyz_n_rgba.ply";
				}
				else if (addingNewModel == "AsteroidExtra4")
				{
					modelFileName = "Asteroid_011_x10_flatshaded_xyz_n_rgba.ply";
				}

				if (addingNewModel == "AsteroidExtra5")
				{
					modelFileName = "Asteroid_015_x10_flatshaded_xyz_n_rgba.ply";
				}
				else if (addingNewModel == "AsteroidExtra6")
				{
					modelFileName = "Asteroid_011_x10_flatshaded_xyz_n_rgba.ply";
				}



				//SpaceShip Models
				else if (addingNewModel == "BirdsOfPrey")
				{
					modelFileName = "BirdOfPrey_xyz_n_rgba_centred_facing_on_positive_Z.ply";
				}

				else if (addingNewModel == "MotherShip")
				{
					modelFileName = "SM_Ship_Massive_Transport_01_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply";
				}

				else if (addingNewModel == "Shipyard")
				{
					modelFileName = "Lisse_mobile_shipyard_xyz_n_rgba_uv.ply";
				}


				else if (addingNewModel == "modCommand")
				{
					modelFileName = "mod-command_xyz_n_rgba_uv.ply";
				}

				//Props

				else if (addingNewModel == "Bunny")
				{
					modelFileName = "bun_zipper_res2.ply";
				}

				else if (addingNewModel == "Bed")
				{
					modelFileName = "SM_Prop_Bed_02_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply";
				}

				else if (addingNewModel == "Cabinet")
				{
					modelFileName = "SM_Prop_Cabinets_02_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply";
				}

				else if (addingNewModel == "Desk")
				{
					modelFileName = "SM_Prop_Desk_Lab_02_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply";
				}



			 w_game_engine.Load3DModels(modelFileName, addingNewModel, 0.0f, 0.0f, 0.0f);

			loadedModels[addingNewModel] = true; // Mark the model as loaded
			}


			w_game_engine.ResizeMesh(addingNewModel, scale);

				w_game_engine.RotateMesh(addingNewModel, 10,rotatex, rotatex, rotatez);

				if (rgbToggle == 1) {
					w_game_engine.ChangeColor(addingNewModel, red, green, blue, true);
				}
				else {
					// Turn off RGB color if rgbToggle is 0
					w_game_engine.ChangeColor(addingNewModel, 0.0f, 0.0f, 0.0f, false);
				}
 
			 w_game_engine.TranslateMesh(addingNewModel, translateX, translateY, translateZ);


	}


	file.close();
}


  
int main()
{
  
	int result = 0;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

 

	result = w_game_engine.InitializeGameEngine();

	if (result != 0)
		return -1;

	w_game_engine.AdjustCameraPosition(750, 40.0f, 10.0f);
 

	//----------------------------------------------------------------

	//Loading models from models_attributes.txt
	LoadModelsFromTextFile("models_attributes.txt", w_game_engine);
	 

	//Loading Lights
	w_game_engine.CreateNewLight(0, 0.0f, 10.0f, 0.0f);

	int light_id = 0;

 
	//Spot Lights
	light_id = 0;

	w_game_engine.CreateNewLight(light_id, 0.0, 0.0, 0.0);
	w_game_engine.SetLightType(light_id, 1.0f);
	w_game_engine.AdjustLightIntensity(light_id, 0.07f, 0.0f);
	w_game_engine.ModifyLightAngle(light_id, 50.0, 200.0);
	w_game_engine.PositionLightSource(light_id, 0.0f, 65.0f, -70.0f);



	light_id = 1;

	w_game_engine.CreateNewLight(light_id, 0.0, 0.0, 0.0);
	w_game_engine.SetLightType(light_id, 1.0f);
	w_game_engine.AdjustLightIntensity(light_id, 0.07f, 0.0f);
	w_game_engine.ModifyLightAngle(light_id, 50.0, 200.0);
	w_game_engine.PositionLightSource(light_id, 0.0f, -35.0f, 60.0f);
 

	//Point Lights
	light_id = 2;

	w_game_engine.CreateNewLight(light_id, 0.0, 0.0, 0.0);
	w_game_engine.SetLightType(light_id, 0.0f);
	w_game_engine.AdjustLightIntensity(light_id, 0.05f, 0.0f);
	w_game_engine.ModifyLightAngle(light_id, 250.0, 500.0);
	w_game_engine.PositionLightSource(light_id, 300.0f, 200.0f, 0.0f);

	light_id = 3;

	w_game_engine.CreateNewLight(light_id, 0.0, 0.0, 0.0);
	w_game_engine.SetLightType(light_id, 0.0f);
	w_game_engine.AdjustLightIntensity(light_id, 0.05f, 0.0f);
	w_game_engine.ModifyLightAngle(light_id, 250.0, 500.0);
	w_game_engine.PositionLightSource(light_id, -300.0f, 100.0f, 0.0f);



	light_id = 4;

	w_game_engine.CreateNewLight(light_id, 0.0, 0.0, 0.0);
	w_game_engine.SetLightType(light_id, 0.0f);
	w_game_engine.AdjustLightIntensity(light_id, 0.07f, 0.0f);
	w_game_engine.ModifyLightAngle(light_id, 250.0, 500.0);
	w_game_engine.PositionLightSource(light_id, 300.0f, 50.0f, 0.0f);

 
	result = w_game_engine.GameEngineMain(window);

	if (result != 0)
		return 0;
}