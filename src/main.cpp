#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer("An SDL3 window", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer);

    bool running = true;
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
