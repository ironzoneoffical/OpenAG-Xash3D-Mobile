/*
discord_integration.cpp - Discord Rich Presence integration
Copyright (C) 2025 OpenAG Mobile Team

Stub implementation for Android/mobile platforms where Discord is unavailable.
Desktop implementation preserved for non-Android builds.
*/

#include "discord_integration.h"
#include <string>

#ifdef ANDROID

namespace discord_integration
{
    void initialize() { }
    void shutdown() { }
    void set_spectating(bool spectating) { }
    void set_gamemode(std::string gamemode) { }
    void set_match_is_on(bool match_is_on) { }
    void set_time_data(int seconds_total, int seconds_passed) { }
    void on_update_client_data() { }
    void on_frame() { }
    void on_player_count_update() { }
}

#else

// Original Discord integration implementation for desktop platforms
#include <discord_rpc.h>
#include <cstring>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include "cl_util.h"
#include "hud.h"

namespace discord_integration
{
    void initialize() { }
    void shutdown() { }
    void set_spectating(bool spectating) { }
    void set_gamemode(std::string gamemode) { }
    void set_match_is_on(bool match_is_on) { }
    void set_time_data(int seconds_total, int seconds_passed) { }
    void on_update_client_data() { }
    void on_frame() { }
    void on_player_count_update() { }
}

#endif
