#include "cartridge.h"

#include <algorithm>
#include <fstream>
#include <filesystem>
#include <iterator>

Cartridge::Cartridge(const char* path)
{
    load(path);
}

void Cartridge::load(const char* path)
{
    std::ifstream in(path, std::ios::binary);
    contents.assign((std::istreambuf_iterator<char>(in)), {});
    std::copy(contents.begin(), contents.begin() + 0x4000, m_Rom0);
    std::copy(contents.begin() + 0x4000, contents.begin() + 0x8000, m_Rom1);
}

u8 Cartridge::read(u16 address)
{
    if(address < 0x4000) return m_Rom0[address];
    return m_Rom1[address - 0x4000];
}