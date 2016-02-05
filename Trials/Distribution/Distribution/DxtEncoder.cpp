#include "DxtEncoder.h"

DxtEncoder::~DxtEncoder()
{
    terminate();
}

IZ_BOOL DxtEncoder::init(
    izanagi::IMemoryAllocator* allocator,
    izanagi::graph::CGraphicsDevice* device,
    IZ_UINT width, IZ_UINT height,
    const char* vtxShader,
    const char* dxtShader,
    const char* pixelShader)
{
    m_width = width;
    m_height = height;

    char* buf = nullptr;
    IZ_UINT allocatedSize = 0;

    {
        izanagi::CFileInputStream in;
        VRETURN(in.Open(dxtShader));

        allocatedSize = in.GetSize();
        buf = (char*)ALLOC(allocator, allocatedSize);

        in.Read(buf, 0, allocatedSize);
        buf[allocatedSize] = 0;

        m_dxt = device->CreatePixelShader(buf);
        VRETURN(m_dxt);
    }

    {
        izanagi::CFileInputStream in;
        VRETURN(in.Open(vtxShader));

        auto size = in.GetSize();
        IZ_ASSERT(allocatedSize >= size);

        in.Read(buf, 0, size);
        buf[size] = 0;

        m_vs = device->CreateVertexShader(buf);
        VRETURN(m_vs);
    }

    FREE(allocator, buf);

    {
        m_shd = device->CreateShaderProgram();
        VRETURN(m_shd);

        VRETURN(m_shd->AttachVertexShader(m_vs));
        VRETURN(m_shd->AttachPixelShader(m_dxt));

        m_hImage = m_shd->GetHandleByName("image");
        m_hMode = m_shd->GetHandleByName("mode");
    }

    {
        m_tex = device->CreateTexture(
            width, height,
            1,
            izanagi::graph::E_GRAPH_PIXEL_FMT_DXT5,
            izanagi::graph::E_GRAPH_RSC_USAGE_DYNAMIC);
        VRETURN(m_tex);

        CALL_GL_API(glGenFramebuffers(1, &m_fbo));

        glGenBuffers(1, &m_pbo);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, m_pbo);
        glBufferData(GL_PIXEL_PACK_BUFFER, width * height, 0, GL_STREAM_COPY);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    }

    return IZ_TRUE;
}

void DxtEncoder::encode(
    izanagi::graph::CGraphicsDevice* device,
    izanagi::graph::CTexture* texture)
{
    device->SaveRenderState();

    device->SetRenderState(
        izanagi::graph::E_GRAPH_RS_ZENABLE,
        IZ_FALSE);
    device->SetRenderState(
        izanagi::graph::E_GRAPH_RS_CULLMODE,
        izanagi::graph::E_GRAPH_CULL_NONE);

    auto texHandle = texture->GetTexHandle();

    // Set FBO.
    CALL_GL_API(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
    CALL_GL_API(glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        texHandle,
        0));

    glDisable(GL_FRAMEBUFFER_SRGB);

    device->SetShaderProgram(m_shd);

    device->SetTexture(0, texture);

    glUniform1i(m_hImage, 0);
    glUniform1i(m_hMode, 0);

    // TODO
    // Why 1/4 ?
    device->SetViewport(
        izanagi::graph::SViewport(0, 0, m_width >> 2, m_height >> 2));

    // NOTE
    // ���_�o�b�t�@���g�킸�S��ʂɕ`�悷�钸�_�V�F�[�_.
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Readback.
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, m_pbo);
    glReadPixels(
        0, 0,
        m_width >> 2, m_height >> 2,
        GL_RGBA_INTEGER,
        GL_UNSIGNED_INT,
        0);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

    device->LoadRenderState();
}

void DxtEncoder::terminate()
{
    SAFE_RELEASE(m_vs);
    SAFE_RELEASE(m_dxt);
    SAFE_RELEASE(m_shd);

    SAFE_RELEASE(m_tex);
}