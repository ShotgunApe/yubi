#ifndef AUDIO_H
#define AUDIO_H

/*      /engine/audio.h
 *
 *      This is my attempt at using a real-time-esque approach (thanks to SDL3)
 *      in a game. All audio processing is done within the audio_callback, like
 *      that of SDL2. I have no idea if this is the best approach but time will
 *      tell.
 *
 *      As an overview, the audio engine:
 *      1). Loads a .WAV file to the heap, returning a ptr to the address where
 *          it is stored.
 *
 *      2). Starts a separate thread for SDL's audiospec object.
 *
 *      3). Performs any processing before copying the audio data from the heap
 *          to the current buffer to be played.
 *
 *      The resulting code should be low latency and in sync with anything that
 *      occurs on screen. Assuming I write performant enough code, that is.
 *
 *      There is still a lot of work to be done in this regard, but I hope this
 *      explanation makes sense to any future dev looking at the code :>     */

#include <SDL3/SDL_audio.h>

namespace realtime_audio {
    void SDLCALL primary_audio_callback(void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount);
}

#endif
