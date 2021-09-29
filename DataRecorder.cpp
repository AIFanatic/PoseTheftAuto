#include "DataRecorder.h"

DataRecorder::DataRecorder(std::string recordingsRelativePath) {
	this->recordingsRelativePath = recordingsRelativePath;

	CreateDirectory(recordingsRelativePath.c_str(), NULL);
}

void DataRecorder::Enable(std::string cutsceneName) {
	std::string cutscenePath = this->recordingsRelativePath + cutsceneName;
	CreateDirectory(cutscenePath.c_str(), NULL);

	std::string csvFilenamePeds = this->recordingsRelativePath + cutsceneName + "/peds.csv";
	this->dataRecorderFilePeds = fopen(csvFilenamePeds.c_str(), "a");
	fprintf(this->dataRecorderFilePeds, "frame, character, bone, x, y, z, x_2d, y_2d, occluded\n");

	std::string csvFilenameCamera = this->recordingsRelativePath + cutsceneName + "/camera.csv";
	this->dataRecorderFileCamera = fopen(csvFilenameCamera.c_str(), "a");
	fprintf(this->dataRecorderFileCamera, "frame, x, y, z, rot_x, rot_y, rot_z\n");

	this->currentFrame = 0;

	// TODO: _GET_ACTIVE_SCREEN_RESOLUTION
	std::string framesRelativePath = this->recordingsRelativePath + cutsceneName + "/frames/";
	CreateDirectory(framesRelativePath.c_str(), NULL);
	screenRecorder = new ScreenRecorder(framesRelativePath, 1920, 1080);

	this->enabled = true;
}

void DataRecorder::Disable() {
	fclose(this->dataRecorderFilePeds);
	fclose(this->dataRecorderFileCamera);

	this->enabled = false;
}

void DataRecorder::Update(Vector3 cameraPosition, Vector3 cameraRotation) {
	if (!this->enabled) return;

	this->currentFrame++;

	std::vector<PedJoints> pedJoints = DataFilter::GetPedsJoints(cameraPosition);

	// Record peds
	for (auto& ped : pedJoints) {
		for (auto& pedJoint : ped.joints) {
			fprintf(this->dataRecorderFilePeds, "%i, %i, %i, %f, %f, %f, %f, %f, %i\n",
			this->currentFrame, ped.modelHash, pedJoint.boneId, pedJoint.position.x, pedJoint.position.y, pedJoint.position.z, pedJoint.x_2d, pedJoint.y_2d, pedJoint.occluded);
		}
	}

	// Record camera
	fprintf(this->dataRecorderFileCamera, "%i, %f, %f, %f, %f, %f, %f\n",
	this->currentFrame, cameraPosition.x, cameraPosition.y, cameraPosition.z, cameraRotation.x, cameraRotation.y, cameraRotation.z);

	this->screenRecorder->Record_Frame(this->currentFrame);
}