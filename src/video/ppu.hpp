#pragma once

#include "core.hpp"

#include <array>
#include <functional>

#include "video_defs.hpp"

class Gameboy;

class PPU
{
    public:
        PPU(Gameboy& gb);

        /**
         * @brief Sets the callback function for when the screen is ready to be drawn
         * 
         * @param callback The callback function to be called
         */
        void setDrawCallback(std::function<void(std::array<u8, FRAME_BUFFER_SIZE> buffer)> callback);

        /**
         * @brief Emulate the PPU for a specified amount of cycles
         * once the CPU has finished its instruction
         * 
         * @param cycles The amount of cycles that has passed
         */
        void tick(u8 cycles);

        /**
         * @brief Returns the mode the PPU is in
        **/
        auto getMode() -> VideoMode;

    private:
        /**
         * @brief Draw a background line to the screen
         * 
         * @param line The background line to draw
         */
        void drawBackgroundLine(u8 line);

        /**
         * @brief Draw a window line to the screen
         * 
         * @param line The window line to draw
         */
        void drawWindowLine(u8 line);

        /**
         * @brief Draw the sprites to the screen
         * 
         */
        void drawSprites();

        /**
         * @brief Get the gameboy colour of a pixel within a tile
         * 
         * @param pixelXPos The x position of the pixel within
         * the tile
         * 
         * @param tileAddress The address of the tile to get the
         * colour information from
         */
        auto getGBColour(u8 pixelXPos, u16 tileAddress) -> Colour::GBColour;

        /**
         * @brief Convert a GB Colour into a screen colour
         * 
         * @param colour The colour of the gb colour to convert into a screen colour
         */
        auto getScreenColour(Colour::GBColour colour) -> Colour::ScreenColour;

        /**
         * @brief Draw a specified pixel at position (x, y) with
         * colour c
         * 
         * @param x The x coordinate of the pixel
         * 
         * @param y The y coordinate of the pixel
         *
         * @param c The colour of the pixel
         */
        void drawPixel(u8 x, u8 y, Colour::ScreenColour c);
    private:
        Gameboy& m_Gameboy;

        std::array<u8, FRAME_BUFFER_SIZE> m_FrameBuffer      {{}};
        std::function<void(std::array<u8, FRAME_BUFFER_SIZE> buffer)> m_DrawCallback;

        VideoMode m_Mode;
        u16 m_Cycles;
        u8 m_Line;

        // Temp drawing before implementing pixel FIFO
        // HBLANK and DRAWING clocks might be different with FIFO
        static constexpr u16 CYCLES_PER_HBLANK   = 204;
        static constexpr u16 CYCLES_PER_VBLANK   = 4560;
        static constexpr u16 CYCLES_PER_OAM_SCAN = 80;
        static constexpr u16 CYCLES_PER_TRANSFER = 172;

        static constexpr u16 CYCLES_PER_LINE     = CYCLES_PER_HBLANK
                                                 + CYCLES_PER_OAM_SCAN
                                                 + CYCLES_PER_TRANSFER;

};
