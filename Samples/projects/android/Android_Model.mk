LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := prebuild-libShader
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../Libs/project/lib/libShader.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := prebuild-libMath
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../Libs/project/lib/libMath.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := prebuild-libSceneGraph
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../Libs/project/lib/libSceneGraph.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := prebuild-libSystem
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../Libs/project/lib/libSystem.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := prebuild-libDebugUtil
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../Libs/project/lib/libDebugUtil.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := prebuild-libGraph
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../Libs/project/lib/libGraph.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := prebuild-libStd
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../Libs/project/lib/libStd.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := prebuild-libSampleKit
LOCAL_SRC_FILES := $(LOCAL_PATH)/obj/local/armeabi/libSampleKit.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE     := libModel
LOCAL_LDLIBS     := -llog -lGLESv2 -landroid
LOCAL_CFLAGS     := -DANDROID -D__IZ_GLES2__ -D_DEBUG -D__IZANAGI_NO_USE_D3D__ -D__IZ_DEBUG__ -D__IZ_OGL__
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Libs/include $(LOCAL_PATH)/../../SampleKit
LOCAL_SRC_FILES  := ../../Model/main.cpp \
../../Model/ModelApp.cpp \
../../Model/StateBase.cpp \
../../Model/StateCollada.cpp \
../../Model/StateManager.cpp \
../../Model/StateXFile.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := prebuild-libShader \
prebuild-libMath \
prebuild-libSceneGraph \
prebuild-libSystem \
prebuild-libDebugUtil \
prebuild-libGraph \
prebuild-libStd \
prebuild-libSampleKit

include $(BUILD_SHARED_LIBRARY)
