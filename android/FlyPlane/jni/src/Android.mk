LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL2
SDL_IMAGE_PATH := ../SDL2_image
SDL_MIXER_PATH := ../SDL2_mixer
SDL_TTF_PATH := ../SDL2_ttf
SDL_ENGINE_PATH := ../SDL_Engine
SDL_GFX_PATH := ../SDL2_gfx

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
$(LOCAL_PATH)/$(SDL_IMAGE_PATH) \
$(LOCAL_PATH)/..                \
$(LOCAL_PATH)/$(SDL_MIXER_PATH) \
$(LOCAL_PATH)/$(SDL_TTF_PATH)   \
$(LOCAL_PATH)/$(SDL_GFX_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	$(subst $(LOCAL_PATH)/,, $(wildcard $(LOCAL_PATH)/*.cpp))

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL_Engine SDL2_gfx

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
