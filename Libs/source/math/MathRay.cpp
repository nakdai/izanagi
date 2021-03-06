#include "math/MathRay.h"
#include "math/MathUtil.h"

namespace izanagi
{
namespace math
{
    CRay::CRay()
    {
        p.Set(0.0f, 0.0f, 0.0f);
        v.Set(0.0f, 0.0f, 0.0f, 0.0f);
        t = 0.0f;
    }

    CRay::CRay(const SVector4& ptr, const SVector4& dir)
    {
        IZ_FLOAT t = SVector4::Length(dir);

        SVector4 v;
        SVector4::Normalize(v, dir);

        Set(ptr, v, t);
    }

    CRay::CRay(const SVector4& ptr, const SVector4& dir, IZ_FLOAT _t)
    {
        Set(ptr, dir, _t);
    }

    CRay::CRay(const SRay& rhs)
    {
        Set(rhs.p, rhs.v, rhs.t);
    }

    // 直線をコピー.
    const CRay& CRay::operator=(const SRay& rhs)
    {
        Set(rhs.p, rhs.v, rhs.t);
        return *this;
    }

    // 直線を設定する.
    void CRay::Set(
        const SVector4& ptr,
        const SVector4& dir,
        IZ_FLOAT _t)
    {
        SVector4::Copy(p, ptr);
        SVector4::CopyXYZ(v, dir);
        t = _t;

        Normalize();
    }

    // 平行かどうか.
    IZ_BOOL CRay::IsParallel(const SRay& rhs) const
    {
        // NOTE
        // 方向ベクトルは正規化済み

        IZ_BOOL ret = (CMath::IsNearyEqual(v.x, rhs.v.x)
            && CMath::IsNearyEqual(v.y, rhs.v.y)
            && CMath::IsNearyEqual(v.z, rhs.v.z));
        return ret;
    }

    // 無限遠方の直線にする.
    void CRay::SetInifite()
    {
        t = IZ_FLOAT_MAX;
    }

    // 係数を掛けた方向ベクトルを取得.
    void CRay::GetMulAttnDir(SVector4& dir)
    {
        SVector4::ScaleXYZ(dir, v, t);
    }

    // 直線上にあるかどうか.
    IZ_BOOL CRay::IsOnRay(const SVector4& ptr)
    {
        // TODO
        return IZ_TRUE;
    }

    // 方向ベクトルを正規化.
    void CRay::Normalize()
    {
        SVector4::Normalize(v, v);
    }
}   // namespace math
}   // namespace izanagi
