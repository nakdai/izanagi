#if !defined(__STATE_BASE_H__)
#define __STATE_BASE_H__

#include "izSceneGraph.h"
#include "izDebugUtil.h"

namespace izanagi {
    namespace sample {
        class CSampleApp;
    }
}

class CSampleMdlRenderHandler;

class CStateBase : public izanagi::CSceneStateBase {
public:
    CStateBase(izanagi::sample::CSampleApp* app);
    virtual ~CStateBase() {}

public:
    // 初期化.
    virtual IZ_BOOL Init();

    // 更新.
    virtual IZ_BOOL Update();

    // 終了.
    virtual IZ_BOOL Destroy();

    virtual IZ_BOOL Render(izanagi::graph::CGraphicsDevice* device);

    // キー押下
    virtual IZ_BOOL OnKeyDown(IZ_UINT nChar);

    virtual IZ_BOOL EnableBgColor() const { return IZ_FALSE; }
    virtual IZ_COLOR GetBgColor() const { return 0xffffffff; }

protected:
    IZ_BOOL InitObject(
        izanagi::IMemoryAllocator* allocator,
        izanagi::graph::CGraphicsDevice* device,
        IZ_FLOAT cameraZ,
        IZ_PCSTR imgPath,
        IZ_PCSTR mshPath,
        IZ_PCSTR sklPath,
        IZ_PCSTR shdPath);

    void ReleaseObject();

    virtual IZ_UINT GetTexIdx() const = 0;
    virtual IZ_UINT GetShaderPassIdx() const = 0;

protected:
    void RenderName(
        izanagi::graph::CGraphicsDevice* device,
        const char* name);

    static void SetShaderParam(
        izanagi::shader::CShaderBasic* shader,
        const char* name,
        const void* value,
        IZ_UINT bytes);

protected:
    izanagi::sample::CSampleApp* m_App;

    izanagi::CImage* m_Img;
    izanagi::CModel* m_Mdl;
    izanagi::CMesh* m_Msh;
    izanagi::CSkeleton* m_Skl;
    izanagi::shader::CShaderBasic* m_Shd;

    CSampleMdlRenderHandler* m_MdlRenderHandler;
};

#endif    // #if !defined(__STATE_BASE_H__)