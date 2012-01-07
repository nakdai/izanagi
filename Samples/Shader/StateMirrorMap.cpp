#include "StateMirrorMap.h"
#include "izGraph.h"
#include "izIo.h"

CStateMirrorMap::CStateMirrorMap(izanagi::SCameraParam& camera)
: m_Camera(camera)
{
	m_Img = IZ_NULL;
	m_Shader = IZ_NULL;
	m_Sphere = IZ_NULL;
}

CStateMirrorMap::~CStateMirrorMap()
{
	Destroy();
}

// 初期化.
IZ_BOOL CStateMirrorMap::Init()
{
	// Nothing is done...
	return IZ_TRUE;
}

// 更新
IZ_BOOL CStateMirrorMap::Update()
{
	return IZ_TRUE;
}

namespace {
	inline void _SetShaderParam(
		izanagi::CShaderBasic* shader,
		const char* name,
		void* value,
		IZ_UINT bytes)
	{
		izanagi::IZ_SHADER_HANDLE handle = shader->GetParameterByName(name);
		if (handle > 0) {
			shader->SetParamValue(
				handle,
				value,
				bytes);
		}
	}
}

// 描画.
IZ_BOOL CStateMirrorMap::Render(izanagi::CGraphicsDevice* device)
{
	izanagi::SMatrix mtxL2W;
	izanagi::SMatrix::SetUnit(mtxL2W);

	device->SetTexture(0, m_Img->GetTexture(0));

	m_Shader->Begin(0, IZ_FALSE);
	{
		if (m_Shader->BeginPass(0)) {
			// パラメータ設定
			_SetShaderParam(
				m_Shader,
				"g_mL2W",
				(void*)&mtxL2W,
				sizeof(izanagi::SMatrix));

			_SetShaderParam(
				m_Shader,
				"g_mW2C",
				(void*)&m_Camera.mtxW2C,
				sizeof(izanagi::SMatrix));

			_SetShaderParam(
				m_Shader,
				"g_mW2V",
				(void*)&m_Camera.mtxW2V,
				sizeof(izanagi::SMatrix));

			m_Shader->CommitChanges();

			m_Sphere->Draw();
		}
	}
	m_Shader->End();

	return IZ_TRUE;
}

// 開始
IZ_BOOL CStateMirrorMap::Enter(
	izanagi::IMemoryAllocator* allocator,
	void* val)
{
	izanagi::CGraphicsDevice* device = reinterpret_cast<izanagi::CGraphicsDevice*>(val);

	IZ_BOOL result = IZ_TRUE;

	// テクスチャ
	{
		izanagi::CFileInputStream in;
		VRETURN(in.Open("data/EnvMap.img"));

		m_Img = izanagi::CImage::CreateImage(
					allocator,
					device,
					&in);
		VGOTO(result = (m_Img != IZ_NULL), __EXIT__);
	}

	// シェーダ
	{
		izanagi::CFileInputStream in;
		VRETURN(in.Open("data/MirrorMapShader.shd"));

		m_Shader = izanagi::CShaderBasic::CreateShader<izanagi::CShaderBasic>(
					allocator,
					device,
					&in);
		VGOTO(result = (m_Shader != IZ_NULL), __EXIT__);
	}

	// 球
	{
		IZ_UINT flag = izanagi::E_DEBUG_MESH_VTX_FORM_POS
						| izanagi::E_DEBUG_MESH_VTX_FORM_NORMAL;

		m_Sphere = izanagi::CDebugMeshSphere::CreateDebugMeshSphere(
						allocator,
						device,
						flag,
						IZ_COLOR_RGBA(0xff, 0xff, 0xff, 0xff),
						5.0f,
						20, 20);
		VGOTO(result = (m_Sphere != IZ_NULL), __EXIT__);
	}

__EXIT__:
	if (!result) {
		Leave();
	}

	return result;
}

// 終了.
IZ_BOOL CStateMirrorMap::Destroy()
{
	return Leave();
}

// ステートから抜ける（終了）.
IZ_BOOL CStateMirrorMap::Leave()
{
	SAFE_RELEASE(m_Img);
	SAFE_RELEASE(m_Shader);
	SAFE_RELEASE(m_Sphere);

	return IZ_TRUE;
}

// キー押下
IZ_BOOL CStateMirrorMap::OnKeyDown(IZ_UINT nChar)
{
	return IZ_TRUE;
}