#pragma once

#include <string>

#include <ScriptHookV/inc/main.h>
#include <ScriptHookV/inc/types.h>
#include <ScriptHookV/inc/natives.h>

#include "ScreenRecorder.h"
#include "DataFilter.h"

class DataRecorder
{
	public:
		DataRecorder::DataRecorder(std::string recordingsRelativePath);

		void DataRecorder::Update(Vector3 cameraPosition, Vector3 cameraRotation);

		void DataRecorder::Enable(std::string cutsceneName);
		void DataRecorder::Disable();

	private:
		std::string recordingsRelativePath;

		FILE* dataRecorderFilePeds;
		FILE* dataRecorderFileCamera;
		ScreenRecorder* screenRecorder;

		float positionPedMaxDistance = 20.0;

		bool enabled;

		int currentFrame;
};

