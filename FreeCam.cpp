#include "FreeCam.h"

FreeCam::FreeCam() {
}

void FreeCam::_Enable() {
	Vector3 position = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 rotation = CAM::GET_GAMEPLAY_CAM_ROT(0);
	float fov = CAM::GET_GAMEPLAY_CAM_FOV();

	this->camera = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, fov, 1, 2);
	this->cameraRotationOffset = Vector3();

	CAM::RENDER_SCRIPT_CAMS(true, 0, 3000, 1, 0);
	CAM::SET_CAM_ACTIVE(this->camera, true);
}

void FreeCam::Enable(int startDelay) {
	this->enabled = true;

	this->playerPosition = CAM::GET_GAMEPLAY_CAM_COORD();

	this->startDelay = startDelay * 60;
}

bool FreeCam::IsEnabled() {
	return this->hasStarted;
}

void FreeCam::Disable() {
	CAM::DESTROY_CAM(this->camera, 0);
	CAM::RENDER_SCRIPT_CAMS(false, 0, 3000, 1, 0);

	STREAMING::_SET_FOCUS_AREA(this->playerPosition.x, this->playerPosition.y, this->playerPosition.z, 0, 0, 0);

	this->enabled = false;
	this->hasStarted = false;
}

Vector3 FreeCam::rot_to_direction(Vector3* rot)
{
	float radiansZ = rot->z * 0.0174532924f;
	float radiansX = rot->x * 0.0174532924f;
	float num = std::abs((float)std::cos((double)radiansX));
	Vector3 dir;
	dir.x = (float)((double)((float)(-(float)std::sin((double)radiansZ))) * (double)num);
	dir.y = (float)((double)((float)std::cos((double)radiansZ)) * (double)num);
	dir.z = (float)std::sin((double)radiansX);
	return dir;

}

Vector3 FreeCam::cross(Vector3 a, Vector3 b) {
	float ax = a.x;
	float ay = a.y; 
	float az = a.z;

	float bx = b.x;
	float by = b.y;
	float bz = b.z;

	Vector3 result = Vector3();
	result.x = ay * bz - az * by;
	result.y = az * bx - ax * bz;
	result.z = ax * by - ay * bx;

	return result;
}

void FreeCam::GetCameraBasis(Cam camera, Vector3 *forward, Vector3 *right, Vector3 *up) {
	Vector3 rot = CAM::GET_CAM_ROT(this->camera, 0);
	*forward = rot_to_direction(&rot);

	Vector3 worldRight = Vector3();
	worldRight.z = 1;

	Vector3 worldUp = Vector3();
	worldUp.x = 1;

	*right = cross(*forward, worldRight);
	*up = cross(*forward, worldUp);
}

void FreeCam::Update() {
	if (!this->enabled) return;

	if (this->startDelay > 0 && !this->hasStarted) {
		this->startDelay--;
		if (this->startDelay == 0) {
			this->_Enable();
			this->hasStarted = true;
		}
		return;
	}
	if (!this->hasStarted) return;
	if (!this->camera) return;

	CAM::RENDER_SCRIPT_CAMS(true, false, 1, false, false);
	CAM::STOP_CUTSCENE_CAM_SHAKING();
	CUTSCENE::CAN_SET_EXIT_STATE_FOR_CAMERA(false);

	Vector3 position = CAM::GET_CAM_COORD(this->camera);
	Vector3 forward;
	Vector3 right;
	Vector3 up;

	GetCameraBasis(this->camera, &forward, &right, &up);

	float speed = 5;
	if (GetKeyState(VK_SHIFT) & 0x8000) {
		speed *= 10;
	}
	if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, MoveUpOnly)) {
		position.x += (forward.x * 0.1 * speed);
		position.y += (forward.y * 0.1 * speed);
		position.z += (forward.z * 0.1 * speed);
	}
	if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, MoveDownOnly)) {
		position.x -= (forward.x * 0.1 * speed);
		position.y -= (forward.y * 0.1 * speed);
		position.z -= (forward.z * 0.1 * speed);
	}
	if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, MoveRightOnly)) {
		position.x += (right.x * 0.1 * speed);
		position.y += (right.y * 0.1 * speed);
		position.z += (right.z * 0.1 * speed);
	}
	if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, MoveLeftOnly)) {
		position.x -= (right.x * 0.1 * speed);
		position.y -= (right.y * 0.1 * speed);
		position.z -= (right.z * 0.1 * speed);
	}

	this->cameraRotationOffset.x -= CONTROLS::GET_DISABLED_CONTROL_NORMAL(0, LookUpDown) * 8;
	this->cameraRotationOffset.z -= CONTROLS::GET_DISABLED_CONTROL_NORMAL(0, LookLeftRight) * 8;

	this->cameraPosition = position;

	CAM::SET_CAM_ROT(this->camera, this->cameraRotationOffset.x, this->cameraRotationOffset.y, this->cameraRotationOffset.z, 0);
	CAM::SET_CAM_COORD(this->camera, position.x, position.y, position.z);

	STREAMING::_SET_FOCUS_AREA(position.x, position.y, position.z, 0, 0, 0);
}