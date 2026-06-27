# OpenAG for Xash3D Android Mobile
# Application.mk - NDK build configuration

APP_PLATFORM := android-21
APP_STL := c++_static
APP_CPPFLAGS += -std=c++14 -fno-exceptions -fno-rtti
APP_CFLAGS += -DANDROID -D_LINUX -DLINUX -DPOSIX -D_POSIX
APP_ABI := armeabi-v7a arm64-v8a
APP_OPTIM := release
