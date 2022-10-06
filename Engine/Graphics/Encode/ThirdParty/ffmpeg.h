#pragma once
#ifdef USE_ENCODE_MODULE
    #pragma warning(disable:4244 4819)

// https://github.com/m-ab-s/media-autobuild_suite


    #include "CUDA.h"

    extern "C"
    {
    #include "ffmpeg/include/libavformat/avformat.h"
    #include "ffmpeg/include/libavcodec/avcodec.h"
    #include "ffmpeg/include/libavdevice/avdevice.h"
    #include "ffmpeg/include/libavfilter/avfilter.h"
    #include "ffmpeg/include/libavutil/avutil.h"
    #include "ffmpeg/include/libavutil/imgutils.h"
    #include "ffmpeg/include/libavutil/hwcontext.h"
    #include "ffmpeg/include/libavutil/fifo.h"
    #include "ffmpeg/include/libswscale/swscale.h"
    #include "ffmpeg/include/libswresample/swresample.h"

    // HW
    #include "ffmpeg/include/libavutil/hwcontext.h"
    #include "ffmpeg/include/libavutil/hwcontext_cuda.h"
    #include "ffmpeg/include/libavutil/hwcontext_qsv.h"
    #include "ffmpeg/include/libavutil/hwcontext_d3d11va.h"
    #include "ffmpeg/include/libavcodec/qsv.h"
    }

    #ifdef _M_AMD64
    #pragma comment(lib, "ixrEngine/03.Graphics/ixrEncode/00.ThirdParty/ffmpeg/lib/x64/avcodec.lib")
    #pragma comment(lib, "ixrEngine/03.Graphics/ixrEncode/00.ThirdParty/ffmpeg/lib/x64/avdevice.lib")
    #pragma comment(lib, "ixrEngine/03.Graphics/ixrEncode/00.ThirdParty/ffmpeg/lib/x64/avfilter.lib")
    #pragma comment(lib, "ixrEngine/03.Graphics/ixrEncode/00.ThirdParty/ffmpeg/lib/x64/avformat.lib")
    #pragma comment(lib, "ixrEngine/03.Graphics/ixrEncode/00.ThirdParty/ffmpeg/lib/x64/avutil.lib")
    #pragma comment(lib, "ixrEngine/03.Graphics/ixrEncode/00.ThirdParty/ffmpeg/lib/x64/swresample.lib")
    #pragma comment(lib, "ixrEngine/03.Graphics/ixrEncode/00.ThirdParty/ffmpeg/lib/x64/swscale.lib")
    #else
    //#pragma comment(lib, "win32/avcodec.lib")
    //#pragma comment(lib, "win32/avdevice.lib")
    //#pragma comment(lib, "win32/avfilter.lib")
    //#pragma comment(lib, "win32/avformat.lib")
    //#pragma comment(lib, "win32/avutil.lib")
    //#pragma comment(lib, "win32/postproc.lib")
    //#pragma comment(lib, "win32/swresample.lib")
    //#pragma comment(lib, "win32/swscale.lib")
    #endif

    #ifdef av_err2str
    #undef av_err2str
    static av_always_inline char* av_err2str(int errnum)
    {
        // static char str[AV_ERROR_MAX_STRING_SIZE];
        // thread_local may be better than static in multi-thread circumstance
        thread_local char str[AV_ERROR_MAX_STRING_SIZE];
        memset(str, 0, sizeof(str));
        return av_make_error_string(str, AV_ERROR_MAX_STRING_SIZE, errnum);
    }
    #endif
    #pragma warning(default:4244 4819)
#endif // USE_ENCODE_MODULE