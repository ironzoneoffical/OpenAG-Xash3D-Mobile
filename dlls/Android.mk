# OpenAG Server DLL for Xash3D Android
# Copyright (C) 2025 OpenAG Mobile Team

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hl

# Compiler flags
LOCAL_CFLAGS := -DGNUC -DPOSIX -D_POSIX \
    -Dstricmp=strcasecmp -Dstrnicmp=strncasecmp -D_strnicmp=strncasecmp \
    -D_snprintf=snprintf -D_vsnprintf=vsnprintf \
    -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti \
    -Wno-write-strings \
    -DANDROID -D_LINUX -DLINUX

LOCAL_CPPFLAGS := -std=c++14 -fno-exceptions -fno-rtti
LOCAL_CONLYFLAGS := -std=c99

# Include paths
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/.. \
    $(LOCAL_PATH)/../common \
    $(LOCAL_PATH)/../engine \
    $(LOCAL_PATH)/../game_shared \
    $(LOCAL_PATH)/../pm_shared \
    $(LOCAL_PATH)/../public

# Server source files
LOCAL_SRC_FILES := \
    agrunt.cpp \
    airtank.cpp \
    aflock.cpp \
    animating.cpp \
    animation.cpp \
    apache.cpp \
    barnacle.cpp \
    barney.cpp \
    bigmomma.cpp \
    bloater.cpp \
    bmodels.cpp \
    bullsquid.cpp \
    buttons.cpp \
    cbase.cpp \
    client.cpp \
    combat.cpp \
    controller.cpp \
    crossbow.cpp \
    crowbar.cpp \
    defaultai.cpp \
    doors.cpp \
    effects.cpp \
    egon.cpp \
    explode.cpp \
    flyingmonster.cpp \
    func_break.cpp \
    func_tank.cpp \
    game.cpp \
    gamerules.cpp \
    gargantua.cpp \
    gauss.cpp \
    genericmonster.cpp \
    ggrenade.cpp \
    globals.cpp \
    gman.cpp \
    h_ai.cpp \
    h_cine.cpp \
    h_cycler.cpp \
    handgrenade.cpp \
    hassassin.cpp \
    headcrab.cpp \
    healthkit.cpp \
    hgrunt.cpp \
    hornet.cpp \
    hornetgun.cpp \
    hostage.cpp \
    houndeye.cpp \
    ichthyosaur.cpp \
    islave.cpp \
    items.cpp \
    leech.cpp \
    lights.cpp \
    maprules.cpp \
    monsters.cpp \
    monsterstate.cpp \
    mortar.cpp \
    mp5.cpp \
    multiplay_gamerules.cpp \
    nihilanth.cpp \
    nodes.cpp \
    observer.cpp \
    osprey.cpp \
    pathcorner.cpp \
    plane.cpp \
    plats.cpp \
    player.cpp \
    python.cpp \
    rat.cpp \
    roach.cpp \
    scientist.cpp \
    scripted.cpp \
    singleplay_gamerules.cpp \
    skill.cpp \
    sound.cpp \
    soundent.cpp \
    spectator.cpp \
    squadmonster.cpp \
    squeakgrenade.cpp \
    subs.cpp \
    talkmonster.cpp \
    teamplay_gamerules.cpp \
    tentacle.cpp \
    triggers.cpp \
    tripmine.cpp \
    turret.cpp \
    util.cpp \
    weapons.cpp \
    world.cpp \
    xen.cpp \
    zombie.cpp \
    wpn_shared/hl_wpn_glock.cpp

# Common shared sources
LOCAL_SRC_FILES += \
    ../common/parsemsg.cpp \
    ../common/interface.cpp

# Link libraries
LOCAL_LDLIBS := -llog -landroid

# Build as shared library
include $(BUILD_SHARED_LIBRARY)
