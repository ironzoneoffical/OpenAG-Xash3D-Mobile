/*
steam_id.cpp - Steam ID integration for model forcing
Copyright (C) 2025 OpenAG Mobile Team

Stub implementation for Android/mobile platforms where Steam is unavailable.
*/

#include "steam_id.h"
#include <string>

#ifdef ANDROID

namespace steam_id
{
    static std::string empty_string;

    void hook_messages() { }

    const std::string& get_steam_id(size_t player_index)
    {
        return empty_string;
    }

    bool is_showing_real_names()
    {
        return false;
    }

    const std::string& get_real_name(size_t player_index)
    {
        return empty_string;
    }
}

#else

namespace steam_id
{
    void hook_messages() { }
    const std::string& get_steam_id(size_t player_index) { static std::string s; return s; }
    bool is_showing_real_names() { return false; }
    const std::string& get_real_name(size_t player_index) { static std::string s; return s; }
}

#endif
