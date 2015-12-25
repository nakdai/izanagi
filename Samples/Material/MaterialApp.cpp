#include "MaterialApp.h"
#include "StateManager.h"
#include "StateBase.h"

CMaterialApp::CMaterialApp()
{
}

CMaterialApp::~CMaterialApp()
{
}

// キーボード押下
IZ_BOOL CMaterialApp::OnKeyDown(izanagi::sys::E_KEYBOARD_BUTTON key)
{
    return CStateManager::GetInstance().OnKeyDown(key);
}

// 初期化.
IZ_BOOL CMaterialApp::InitInternal(
    izanagi::IMemoryAllocator* allocator,
    izanagi::graph::CGraphicsDevice* device,
    izanagi::sample::CSampleCamera& camera)
{
    CStateManager::GetInstance().Create(this);

    return CStateManager::GetInstance().Init();
}

// 解放.
void CMaterialApp::ReleaseInternal()
{
    CStateManager::GetInstance().Destroy();
}

// 更新.
void CMaterialApp::UpdateInternal(izanagi::graph::CGraphicsDevice* device)
{
    GetCamera().Update();

    CStateManager::GetInstance().Update(
        0.0f,   // Not used.
        m_Allocator, m_Device);
}

// 描画.
void CMaterialApp::RenderInternal(izanagi::graph::CGraphicsDevice* device)
{
    CStateManager::GetInstance().Render(device);
}

// 背景色取得.
IZ_COLOR CMaterialApp::GetBgColor() const
{
    izanagi::CSceneStateBase* state = CStateManager::GetInstance().GetState(
        CStateManager::GetInstance().GetCurrentState());

    IZ_BOOL enableBgColor = (reinterpret_cast<CStateBase*>(state))->EnableBgColor();
    if (enableBgColor)
    {
        return (reinterpret_cast<CStateBase*>(state))->GetBgColor();
    }

    return CSampleApp::GetBgColor();
}
