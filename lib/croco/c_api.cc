#include "json.hpp"
#include "croco/c_api.h"

/**
 * get croco::NGT::Index version
 *
 * @access public
 * @return int
 */
int NgtVersion()
{
    return NGT_VERSION;
}

/**
 * get croco::NGT::Index size
 *
 * @access public
 * @return int
 */
int NgtSize()
{
    return sizeof(croco::Index);
}

/**
 * create a croco::NGT::Index handle
 *
 * @access public
 * @return NgtHandle
 */
NgtHandle NgtCreate()
{
    NgtHandle handle = new croco::Index;
    return handle;
}

/**
 * free a croco::NGT::Index handle
 *
 * @access public
 * @param  NgtHandle handle
 * @return void
 */
void NgtFree(NgtHandle handle)
{
    delete static_cast<croco::Index*>(handle);
}

/**
 * free a NgtStr handle
 *
 * @access public
 * @param  NgtStr str
 * @return void
 */
void NgtStrFree(NGTStr str)
{
    if (nullptr != str->buff) {
        delete[] str->buff;
    }

    if (nullptr != str) {
        delete str;
    }
}

/**
 * Create database
 *
 * @access public
 * @param  NgtHandle handle
 * @param  int dimension
 * @param  int edgeSizeForCreation
 * @param  int edgeSizeForSearch
 * @param  const char* distanceType
 * @param  const char* objectType
 * @return void
 */
void NgtCreateDB(
    NgtHandle handle, 
    int dimension,
    int edgeSizeForCreation,
    int edgeSizeForSearch,
    const char* distanceType,
    const char* objectType
) {
    croco::Index *index = static_cast<croco::Index*>(handle);

    index->create(
        dimension,
        edgeSizeForCreation,
        edgeSizeForSearch,
        std::string(distanceType),
        std::string(objectType)
    );
}

/**
 * Is empty index
 *
 * @access public
 * @return int
 */
int NgtEmptyIndex(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    if (!index->emptyIndex()) {
        return NGT_FALSE;
    }
    return NGT_TRUE;
}

/**
 * get dimension
 *
 * @access public
 * @return int
 */
int NgtGetDimension(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);
    return index->getDimension();
}

/**
 * 
 *
 * @access public
 * @return int
 */
void NgtExportIndex(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);
    index->exportIndex();
}

/**
 * 
 *
 * @access public
 * @return int
 */
NGTStr NgtGetObjectString(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string output;
    index->getObjectString(&output);

    NGTStr retval = new struct _NGTStr;
    retval->len = output.length();
    retval->buff = new char[retval->len + 1];
    strcpy(retval->buff, output.c_str());

    return retval;
}

/**
 * 
 *
 * @access public
 * @return int
 */
NGTStr NgtGetDistanceString(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string output;
    index->getDistanceString(&output);

    NGTStr retval = new struct _NGTStr;
    retval->len = output.length();
    retval->buff = new char[retval->len + 1];
    strcpy(retval->buff, output.c_str());

    return retval;
}

/**
 * 
 *
 * @access public
 * @return int
 */
NGTStr NgtGetLeafNodeString(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string output;
    index->getLeafNodeString(&output);

    NGTStr retval = new struct _NGTStr;
    retval->len = output.length();
    retval->buff = new char[retval->len + 1];
    strcpy(retval->buff, output.c_str());

    return retval;
}

/**
 * 
 *
 * @access public
 * @return int
 */
NGTStr NgtGetInternalNodeString(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string output;
    index->getInternalNodeString(&output);

    NGTStr retval = new struct _NGTStr;
    retval->len = output.length();
    retval->buff = new char[retval->len + 1];
    strcpy(retval->buff, output.c_str());

    return retval;
}

/**
 * 
 *
 * @access public
 * @return int
 */
void NgtSetObjectString(NgtHandle handle, const uint8_t* data, size_t len)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string strdata(reinterpret_cast<const char *>(data), len);
    index->setObjectString(strdata);
}

/**
 * 
 *
 * @access public
 * @return int
 */
void NgtSetDistanceString(NgtHandle handle, const uint8_t* data, size_t len)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string strdata(reinterpret_cast<const char *>(data), len);
    index->setDistanceString(strdata);
}

/**
 * 
 *
 * @access public
 * @return int
 */
void NgtSetLeafNodeString(NgtHandle handle, const uint8_t* data, size_t len)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string strdata(reinterpret_cast<const char *>(data), len);
    index->setLeafNodeString(strdata);
}

/**
 * 
 *
 * @access public
 * @return int
 */
void NgtSetInternalNodeString(NgtHandle handle, const uint8_t* data, size_t len)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string strdata(reinterpret_cast<const char *>(data), len);
    index->setInternalNodeString(strdata);
}

/**
 * 
 *
 * @access public
 * @return int
 */
void NgtAddObjectData(NgtHandle handle, const uint8_t* data, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    index->addObjectData(data, size);
}

/**
 * 
 *
 * @access public
 * @return int
 */
void NgtAddDistanceData(NgtHandle handle, const uint8_t* data, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    index->addDistanceData(data, size);
}

/**
 * 
 *
 * @access public
 * @return int
 */
void NgtAddLeafNodeData(NgtHandle handle, const uint8_t* data, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    index->addLeafNodeData(data, size);
}

/**
 * 
 *
 * @access public
 * @return int
 */
void NgtAddInternalNodeData(NgtHandle handle, const uint8_t* data, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    index->addInternalNodeData(data, size);
}

/**
 * 
 *
 * @access public
 * @return int
 */
void NgtImportIndex(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    index->importIndex();
}


/**
 * Insert object
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const char* path
 * @return void
 */
void NgtInsert(NgtHandle handle, const char* json, size_t len, int objectCount, int numThreads)
{
    croco::Index *index = static_cast<croco::Index*>(handle);
    std::string strjson(json, len);
    nlohmann::json parsed = nlohmann::json::parse(strjson);
    std::vector<float> data;

    for (auto &val : parsed) {
        data.push_back(val);
    }
    index->batchInsert(data, objectCount, numThreads);
}

/**
 * Search object
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const char* path
 * @return int
 */
NGTStr NgtSearch(NgtHandle handle, const char* json, size_t len, int row, float epsilon, int edgeSize)
{
    croco::Index *index = static_cast<croco::Index*>(handle);
    std::string strjson(json, len);
    nlohmann::json parsed = nlohmann::json::parse(strjson);
    std::vector<float> query;

    for (auto &val : parsed) {
        query.push_back(val);
    }

    std::vector<std::pair<int, float>> result = index->search(query, row, epsilon, edgeSize);

    nlohmann::json retj;
    int idx = 0;
    for (const auto &row : result) {
        retj[idx]["Rank"]     = idx + 1;
        retj[idx]["ID"]       = row.first;
        retj[idx]["Distance"] = row.second;
        idx++;
    }

    std::string retstr = retj.dump();
    NGTStr retval = new struct _NGTStr;
    retval->len = retstr.length();
    retval->buff = new char[retval->len + 1];
    strcpy(retval->buff, retstr.c_str());

    return retval;
}

/**
 * Remove object
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const char* path
 * @return int
 */
void NgtRemove(NgtHandle handle, int id)
{
    croco::Index *index = static_cast<croco::Index*>(handle);
    index->remove(id);
}

/**
 * Get object
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const char* path
 * @return int
 */
NGTStr NgtGetObject(NgtHandle handle, int id)
{
    croco::Index *index = static_cast<croco::Index*>(handle);
    std::vector<float> object = index->getObject(id);

    nlohmann::json retj;
    int idx = 0;
    for (const auto &row : object) {
        retj[idx] = row;
        idx++;
    }

    std::string retstr = retj.dump();
    NGTStr retval = new struct _NGTStr;
    retval->len = retstr.length();
    retval->buff = new char[retval->len + 1];
    strcpy(retval->buff, retstr.c_str());

    return retval;
}
