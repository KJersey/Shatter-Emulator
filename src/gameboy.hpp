#pragma once

#include "core.hpp"

#include "audio/apu.hpp"

#include "mmu.hpp"

#include "cpu/cpu.hpp"
#include "cpu/timer.hpp"

#include "video/screen.hpp"
#include "video/ppu.hpp"

#include "joypad.hpp"
#include "video/video_defs.hpp"

class Gameboy
{
    public:
        Gameboy();
        Gameboy(const std::string& path);
        ~Gameboy();

        void reset();

        /**
         * @brief Loads a rom into memory
         * 
         * @param path The filepath to the rom
         */
        void load(const std::string& path);

        /**
         * @brief Loads the rom from the current path into memory
         * 
         */
        void load();

        /**
         * @brief Loads a bootrom into memory
         * 
         * @param path The filepath to the bootrom
         */
        void loadBoot(const std::string& path);

        /**
         * @brief Saves a ram to disk
         * 
         */
        void save();

        /**
         * @brief Starts the Gameboy
         * 
         */
        void start();

        /**
         * @brief Emulates a step of the cpu, apu and ppu
         * 
         */
        void tick();

        /**
         * @brief Renders a single frame of the gameboy
         * 
         */
        void renderFrame();

        /**
         * @brief Stops the Gameboy
         * 
         */
        void stop();

        /**
         * @brief Checks if the Gameboy is currently running
         * 
         * @return The state of the Gameboy
         */
        auto isRunning() const -> bool;

        /**
         * @brief Reads a byte from the specified memory address
         * 
         * @param address The address to read from
         * @return The value stored at that address
         */
        [[nodiscard]] __always_inline auto read(u16 address) const -> u8;

        /**
         * @brief Writes a byte at the specified memory address
         * 
         * @param address The address to write to
         * @param val The value to write
         */
        __always_inline void write(u16 address, u8 val);

        /**
         * @brief Returns if the bootrom is enabled
         * 
         * @return The status of if the bootrom is enabled
         */
        [[nodiscard]] __always_inline auto isBootEnabled() const -> u8;

        /**
         * @brief Gets the status of the IME (interrupt master enable)
         * 
         * @return The current value of the IME
         */
        [[nodiscard]] __always_inline auto getIME() const -> bool;

        /**
         * @brief Sets the IME (interrupt master enable) to the specified state
         * 
         * @param ime The state to set the IME to
         */
        __always_inline void setIME(bool ime);

        /**
         * @brief Raise an interrupt of a specified type
         * 
         * @param flag The type of interrupt to raise
         */
        __always_inline void raiseInterrupt(const Flags::Interrupt& flag);

        /**
         * @brief Presses a button on the joypad
         * 
         * @param button The button to press
         */
        __always_inline void press(Button button);

        /**
         * @brief Releases a button on the joypad
         * 
         * @param button The button to release
         */
        __always_inline void release(Button button);

        /**
         * @brief Writes an input state to the joypad
         * 
         * @param val The input state to write
         */
        __always_inline void setInput(u8 val);

        /**
         * @brief Gets the current joypad input state
         * 
         */
        [[nodiscard]]  __always_inline auto getInput() -> u8;

        /**
         * @brief Gets the button from an SDL keycode
         * 
         */
        [[nodiscard]] __always_inline auto getButton(SDL_Keycode keycode) -> Button;

        /**
         * @brief Gets the value of the DIV register
         * 
         */
        __always_inline auto getDIV() -> u8;

        /**
         * @brief Resets the DIV counter in the timer
         * 
         */
        __always_inline void resetDiv();

        /**
         * @brief Sets the speed of the timer
         * 
         * @param speed The speed to be set
         */
        __always_inline void setTimerSpeed(u32 speed);


        /**
         * @brief Get the video mode of the PPU
         * 
         */
        __always_inline auto getVideoMode() const -> VideoMode;

        /**
         * @brief Set the title of the window
         * 
         * @param title The title to set
         */
        __always_inline void setTitle(std::string title);

        /**
         * @brief Get the title of the window
         * 
         */
        __always_inline auto getTitle(std::string title) const -> const std::string&;

        /**
         * @brief Set the fps in the title of the window
         * 
         * @param fps The fps to set
         */
        __always_inline void setTitleFPS(u32 fps);

        /**
         * @brief Set the rendering scale of the window
         * 
         * @param scale The rendering scale to set
         */
        __always_inline void setRenderingScale(u8 renderingScale);

        /**
         * @brief Get the rendering scale of the window
         * 
         */
        __always_inline auto getRenderingScale() const -> u32;
    private:
        MMU m_MMU;
        APU m_APU;
        CPU m_CPU;
        PPU m_PPU;

        u32 m_Cycles;

        Joypad m_Joypad;
        Timer  m_Timer;
        Screen m_Screen;

        std::string m_Path;
        std::string m_BootPath;
        bool m_Running;
};

//--------------------------  Inline function implementations --------------------------//

__always_inline auto Gameboy::read(u16 address) const -> u8
{
    return m_MMU.read(address);
}

__always_inline void Gameboy::write(u16 address, u8 val)
{
    m_MMU.write(address, val);
}

__always_inline auto Gameboy::isBootEnabled() const -> u8
{
    return m_MMU.isBootEnabled();
}

__always_inline auto Gameboy::getIME() const -> bool
{
    return m_CPU.getIME();
}

__always_inline void Gameboy::setIME(bool ime)
{
    m_CPU.setIME(ime);
}

__always_inline void Gameboy::raiseInterrupt(const Flags::Interrupt& flag)
{
    m_CPU.raiseInterrupt(flag);
}

__always_inline void Gameboy::press(Button button)
{
    m_Joypad.press(button);
    raiseInterrupt(Flags::Interrupt::Joypad);
}

__always_inline void Gameboy::release(Button button)
{
    m_Joypad.release(button);
}

__always_inline void Gameboy::setInput(u8 val)
{
    m_Joypad.setInput(val);
}

__always_inline auto Gameboy::getInput() -> u8
{
    return m_Joypad.getInput();
}


__always_inline auto Gameboy::getButton(SDL_Keycode keycode) -> Button
{
    return m_Joypad.getButton(keycode);
}

__always_inline auto Gameboy::getDIV() -> u8
{
    return m_Timer.getDIV();
}

__always_inline void Gameboy::resetDiv()
{
    m_Timer.resetDiv();
}

__always_inline void Gameboy::setTimerSpeed(u32 speed)
{
    m_Timer.setSpeed(speed);
}

__always_inline auto Gameboy::getVideoMode() const -> VideoMode
{
    return m_PPU.getMode();
}

__always_inline void Gameboy::setTitle(std::string title)
{
    m_Screen.setTitle(title);
}

__always_inline auto Gameboy::getTitle(std::string title) const -> const std::string&
{
    return m_Screen.getTitle();
}

__always_inline void Gameboy::setTitleFPS(u32 fps)
{
    m_Screen.setTitleFPS(fps);
}

__always_inline void Gameboy::setRenderingScale(u8 renderingScale)
{
    m_Screen.setRenderingScale(renderingScale);
}

__always_inline auto Gameboy::getRenderingScale() const -> u32
{
    return m_Screen.getRenderingScale();
}
