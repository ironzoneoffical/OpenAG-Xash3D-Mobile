/*
input_android.cpp - Android input handling for OpenAG on Xash3D
Copyright (C) 2025 OpenAG Mobile Team

This file replaces inputw32.cpp for Android platform.
Uses Xash3D's touch input system and mobility interface.
*/

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "weapons.h"
#include "usercmd.h"
#include "input.h"
#include "hud.h"
#include "com_model.h"
#include "kbutton.h"
#include "pm_defs.h"
#include "event_api.h"
#include "pmtrace.h"
#include "in_defs.h"

#ifdef ANDROID

// Xash3D touch system integration
extern "C" {
    void IN_Android_TouchInit(void);
    void IN_Android_TouchShutdown(void);
}

// Movement command
float in_forwardmove;
float in_sidemove;
float in_upmove;

// Look angles
float in_pitch;
float in_yaw;

// Touch input state
struct TouchState {
    bool forward;
    bool back;
    bool left;
    bool right;
    bool jump;
    bool duck;
    bool attack;
    bool attack2;
    bool reload;
    bool use;
    float look_dx;
    float look_dy;
    float move_x;
    float move_y;
} g_TouchState;

// Initialize Android input system
void IN_Init(void)
{
    g_TouchState = {};
    in_forwardmove = 0;
    in_sidemove = 0;
    in_upmove = 0;
    in_pitch = 0;
    in_yaw = 0;
    
    IN_Android_TouchInit();
}

// Shutdown Android input system
void IN_Shutdown(void)
{
    IN_Android_TouchShutdown();
}

// Move event from touch system
void IN_Android_MoveEvent(float forward, float side)
{
    g_TouchState.move_x = side;
    g_TouchState.move_y = forward;
}

// Look event from touch system (right stick or swipe)
void IN_Android_LookEvent(float yaw, float pitch)
{
    g_TouchState.look_dx = yaw;
    g_TouchState.look_dy = pitch;
}

// Button events from touch system
void IN_Android_ButtonEvent(int button, bool pressed)
{
    switch(button)
    {
        case 0: g_TouchState.jump = pressed; break;
        case 1: g_TouchState.duck = pressed; break;
        case 2: g_TouchState.attack = pressed; break;
        case 3: g_TouchState.attack2 = pressed; break;
        case 4: g_TouchState.reload = pressed; break;
        case 5: g_TouchState.use = pressed; break;
    }
}

// Accumulate input for the frame
void IN_Commands(void)
{
    in_forwardmove = g_TouchState.move_y * 400.0f;
    in_sidemove = g_TouchState.move_x * 400.0f;
    
    in_yaw = g_TouchState.look_dx;
    in_pitch = g_TouchState.look_dy;
    
    g_TouchState.look_dx = 0;
    g_TouchState.look_dy = 0;
}

void IN_MouseEvent(int mstate)
{
}

void IN_ClearStates(void)
{
    g_TouchState = {};
    in_forwardmove = 0;
    in_sidemove = 0;
    in_upmove = 0;
    in_pitch = 0;
    in_yaw = 0;
}

void CreateMove(float frametime, struct usercmd_s *cmd, int active)
{
    memset(cmd, 0, sizeof(*cmd));
    
    if (!active)
        return;
    
    cmd->forwardmove = (int)in_forwardmove;
    cmd->sidemove = (int)in_sidemove;
    cmd->upmove = (int)in_upmove;
    
    cl.viewangles[YAW] += in_yaw * frametime;
    cl.viewangles[PITCH] += in_pitch * frametime;
    
    if (cl.viewangles[PITCH] > 80.0f)
        cl.viewangles[PITCH] = 80.0f;
    if (cl.viewangles[PITCH] < -80.0f)
        cl.viewangles[PITCH] = -80.0f;
    
    cmd->viewangles[0] = cl.viewangles[PITCH] * 65536.0f / 360.0f;
    cmd->viewangles[1] = cl.viewangles[YAW] * 65536.0f / 360.0f;
    cmd->viewangles[2] = cl.viewangles[ROLL] * 65536.0f / 360.0f;
    
    if (g_TouchState.attack)
        cmd->buttons |= IN_ATTACK;
    if (g_TouchState.attack2)
        cmd->buttons |= IN_ATTACK2;
    if (g_TouchState.jump)
        cmd->buttons |= IN_JUMP;
    if (g_TouchState.duck)
        cmd->buttons |= IN_DUCK;
    if (g_TouchState.reload)
        cmd->buttons |= IN_RELOAD;
    if (g_TouchState.use)
        cmd->buttons |= IN_USE;
    
    cmd->msec = (int)(frametime * 1000);
}

void IN_Accumulate(void) {}
void IN_StartupJoystick(void) {}
void IN_JoystickMove(float *forward, float *side) {}
void IN_JoystickAdvancedUpdate(void) {}

int DLLEXPORT HUD_Key_Event(int eventcode, int keynum, const char *pszCurrentBinding)
{
    return 1;
}

void IN_Android_TouchInit(void)
{
}

void IN_Android_TouchShutdown(void)
{
}

#endif // ANDROID
