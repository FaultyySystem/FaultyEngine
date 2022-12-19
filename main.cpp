#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* argv[]) {

if (SDL_Init(SDL_INIT_VIDEO) != 0) {
  printf("Error initializing SDL: %s\n", SDL_GetError());
  return 1;
}

SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

SDL_Window* window = SDL_CreateWindow(
    "GameEngine",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    640,
    480,
    SDL_WINDOW_OPENGL
);
if (window == nullptr) {
  printf("Error initializing Window: %s\n", SDL_GetError());
  return 1;
}

SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

SDL_GLContext glContext = SDL_GL_CreateContext(window);
if (glContext == nullptr) {
  printf("Error initializing GLContext: %s\n", SDL_GetError());
  return 1;
}

bool running = true;
while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }

    SDL_Rect camera = {0, 0, 640, 480};

    // Viewport
    SDL_RenderSetViewport(renderer, &camera);

    // Camera position
    camera.x = 640/2;
    camera.y = 480/2;

    SDL_RenderPresent(renderer);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_Surface* surface = IMG_Load("./image.png");

    if (surface == NULL) {
      printf("Error initializing Surface: %s\n", SDL_GetError());
      return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int x = camera.x, y = camera.y, width = 100, height = 100; 
    //width = surface->w, height = surface->h;

    //SDL_Rect destRect;
    camera.x = x;
    camera.y = y;
    camera.w = width;
    camera.h = height;

    SDL_RenderCopy(renderer, texture, NULL, &camera);

    SDL_RenderPresent(renderer);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
