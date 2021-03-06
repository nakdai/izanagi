#include "StateRimLight.h"
#include "MySystem.h"
#include "MyCamera.h"
#include "MyAppl.h"
#include "DebugInfoRenderer.h"
#include "TextureManager.h"

CStateRimLight::CStateRimLight()
{
	m_pShader = IZ_NULL;

	m_pGrid = IZ_NULL;
	m_pAxis = IZ_NULL;
	m_pMesh = IZ_NULL;
}

CStateRimLight::~CStateRimLight()
{
}

IZ_BOOL CStateRimLight::Init()
{
	return IZ_TRUE;
}

IZ_BOOL CStateRimLight::Render(izanagi::graph::CGraphicsDevice* device)
{
	Render3D();
	Render2D();

	return IZ_TRUE;
}

IZ_BOOL CStateRimLight::Render2D()
{
	CDebugInfoRenderer::Render("RimLight");
	return IZ_TRUE;
}

IZ_BOOL CStateRimLight::Render3D()
{
	izanagi::graph::CGraphicsDevice* pDevice = CMySystem::GetInstance().GetGraphicsDevice();

	// 描画開始
	m_pShader->Begin(0);

	// 念のため確認
	IZ_UINT nPassCnt = m_pShader->GetPassCount();
	IZ_ASSERT(nPassCnt >= 2);

	// シェーダパラメータセット
	{
		izanagi::math::SMatrix mL2W;
		izanagi::math::SMatrix::SetUnit(mL2W);
		m_pShader->SetL2W(mL2W);

		m_pShader->SetW2C(CMyCamera::GetInstance().GetRawInterface().GetParam().mtxW2C);
		m_pShader->SetCameraPos(CMyCamera::GetInstance().GetRawInterface().GetParam().pos);
	}

	// グリッド描画
	m_pShader->BeginPass(1);
	m_pGrid->Draw();
	m_pAxis->Draw();
	m_pShader->EndPass();

	// テクスチャセット
	izanagi::graph::CTexture* pTex = izanagi::CTextureManager::GetInstance().Get(DEMO_TEX_EARTH);
	pDevice->SetTexture(0, pTex);

	IZ_BOOL bIsOnShader = CMyAppl::GetInstance().IsOnShader();

	// メッシュ描画
	m_pShader->BeginPass(bIsOnShader ? 0 : 2);
	m_pMesh->Draw();
	m_pShader->EndPass();

	// 描画終了
	m_pShader->End();

	return IZ_TRUE;
}

IZ_BOOL CStateRimLight::Update()
{
	return IZ_TRUE;
}

IZ_BOOL CStateRimLight::Destroy()
{
	Leave();
	return IZ_TRUE;
}

IZ_BOOL CStateRimLight::Enter(izanagi::IMemoryAllocator* allocator, void* val)
{
	izanagi::graph::CGraphicsDevice* pDevice = CMySystem::GetInstance().GetGraphicsDevice();
	izanagi::IMemoryAllocator* pAllocator = CMySystem::GetInstance().GetMemoryAllocator();

	// シェーダ
	m_pShader = CShaderBase::CreateShader<CRimLightShader>(
					pAllocator,
					pDevice,
					"./data/RimLightShader.bin");
	IZ_ASSERT(m_pShader != IZ_NULL);

	// テストなので、ここで各種パラメータ設定
	if (m_pShader != IZ_NULL) {
		// ライト
		izanagi::SParallelLightParam sParallel;
		{
			//sParallel.vDir.Set(-1.0f, -1.0f, -1.0f, 0.0f);
			sParallel.vDir.Set(0.0f, 0.0f, -1.0f, 0.0f);
			izanagi::math::SVector::Normalize(sParallel.vDir, sParallel.vDir);

			sParallel.color.Set(0.5f, 0.5f, 0.5f, 1.0f);
		}

		izanagi::SAmbientLightParam sAmbient;
		izanagi::math::SVector::SetZero(sAmbient.color);

		// マテリアル
		izanagi::SMaterialParam sMtrl;
		{
			sMtrl.vDiffuse.Set(1.0f, 1.0f, 1.0f, 1.0f);
			sMtrl.vAmbient.Set(1.0f, 1.0f, 1.0f, 1.0f);
			sMtrl.vSpecular.Set(1.0f, 1.0f, 1.0f, 20.0f);
			sMtrl.vRim.Set(1.0f, 1.0f, 1.0f, 0.8f);
		}

		m_pShader->SetLight(sParallel, sAmbient);
		m_pShader->SetMaterial(sMtrl);
	}

	// グリッド
	m_pGrid = izanagi::CDebugMeshGrid::CreateDebugMeshGrid(
				pAllocator,
				pDevice,
				0xffffffff,
				20, 20,
				10.0f);
	IZ_ASSERT(m_pGrid != IZ_NULL);

	// XYZ軸
	m_pAxis = izanagi::CDebugMeshAxis::CreateDebugMeshAxisDefault(
				pAllocator,
				pDevice);
	IZ_ASSERT(m_pAxis != IZ_NULL);

	// 球
	m_pMesh = izanagi::CDebugMeshSphere::CreateDebugMeshSphere(
					pAllocator,
					pDevice,
					izanagi::E_DEBUG_MESH_VTX_FORM_POS | izanagi::E_DEBUG_MESH_VTX_FORM_COLOR | izanagi::E_DEBUG_MESH_VTX_FORM_UV | izanagi::E_DEBUG_MESH_VTX_FORM_NORMAL,
					0xffffffff,
					5.0f,
					50, 50);
	IZ_ASSERT(m_pMesh != IZ_NULL);

	return IZ_TRUE;
}

IZ_BOOL CStateRimLight::Leave()
{
	SAFE_RELEASE(m_pShader);
	SAFE_RELEASE(m_pGrid);
	SAFE_RELEASE(m_pAxis);
	SAFE_RELEASE(m_pMesh);

	return IZ_TRUE;
}

IZ_BOOL CStateRimLight::OnKeyDown(IZ_UINT nChar)
{
	return IZ_TRUE;
}

IZ_BOOL CStateRimLight::OnMouseMove(IZ_INT x, IZ_INT y)
{
	return IZ_TRUE;
}

IZ_BOOL CStateRimLight::OnMouseWheel(IZ_SHORT zDelta)
{
	return IZ_TRUE;
}