LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#cd /cygdrive/d/cocos2dx_example/workplace/brave/proj.android/ && /cygdrive/c/Cocos/frameworks/android-ndk-windows/android-ndk-r10d/ndk-build NDK_PROJECT_PATH=. NDK_APPLICATION_MK=./jni/Application.mk NDK_MODULE_PATH=/cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                    ../../Classes/AppDelegate.cpp \
                    ../../Classes/Background.cpp \
                    ../../Classes/CustomTool.cpp \
                    ../../Classes/FSM.cpp \
                    ../../Classes/GameOverLayer.cpp \
                    ../../Classes/MainScene.cpp \
                    ../../Classes/PauseLayer.cpp \
                    ../../Classes/Player.cpp \
                    ../../Classes/Progress.cpp \
                    ../../Classes/StartScene.cpp \
                    ../../Classes/VisibleRect.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
                
$(call import-add-path,  /cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/extensions)
$(call import-add-path,  /cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/external)
$(call import-add-path,  /cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/cocos)
$(call import-add-path,  /cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1)

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

#$(call import-module,./prebuilt-mk)
$(call import-module,cocos)
$(call import-module,extensions)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
