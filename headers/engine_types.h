#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

#include <string>
#include <cstdint>

enum ZSGAPI {OGL32, VULKAN};
enum ZSPERSPECTIVE {PERSP_3D = 3, PERSP_2D = 2};

typedef struct ZSENGINE_CREATE_INFO{
    char* appName; //String to store name of application
    bool createWindow; //will engine create SDL window at start
    ZSGAPI graphicsApi; //Selected graphics API
}ZSENGINE_CREATE_INFO;

typedef struct ZSGAME_DESC{
    std::string app_label;
    int app_version;

    std::string game_dir; //Game root directory
    std::string blob_root_path; //Relative path to directory with blobs
    std::string resource_map_file_path; //Relative path to resource map
    ZSPERSPECTIVE game_perspective; //Perspective of game scenes
    std::string startup_scene; //Relative path to scene, what loaded on startup

}ZSGAME_DESC;

#endif // ENGINE_TYPES_H
