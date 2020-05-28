// Copyright (c) 2018-2020 Intel Corporation
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _MFX_CONFIG_H_
#define _MFX_CONFIG_H_

#include "mfxdefs.h"

#ifndef OPEN_SOURCE
// disable additional features
//#define MFX_FADE_DETECTION_FEATURE_DISABLE
//#define MFX_PRIVATE_AVC_ENCODE_CTRL_DISABLE
//#define MFX_DEC_VIDEO_POSTPROCESS_DISABLE
//#define MFX_EXT_BRC_DISABLE
//#define STRIP_EMBARGO
//#define MFX_ADAPTIVE_PLAYBACK_DISABLE
//#define MFX_EXT_DPB_HEVC_DISABLE
//#define MFX_CAMERA_FEATURE_DISABLE
//#define MFX_FUTURE_FEATURE_DISABLE
//#define MFX_AVC_ENCODING_UNIT_DISABLE

#define MFX_EXTBUFF_GPU_HANG_ENABLE
#define MFX_UNDOCUMENTED_QUANT_MATRIX
#define MFX_UNDOCUMENTED_DUMP_FILES
#define MFX_UNDOCUMENTED_VPP_VARIANCE_REPORT
#define MFX_UNDOCUMENTED_CO_DDI
//#define MFX_EXTBUFF_FORCE_PRIVATE_DDI_ENABLE

//#define MFX_ENABLE_SVC_VIDEO_DECODE
#define MFX_ENABLE_VPP_SVC
#endif // #ifndef OPEN_SOURCE

#if defined(_WIN32) || defined(_WIN64)
#undef MFX_DEBUG_TOOLS
#define MFX_DEBUG_TOOLS

#define MFX_ENABLE_LP_LOOKAHEAD

#if defined(DEBUG) || defined(_DEBUG)
#undef  MFX_DEBUG_TOOLS // to avoid redefinition
#define MFX_DEBUG_TOOLS
#endif
#endif // #if defined(_WIN32) || defined(_WIN64)

#ifdef MFX_VA
    #if defined(LINUX32) || defined(LINUX64)
        #include <va/va_version.h>
        #undef  MFX_VA_LINUX
        #define MFX_VA_LINUX
    #endif
#endif

#if defined(ANDROID)
    // we don't support config auto-generation on Android and have hardcoded
    // definition instead
    #include "mfx_android_defs.h"
#else
    // mfxconfig.h is auto-generated file containing mediasdk per-component
    // enable defines
    #include "mfxconfig.h"

    #if defined(AS_H264LA_PLUGIN)
        #define MFX_ENABLE_LA_H264_VIDEO_HW
        #undef MFX_ENABLE_H264_VIDEO_FEI_ENCODE
    #else
        #if MFX_VERSION >= 1025
            #define MFX_ENABLE_MFE
        #endif
        #define MFX_ENABLE_VPP
    #endif
#endif // #if defined(ANDROID)

// Here follows per-codec feature enable options which as of now we don't
// want to expose on build system level since they are too detailed.
#if defined(MFX_ENABLE_H264_VIDEO_ENCODE)
    #define MFX_ENABLE_H264_VIDEO_ENCODE_HW
    #if MFX_VERSION >= 1023
        #define MFX_ENABLE_H264_REPARTITION_CHECK
    #endif
    #if MFX_VERSION >= 1027
        #define MFX_ENABLE_H264_ROUNDING_OFFSET
    #endif
    #if defined(MFX_ENABLE_H264_VIDEO_FEI_ENCODE)
        #define MFX_ENABLE_H264_VIDEO_FEI_ENCPAK
        #define MFX_ENABLE_H264_VIDEO_FEI_PREENC
        #define MFX_ENABLE_H264_VIDEO_FEI_ENC
        #define MFX_ENABLE_H264_VIDEO_FEI_PAK
    #endif
#endif

#if defined(MFX_ENABLE_H265_VIDEO_ENCODE)
    #define MFX_ENABLE_HEVCE_INTERLACE
    #define MFX_ENABLE_HEVCE_ROI
    #define MFX_ENABLE_HEVCE_HDR_SEI
    #define MFX_ENABLE_HEVCE_WEIGHTED_PREDICTION
    #define MFX_ENABLE_HEVCE_FADE_DETECTION
    //#define MFX_ENABLE_HEVCE_DIRTY_RECT
#endif

#if defined(MFX_ENABLE_VP9_VIDEO_ENCODE)
    #define MFX_ENABLE_VP9_VIDEO_ENCODE_HW
#endif

#if defined(MFX_ENABLE_VP9_VIDEO_DECODE)
#define MFX_ENABLE_VP9_VIDEO_DECODE_HW
#endif

#if defined(MFX_ENABLE_VP8_VIDEO_DECODE)
#define MFX_ENABLE_VP8_VIDEO_DECODE_HW
#endif

#if defined(MFX_ENABLE_VPP)
    #define MFX_ENABLE_VPP_COMPOSITION
    #define MFX_ENABLE_VPP_ROTATION
    #define MFX_ENABLE_VPP_VIDEO_SIGNAL
    #if MFX_VERSION >= MFX_VERSION_NEXT
        #define MFX_ENABLE_VPP_RUNTIME_HSBC
    #endif
    //#define MFX_ENABLE_VPP_FRC
#endif

#if defined(MFX_ENABLE_ASC)
    #define MFX_ENABLE_SCENE_CHANGE_DETECTION_VPP
#endif

#if (MFX_VERSION >= MFX_VERSION_NEXT) && defined(MFX_ENABLE_MCTF)
    #define MFX_ENABLE_MCTF_EXT // extended MCTF interface
#endif

#if MFX_VERSION >= 1028
    #define MFX_ENABLE_RGBP
    #define MFX_ENABLE_FOURCC_RGB565
#endif

#if MFX_VERSION >= 1031
    #define MFX_ENABLE_PARTIAL_BITSTREAM_OUTPUT
#endif

#if defined(MFX_VA_LINUX)
    #if VA_CHECK_VERSION(1,3,0)
        #define MFX_ENABLE_QVBR
    #endif
#endif

#define CMAPIUPDATE

#define MFX_ENABLE_HEVCEHW_REFACTORING

#endif // _MFX_CONFIG_H_
