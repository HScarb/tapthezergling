LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)





LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \       
			../../Classes/AppDelegate.cpp \    
			../../Classes/HelloWorldScene.cpp\
				   ../../Classes/AnimationUtil.cpp \
				   ../../Classes/DoubleTapScene.cpp \
				   ../../Classes/EatCandiesScene.cpp \
				   ../../Classes/FilterSprite.cpp \
				   ../../Classes/LoadingScene.cpp \
				   ../../Classes/MainScene.cpp \
				   ../../Classes/SceneManager.cpp \
				   ../../Classes/SlideCutScene.cpp \
				   ../../Classes/TemplateScene.cpp \
				   ../../Classes/TimeManager.cpp \
				   ../../Classes/TollgateScene.cpp \
				   ../../Classes/VisibleRect.cpp \
				   ../../Classes/Zergling.cpp \
				   ../../Classes/Farmer.cpp \
				   ../../Classes/SettingsScene.cpp \
				   ../../Classes/TollgateControlLayer.cpp \
				   ../../Classes/PauseLayer.cpp \
				   ../../Classes/Flower.cpp \
				   ../../Classes/GameManager.cpp \
				   ../../Classes/DataManager.cpp \
				   ../../Classes/JumpingOnPoolScene.cpp \
				   ../../Classes/BurrowAndAttack.cpp \
				   ../../Classes/SmallZergling.cpp \
				   ../../Classes/EatFlowersScene.cpp \
				   ../../Classes/ClassifyUnits.cpp \
				   ../../Classes/BOSS2ZerglingNinja.cpp \
				   ../../Classes/BOSS1ZerglingKing.cpp \
				   ../../Classes/Worker.cpp \
				   ../../Classes/FeedSnacks.cpp \
				   ../../Classes/farmerandflower.cpp \
				   ../../Classes/CheckThethingScene.cpp \
				   ../../Classes/Shake.cpp \
				   ../../Classes/ScoreScene.cpp \
				   ../../Classes/SoundManager.cpp \
				   ../../Classes/CardControlLayer.cpp \
				   ../../Classes/Card.cpp \
				   ../../Classes/CardManager.cpp \
				   ../../Classes/CardInfoLayer.cpp \
			       ../../Classes/NoTouchLayer.cpp \
				   ../../Classes/Chest.cpp \
				   ../../Classes/CsvUtil.cpp \
				   ../../Classes/StringUtil.cpp \
				   ../../Classes/Circle.cpp \
				   ../../Classes/CsvManager.cpp \
				   ../../Classes/fitthecircle.cpp \
				   ../../Classes/Meteorolite.cpp \
				   ../../Classes/RunScene.cpp \				   
				   ../../Classes/CsvData.cpp \				   
				   ../../Classes/FreeCardLayer.cpp \				   
				   ../../Classes/JsonData.cpp \				   

define walk
$(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef

ALLFILES = $(call walk, $(LOCAL_PATH)/../../Classes)
FILE_LIST := hellocpp/main.cpp
FILE_LIST += $(filter %.cpp, $(ALLFILES))

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)



# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
