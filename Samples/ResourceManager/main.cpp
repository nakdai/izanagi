#include "ResourceManager.h"

static const IZ_UINT BUF_SIZE = 4 * 1024 * 1024;
static IZ_UINT8 BUF[BUF_SIZE];

static const IZ_UINT GFX_BUF_SIZE = 4 * 1024 * 1024;
static IZ_UINT GFX_BUF[GFX_BUF_SIZE];

IzMain(SCREEN_WIDTH, SCREEN_HEIGHT)
{
    CResourceManagerApp app;

    int ret = SampleMain(
        IzGetSystemDataForMainFunc(),
        &app,
        "ResourceManager",
        IzGetScreenWidth(), IzGetScreenHeight(),
        BUF, BUF_SIZE,
        GFX_BUF, GFX_BUF_SIZE);

    return ret;
}
