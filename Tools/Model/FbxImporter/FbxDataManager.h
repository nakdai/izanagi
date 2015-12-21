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
};

struct PosData {
    IZ_UINT idxInMesh;
    FbxVector4 pos;
};

struct VertexData {
    IZ_UINT idxInMesh;
    FbxVector2 uv;
    FbxVector4 pos;

    bool operator==(const VertexData& rhs)
    {
        IZ_BOOL p0 = (this->pos.mData[0] == rhs.pos.mData[0]);
        IZ_BOOL p1 = (this->pos.mData[1] == rhs.pos.mData[1]);
        IZ_BOOL p2 = (this->pos.mData[2] == rhs.pos.mData[2]);

        IZ_BOOL u0 = (this->uv.mData[0] == rhs.uv.mData[0]);
        IZ_BOOL u1 = (this->uv.mData[1] == rhs.uv.mData[1]);
        IZ_BOOL u2 = (this->uv.mData[2] == rhs.uv.mData[2]);

        return (p0 && p1 && p2 && u0 && u1 && u2);
    }
};

struct MeshSubset {
    std::vector<Face> faces;

    FbxMesh* fbxMesh = nullptr;
    FbxSurfaceMaterial* mtrl = nullptr;

    std::vector<IZ_UINT> indices;
    std::vector<VertexData> vertices;

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
};

#endif  // #if !defined(__MODEL_LIB_FBX_DATA_MANAGER_H__)
