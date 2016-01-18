LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)





LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/BulletLayer.cpp\
                   ../../Classes/ControlLayer.cpp\
                   ../../Classes/Enemy.cpp\
                   ../../Classes/EnemyLayer.cpp\
                   ../../Classes/GameLayer.cpp\
                   ../../Classes/GameOverLayer.cpp\
                   ../../Classes/GameOverScene.cpp\
                   ../../Classes/GameScene.cpp\
                   ../../Classes/HelloWorldScene.cpp\
                   ../../Classes/MutiBulletsLayer.cpp\
                   ../../Classes/NoTouchLayer.cpp\
                   ../../Classes/PlaneLayer.cpp\
                   ../../Classes/UFOLayer.cpp\
                   ../../Classes/WelcomLayer.cpp\
                   ../../Classes/WelcomScene.cpp

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
