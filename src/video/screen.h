#pragma once

#include "core.h"

#include <SDL2/SDL.h>

class Gameboy;

class Screen
{
    public:
        static void init();
        static void quit();
    public:
        Screen();
        ~Screen();

        inline u32 getWindowID() const { return static_cast<u32>(SDL_GetWindowID(m_Window)); }

        void poll();
        void draw(u8* buffer);
    private:
        SDL_Window*     m_Window;
        SDL_Renderer*   m_Renderer;
        SDL_Texture*    m_Texture;

        int m_Scale = 3;
};