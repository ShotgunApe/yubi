#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

typedef struct audio_buffer {
    SDL_AudioStream *stream;
} audio_buffer;

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;

    SDL_Event event;
    SDL_AudioSpec spec;
    static SDL_AudioDeviceID audio_device = 0;

    Uint64 d_time_now = SDL_GetPerformanceCounter();
    Uint64 d_time_last = 0;
    double delta_time = 0;

    SDL_Init(SDL_INIT_VIDEO);

    // "do nothing" window flag https://wiki.libsdl.org/SDL2/SDL_WindowFlags
    SDL_CreateWindowAndRenderer("Audio Engine Testing", 640, 480, 0x00000000, &window, &renderer);

    bool running = true;

    while (running) {
        d_time_last = d_time_now;
        d_time_now = SDL_GetPerformanceCounter();
        delta_time = (double) ((d_time_now - d_time_last) * 1000 / (double) SDL_GetPerformanceFrequency());

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

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
