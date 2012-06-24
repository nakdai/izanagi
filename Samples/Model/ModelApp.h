#if !defined(__MODEL_APP_H__)
#define __MODEL_APP_H__

#include "izSampleKit.h"

static const IZ_UINT SCREEN_WIDTH = 1280;
static const IZ_UINT SCREEN_HEIGHT = 720;

class CModelApp : public izanagi::sample::CSampleApp {
public:
	CModelApp();
	virtual ~CModelApp();

protected:
	// 初期化.
	virtual IZ_BOOL InitInternal(
		izanagi::IMemoryAllocator* allocator,
		izanagi::CGraphicsDevice* device,
		izanagi::sample::CSampleCamera& camera);

	// 解放.
	virtual void ReleaseInternal();

	// 更新.
	virtual void UpdateInternal(
		izanagi::CCamera& camera,
		izanagi::CGraphicsDevice* device);

	// 描画.
	virtual void RenderInternal(izanagi::CGraphicsDevice* device);

private:
	izanagi::CImage* m_Img;
	izanagi::CModel* m_Mdl;
	izanagi::CMesh* m_Msh;
	izanagi::CSkeleton* m_Skl;
	izanagi::CShaderBasic* m_Shd;
};

#endif	// #if !defined(__MODEL_APP_H__)