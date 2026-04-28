#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

#include "engine/audio/audio.h"
#include "engine/os/filesystem.h"
#include "engine/os/hints.h"

int main(int argc, char **argv) {
    if (argc < 2) { SDL_Log("Usage: ./yubi '[file].wav'"); std::exit(1); } set_hints();

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_AudioStream *stream;
    SDL_Event event;

    Uint64 d_time_now = SDL_GetPerformanceCounter();
    Uint64 d_time_last = 0;
    double delta_time, elapsed_time = 0;
    const int target_fps = 500;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_CreateWindowAndRenderer("Audio Engine Testing", 640, 480, 0x00000000, &window, &renderer);

    float *audio_file = os_junk::load_file_to_ptr(argv[1]);
    if (audio_file == nullptr) { std::exit(1); }

    // At this point: A valid .wav audio file is saved in memory and ready to be read from with real-time shit
    // IMPORTANT!!!! the spec MUST match spec of audio file used TODO: is there some  way to detect this automatically?
    SDL_AudioSpec spec {SDL_AUDIO_S16, 2, 44100};
    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, realtime_audio::primary_audio_callback, audio_file);
    SDL_ResumeAudioStreamDevice(stream);

    bool running = true;

    while (running) {
        d_time_last = d_time_now;
        d_time_now = SDL_GetPerformanceCounter();
        delta_time = (double) ((d_time_now - d_time_last) * 1000 / (double) SDL_GetPerformanceFrequency());
        elapsed_time += delta_time;

        while (SDL_PollEvent(&event)) {
            // TODO: add switch statement here for different types of input
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);

        // TODO: Create separate function to draw to the screen - only when delta target has been reached(?)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        const int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
        SDL_RenderDebugTextFormat(renderer, 15, 15, "delta_time: %f", delta_time);
        SDL_RenderDebugTextFormat(renderer, 15, 25, "elapsed_time: %f", elapsed_time * 0.001);
        SDL_RenderDebugTextFormat(renderer, 15, 35, "fps: %f", (1000 / delta_time));

        SDL_RenderPresent(renderer);

        // when waiting, use the modulus of target fps to account for any leftover delta time in between framegen and next target frame
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    delete[] audio_file;

    return 0;
}
