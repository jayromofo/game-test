#pragma once
#include <stdbool.h>

typedef struct Config {
    char *settings;
} Config;

typedef struct VideoSettings {
    char* video;
} VideoSettings;

typedef struct AudioSettings {
    int master_volume;
    int sfx_volume;
    int music_volume;
} AudioSettings;

typedef struct GeneralSettings {
    char *general;
} GeneralSettings;
