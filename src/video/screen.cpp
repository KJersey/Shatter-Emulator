#include "SDL_video.h"
#include "core.hpp"

#include "screen.hpp"

#include "gameboy.hpp"

void Screen::init()
{
    SDL_Init(SDL_INIT_VIDEO);
}

void Screen::quit()
{
    SDL_Quit();
}

Screen::Screen()
{
    DEBUG("Initializing Screen!");
    
    m_Window = SDL_CreateWindow("Shatter Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                GAMEBOY_WIDTH * m_Scale, GAMEBOY_HEIGHT * m_Scale, SDL_WINDOW_SHOWN);
    if(!m_Window)
    {
        CRITICAL("\tCould not create window: " << SDL_GetError());
        return;
    }
    DEBUG("\tWindow Created.");

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if(!m_Renderer)
    {
        CRITICAL("\tCould not create renderer: " << SDL_GetError());
        return;
    }
    DEBUG("\tRenderer Created.");

    m_Texture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, GAMEBOY_WIDTH, GAMEBOY_HEIGHT);
}

Screen::~Screen()
{
    SDL_DestroyTexture(m_Texture);
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
}

void Screen::draw(const std::array<u8, FRAME_BUFFER_SIZE>& buffer)
{
    SDL_UpdateTexture(m_Texture, nullptr, buffer.data(), GAMEBOY_WIDTH * 4);
    SDL_RenderCopy(m_Renderer, m_Texture, nullptr, nullptr);
    SDL_RenderPresent(m_Renderer);
}

void Screen::setTitle(std::string title)
{
    SDL_SetWindowTitle(m_Window, title.c_str());
}
