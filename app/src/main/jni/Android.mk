LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := driver
LOCAL_SRC_FILES := driver.cpp

include $(BUILD_SHARED_LIBRARY)
