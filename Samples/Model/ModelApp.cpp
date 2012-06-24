#include "ModelApp.h"

/////////////////////////////////////////////////

// ジョイントマトリクスを描画時に設定するためのハンドラ
class CSampleMdlRenderHandler : public izanagi::IMshRenderHandler {
	// NOTE
	// IMshRenderHandlerが持つインスタンス作成用メソッドに対して
	// コンストラクタを見せるために必要
	friend class izanagi::IMshRenderHandler;

private:
	CSampleMdlRenderHandler()
	{
		m_pShader = IZ_NULL;
	}

	~CSampleMdlRenderHandler()
	{
		SAFE_RELEASE(m_pShader);
	}

public:
	virtual void BeginRenderMesh();
	virtual void EndRenderMesh();

	virtual void SetJointMatrix(
		IZ_UINT nIdx,
		const izanagi::SMatrix& mtx);

	virtual void CommitChanges();

public:
	void SetShader(izanagi::IShader* pShader)
	{
		SAFE_REPLACE(m_pShader, pShader);
	}

	izanagi::IShader* GetShader() { return m_pShader; }

private:
	izanagi::IShader* m_pShader;

	IZ_UINT m_nCnt;
	izanagi::SMatrix m_Mtx[48];

	izanagi::IZ_SHADER_HANDLE m_Handle;
};

void CSampleMdlRenderHandler::BeginRenderMesh()
{
	m_nCnt = 0;

	izanagi::SMatrix::SetUnit(m_Mtx[0]);
	izanagi::SMatrix::SetUnit(m_Mtx[1]);
	izanagi::SMatrix::SetUnit(m_Mtx[2]);
	izanagi::SMatrix::SetUnit(m_Mtx[3]);

	m_Handle = 0;
}

void CSampleMdlRenderHandler::EndRenderMesh()
{
}

void CSampleMdlRenderHandler::SetJointMatrix(
	IZ_UINT nIdx,
	const izanagi::SMatrix& mtx)
{
	izanagi::SMatrix::Copy(m_Mtx[m_nCnt], mtx);
	m_nCnt++;
}

void CSampleMdlRenderHandler::CommitChanges()
{
	if (m_Handle == 0) {
		m_Handle = m_pShader->GetParameterByName("vJointMatrix");
		IZ_ASSERT(m_Handle > 0);
	}

	m_pShader->SetParamValue(
		m_Handle,
		m_Mtx,
		sizeof(izanagi::SMatrix) * m_nCnt);

	m_pShader->CommitChanges();
}

static CSampleMdlRenderHandler* s_MdlRenderHandler = IZ_NULL;

/////////////////////////////////////////////////

#if 1
	#define MSH_FILE_NAME	"data/Seymour.msh"
	#define SKL_FILE_NAME	"data/Seymour.skl"
	#define IMG_IDX		(0)
	#define CAMERA_Z	(30.0f)
#else
	#define MSH_FILE_NAME	"data/tiny.msh"
	#define SKL_FILE_NAME	"data/tiny.skl"
	#define IMG_IDX		(1)
	#define CAMERA_Z	(300.0f)
#endif

CModelApp::CModelApp()
{
	m_Img = IZ_NULL;
	m_Mdl = IZ_NULL;
	m_Msh = IZ_NULL;
	m_Skl = IZ_NULL;
	m_Shd = IZ_NULL;
}

CModelApp::~CModelApp()
{
}

// 初期化.
IZ_BOOL CModelApp::InitInternal(
	izanagi::IMemoryAllocator* allocator,
	izanagi::CGraphicsDevice* device,
	izanagi::sample::CSampleCamera& camera)
{
	IZ_BOOL result = IZ_TRUE;

	// Texture
	{
		izanagi::CFileInputStream in;
		VRETURN(in.Open("data/ModelImage.img"));

		m_Img = izanagi::CImage::CreateImage(
					allocator,
					device,
					&in);

		VGOTO(result = (m_Img != IZ_NULL), __EXIT__);
	}

	// Mesh
	{
		izanagi::CFileInputStream in;
		VRETURN(in.Open(MSH_FILE_NAME));

		m_Msh = izanagi::CMesh::CreateMesh(
					allocator,
					device,
					&in);
		
		VGOTO(result = (m_Msh != IZ_NULL), __EXIT__);
	}

	// Skelton
	{
		izanagi::CFileInputStream in;
		VRETURN(in.Open(SKL_FILE_NAME));

		m_Skl = izanagi::CSkeleton::CreateSkeleton(
					allocator,
					&in);

		VGOTO(result = (m_Skl != IZ_NULL), __EXIT__);
	}

	// Shader
	{
		izanagi::CFileInputStream in;
		VRETURN(in.Open("data/SkinShader.shd"));

		m_Shd = izanagi::CShaderBasic::CreateShader<izanagi::CShaderBasic>(
					allocator,
					device,
					&in);

		VGOTO(result = (m_Shd != IZ_NULL), __EXIT__);

		// ジョイントマトリクスを描画時に設定するためのハンドラ
		s_MdlRenderHandler = izanagi::IMshRenderHandler::CreateMshRenderHandler<CSampleMdlRenderHandler>(allocator);
		s_MdlRenderHandler->SetShader(m_Shd);
		VGOTO(result = (s_MdlRenderHandler != IZ_NULL), __EXIT__);
	}

	// Model
	{
		m_Mdl = izanagi::CModel::CreateModel(
					allocator,
					m_Msh,
					m_Skl,
					s_MdlRenderHandler);

		VGOTO(result = (m_Mdl != IZ_NULL), __EXIT__);
	}

	// カメラ
	camera.Init(
		izanagi::CVector(0.0f, 5.0f, CAMERA_Z, 1.0f),
		izanagi::CVector(0.0f, 5.0f, 0.0f, 1.0f),
		izanagi::CVector(0.0f, 1.0f, 0.0f, 1.0f),
		1.0f,
		500.0f,
		izanagi::CMath::Deg2Rad(60.0f),
		(IZ_FLOAT)SCREEN_WIDTH / SCREEN_HEIGHT);
	camera.Update();

__EXIT__:
	if (!result) {
		ReleaseInternal();
	}

	return IZ_TRUE;
}

// 解放.
void CModelApp::ReleaseInternal()
{
	SAFE_RELEASE(m_Img);
	SAFE_RELEASE(m_Mdl);
	SAFE_RELEASE(m_Msh);
	SAFE_RELEASE(m_Skl);
	SAFE_RELEASE(m_Shd);

	SAFE_RELEASE(s_MdlRenderHandler);
}

// 更新.
void CModelApp::UpdateInternal(
	izanagi::CCamera& camera,
	izanagi::CGraphicsDevice* device)
{
	camera.Update();
	m_Mdl->Update();
}

namespace {
	inline void _SetShaderParam(
		izanagi::CShaderBasic* shader,
		const char* name,
		const void* value,
		IZ_UINT bytes)
	{
		izanagi::IZ_SHADER_HANDLE handle = shader->GetParameterByName(name);
		IZ_ASSERT(handle != 0);

		shader->SetParamValue(
			handle,
			value,
			bytes);
	}
}

// 描画.
void CModelApp::RenderInternal(izanagi::CGraphicsDevice* device)
{
	izanagi::sample::CSampleCamera& camera = GetCamera();

	IZ_UINT passCnt = m_Shd->Begin(0, IZ_FALSE);
	{
		IZ_ASSERT(passCnt >= 1);
		if (m_Shd->BeginPass(0)) {
			// シェーダ定数セット
			{
				_SetShaderParam(
					m_Shd,
					"g_mW2C",
					(void*)&camera.GetParam().mtxW2C,
					sizeof(camera.GetParam().mtxW2C));
			}

			// テクスチャセット
			device->SetTexture(0, m_Img->GetTexture(IMG_IDX));

			m_Shd->CommitChanges();

			// モデル描画
			m_Mdl->Render();

			m_Shd->EndPass();
		}
	}
	m_Shd->End();
}