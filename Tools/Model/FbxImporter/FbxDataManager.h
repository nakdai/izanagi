#if !defined(__MODEL_LIB_FBX_DATA_MANAGER_H__)
#define __MODEL_LIB_FBX_DATA_MANAGER_H__

#include "izToolKit.h"
#include "fbxsdk.h"

#include <map>
#include <set>

struct Face {
    IZ_UINT vtx[3];
};

struct UVData {
    IZ_UINT idxInMesh;
    FbxVector2 uv;

    FbxMesh* fbxMesh = nullptr;
    FbxSurfaceMaterial* mtrl = nullptr;
};

struct PosData {
    IZ_UINT idxInMesh;
    FbxVector4 pos;

    FbxMesh* fbxMesh = nullptr;
    FbxSurfaceMaterial* mtrl = nullptr;
};

struct VertexData {
    IZ_UINT idxInMesh;
    FbxVector2 uv;
    FbxVector4 pos;

    FbxMesh* fbxMesh = nullptr;
    FbxSurfaceMaterial* mtrl = nullptr;

    bool operator==(const VertexData& rhs)
    {
        IZ_BOOL isPos = (this->pos.mData[0] == rhs.pos.mData[0])
                        && (this->pos.mData[1] == rhs.pos.mData[1])
                        && (this->pos.mData[2] == rhs.pos.mData[2]);

        IZ_BOOL isUV = (this->uv.mData[0] == rhs.uv.mData[0])
                        && (this->uv.mData[1] == rhs.uv.mData[1])
                        && (this->uv.mData[2] == rhs.uv.mData[2]);

        IZ_BOOL isMesh = (this->fbxMesh == rhs.fbxMesh);
        IZ_BOOL isMtrl = (this->mtrl == rhs.mtrl);

        return (isPos && isUV && isMesh && isMtrl);
    }
};

struct IndexData
{
    IZ_UINT idxInMesh;

    FbxMesh* fbxMesh = nullptr;
    FbxSurfaceMaterial* mtrl = nullptr;

    IndexData(IZ_UINT idx, FbxMesh* mesh, FbxSurfaceMaterial* _mtrl)
        : idxInMesh(idx), fbxMesh(mesh), mtrl(_mtrl)
    {}
};

struct MeshSubset {
    std::vector<Face> faces;

    FbxMesh* fbxMesh = nullptr;
    FbxSurfaceMaterial* mtrl = nullptr;

    IZ_UINT vtxNum = 0;

    MeshSubset() {}

    MeshSubset(FbxMesh* _mesh, FbxSurfaceMaterial* _mtrl)
        : fbxMesh(_mesh), mtrl(_mtrl)
    {}

    bool operator==(const MeshSubset& rhs)
    {
        return (fbxMesh == rhs.fbxMesh && mtrl == rhs.mtrl);
    }
};

class FbxDataManager {
private:
    static FbxDataManager s_Instance;

public:
    static FbxDataManager& Instance()
    {
        return s_Instance;
    }

private:
    FbxDataManager() {}
    ~FbxDataManager() {}

public:
    IZ_BOOL Open(const char* path);

    void Close();

    IZ_UINT GetFbxMeshNum() const;

    FbxMesh* GetFbxMesh(IZ_UINT idx);

    IZ_UINT GetMeshNum() const;

    MeshSubset& GetMesh(IZ_UINT idx);
    const MeshSubset& GetMesh(IZ_UINT idx) const;

    IZ_UINT GetVtxNum() const;

    const VertexData& GetVertex(IZ_UINT idx) const;

    IZ_UINT GetNodeNum() const;

    FbxNode* GetNode(IZ_UINT idx);

    IZ_UINT GetNodeIndex(const FbxNode* node) const;

    FbxCluster* GetClusterByNode(const FbxNode* node);

    IZ_UINT ConvertToEntireVtxIdx(FbxMesh* mesh, IZ_UINT vtxIdxInMesh);

private:
    // ノードを集める.
    void GatherNodes(FbxNode* node);

    void GatherMeshes();

    void GatherClusters();

    void GatherFaces();

    void GatherVertices();

    void GatherPos(std::map<FbxMesh*, std::vector<PosData>>& posList);
    void GatherUV(std::map<FbxMesh*, std::vector<UVData>>& uvList);

private:
    FbxManager* m_manager{ nullptr };
    FbxScene* m_scene{ nullptr };

    std::vector<FbxNode*> m_nodes;
    std::vector<FbxMesh*> m_fbxMeshes;

    std::vector<FbxCluster*> m_clusters;

    std::vector<MeshSubset> m_meshes;

    std::vector<IndexData> m_indices;
    std::vector<VertexData> m_vertices;
};

#endif  // #if !defined(__MODEL_LIB_FBX_DATA_MANAGER_H__)
