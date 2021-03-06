// ImageBuilder.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#ifndef _WIN32_WINNT        // Windows XP 以降のバージョンに固有の機能の使用を許可します。                   
#define _WIN32_WINNT 0x0501 // これを Windows の他のバージョン向けに適切な値に変更してください。
#endif                      

#include "izToolKit.h"
#include "izMath.h"
#include "Option.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

namespace {
    inline void _DispUsage()
    {
        printf(
            "NormalMapCreator Ver.0.01\n"
            "\n"
            "[USAGE]\n"
            "NormalMapCreator.exe -i [in] -o [out]\n"
            "\n"
            " -i [xml] : 基になる高さマップのファイル名\n"
            " -o [out] : 出力ファイル名\n"
            "            指定が無い場合は入力ファイルをもとに自動で設定される\n"
            " -s [scale] : 高さのスケール値\n"
            "              デフォルトでは1.0で扱われる\n"
            "\n"
            "Attention : 必ずPNGとして出力される\n"
        );
    }
}   // namespace

#ifdef VGOTO
#undef VGOTO
#endif

#define VGOTO(b)    if (!(b)) { IZ_ASSERT(FALSE); nRetCode = 1; goto __EXIT__; }

int main(int argc, char* argv[])
{
    int nRetCode = 0;

    COption option;

    izanagi::tool::CGraphicsDeviceLite* device = IZ_NULL;
    izanagi::tool::CTextureLite* texHeight = IZ_NULL;
    izanagi::tool::CTextureLite* texNml = IZ_NULL;

    // ウインドウハンドル取得
    HWND hWnd = ::GetConsoleWindow();
    VGOTO(hWnd != NULL);

    // グラフィックスデバイス作成
    device = izanagi::tool::CGraphicsDeviceLite::CreateGraphicsDeviceLight(hWnd);
    VGOTO(device != NULL);

    // オプション解析
    IZ_BOOL result = option.Analysis(argc, argv);
    VGOTO(result);
    VGOTO(option.IsValid());

    // TODO
    // ミップマップ

    // 高さマップ読み込み
    texHeight = device->CreateTextureFromFile(option.in);
    VGOTO(texHeight != NULL);

    // 出力用法線マップ作成
    texNml = device->CreateTexture(
                texHeight->GetWidth(0),
                texHeight->GetHeight(0),
                D3DFMT_A8R8G8B8);
    VGOTO(texNml != NULL);

    // データ読み込み
    IZ_UINT8* src = IZ_NULL;
    IZ_UINT srcPitch = texHeight->Lock(0, (void**)&src);

    IZ_UINT8* dst = IZ_NULL;
    IZ_UINT dstPitch = texNml->Lock(0, (void**)&dst);

    IZ_UINT width = texHeight->GetWidth(0);
    IZ_UINT height = texHeight->GetHeight(0);

    IZ_UINT srcBPP = izanagi::graph::CGraphUtil::GetBPP(
                        texHeight->GetPixelFormat());

    // NOTE
    // 法線マップではテクスチャのX方向、Y方向をそれぞれX、Y軸として
    // テクスチャの上方向をZ軸とする
    // つまり、あるピクセルの上下左右隣接ピクセルとの高さの差はZ軸方向の向きとなる

    // TODO
    // X、Y方向のピクセル間の大きさをどのようにするか
    IZ_FLOAT lengthPerPixel = 0.1f;

    IZ_FLOAT div = 1.0f / 255.0f;

    for (IZ_UINT y = 0; y < height; y++) {
        izanagi::SColor* d = reinterpret_cast<izanagi::SColor*>(dst + dstPitch * y);

        IZ_UINT pos = 0;

        for (IZ_UINT x = 0; x < width; x++) {
#if 1
            // 法線
            izanagi::math::SVector4 nml;

            // 高さ
            IZ_FLOAT h = src[y * srcPitch + x * srcBPP] * div * option.scale;

            // 水平方向の高さの参照の向き
            IZ_BOOL isRight = (x + 1 < width);

            // 水平方向の高さ
            IZ_UINT pos = (isRight
                            ? y * srcPitch + (x + 1) * srcBPP
                            : y * srcPitch + (x - 1) * srcBPP);
            IZ_FLOAT heightH = src[pos] * div * option.scale;

            // 水平方向のベクトル
            izanagi::math::CVector4 vecH(lengthPerPixel, 0.0f, heightH - h);

            // 垂直方向の高さの参照の向き
            IZ_BOOL isBottom = (y + 1 < height);

            // 下ピクセルの高さ
            pos = (isBottom
                    ? (y + 1) * srcPitch + x * srcBPP
                    : (y - 1) * srcPitch + x * srcBPP);
            IZ_FLOAT heightV = src[pos] * div * option.scale;

            // 垂直方向のベクトル
            izanagi::math::CVector4 vecV(0.0f, lengthPerPixel, heightV - h);

            // 外積を計算
#if 0
            if ((isRight && isBottom)
                || (!isRight && !isBottom))
            {
                izanagi::math::SVector4::Cross(nml, vecH, vecV);
            }
            else {
                izanagi::math::SVector4::Cross(nml, vecV, vecH);
            }
#else
            izanagi::math::SVector4::Cross(nml, vecH, vecV);
#endif
#else
            // 右ピクセルの高さ
            IZ_UINT pos = y * srcPitch + ((x + 1) % width) * srcBPP;
            IZ_FLOAT rightHeight = src[pos] * div * option.scale;

            // 下ピクセルの高さ
            pos = ((y + 1) % height) * srcPitch + x * srcBPP;
            IZ_FLOAT bottomHeight = src[pos] * div * option.scale;

            // 高さ
            IZ_FLOAT h = src[y * srcPitch + x * srcBPP] * div * option.scale;

            izanagi::math::SVector4 nml;

            izanagi::math::CVector4 right(lengthPerPixel, 0.0f, rightHeight - h);

            izanagi::math::CVector4 bottom(0.0f, lengthPerPixel, bottomHeight - h);

            // 外積を計算
            izanagi::math::SVector4::Cross(nml, bottom, right);
#endif

            // 正規化
            izanagi::math::SVector4::Normalize(nml, nml);

            // -1.0 - 1.0 のレンジを 0.0 - 1.0 のレンジに変換
            nml.x = nml.x * 0.5f + 0.5f;
            nml.y = nml.y * 0.5f + 0.5f;
            nml.z = nml.z * 0.5f + 0.5f;

            // 法線マップに描きこみ
            d->r = static_cast<IZ_UINT8>(nml.x * 255.0f);
            d->g = static_cast<IZ_UINT8>(nml.y * 255.0f);
            d->b = static_cast<IZ_UINT8>(nml.z * 255.0f);
            d->a = 255;

            d++;
        }
    }
    
    texHeight->Unlock(0);
    texNml->Unlock(0);

    // 出力
    device->SaveTexture(
        option.out,
        texNml,
        izanagi::tool::TextureExportTypePNG);

__EXIT__:
    SAFE_RELEASE(texHeight);
    SAFE_RELEASE(texNml);
    SAFE_RELEASE(device);

    return nRetCode;
}
