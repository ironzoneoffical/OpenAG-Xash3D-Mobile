# OpenAG for Xash3D Android Mobile
# Master Android.mk - builds OpenAG client and server modules for Xash3D

LOCAL_PATH := $(call my-dir)

# Include OpenAG Client Module
include $(LOCAL_PATH)/cl_dll/Android.mk

# Include OpenAG Server Module  
include $(LOCAL_PATH)/dlls/Android.mk
