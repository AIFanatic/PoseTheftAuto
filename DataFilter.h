#pragma once

#include <ScriptHookV/inc/types.h>
#include <ScriptHookV/inc/natives.h>

#include <vector>
#include "pta_enums.h"

struct PedJoint {
	int boneId;
	Vector3 position;
	float x_2d;
	float y_2d;
	bool occluded;
};

struct PedJoints {
	Ped ped;
	Hash modelHash;
	std::vector<PedJoint> joints;
};

class DataFilter {
	public:
		static std::vector<PedJoints> GetPedsJoints(Vector3 cameraPosition) {
			EnableCollisions();

			std::vector<PedJoints> allPedJoints;

			const int max_number_of_peds = 64;
			const float positionPedMaxDistance = 20.0;

			Ped peds[max_number_of_peds];
			int number_of_peds = worldGetAllPeds(peds, max_number_of_peds);

			// scan all the pedestrians taken
			for (int i = 0; i < number_of_peds; i++) {
				//Ped ped = playerPed;
				Ped ped = peds[i];
				if (!ENTITY::IS_AN_ENTITY(ped)) continue;
				if (!ENTITY::IS_ENTITY_A_PED(ped)) continue;
				if (!ENTITY::IS_ENTITY_ON_SCREEN(ped)) continue;
				if (!ENTITY::IS_ENTITY_VISIBLE(ped)) continue;
				if (!PED::IS_PED_HUMAN(ped)) continue;

				Vector3 ped_coords = ENTITY::GET_ENTITY_COORDS(ped, TRUE);

				float dist = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(cameraPosition.x, cameraPosition.y, cameraPosition.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE);
				if (dist > positionPedMaxDistance) continue;

				Hash modelHash = ENTITY::GET_ENTITY_MODEL(ped);

				PedJoints pedJoints;
				pedJoints.ped = ped;
				pedJoints.modelHash = modelHash;

				for (int n = 0; n < ped_cs_bones_index_len; n++) {
					int boneId = ped_cs_bones_index[n];
					int boneIndex = PED::GET_PED_BONE_INDEX(ped, boneId);
					if (boneIndex < 0) continue;

					Vector3 joint_coords = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(ped, boneIndex);

					bool occluded = IsPointOccluded(cameraPosition, joint_coords, ped);

					float x2d, y2d;
					bool pointOnScreen = GRAPHICS::_WORLD3D_TO_SCREEN2D(joint_coords.x, joint_coords.y, joint_coords.z, &x2d, &y2d);

					PedJoint pedJoint;
					pedJoint.position = joint_coords;
					pedJoint.occluded = occluded;
					pedJoint.boneId = boneId;
					pedJoint.x_2d = x2d;
					pedJoint.y_2d = y2d;

					pedJoints.joints.push_back(pedJoint);
				}

				allPedJoints.push_back(pedJoints);
			}

			return allPedJoints;
		}

	private:
		static void DataFilter::EnableCollisions() {
			const int max_number_of_entities = 128;

			Entity entities[max_number_of_entities];
			int number_of_vehicles = worldGetAllVehicles(entities, max_number_of_entities);

			for (int i = 0; i < number_of_vehicles; i++) {
				Entity entity = entities[i];
				ENTITY::SET_ENTITY_COLLISION(entity, true, true);
			}

			Entity objects[max_number_of_entities];
			int number_of_objects = worldGetAllObjects(objects, max_number_of_entities);

			for (int i = 0; i < number_of_objects; i++) {
				Entity entity = objects[i];
				ENTITY::SET_ENTITY_COLLISION(entity, true, true);
			}

			Ped peds[max_number_of_entities];
			int number_of_peds = worldGetAllPeds(peds, max_number_of_entities);

			for (int i = 0; i < number_of_peds; i++) {
				Entity entity = peds[i];
				ENTITY::SET_ENTITY_COLLISION(entity, true, true);
			}
		}

		static bool DataFilter::IsPointOccluded(Vector3 cameraPosition, Vector3 point, Ped ped) {
			float x2d, y2d;
			bool pointOnScreen = GRAPHICS::_WORLD3D_TO_SCREEN2D(point.x, point.y, point.z, &x2d, &y2d);

			if (!pointOnScreen) return true;

			BOOL occluded_world;
			Vector3 endCoords1, surfaceNormal1;
			Entity entity1;
			int rayJointToCamera = WORLDPROBE::_CAST_RAY_POINT_TO_POINT(cameraPosition.x, cameraPosition.y, cameraPosition.z, point.x, point.y, point.z, (~0 ^ (8 | 4)), ped, 7);
			WORLDPROBE::_GET_RAYCAST_RESULT(rayJointToCamera, &occluded_world, &endCoords1, &surfaceNormal1, &entity1);

			if (occluded_world) return true;

			//finding the versor (dx, dy, dz) pointing from the joint to the cam
			float joint2cam_distance = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(
				point.x, point.y, point.z,
				cameraPosition.x, cameraPosition.y, cameraPosition.z, 1
			);
			float dx = (cameraPosition.x - point.x) / joint2cam_distance;
			float dy = (cameraPosition.y - point.y) / joint2cam_distance;
			float dz = (cameraPosition.z - point.z) / joint2cam_distance;

			BOOL occluded_self;
			Vector3 endCoords2, surfaceNormal2;
			Entity entity2;
			int rayHandle = WORLDPROBE::_CAST_RAY_POINT_TO_POINT(cameraPosition.x, cameraPosition.y, cameraPosition.z, point.x + 0.2f * dx, point.y + 0.2f * dy, point.z + 0.2f * dz, 8, 0, 7);
			WORLDPROBE::_GET_RAYCAST_RESULT(rayHandle, &occluded_self, &endCoords2, &surfaceNormal2, &entity2);

			if (occluded_self) return true;

			return false;
		}
};

