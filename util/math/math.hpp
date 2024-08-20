#pragma once
#include "natives.hpp"

namespace insight {
    class vectors {
    public:
        Vector3 get_ground_coordinates(Vector2 coords, int tries = 10);
		Vector3 get_cam_direction(Vector3 rotation);
        Vector3 get_vector_cross(Vector3 a, Vector3 b);
        Vector3 get_direction();
        Vector3 get_right_vector();
        Vector3 get_front_camera_coordinates_local(int distance);
        Vector3 get_front_of_entity(int ent, int distance, int bone = 0);
        Vector3 get_front_camera_coordinates(int distance, Cam camera);
        Vector3 get_360_vec_around_entity_in_world(int ent, float far_distance, float up_down_distance, int angles);
        Vector3 get_360_vec_around_coord(const Vector3& position, float far_distance, float up_down_distance, int angles);
        Vector3  get_360_vec_around_coord(const Vector3& position, float far_distance, float up_down_distance, int angles, int& iterator);
        Vector3 get_360_iterator_vec_around_coord(const Vector3& position, float far_distance, float up_down_distance, int& get_360_around_entity_iterator, int angles);
        Vector3 get_custom_angle_vec_around_coord(const Vector3& position, float far_distance, float up_down_distance, int num_angles, float target_angle_degrees);
        Vector3 get_waypoint_coordinates();
        Vector3 get_blip_coordinates(int blip);
        float getModelLength(Hash model);
        float get_vector_length(Vector3 vector);
        std::uint32_t get_random_vector(std::vector<std::uint32_t> arr);
        std::vector<std::uint32_t> get_rainbow_fade_colors(float speed = 1.6f);
        float PointToPointYaw(Vector3 startPos, Vector3 targetPos);
        Vector3 lerp(const Vector3& start, const Vector3& end, float t);
        Vector3 calculate_rotation_from_v3s(const Vector3 start, const Vector3 next_pos);
    public:
        static vectors* get() {
            static vectors i;
            return &i;
        }
    };
    class mathfloat {
    public:
         float dtr(float degs) {
            return degs * 3.141592653589793f / 180.f;
        }

    public:
        static mathfloat* get() {
            static mathfloat i;
            return &i;
        }
    };
}