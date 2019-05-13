#include "json.hpp"
#include "croco/c_api.h"

/**
 * Get croco::NGT::Index version
 *
 * @access public
 * @return int
 */
int NgtVersion()
{
    return NGT_VERSION;
}

/**
 * Get croco::NGT::Index size
 *
 * @access public
 * @return int
 */
int NgtSize()
{
    return sizeof(croco::Index);
}

/**
 * Create a croco::NGT::Index handle
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
 * Free a croco::NGT::Index handle
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
 * Free a NgtStr handle
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
 * @param  NgtHandle handle
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
 * Get dimension
 *
 * @access public
 * @param  NgtHandle handle
 * @return int
 */
int NgtGetDimension(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);
    return index->getDimension();
}

/**
 * Export index
 *
 * @access public
 * @param  NgtHandle handle
 * @return void
 */
void NgtExportIndex(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);
    index->exportIndex();
}

/**
 * Get binary string of object structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @return NGTStr
 */
NGTStr NgtGetObjectString(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string output = index->getObjectString();

    NGTStr retval = new struct _NGTStr;
    retval->len = output.size();
    retval->buff = new char[retval->len];
    memcpy(retval->buff, output.c_str(), retval->len);

    return retval;
}

/**
 * Get binary string of distance structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @return NGTStr
 */
NGTStr NgtGetDistanceString(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string output = index->getDistanceString();

    NGTStr retval = new struct _NGTStr;
    retval->len = output.size();
    retval->buff = new char[retval->len];
    memcpy(retval->buff, output.c_str(), retval->len);

    return retval;
}

/**
 * Get binary string of leaf node structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @return NGTStr
 */
NGTStr NgtGetLeafNodeString(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string output = index->getLeafNodeString();

    NGTStr retval = new struct _NGTStr;
    retval->len = output.size();
    retval->buff = new char[retval->len];
    memcpy(retval->buff, output.c_str(), retval->len);

    return retval;
}

/**
 * Get binary string of internal node structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @return NGTStr
 */
NGTStr NgtGetInternalNodeString(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string output = index->getInternalNodeString();

    NGTStr retval = new struct _NGTStr;
    retval->len = output.size();
    retval->buff = new char[retval->len];
    memcpy(retval->buff, output.c_str(), retval->len);

    return retval;
}

/**
 * Get json string of object structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @return NGTStr
 */
NGTStr NgtGetObjectJson(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string output = index->getObjectJson();

    NGTStr retval = new struct _NGTStr;
    retval->len = output.size();
    retval->buff = new char[retval->len + 1];
    strcpy(retval->buff, output.c_str());

    return retval;
}

/**
 * Get json string of distance structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @return NGTStr
 */
NGTStr NgtGetDistanceJson(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string output = index->getDistanceJson();

    NGTStr retval = new struct _NGTStr;
    retval->len = output.size();
    retval->buff = new char[retval->len + 1];
    strcpy(retval->buff, output.c_str());

    return retval;
}

/**
 * Get json string of leaf node structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @return NGTStr
 */
NGTStr NgtGetLeafNodeJson(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string output = index->getLeafNodeJson();

    NGTStr retval = new struct _NGTStr;
    retval->len = output.size();
    retval->buff = new char[retval->len + 1];
    strcpy(retval->buff, output.c_str());

    return retval;
}

/**
 * Get json string of internal node structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @return NGTStr
 */
NGTStr NgtGetInternalNodeJson(NgtHandle handle)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string output = index->getInternalNodeJson();

    NGTStr retval = new struct _NGTStr;
    retval->len = output.size();
    retval->buff = new char[retval->len + 1];
    strcpy(retval->buff, output.c_str());

    return retval;
}

/**
 * Set binary data of object structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const uint8_t* data
 * @param  size_t size
 * @return void
 */
void NgtSetObjectData(NgtHandle handle, const uint8_t* data, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string strdata(reinterpret_cast<const char *>(data), size);
    index->setObjectString(strdata);
}

/**
 * Set binary data of distance structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const uint8_t* data
 * @param  size_t size
 * @return void
 */
void NgtSetDistanceData(NgtHandle handle, const uint8_t* data, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string strdata(reinterpret_cast<const char *>(data), size);
    index->setDistanceString(strdata);
}

/**
 * Set binary data of leaf node structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const uint8_t* data
 * @param  size_t size
 * @return void
 */
void NgtSetLeafNodeData(NgtHandle handle, const uint8_t* data, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string strdata(reinterpret_cast<const char *>(data), size);
    index->setLeafNodeString(strdata);
}

/**
 * Set binary data of internal node structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const uint8_t* data
 * @param  size_t size
 * @return void
 */
void NgtSetInternalNodeData(NgtHandle handle, const uint8_t* data, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string strdata(reinterpret_cast<const char *>(data), size);
    index->setInternalNodeString(strdata);
}

/**
 * Set json data of object structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const char* json
 * @param  size_t size
 * @return void
 */
void NgtSetObjectJson(NgtHandle handle, const char* json, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string input(json, size);
    index->setObjectJson(input);
}

/**
 * Set json data of distance structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const char* json
 * @param  size_t size
 * @return void
 */
void NgtSetDistanceJson(NgtHandle handle, const char* json, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string input(json, size);
    index->setDistanceJson(input);
}

/**
 * Set json data of leaf node structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const char* json
 * @param  size_t size
 * @return void
 */
void NgtSetLeafNodeJson(NgtHandle handle, const char* json, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string input(json, size);
    index->setLeafNodeJson(input);
}

/**
 * Set json data of internal node structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const char* json
 * @param  size_t size
 * @return void
 */
void NgtSetInternalNodeJson(NgtHandle handle, const char* json, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    std::string input(json, size);
    index->setInternalNodeJson(input);
}

/**
 * Add binary data of object structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const uint8_t* data
 * @param  size_t size
 * @return void
 */
void NgtAddObjectData(NgtHandle handle, const uint8_t* data, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    index->addObjectData(data, size);
}

/**
 * Add binary data of distance structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const uint8_t* data
 * @param  size_t size
 * @return void
 */
void NgtAddDistanceData(NgtHandle handle, const uint8_t* data, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    index->addDistanceData(data, size);
}

/**
 * Add binary data of leaf node structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const uint8_t* data
 * @param  size_t size
 * @return void
 */
void NgtAddLeafNodeData(NgtHandle handle, const uint8_t* data, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    index->addLeafNodeData(data, size);
}

/**
 * Add binary data of internal node structure.
 *
 * @access public
 * @param  NgtHandle handle
 * @param  const uint8_t* data
 * @param  size_t size
 * @return void
 */
void NgtAddInternalNodeData(NgtHandle handle, const uint8_t* data, size_t size)
{
    croco::Index *index = static_cast<croco::Index*>(handle);

    index->addInternalNodeData(data, size);
}

/**
 * Import index
 *
 * @access public
 * @param  NgtHandle handle
 * @return void
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
