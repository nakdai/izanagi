#include "text/FontRenderer.h"
#include "text/FontRendererBmp.h"
#include "izIo.h"
#include "izGraph.h"

using namespace izanagi;

/**
*/
CFontRenderer* CFontRenderer::CreateFontRendererBmp(
    IMemoryAllocator* allocator,
    graph::CGraphicsDevice* device,
    IZ_UINT maxRegisterNum,
    IInputStream* in)
{
    CFontRenderer* ret = CFontRendererBmp::CreateFontRendererBmp(
                            allocator,
                            device,
                            maxRegisterNum,
                            in);
    return ret;
}

/**
*/
CFontRenderer* CreateFontRendererFT(
    IMemoryAllocator* allocator,
    graph::CGraphicsDevice* device,
    IZ_UINT maxRegisterNum)
{
    // TODO
    IZ_ASSERT(IZ_FALSE);
    return IZ_NULL;
}
