#pragma once

#include "core.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <vector>

using Data = std::vector<u8>;

namespace Cart
{
    enum Type
    {
        ROM_ONLY                       = 0x00,
        MBC1                           = 0x01,
        MBC1_RAM                       = 0x02,
        MBC1_RAM_BATTERY               = 0x03,
        MBC2                           = 0x05,
        MBC2_BATTERY                   = 0x06,
        ROM_RAM_1                      = 0x08,
        ROM_RAM_BATTERY_1              = 0x09,
        MMM01                          = 0x0B,
        MMM01_RAM                      = 0x0C,
        MMM01_RAM_BATTERY              = 0x0D,
        MBC3_TIMER_BATTERY             = 0x0F,
        MBC3_TIMER_RAM_BATTERY_2       = 0x10,
        MBC3                           = 0x11,
        MBC3_RAM_2                     = 0x12,
        MBC3_RAM_BATTERY_2             = 0x13,
        MBC5                           = 0x19,
        MBC5_RAM                       = 0x1A,
        MBC5_RAM_BATTERY               = 0x1B,
        MBC5_RUMBLE                    = 0x1C,
        MBC5_RUMBLE_RAM                = 0x1D,
        MBC5_RUMBLE_RAM_BATTERY        = 0x1E,
        MBC6                           = 0x20,
        MBC7_SENSOR_RUMBLE_RAM_BATTERY = 0x22,
        POCKET_CAMERA                  = 0xFC,
        BANDAI_TAMA5                   = 0xFD,
        HUC3                           = 0xFE,
        HUC1_RAM_BATTERY               = 0xFF
    };
}

class MBC
{
    public:
        static auto getCartType(const char* path) -> Cart::Type;
    public:
        MBC() = default;

        /**
         * @brief Load a rom file into memory
         * 
         * @param path The filepath to the rom 
         */
        virtual void load(const char* path);

        /**
         * @brief Reads a byte from the specified memory address
         * 
         * @param address The address to read from
         * @return The value stored at that address
         */
        [[nodiscard]] virtual auto read(u16 address) const -> u8;

        /**
         * @brief Writes a byte at the specified memory address
         * 
         * @param address The address to write to
         * @param val The value to write
         */
        virtual void write(u16 address, u8 val);
    protected:
        Data m_Data;
};
