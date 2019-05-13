#pragma once

#include <string.h>
#include <stdint.h>

#ifdef __cplusplus

#include "croco/Index.h"

extern "C" {

#endif /* __cplusplus */

#ifndef NGT_API
#   if defined(_WIN32) || defined(_WIN64)
#       define NGT_API __declspec(dllimport)
#   else
#       define NGT_API extern
#   endif /* defined(_WIN32) || defined(_WIN64) */
#endif /* NGT_API */

#ifndef NGT_VERSION
#    define NGT_VERSION 12
#endif /* NGT_VERSION */

#define NGT_TRUE           (1)
#define NGT_FALSE          (0)

struct _NGTStr {
    size_t len;
    char *buff;
};

typedef void *NgtHandle;
typedef struct _NGTStr *NGTStr;

NGT_API int NgtVersion();
NGT_API int NgtSize();
NGT_API NgtHandle NgtCreate();
NGT_API void NgtFree(NgtHandle handle);
NGT_API void NgtStrFree(NGTStr str);
NGT_API void NgtCreateDB(
    NgtHandle handle,
    int dimension,
    int edgeSizeForCreation,
    int edgeSizeForSearch,
    const char* distanceType,
    const char* objectType
);
NGT_API int NgtEmptyIndex(NgtHandle handle);
NGT_API int NgtGetDimension(NgtHandle handle);

NGT_API void NgtExportIndex(NgtHandle handle);
NGT_API NGTStr NgtGetObjectString(NgtHandle handle);
NGT_API NGTStr NgtGetDistanceString(NgtHandle handle);
NGT_API NGTStr NgtGetLeafNodeString(NgtHandle handle);
NGT_API NGTStr NgtGetInternalNodeString(NgtHandle handle);
NGT_API NGTStr NgtGetObjectJson(NgtHandle handle);
NGT_API NGTStr NgtGetDistanceJson(NgtHandle handle);
NGT_API NGTStr NgtGetLeafNodeJson(NgtHandle handle);
NGT_API NGTStr NgtGetInternalNodeJson(NgtHandle handle);
NGT_API void NgtSetObjectData(NgtHandle handle, const uint8_t* data, size_t size);
NGT_API void NgtSetDistanceData(NgtHandle handle, const uint8_t* data, size_t size);
NGT_API void NgtSetLeafNodeData(NgtHandle handle, const uint8_t* data, size_t size);
NGT_API void NgtSetInternalNodeData(NgtHandle handle, const uint8_t* data, size_t size);
NGT_API void NgtSetObjectJson(NgtHandle handle, const char* json, size_t size);
NGT_API void NgtSetDistanceJson(NgtHandle handle, const char* json, size_t size);
NGT_API void NgtSetLeafNodeJson(NgtHandle handle, const char* json, size_t size);
NGT_API void NgtSetInternalNodeJson(NgtHandle handle, const char* json, size_t size);
NGT_API void NgtAddObjectData(NgtHandle handle, const uint8_t* data, size_t size);
NGT_API void NgtAddDistanceData(NgtHandle handle, const uint8_t* data, size_t size);
NGT_API void NgtAddLeafNodeData(NgtHandle handle, const uint8_t* data, size_t size);
NGT_API void NgtAddInternalNodeData(NgtHandle handle, const uint8_t* data, size_t size);
NGT_API void NgtImportIndex(NgtHandle handle);

NGT_API void NgtInsert(
    NgtHandle handle, 
    const char* json, size_t len,
    int objectCount, 
    int numThreads
);
NGT_API NGTStr NgtSearch(
    NgtHandle handle, 
    const char* json, size_t len, 
    int row,
    float epsilon,
    int edgeSize
);
NGT_API void NgtRemove(NgtHandle handle, int id);
NGT_API NGTStr NgtGetObject(NgtHandle handle, int id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

