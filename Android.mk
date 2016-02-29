LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := paku

LOCAL_CPP_FLAGS := -std=c++1y -Wall -Wextra
LOCAL_SRC_FILES := \
	source/packet/ether.cpp source/packet/arp.cpp source/packet/ip.cpp source/packet/icmp.cpp source/packet/tcp.cpp \
	source/builder/base.cpp source/builder/buffer.cpp source/builder/icmp.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/paku
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/vendor/optional
LOCAL_C_INCLUDES += $(LOCAL_PATH)/vendor/variant

include $(BUILD_STATIC_LIBRARY)
