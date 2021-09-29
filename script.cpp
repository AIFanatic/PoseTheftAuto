/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2015
*/

#include "script.h"
#include "keyboard.h"

#include <string>
#include "pta_enums.h"

#include <fstream>
#include <iostream>
#include "FreeCam.h"
#include "cutscene_list.h"
#include "MenuV2.h"
#include "DataRecorder.h"
#include "DataFilter.h"

const int max_number_of_peds = 1024;

FILE* logFile;
DataRecorder dataRecorder = DataRecorder("./pta/");
FreeCam freeCam = FreeCam();
MenuHandler* menuHandler;
std::string menuTitle = "Pose Theft Auto";

bool modEnabled = false;
bool visualDebugEnabled = false;
bool dataRecorderEnabled = false;

std::string currentCutscene = "";

void draw_box_2d_from_3d(float x, float y, float z, float w, float h, int color[4]) {
	float x_2d, y_2d;
	if (GRAPHICS::_WORLD3D_TO_SCREEN2D(x, y, z, &x_2d, &y_2d)) {
		GRAPHICS::DRAW_RECT(x_2d, y_2d, w, h, color[0], color[1], color[2], color[3]);
	}
}

void visualDebug() {
	Vector3 cam_coords = freeCam.IsEnabled() ? freeCam.cameraPosition : CAM::GET_GAMEPLAY_CAM_COORD();

	std::vector<PedJoints> pedJoints = DataFilter::GetPedsJoints(cam_coords);

	for (auto & ped : pedJoints) {
		for (auto & pedJoint : ped.joints) {
			float boxSize = 0.0025f;

			int color[4] = { 0, 255, 0, 255 };
			if (pedJoint.occluded) {
				color[0] = 255;
				color[1] = 0;
			}
			draw_box_2d_from_3d(pedJoint.position.x, pedJoint.position.y, pedJoint.position.z, boxSize, boxSize, color);
		}
	}
}

void recordData() {
	menuHandler->disableMenuThisFrame();

	if (currentCutscene == "") {
		Vector3 cameraPosition = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 cameraRotation = CAM::GET_GAMEPLAY_CAM_ROT(0);
		dataRecorder.Update(cameraPosition, cameraRotation);
	}
	else {
		dataRecorder.Update(freeCam.cameraPosition, freeCam.cameraRotationOffset);
	}
}

void update()
{
	if (!modEnabled) return;

	if (visualDebugEnabled) {
		visualDebug();
	}

	if (dataRecorderEnabled) {
		recordData();
	}

	menuHandler->update();
	freeCam.Update();
}

void CallbackMenuPlayCutscene(MenuNode* node) {
	CUTSCENE::REQUEST_CUTSCENE(strdup(node->label.c_str()), 0);
	CUTSCENE::START_CUTSCENE(0);
	
	// Enable freecam after 3s, this allows the scene to fully load in order to have valid gameplay position
	freeCam.Enable(3);

	currentCutscene = node->label;
}

void CallbackMenuStopCutscene(MenuNode* node) {
	CUTSCENE::STOP_CUTSCENE(true);

	freeCam.Disable();

	currentCutscene = "";
}

void CallbackMenuVisualDebug(MenuNode* node) {
	visualDebugEnabled = !visualDebugEnabled;

	if (visualDebugEnabled) {
		node->label = "Disable visual debug";
		freeCam.Enable(1);
	}
	else {
		node->label = "Enable visual debug";
		freeCam.Disable();
	}
}

void CallbackMenuDataRecorder(MenuNode* node) {
	dataRecorderEnabled = !dataRecorderEnabled;

	if (dataRecorderEnabled) {
		node->label = "Stop recording data";

		if (currentCutscene == "") {
			// TODO: Pass time or something if not in cutscene
			dataRecorder.Enable("gameplay");
		}
		else {
			dataRecorder.Enable(currentCutscene);
		}
	}
	else {
		node->label = "Start recording data";

		dataRecorder.Disable();
	}
}

void main()
{
	logFile = fopen("PoseTheftAuto.log", "a");

	MenuNode *menu = new MenuNode("root", NULL);
		MenuNode *cutscene = menu->Add("Play cutscene");
		MenuNode *visualDebug = menu->Add("Enable visual debug", CallbackMenuVisualDebug);
		MenuNode* dataRecorder = menu->Add("Start recording data", CallbackMenuDataRecorder);

	cutscene->Add("STOP CUTSCENE", CallbackMenuStopCutscene);
	cutscene->Add("armenian_1_mcs_1", CallbackMenuPlayCutscene);
	for (int i = 0; i < cutscene_list_length; i++) {
		cutscene->Add(cutscene_list[i], CallbackMenuPlayCutscene);
	}

	Menu menuRoot = Menu(menu);

	menuHandler = &MenuHandler(&menuRoot, menuTitle);

	while (true)
	{
		if (IsKeyJustUp(VK_F5))
		{
			modEnabled = !modEnabled;
		}

		update();
		WAIT(0);
	}
}

void ScriptMain()
{
	main();
}

void ScriptUnregister()
{
}