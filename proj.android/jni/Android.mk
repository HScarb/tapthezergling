LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)





LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/AnimationUtil.cpp \
				   ../../Classes/DoubleTapScene.cpp \
				   ../../Classes/EatCandiesScene.cpp \
				   ../../Classes/FilterSprite.cpp \
				   ../../Classes/LoadingScene.cpp \
				   ../../Classes/MainScene.cpp \
				   ../../Classes/SceneManager.cpp \
				   ../../Classes/SlideScene.cpp \
				   ../../Classes/TemplateScene.cpp \
				   ../../Classes/TimeManager.cpp \
				   ../../Classes/TollgateScene.cpp \
				   ../../Classes/VisibleRect.cpp \
				   ../../Classes/Zergling.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
