#pragma once


#include "cheat/features/globals.hpp"


namespace insight
{
    struct SuperProjectileData {
        timer timer;
        Vector3 vec;
    };
    struct SuperProjectileConfig {
        int objectType;
        int explosionType;
        int explosionTag;
        float explosionRadius;
        int explosionDamage;
        bool explosionSound;
        bool explosionInvisible;
        float explosionCameraShake;
        int time;
        bool explode_timing_mode;
        SuperProjectileConfig()
            : objectType(290600267),
            explosionType(1),
            explosionTag(9999),
            explosionRadius(1.0f),
            explosionDamage(1),
            explosionSound(true),
            explosionInvisible(false),
            explosionCameraShake(1.0f),
            time(0),
            explode_timing_mode(false)
        {
        }

        void setObjectType(int type) {
            objectType = type;
        }
    };

    class SuperProjectileManager {
    public:
        SuperProjectileManager() {}

        void setConfig(const SuperProjectileConfig& config) {
            this->config = config;
        }

        void update() {
            if (toggle) {
                Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(globals::h_local_ped_pos(), 2, config.objectType, 0, 0, 1);
                if (ENTITY::GET_ENTITY_ATTACHED_TO(obj) != globals::h_local_ped()) {
                    Entity new_entity = obj;
                    if (super_grenade_timers.find(new_entity) == super_grenade_timers.end()) {
                        Vector3 pos = { 0, 0, 0 };
                        super_grenade_timers.emplace(new_entity, SuperProjectileData(timer(std::chrono::milliseconds(config.time)), pos));
                    }
                }

                for (auto it = super_grenade_timers.begin(); it != super_grenade_timers.end();) {
                    const Entity& entity = it->first;
                    SuperProjectileData& data = it->second;
                    if (ENTITY::DOES_ENTITY_EXIST(entity)) {
                        if (data.timer.update()) {
                            // Perform timer-based actions
                            if (config.explode_timing_mode)
                            {
                                FIRE::ADD_OWNED_EXPLOSION(globals::h_local_ped(), data.vec, config.explosionTag, config.explosionRadius, config.explosionSound, config.explosionInvisible, config.explosionCameraShake);
                                tasks::get()->delete_entity(entity);
                                super_grenade_timers.erase(it);
                            }
                        }
                        //if (!config.explode_timing_mode)
                        //{
                        //    if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(entity) < 0.5f)
                        //    {
                        //        FIRE::ADD_OWNED_EXPLOSION(globals::h_local_ped(), data.vec, config.explosionTag, config.explosionRadius, config.explosionSound, config.explosionInvisible, config.explosionCameraShake);
                        //        tasks::get()->delete_entity(entity);
                        //        super_grenade_timers.erase(it);
                        //    }
                        //    
                        //}
                        data.vec = ENTITY::GET_ENTITY_COORDS(entity, 0);
                    }
                    else {
                        if (!config.explode_timing_mode)
                        {
                            if (data.vec.x) {
                                FIRE::STOP_FIRE_IN_RANGE(data.vec, 10);
                                FIRE::ADD_OWNED_EXPLOSION(globals::h_local_ped(), data.vec, config.explosionTag, config.explosionRadius, config.explosionSound, config.explosionInvisible, config.explosionCameraShake);
                            }
                            it = super_grenade_timers.erase(it);
                        }
                        //continue;
                    }
                    ++it;
                }
            }
        }

        void setToggle(bool toggle) {
            this->toggle = toggle;
        }

    private:
        std::unordered_map<Entity, SuperProjectileData> super_grenade_timers;
        SuperProjectileConfig config;
        bool toggle = false;
    };

}

