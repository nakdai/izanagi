#if !defined(__IZANAGI_SCENEGRAPH_MESH_INSTANCE_H__)
#define __IZANAGI_SCENEGRAPH_MESH_INSTANCE_H__

#include "izStd.h"
#include "MSHFormat.h"
#include "MeshSetInstance.h"

namespace izanagi {
	class IMemoryAllocator;
	class CGraphicsDevice;
	class CMesh;
	class CMeshSet;
	class IMshRenderHandler;
	class CMeshGroupInstance;
	class CSkeletonInstance;
	class CMaterial;

	/** メッシュデータインスタンス.
	 */
	class CMeshInstance : public CObject {
	public:
		/** インスタンス作成
		 */
		static CMeshInstance* CreateMeshInstance(
			IMemoryAllocator* pAllocator,
			CMesh* pMesh);

	private:
		CMeshInstance();
		~CMeshInstance();

		NO_COPIABLE(CMeshInstance);

		IZ_DEFINE_INTERNAL_RELEASE();

	public:
		/** 描画.
		 */
		IZ_BOOL Render(
			IZ_UINT level,
			CSkeletonInstance* pSkl,
			IMshRenderHandler* pRenderHandler);

		/** スケルトンデータの適用.
		 */
		void ApplySkeleton(
			IZ_UINT level,
			CSkeletonInstance* pSkl);

		/** 描画に利用するマテリアルを設定.
		 */
		IZ_BOOL SetMaterial(
			IZ_UINT level,
			CMaterial* pMtrl);

		IZ_UINT GetMeshGroupNum() const { return m_nGroupNum; }

		IZ_UINT GetMeshSetNum(IZ_UINT level) const;

		CMeshSetInstance* GetMeshSet(IZ_UINT level, IZ_UINT idx);

	private:
		IMemoryAllocator* m_pAllocator;

		CMesh* m_pBody;

		IZ_UINT m_nGroupNum;
		CMeshGroupInstance** m_pGroups;
	};
}	// namespace izanagi

#endif	// #if !defined(__IZANAGI_SCENEGRAPH_MESH_INSTANCE_H__)
