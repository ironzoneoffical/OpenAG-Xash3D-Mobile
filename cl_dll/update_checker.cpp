/*
update_checker.cpp - Update checker for OpenAG
Copyright (C) 2025 OpenAG Mobile Team

Stub implementation for Android/mobile platforms.
*/

#include "update_checker.h"

#ifdef ANDROID

namespace update_checker
{
    void check_for_updates() { }
    bool is_update_available() { return false; }
}

#else

namespace update_checker
{
    void check_for_updates() { }
    bool is_update_available() { return false; }
}

#endif
