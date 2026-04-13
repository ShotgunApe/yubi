#include <string>
#include <sys/stat.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

static void SDLCALL audio_callback(void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount) {
    // this doesn't need to do much for now - eventually this will add post-processing + additional sound effects to provide proper alignment
    additional_amount /= sizeof (float);
    for (int i = 0; i < additional_amount; i += 320 * sizeof(int16_t)) {
        //buffer = nullptr);
        //SDL_PutAudioStreamData(stream, buffer);
    }
}

int main(int argc, char **argv) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_AudioStream *stream;

    SDL_Event event;
    Uint64 d_time_now = SDL_GetPerformanceCounter();
    Uint64 d_time_last = 0;
    double delta_time, elapsed_time = 0;
    const int target_fps = 240;

    #ifdef __linux__
    SDL_SetHintWithPriority("SDL_AUDIO_DRIVER", "pulseaudio", SDL_HINT_OVERRIDE);
    SDL_SetHintWithPriority("SDL_HINT_AUDIO_DEVICE_SAMPLE_FRAMES", "240", SDL_HINT_OVERRIDE);
    #endif

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_CreateWindowAndRenderer("Audio Engine Testing", 640, 480, 0x00000000, &window, &renderer);

    SDL_AudioSpec spec {SDL_AUDIO_F32, 1, 44100};
    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, audio_callback, NULL);

    if (argc < 2) {
        SDL_Log("Usage: ./yubi '[file].wav'");
        return 1;
    }

    struct stat tmp_buf;
    const std::string file_to_open = argv[1];
    if (stat(file_to_open.c_str(), &tmp_buf) != 0) {
        SDL_Log("File does not exist, exiting...");
        return 1;
    }

    SDL_IOStream *wav_to_vect = SDL_IOFromFile(argv[1], "rb");
    if (wav_to_vect == nullptr) {
        SDL_Log("SDL_IOFromFile failed, exiting...");
        return 1;
    }

    size_t wav_len = SDL_GetIOSize(wav_to_vect);
    float *audio_file = new float[wav_len];

    // TODO: copy wav_to_vect data to arr in heap

    SDL_CloseIO(wav_to_vect);

    // only resume after audio is successfully loaded (First puts to buffer?)
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

    delete [] audio_file;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
