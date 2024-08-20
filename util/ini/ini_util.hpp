#include <iostream>

namespace insight {
    class ini {
    public:
        void load_objects_ini();
        std::vector<std::string> all_objects = {};

        void load_favorite_objects_ini();
        std::vector<std::string> favorite_objects_name = {};
        std::vector<std::string> favorite_objects_hash = {};
        void add_favorite_object(const std::string hash, const std::string real_name);

    public:
        static ini* get() {
            static ini i;
            return &i;
        }
    };
}
#pragma once
