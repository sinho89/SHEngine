#pragma once
#ifdef USE_ENCODE_MODULE
#include "CUDA/v11.7/include/cuda_d3d11_interop.h"
#include "CUDA/v11.7/include/cuda.h"

// https://developer.nvidia.com/nvidia-video-codec-sdk/download
#include "CUDA/v11.7/include/cuviddec.h"
#include "CUDA/v11.7/include/nvcuvid.h"
#include "CUDA/v11.7/include/nvEncodeAPI.h"

#pragma comment(lib, "ixrEngine/03.Graphics/ixrEncode/00.ThirdParty/CUDA/v11.7/lib/x64/cuda.lib")
#pragma comment(lib, "ixrEngine/03.Graphics/ixrEncode/00.ThirdParty/CUDA/v11.7/lib/x64/cudart.lib")
#pragma comment(lib, "ixrEngine/03.Graphics/ixrEncode/00.ThirdParty/CUDA/v11.7/lib/x64/nvencodeapi.lib")

//#pragma comment(lib, "v11.4/lib/x64/nvrtc-prev/nvrtc.lib")
//#pragma comment(lib, "v11.4/lib/x64/cublas.lib")
//#pragma comment(lib, "v11.4/lib/x64/cublasLt.lib")
//#pragma comment(lib, "v11.4/lib/x64/cudadevrt.lib")
//#pragma comment(lib, "v11.4/lib/x64/cudart_static.lib")
//#pragma comment(lib, "v11.4/lib/x64/cufft.lib")
//#pragma comment(lib, "v11.4/lib/x64/cufftw.lib")
//#pragma comment(lib, "v11.4/lib/x64/cufilt.lib")
//#pragma comment(lib, "v11.4/lib/x64/curand.lib")
//#pragma comment(lib, "v11.4/lib/x64/cusolver.lib")
//#pragma comment(lib, "v11.4/lib/x64/cusolverMg.lib")
//#pragma comment(lib, "v11.4/lib/x64/cusparse.lib")
//#pragma comment(lib, "v11.4/lib/x64/nppc.lib")
//#pragma comment(lib, "v11.4/lib/x64/nppial.lib")
//#pragma comment(lib, "v11.4/lib/x64/nppicc.lib")
//#pragma comment(lib, "v11.4/lib/x64/nppidei.lib")
//#pragma comment(lib, "v11.4/lib/x64/nppif.lib")
//#pragma comment(lib, "v11.4/lib/x64/nppig.lib")
//#pragma comment(lib, "v11.4/lib/x64/nppim.lib")
//#pragma comment(lib, "v11.4/lib/x64/nppist.lib")
//#pragma comment(lib, "v11.4/lib/x64/nppisu.lib")
//#pragma comment(lib, "v11.4/lib/x64/nppitc.lib")
//#pragma comment(lib, "v11.4/lib/x64/npps.lib")
//#pragma comment(lib, "v11.4/lib/x64/nvblas.lib")
//#pragma comment(lib, "v11.4/lib/x64/nvjpeg.lib")
//#pragma comment(lib, "v11.4/lib/x64/nvml.lib")
//#pragma comment(lib, "v11.4/lib/x64/nvptxcompiler_static.lib")
//#pragma comment(lib, "v11.4/lib/x64/nvrtc.lib")

//#define NVENC_API_CALL( nvencAPI )                                                                                 \
//    do                                                                                                             \
//    {                                                                                                              \
//        NVENCSTATUS errorCode = nvencAPI;                                                                          \
//        if( errorCode != NV_ENC_SUCCESS)                                                                           \
//        {                                                                                                          \
//            std::ostringstream errorLog;                                                                           \
//            errorLog << #nvencAPI << " returned error " << errorCode;                                              \
//            throw NVENCException::makeNVENCException(errorLog.str(), errorCode, __FUNCTION__, __FILE__, __LINE__); \
//        }                                                                                                          \
//    } while (0)

//#define CUDA_DRVAPI_CALL( call )                                                                                                 \
//    do                                                                                                                           \
//    {                                                                                                                            \
//        CUresult err__ = call;                                                                                                   \
//        if (err__ != CUDA_SUCCESS)                                                                                               \
//        {                                                                                                                        \
//            const char *szErrName = NULL;                                                                                        \
//            cuGetErrorName(err__, &szErrName);                                                                                   \
//            std::ostringstream errorLog;                                                                                         \
//            errorLog << "CUDA driver API error " << szErrName ;                                                                  \
//            throw NVENCException::makeNVENCException(errorLog.str(), NV_ENC_ERR_GENERIC, __FUNCTION__, __FILE__, __LINE__);      \
//        }                                                                                                                        \
//    }                                                                                                                            \
//    while (0)

#define CUDA_DRVAPI_CALL( call )                                                                                                 \
    do                                                                                                                           \
    {                                                                                                                            \
        CUresult err__ = call;                                                                                                   \
        if (err__ != CUDA_SUCCESS)                                                                                               \
        {                                                                                                                        \
             assert(false);                                                                                                      \
        }                                                                                                                        \
    }                                                                                                                            \
    while (0)

#define NVENC_API_CALL( nvencAPI )                                                                                 \
    do                                                                                                             \
    {                                                                                                              \
        NVENCSTATUS errorCode = nvencAPI;                                                                          \
        if( errorCode != NV_ENC_SUCCESS)                                                                           \
        {                                                                                                          \
            assert(false);                                                                                         \
        }                                                                                                          \
    } while (0)

static bool LoadCudaDLL() {
    __try {
        return !FAILED(__HrLoadAllImportsForDll("nvcuda.dll"));
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
    }
    return false;
}
#endif