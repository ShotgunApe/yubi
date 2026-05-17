#include "audio.h"

namespace realtime_audio {
    void SDLCALL primary_audio_callback(void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount) {
        additional_amount /= sizeof (float);
        static int current_pos = 44;
        while (additional_amount > 0) {
            float samples[64] = {0};
            const int total = SDL_min(additional_amount, SDL_arraysize(samples));

            for (int i = 0; i < total; i++) {
                samples[i] = static_cast<float *> (userdata)[current_pos];
                current_pos++;
            }

            SDL_PutAudioStreamData(stream, samples, total * sizeof (float));
            additional_amount -= total;
        }
    }
}


