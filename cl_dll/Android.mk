# OpenAG Client DLL for Xash3D Android
# Copyright (C) 2025 OpenAG Mobile Team

LOCAL_PATH := $(call my-dir)
CLEAR_VARS_MODULE := openag_client

include $(CLEAR_VARS)

LOCAL_MODULE := client

# Compiler flags
LOCAL_CFLAGS := -DCLIENT_DLL -DCLIENT_WEAPONS -DGNUC -DPOSIX -D_POSIX \
    -Dstricmp=strcasecmp -Dstrnicmp=strncasecmp -D_strnicmp=strncasecmp \
    -D_snprintf=snprintf -D_vsnprintf=vsnprintf \
    -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti \
    -Wno-write-strings -Wno-invalid-offsetof \
    -DANDROID -D_LINUX -DLINUX \
    -DDISABLE_JUMP_ORIGIN -DDISABLE_VEC_ORIGIN \
    -DDISABLE_DISCORD -DDISABLE_STEAM -DDISABLE_UPDATE_CHECK

LOCAL_CPPFLAGS := -std=c++14 -fno-exceptions -fno-rtti
LOCAL_CONLYFLAGS := -std=c99

# Include paths
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/.. \
    $(LOCAL_PATH)/../common \
    $(LOCAL_PATH)/../engine \
    $(LOCAL_PATH)/../game_shared \
    $(LOCAL_PATH)/../pm_shared \
    $(LOCAL_PATH)/../public \
    $(LOCAL_PATH)/../public/cl_dll \
    $(LOCAL_PATH)/../external/discord-rpc/include \
    $(LOCAL_PATH)/../utils/vgui/include \
    $(LOCAL_PATH)/../dlls \
    $(LOCAL_PATH)/../dlls/wpn_shared

# Client source files (excluding Windows-specific and disabled modules)
LOCAL_SRC_FILES := \
    ammo.cpp \
    ammo_secondary.cpp \
    ammohistory.cpp \
    battery.cpp \
    cdll_int.cpp \
    color_tags.cpp \
    com_weapons.cpp \
    death.cpp \
    demo.cpp \
    discord_integration.cpp \
    entity.cpp \
    ev_common.cpp \
    ev_hldm.cpp \
    events.cpp \
    flashlight.cpp \
    forcemodel.cpp \
    GameStudioModelRenderer.cpp \
    geiger.cpp \
    health.cpp \
    hud.cpp \
    hud_bench.cpp \
    hud_benchtrace.cpp \
    hud_countdown.cpp \
    hud_crosshairs.cpp \
    hud_ctf.cpp \
    hud_customtimer.cpp \
    hud_debug.cpp \
    hud_jumpspeed.cpp \
    hud_location.cpp \
    hud_msg.cpp \
    hud_nextmap.cpp \
    hud_oldscoreboard.cpp \
    hud_playerid.cpp \
    hud_redraw.cpp \
    hud_scores.cpp \
    hud_servers.cpp \
    hud_settings.cpp \
    hud_spectator.cpp \
    hud_speedometer.cpp \
    hud_strafeguide.cpp \
    hud_suddendeath.cpp \
    hud_timeout.cpp \
    hud_timer.cpp \
    hud_update.cpp \
    hud_vote.cpp \
    hud_watermark.cpp \
    hudgl.cpp \
    in_camera.cpp \
    interpolation.cpp \
    menu.cpp \
    message.cpp \
    overview.cpp \
    rainbow.cpp \
    saytext.cpp \
    scoreboard.cpp \
    steam_id.cpp \
    status_icons.cpp \
    statusbar.cpp \
    studio_util.cpp \
    StudioModelRenderer.cpp \
    text_message.cpp \
    train.cpp \
    tri.cpp \
    update_checker.cpp \
    util.cpp \
    view.cpp \
    voice_status.cpp \
    vgui_ClassMenu.cpp \
    vgui_ConsolePanel.cpp \
    vgui_ControlConfigPanel.cpp \
    vgui_CustomObjects.cpp \
    vgui_int.cpp \
    vgui_MOTDWindow.cpp \
    vgui_SchemeManager.cpp \
    vgui_ScorePanel.cpp \
    vgui_ServerBrowser.cpp \
    vgui_SpectatorPanel.cpp \
    vgui_TeamFortressViewport.cpp \
    vgui_teammenu.cpp \
    vgui_UnicodeTextImage.cpp \
    hl/hl_baseentity.cpp \
    hl/hl_events.cpp \
    hl/hl_objects.cpp \
    hl/hl_weapons.cpp

# Platform-specific input handling for Android
LOCAL_SRC_FILES += \
    platform/android/input_android.cpp

# Common shared sources
LOCAL_SRC_FILES += \
    ../common/parsemsg.cpp \
    ../common/interface.cpp

# Link libraries
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv1_CM

LOCAL_STATIC_LIBRARIES := 

# Build as shared library
include $(BUILD_SHARED_LIBRARY)
