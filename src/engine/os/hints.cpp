#include "hints.h"

void set_hints() {
    #ifdef __linux__
    SDL_SetHintWithPriority("SDL_AUDIO_DRIVER", "pulseaudio", SDL_HINT_OVERRIDE);
    SDL_SetHintWithPriority("SDL_AUDIO_DEVICE_SAMPLE_FRAMES", BUFFER_SIZE_CHAR, SDL_HINT_OVERRIDE);
    #endif
}
