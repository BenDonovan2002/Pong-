#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int TIME_STEP = 1000 / 60; // 60 updates per second

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect paddle1 = {40, SCREEN_HEIGHT / 2 - 40, 20, 80};
    SDL_Rect paddle2 = {SCREEN_WIDTH - 60, SCREEN_HEIGHT / 2 - 40, 20, 80};
    SDL_Rect ball = {SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 - 10, 20, 20};

    float ballSpeedX = 0.5;
    float ballSpeedY = 0.5;

    bool quit = false;
    SDL_Event e;

    Uint32 currentTime, elapsedTime, lastUpdateTime = SDL_GetTicks();

    while (!quit) {
        currentTime = SDL_GetTicks();
        elapsedTime = currentTime - lastUpdateTime;

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_W] && paddle1.y > 0) {
            paddle1.y -= 3;
        }
        if (currentKeyStates[SDL_SCANCODE_S] && paddle1.y < SCREEN_HEIGHT - paddle1.h) {
            paddle1.y += 3;
        }
        if (currentKeyStates[SDL_SCANCODE_UP] && paddle2.y > 0) {
            paddle2.y -= 3;
        }
        if (currentKeyStates[SDL_SCANCODE_DOWN] && paddle2.y < SCREEN_HEIGHT - paddle2.h) {
            paddle2.y += 3;
        }

        if (elapsedTime >= TIME_STEP) {
            ball.x += ballSpeedX * elapsedTime;
            ball.y += ballSpeedY * elapsedTime;

            if (ball.y <= 0 || ball.y + ball.h >= SCREEN_HEIGHT) {
                ballSpeedY = -ballSpeedY;
            }

            if (SDL_HasIntersection(&ball, &paddle1) || SDL_HasIntersection(&ball, &paddle2)) {
                ballSpeedX = -ballSpeedX;
            }

            lastUpdateTime = currentTime;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &paddle1);
        SDL_RenderFillRect(renderer, &paddle2);
        SDL_RenderFillRect(renderer, &ball);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit    ();

    return 0;
}
