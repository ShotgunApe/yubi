#include <SDL3/SDL.h>
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

typedef struct audio_wrapper {
    Uint8* wav_data;
    Uint32 wav_data_len;
    SDL_AudioStream* buffer;
} audio_wrapper;

int main(int argc, char **argv) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;

    SDL_Event event;
    Uint64 d_time_now = SDL_GetPerformanceCounter();
    Uint64 d_time_last = 0;
    double delta_time, elapsed_time = 0;

    // TODO: I guess make compiler flag to use different audio drivers
    SDL_SetHintWithPriority("SDL_AUDIO_DRIVER", "pulseaudio", SDL_HINT_OVERRIDE);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    static SDL_AudioDeviceID audio_device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    static audio_wrapper selected_song;
    SDL_AudioSpec spec;

    // "do nothing" window flag https://wiki.libsdl.org/SDL2/SDL_WindowFlags
    SDL_CreateWindowAndRenderer("Audio Engine Testing", 640, 480, 0x00000000, &window, &renderer);

    if (!SDL_LoadWAV(argv[1], &spec, &selected_song.wav_data, &selected_song.wav_data_len)) {
        SDL_Log("Usage: ./yubi 'file'");
        return 1;
    }

    selected_song.buffer = SDL_CreateAudioStream(&spec, NULL);
    if (!SDL_BindAudioStream(audio_device, selected_song.buffer)) {
        SDL_Log("Couldn't bind audio stream.");
        return 1;
    }

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

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        const int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
        SDL_RenderDebugTextFormat(renderer, 15, 15, "delta_time: %f", delta_time);
        SDL_RenderDebugTextFormat(renderer, 15, 25, "elapsed_time: %f", elapsed_time * 0.001);
        SDL_RenderDebugTextFormat(renderer, 15, 35, "fps: %f", (1000 / delta_time));

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
