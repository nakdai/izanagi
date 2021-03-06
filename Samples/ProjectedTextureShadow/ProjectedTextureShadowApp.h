#if !defined(__PROJECTED_TEXTURE_SHADOW_APP_H__)
#define __PROJECTED_TEXTURE_SHADOW_APP_H__

#include "izSampleKit.h"

class CShadow;

static const IZ_UINT SCREEN_WIDTH = 1280;
static const IZ_UINT SCREEN_HEIGHT = 720;

class CProjectedTextureShadowApp : public izanagi::sample::CSampleApp {
public:
    CProjectedTextureShadowApp();
    virtual ~CProjectedTextureShadowApp();

protected:
    // 初期化.
    virtual IZ_BOOL InitInternal(
        izanagi::IMemoryAllocator* allocator,
        izanagi::graph::CGraphicsDevice* device,
        izanagi::sample::CSampleCamera& camera);

    // 解放.
    virtual void ReleaseInternal();

    // 更新.
    virtual void UpdateInternal(izanagi::graph::CGraphicsDevice* device);

    // 描画.
    virtual void RenderInternal(izanagi::graph::CGraphicsDevice* device);

    void RenderForShadow(izanagi::graph::CGraphicsDevice* device);

private:
    izanagi::CDebugMesh* m_Torus;
    izanagi::CDebugMesh* m_Plane;

    izanagi::CDebugMeshAxis* m_Axis;

    izanagi::CImage* m_Img;

    izanagi::shader::CShaderBasic* m_Shader;

    CShadow* m_Shadow;
};

#endif    // #if !defined(__PROJECTED_TEXTURE_SHADOW_APP_H__)