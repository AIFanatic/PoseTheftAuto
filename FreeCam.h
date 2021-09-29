#pragma once
#include <ScriptHookV/inc/types.h>
#include <ScriptHookV/inc/natives.h>
#include "keyboard.h"

#include <cmath>

class FreeCam
{
	public:
		FreeCam();
		void FreeCam::Enable(int startDelay = 1);
		void FreeCam::Disable();
		void FreeCam::Update();
		bool FreeCam::IsEnabled();

		Vector3 cameraRotationOffset;
		Vector3 cameraPosition;

	private:
		void FreeCam::_Enable();
		void FreeCam::GetCameraBasis(Cam camera, Vector3* foward, Vector3* right, Vector3* up);
		Vector3 FreeCam::rot_to_direction(Vector3* rot);
		Vector3 FreeCam::cross(Vector3 a, Vector3 b);

		Vector3 playerPosition;
		bool enabled;
		Cam camera;

		int startDelay;
		bool hasStarted;

		enum CONTROLS_MAP {
			LookLeftRight = 1,
			LookUpDown = 2,
			MoveUpOnly = 32,
			MoveDownOnly = 33,
			MoveLeftOnly = 34,
			MoveRightOnly = 35
		};
};

