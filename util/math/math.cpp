#include "math.hpp"
#include <cmath>
#include "util/script/script.hpp"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
namespace insight {

	Vector3 vectors::get_ground_coordinates(Vector2 coords, int tries) {
		float groundZ;
		Vector3 Results;
		for (int i = 0; i < tries; ++i)
		{
			if (i)
			{
				for (float z = 1000.f; z >= 0.f; z -= 100.f)
				{
					STREAMING::REQUEST_COLLISION_AT_COORD(Vector3(coords.x, coords.y, z));
					script::get_current()->yield();
				}
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD(Vector3(coords.x, coords.y, 1000.f), &groundZ, 0, 0))
			{
				return Vector3(Results.x = coords.x, Results.y = coords.y, Results.z = groundZ + 1);

			}
		}
		return Vector3(Results.x = coords.x, Results.y = coords.y, Results.z = 1000.f);
	}

	Vector3 vectors::get_cam_direction(Vector3 rotation) {
		Vector3 tmp;
		tmp.y = rotation.z * 0.0174532924f;
		tmp.x = rotation.x * 0.0174532924f;
		tmp.z = abs(cos(tmp.x));

		return Vector3((-sin(tmp.y)) * tmp.z, (cos(tmp.y)) * tmp.z, sin(tmp.x));
	}
	Vector3 vectors::get_vector_cross(Vector3 a, Vector3 b) {
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
	Vector3 vectors::get_direction() {
		Vector3 Cam = CAM::GET_GAMEPLAY_CAM_ROT(0);
		float radiansZ = Cam.z * 0.0174532924f;
		float radiansX = Cam.x * 0.0174532924f;
		float num = abs((float)cos((double)radiansX));
		Vector3 dir;
		dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
		dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
		dir.z = (float)sin((double)radiansX); // aids but i didnt write that thansk to jew boy
		return dir;
	}

	Vector3 vectors::get_right_vector() {
		Vector3 cam_direction = get_direction();
		Vector3 up_vector = { 0.0f, 0.0f, 1.0f };

		Vector3 right_vector;
		right_vector.x = cam_direction.y;
		right_vector.y = -cam_direction.x;
		right_vector.z = 0.0f;

		// Normalize the right vector
		float magnitude = sqrt(right_vector.x * right_vector.x + right_vector.y * right_vector.y);
		if (magnitude > 0.0f) {
			right_vector.x /= magnitude;
			right_vector.y /= magnitude;
		}

		return right_vector;
	}

	Vector3 vectors::get_front_camera_coordinates_local(int distance)
	{
		Vector3 cameraPosition = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 cameraRotation = CAM::GET_GAMEPLAY_CAM_ROT(0);
		Vector3 cameraDirection = insight::vectors::get()->get_cam_direction(cameraRotation);
		float distanceOffset = distance;
		Vector3 legVector = cameraDirection * distanceOffset;
		Vector3 result = cameraPosition + legVector;
		return result;
	}
	Vector3 vectors::get_front_of_entity(int ent, int distance, int bone)
	{
		bool is_bone = bone != 0;
		Vector3 cameraPosition = is_bone ? ENTITY::GET_ENTITY_BONE_POSTION(ent, 0) : ENTITY::GET_ENTITY_COORDS(ent, 0);
		Vector3 cameraRotation = is_bone ? ENTITY::GET_ENTITY_BONE_ROTATION(ent, bone) : ENTITY::GET_ENTITY_ROTATION(ent, 0);
		cameraRotation.z = cameraRotation.z + 90;
		Vector3 cameraDirection = insight::vectors::get()->get_cam_direction(cameraRotation);
		float distanceOffset = distance;
		Vector3 legVector = cameraDirection * distanceOffset;
		Vector3 result = cameraPosition + legVector;
		return result;
	}
	Vector3 vectors::get_front_camera_coordinates(int distance, Cam camera)
	{
		Vector3 cameraPosition = CAM::GET_CAM_COORD(camera);
		Vector3 cameraRotation = CAM::GET_CAM_ROT(camera, 0);
		Vector3 cameraDirection = insight::vectors::get()->get_cam_direction(cameraRotation);
		float distanceOffset = distance;
		Vector3 legVector = cameraDirection * distanceOffset;
		Vector3 result = cameraPosition + legVector;
		return result;
	}

	int get_360_around_entity_iterator = 0;
	Vector3 vectors::get_360_vec_around_entity_in_world(int ent, float far_distance, float up_down_distance, int angles)
	{
		const int numAngles = angles;
		const float angleIncrement = 360.0f / numAngles;

		int angleIndex = get_360_around_entity_iterator % numAngles;
		float angle = angleIndex * angleIncrement;
		get_360_around_entity_iterator++;

		float angleInRadians = angle * (M_PI / 180.0f);
		float x = far_distance * cos(angleInRadians);
		float y = far_distance * sin(angleInRadians);

		return ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, Vector3(x, y, 0.0f + up_down_distance));
	}
	int get_360_around_entity_iterator2 = 0;
	Vector3 vectors::get_360_vec_around_coord(const Vector3& position, float far_distance, float up_down_distance, int angles)
	{
		const int numDirections = angles;
		const float angleIncrement = 360.0f / numDirections;
		float angle = get_360_around_entity_iterator2 * angleIncrement;
		get_360_around_entity_iterator2 = (get_360_around_entity_iterator2 + 1) % numDirections;

		float angleInRadians = angle * (M_PI / 180.0f);
		float x = far_distance * cos(angleInRadians);
		float y = far_distance * sin(angleInRadians);

		return   Vector3(x + position.x, y + position.y, up_down_distance + position.z);
	}
	Vector3 vectors::get_360_vec_around_coord(const Vector3& position, float far_distance, float up_down_distance, int angles, int& iterator)
	{
		const int numDirections = angles;
		const float angleIncrement = 360.0f / numDirections;
		float angle = iterator * angleIncrement;
		iterator = (iterator + 1) % numDirections;

		float angleInRadians = angle * (M_PI / 180.0f);
		float x = far_distance * cos(angleInRadians);
		float y = far_distance * sin(angleInRadians);

		return Vector3(x + position.x, y + position.y, up_down_distance + position.z);
	}
	Vector3 vectors::get_360_iterator_vec_around_coord(const Vector3& position, float far_distance, float up_down_distance, int& get_360_around_entity_iterator, int angles)
	{
		const int numDirections = angles;
		const float angleIncrement = 360.0f / numDirections;
		float angle = get_360_around_entity_iterator * angleIncrement;
		get_360_around_entity_iterator = (get_360_around_entity_iterator + 1) % numDirections;

		float angleInRadians = angle * (M_PI / 180.0f);
		float x = far_distance * cos(angleInRadians);
		float y = far_distance * sin(angleInRadians);

		return Vector3(x + position.x, y + position.y, up_down_distance + position.z);
	}
	Vector3 vectors::get_custom_angle_vec_around_coord(const Vector3& position, float far_distance, float up_down_distance, int num_angles, float target_angle_degrees)
	{
		const float angleIncrement = 360.0f / num_angles;

		int custom_iterator = static_cast<int>(target_angle_degrees / angleIncrement);

		float angleInRadians = target_angle_degrees * (M_PI / 180.0f);
		float x = far_distance * cos(angleInRadians);
		float y = far_distance * sin(angleInRadians);

		return Vector3(x + position.x, y + position.y, up_down_distance + position.z);
	}
	Vector3 vectors::get_waypoint_coordinates()
	{
		Vector3 coordinates;
		int waypointBlip = HUD::GET_FIRST_BLIP_INFO_ID(HUD::GET_WAYPOINT_BLIP_ENUM_ID());

		if (HUD::DOES_BLIP_EXIST(waypointBlip))
		{
			if (HUD::GET_BLIP_INFO_ID_TYPE(waypointBlip) == 4)
			{
				coordinates = HUD::GET_BLIP_INFO_ID_COORD(waypointBlip);
				return coordinates;
			}

			waypointBlip = HUD::GET_NEXT_BLIP_INFO_ID(HUD::GET_WAYPOINT_BLIP_ENUM_ID());
		}

		static Vector3 defaultCoordinates;
		return defaultCoordinates;
	}
	Vector3 vectors::get_blip_coordinates(int blip)
	{
		Vector3 coordinates;
		int blipe = HUD::GET_FIRST_BLIP_INFO_ID(blip);

		if (HUD::DOES_BLIP_EXIST(blipe))
		{
			if (HUD::GET_BLIP_INFO_ID_TYPE(blipe) == 4)
			{
				coordinates = HUD::GET_BLIP_INFO_ID_COORD(blipe);
				return coordinates;
			}

			blipe = HUD::GET_NEXT_BLIP_INFO_ID(blipe);
		}

		static Vector3 defaultCoordinates;
		return defaultCoordinates;
	}
	float vectors::get_vector_length(Vector3 vector)
	{
		float length = std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		return length;
	}
	std::uint32_t vectors::get_random_vector(std::vector<std::uint32_t> arr) {
		int size = arr.size();
		if (size == 0) {
			return 0;
		}
		int randomIndex = rand() % size;
		return arr[randomIndex];
	}

	float vectors::getModelLength(Hash model)
	{
		Vector3 front, back;
		MISC::GET_MODEL_DIMENSIONS(model, &front, &back);
		float length = get_vector_length(front - back);
		return length;
	}

	std::vector<std::uint32_t> vectors::get_rainbow_fade_colors(float speed)
	{
		static std::uint32_t cnt = 0;

		// Calculate the frequency based on the given speed.
		constexpr float base_freq = 0.01f;
		float freq = base_freq * speed;

		// Calculate the color values.
		Vector4 color = {
			std::sin(freq * cnt + 0) * 127 + 128,
			std::sin(freq * cnt + 2) * 127 + 128,
			std::sin(freq * cnt + 4) * 127 + 128,
			255
		};

		// Increment the counter and handle overflow.
		if (cnt++ >= std::numeric_limits<std::uint32_t>::max())
		{
			cnt = 0;
		}

		return { static_cast<uint32_t>(color.x), static_cast<uint32_t>(color.y),
				 static_cast<uint32_t>(color.z), static_cast<uint32_t>(color.w) };
	}
	float vectors::PointToPointYaw(Vector3 startPos, Vector3 targetPos)
	{
		Vector3 direction = targetPos - startPos;
		float yaw = std::atan2(direction.y, direction.x) * 180.0f / M_PI;
		return yaw;
	}
	Vector3 vectors::lerp(const Vector3& start, const Vector3& end, float t) {
		t = std::max(0.0f, std::min(t, 1.0f));
		float x = start.x + t * (end.x - start.x);
		float y = start.y + t * (end.y - start.y);
		float z = start.z + t * (end.z - start.z);

		return Vector3(x, y, z);
	}
	Vector3 vectors::calculate_rotation_from_v3s(const Vector3 pos, const Vector3 next_pos)
	{
		Vector3 direction = next_pos;
		direction.x -= pos.x;
		direction.y -= pos.y;
		direction.z -= pos.z;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
		if (length != 0.0f) {
			direction.x /= length;
			direction.y /= length;
			direction.z /= length;
		}
		float yaw = std::atan2(direction.y, direction.x);
		float pitch = std::atan2(-direction.z, std::sqrt(direction.x * direction.x + direction.y * direction.y));
		float roll = 0.0f;
		float yaw_degrees = yaw * 180.0f / M_PI;
		float pitch_degrees = pitch * 180.0f / M_PI;
		float roll_degrees = roll * 180.0f / M_PI;
		return { yaw_degrees, pitch_degrees, roll_degrees };
	}
}
