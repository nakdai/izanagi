#include "PhotoItemManager.h"
#include "PhotoItem.h"
#include "LoadTextureJob.h"
#include "Utility.h"
#include "Configure.h"

//////////////////////////////

PhotoItemList::PhotoItemList()
{
}

PhotoItemList::~PhotoItemList()
{
}

void PhotoItemList::RenderWithTexture(
    izanagi::graph::CGraphicsDevice* device,
    izanagi::shader::CShaderBasic* shader)
{
    izanagi::CStdList<PhotoItem>::Item* item = this->GetTop();

    while (item != IZ_NULL) {
        PhotoItem* photoItem = item->GetData();

        if (photoItem->HasTexture()) {
            const izanagi::math::SMatrix& mtxL2W = photoItem->GetL2W();

            Utility::SetShaderParam(
                shader,
                "g_mL2W",
                (void*)&mtxL2W,
                sizeof(mtxL2W));

            shader->CommitChanges(device);
            photoItem->RenderFront(device);
        }

        item = item->GetNext();
    }
}

void PhotoItemList::RenderWithoutTexture(
    izanagi::graph::CGraphicsDevice* device,
    izanagi::shader::CShaderBasic* shader)
{
    izanagi::CStdList<PhotoItem>::Item* item = this->GetTop();

    while (item != IZ_NULL) {
        PhotoItem* photoItem = item->GetData();

        const izanagi::math::SMatrix& mtxL2W = photoItem->GetL2W();

        Utility::SetShaderParam(
            shader,
            "g_mL2W",
            (void*)&mtxL2W,
            sizeof(mtxL2W));

        shader->CommitChanges(device);

        if (!photoItem->HasTexture()) {
            photoItem->RenderFront(device);
        }

        photoItem->RenderTopAndSide(device);

        item = item->GetNext();
    }
}

//////////////////////////////

PhotoItemManager PhotoItemManager::s_Instance;

PhotoItemManager& PhotoItemManager::Instance()
{
    return s_Instance;
}

PhotoItemManager::PhotoItemManager()
{
    m_Shader = IZ_NULL;
}

PhotoItemManager::~PhotoItemManager()
{
    SAFE_RELEASE(m_Shader);
}

IZ_BOOL PhotoItemManager::Init(
    izanagi::IMemoryAllocator* allocator,
    izanagi::graph::CGraphicsDevice* device,
    IZ_UINT itemNum)
{
    // Compute item count per list.
    IZ_UINT itemNumPerList = itemNum / COUNTOF(m_PhotoItemList);
    itemNumPerList = (itemNumPerList == 0 ? itemNum : itemNumPerList);

    IZ_FLOAT radius[] = {
        Configure::InnerRadius - Configure::Depth * 2.0f,
        Configure::OuterRadius - (Configure::OuterRadius - Configure::InnerRadius) * 0.5f,
        Configure::MostOuterRadius - (Configure::MostOuterRadius - Configure::OuterRadius) * 0.5f,
    };

    const izanagi::math::CVector baseNml(0.0f, 0.0f, 1.0f, 0.0f);

    PhotoItem* prevItem = IZ_NULL;

    // Create photo items.
    for (IZ_UINT i = 0; i < COUNTOF(m_PhotoItemList); i++) {
        // TODO
        IZ_FLOAT step = -IZ_MATH_PI2 / itemNumPerList;

        IZ_FLOAT angle = 0.0f;

        for (IZ_UINT n = 0; n < itemNumPerList; n++) {
            PhotoItem* item = IZ_NULL;
            
            if (prevItem != IZ_NULL) {
                item = PhotoItem::Create(
                    allocator, device,
                    prevItem->GetMesh());
            }
            else {
                item = PhotoItem::Create(allocator, device, IZ_NULL);
            }

            prevItem = item;

            IZ_FLOAT s = izanagi::math::CMath::SinF(angle);
            IZ_FLOAT c = izanagi::math::CMath::CosF(angle);
            
            // Positon.
            izanagi::math::CVector pos(
                c * radius[i],
                Configure::Height * i,
                s * radius[i]);

            // Rotate.
            izanagi::math::CVector nml(-c, 0.0f, -s, 0.0f);
            IZ_FLOAT dot = izanagi::math::SVector::Dot(nml, baseNml);
            IZ_FLOAT theta = ::acosf(dot);
            theta = (nml.x < 0.0f ? -theta : theta);

            item->SetPositionAndRotation(pos, theta);

            m_PhotoItemList[i].AddTail(item->GetListItem());

            angle += step;
        }
        
        itemNum -= itemNumPerList;
        itemNumPerList = (itemNum < itemNumPerList ? itemNum : itemNumPerList);

        if (itemNum == 0) {
            break;
        }
    }

    // Create shader.
    izanagi::CFileInputStream in;
    VRETURN(in.Open("data/BasicShader.shd"));

    m_Shader = izanagi::shader::CShaderBasic::CreateShader<izanagi::shader::CShaderBasic>(
                allocator,
                device,
                &in);
    VRETURN(m_Shader != IZ_NULL);

    return IZ_TRUE;
}

void PhotoItemManager::Terminate()
{
    for (IZ_UINT i = 0; i < COUNTOF(m_PhotoItemList); i++) {
        izanagi::CStdList<PhotoItem>::Item* listItem = m_PhotoItemList[i].GetTop();

        while (listItem != IZ_NULL) {
            PhotoItem* photoItem = listItem->GetData();

            listItem = listItem->GetNext();

            SAFE_RELEASE(photoItem);
        }

        m_PhotoItemList[i].Clear();
    }

    SAFE_RELEASE(m_Shader);
}

IZ_BOOL PhotoItemManager::EnqueueLoadingRequest(
    izanagi::graph::CGraphicsDevice* device,
    const char* path)
{
    PhotoItem* photoItem = FindNotRequestedLoadTexture();
    if (photoItem == IZ_NULL) {
        return IZ_FALSE;
    }

    TextureLoader::Instance().EnqueueLoadingRequest(
        device,
        "data/test.jpg",
        photoItem);

    photoItem->SetIsRequestedLoadTexture(IZ_TRUE);

    return IZ_TRUE;

}

void PhotoItemManager::Render(
    izanagi::graph::CGraphicsDevice* device,
    const izanagi::CCamera& camera)
{
    IZ_ASSERT(device != IZ_NULL);

    // With texture.
    m_Shader->Begin(device, 0, IZ_FALSE);
    {
        if (m_Shader->BeginPass(0)) {
            // �p�����[�^�ݒ�
            Utility::SetShaderParam(
                m_Shader,
                "g_mW2C",
                (void*)&camera.GetParam().mtxW2C,
                sizeof(camera.GetParam().mtxW2C));

            for (int i = 0; i < COUNTOF(m_PhotoItemList); i++) {
                m_PhotoItemList[i].RenderWithTexture(device, m_Shader);
            }

            m_Shader->EndPass();
        }
    }
    m_Shader->End(device);

    // Without texture.
    m_Shader->Begin(device, 1, IZ_FALSE);
    {
        if (m_Shader->BeginPass(0)) {
            // �p�����[�^�ݒ�
            Utility::SetShaderParam(
                m_Shader,
                "g_mW2C",
                (void*)&camera.GetParam().mtxW2C,
                sizeof(camera.GetParam().mtxW2C));

            for (int i = 0; i < COUNTOF(m_PhotoItemList); i++) {
                m_PhotoItemList[i].RenderWithoutTexture(device, m_Shader);
            }

            m_Shader->EndPass();
        }
    }
    m_Shader->End(device);
}

PhotoItem* PhotoItemManager::FindNotRequestedLoadTexture()
{
    for (IZ_UINT i = 0; i < COUNTOF(m_PhotoItemList); i++) {
        izanagi::CStdList<PhotoItem>::Item* listItem = m_PhotoItemList[i].GetTop();

        while (listItem != IZ_NULL) {
            PhotoItem* photoItem = listItem->GetData();

            if (!photoItem->IsRequestedLoadTexture()) {
                return photoItem;
            }

            listItem = listItem->GetNext();
        }
    }

    return IZ_NULL;
}