#include "StateSpotLight.h"
#include "izGraph.h"
#include "izIo.h"
#include "StateManager.h"

CStateSpotLight::CStateSpotLight(
	izanagi::sample::CSampleApp* app,
	izanagi::SCameraParam& camera)
: CStateBase(app, camera)
{
	m_Shader = IZ_NULL;

	m_Light = IZ_NULL;
    
    m_Sphere = IZ_NULL;
    m_Cube = IZ_NULL;
    m_Plane = IZ_NULL;
}

CStateSpotLight::~CStateSpotLight()
{
	Destroy();
}

// 描画.
IZ_BOOL CStateSpotLight::Render(izanagi::CGraphicsDevice* device)
{
	izanagi::SMatrix mtxL2W;
	izanagi::SMatrix::SetUnit(mtxL2W);

	m_Shader->Begin(0, IZ_FALSE);
	{
		if (m_Shader->BeginPass(0)) {
			// パラメータ設定
            SetShaderParam(
				m_Shader,
				"g_mW2C",
				(void*)&m_Camera.mtxW2C,
				sizeof(m_Camera.mtxW2C));

			SetShaderParam(
				m_Shader,
				"g_vEye",
				(void*)&m_Camera.pos,
				sizeof(m_Camera.pos));

            SetShaderParam(
				m_Shader,
                "g_SpotLightPos",
                (void*)&m_SpotLight.vPos,
                sizeof(m_SpotLight.vPos));
            SetShaderParam(
				m_Shader,
                "g_SpotLight",
                (void*)&m_SpotLight.param,
                sizeof(m_SpotLight.param));
            SetShaderParam(
				m_Shader,
                "g_SpotLightColor",
                (void*)&m_SpotLight.color,
                sizeof(m_SpotLight.color));
            SetShaderParam(
				m_Shader,
                "g_SpotLightDir",
                (void*)&m_SpotLight.vDir,
                sizeof(m_SpotLight.vDir));

            // 地面
            RenderScene(
                device, 
                m_Plane,
                izanagi::CVector(0.0f, 0.0f, 0.0f));

            // 球
            RenderScene(
                device, 
                m_Sphere,
                izanagi::CVector(10.0f, 5.0f, 10.0f));
            RenderScene(
                device, 
                m_Sphere,
                izanagi::CVector(10.0f, 5.0f, -10.0f));

            // キューブ
            RenderScene(
                device, 
                m_Cube,
                izanagi::CVector(-10.0f, 5.0f, -10.0f));
            RenderScene(
                device, 
                m_Cube,
                izanagi::CVector(-10.0f, 5.0f, 10.0f));
		}

        if (m_Shader->BeginPass(1)) {
			// パラメータ設定
            SetShaderParam(
				m_Shader,
				"g_mW2C",
				(void*)&m_Camera.mtxW2C,
				sizeof(m_Camera.mtxW2C));

			SetShaderParam(
				m_Shader,
				"g_vEye",
				(void*)&m_Camera.pos,
				sizeof(m_Camera.pos));

            // ライト
			RenderScene(
                device, 
                m_Light,
                m_SpotLight.vPos);
        }
	}
	m_Shader->End();

	RenderName(device, "SpotLight");

	return IZ_TRUE;
}

void CStateSpotLight::RenderScene(
    izanagi::CGraphicsDevice* device,
    izanagi::CDebugMesh* mesh,
    const izanagi::SVector& position)
{
    izanagi::SMatrix mtxL2W;
    izanagi::SMatrix::GetTrans(mtxL2W, position);

    SetShaderParam(
	    m_Shader,
	    "g_mL2W",
	    (void*)&mtxL2W,
	    sizeof(mtxL2W));

	m_Shader->CommitChanges();

	mesh->Draw();
}

// 開始
IZ_BOOL CStateSpotLight::Enter(
	izanagi::IMemoryAllocator* allocator,
	void* val)
{
	izanagi::CGraphicsDevice* device = reinterpret_cast<izanagi::CGraphicsDevice*>(val);

	IZ_BOOL result = IZ_TRUE;

	// シェーダ
	{
		izanagi::CFileInputStream in;
		VRETURN(in.Open("data/SpotLightShader.shd"));

		m_Shader = izanagi::CShaderBasic::CreateShader<izanagi::CShaderBasic>(
					allocator,
					device,
					&in);
		VGOTO(result = (m_Shader != IZ_NULL), __EXIT__);
	}

    IZ_UINT flag = izanagi::E_DEBUG_MESH_VTX_FORM_POS
				| izanagi::E_DEBUG_MESH_VTX_FORM_COLOR;

    // ライト
    {
        m_Light = izanagi::CDebugMeshSphere::CreateDebugMeshSphere(
            allocator,
            device,
            flag,
            IZ_COLOR_RGBA(0xff, 0xff, 0x00, 0xff),
            0.5f, 10, 10);
        VGOTO(result = (m_Light != IZ_NULL), __EXIT__);
    }

	// 球
	{
		m_Sphere = izanagi::CDebugMeshSphere::CreateDebugMeshSphere(
            allocator,
            device,
            flag,
            IZ_COLOR_RGBA(0x00, 0x00, 0x00, 0xff),
            5.0f,
            20, 20);
        VGOTO(result = (m_Sphere != IZ_NULL), __EXIT__);
	}

    // キューブ
    {
        m_Cube = izanagi::CDebugMeshBox::CreateDebugMeshBox(
            allocator,
            device,
            flag,
            IZ_COLOR_RGBA(0x00, 0x00, 0x00, 0xff),
            10.0f, 10.0f, 10.0f);
        VGOTO(result = (m_Cube != IZ_NULL), __EXIT__);
    }

    // 地面
    {
        m_Plane = izanagi::CDebugMeshRectangle::CreateDebugMeshRectangle(
            allocator,
            device,
            flag,
            IZ_COLOR_RGBA(0x00, 0x00, 0x00, 0xff),
            10, 10,
            50.0f, 50.0f);
        VGOTO(result = (m_Plane != IZ_NULL), __EXIT__);
    }

    // ポイントライト
    {
        m_SpotLight.vPos.Set(0.0f, 15.0f, 0.0f);
        m_SpotLight.vDir.Set(0.0f, -1.0f, 0.0f);
        m_SpotLight.color.Set(1.0f, 1.0f, 1.0f, 1.0f);
        m_SpotLight.param.Set(0.0f, 0.0f, 0.01f, 3.0f);
    }

__EXIT__:
	if (!result) {
		Leave();
	}

	return result;
}

// ステートから抜ける（終了）.
IZ_BOOL CStateSpotLight::Leave()
{
	SAFE_RELEASE(m_Shader);

    SAFE_RELEASE(m_Light);
	SAFE_RELEASE(m_Sphere);
    SAFE_RELEASE(m_Cube);
    SAFE_RELEASE(m_Plane);

	return IZ_TRUE;
}
