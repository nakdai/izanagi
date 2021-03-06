#include "collision/ColTriangle.h"
#include "collision/ColRay.h"

namespace izanagi
{
namespace col
{
    Triangle::Triangle()
    {
        m_pt[0].Set(0.0f, 0.0f, 0.0f);
        m_pt[1].Set(0.0f, 0.0f, 0.0f);
        m_pt[2].Set(0.0f, 0.0f, 0.0f);

        m_nml.Set(0.0f, 0.0f, 0.0f, 0.0f);
        m_d = 0.0f;
    }

    Triangle::Triangle(
        const math::SVector4 point[3],
        IZ_BOOL isBothSides/*= IZ_FALSE*/)
    {
        Set(point, isBothSides);
    }

    Triangle::Triangle(
        const math::SVector4& pt0,
        const math::SVector4& pt1,
        const math::SVector4& pt2,
        IZ_BOOL isBothSides/*= IZ_FALSE*/)
    {
        Set(pt0, pt1, pt2, isBothSides);
    }

    Triangle::Triangle(const Triangle& rhs)
    {
        *this = rhs;
    }

    const Triangle& Triangle::operator=(const Triangle& rhs)
    {
        memcpy(m_pt, rhs.m_pt, sizeof(m_pt));
        math::SVector4::Copy(m_nml, rhs.m_nml);
        m_d = rhs.m_d;

        m_isBothSides = rhs.m_isBothSides;

        return *this;
    }

    void Triangle::Set(
        const math::SVector4 point[3],
        IZ_BOOL isBothSides/*= IZ_FALSE*/)
    {
        Set(point[0], point[1], point[2], isBothSides);
    }

    void Triangle::Set(
        const math::SVector4& point0,
        const math::SVector4& point1,
        const math::SVector4& point2,
        IZ_BOOL isBothSides/*= IZ_FALSE*/)
    {
        m_pt[0].Set(point0.x, point0.y, point0.z);
        m_pt[1].Set(point1.x, point1.y, point1.z);
        m_pt[2].Set(point2.x, point2.y, point2.z);

        m_d = computePlane(
            m_pt[0], m_pt[1], m_pt[2],
            m_nml);

        m_isBothSides = isBothSides;
    }

    IZ_FLOAT Triangle::computePlane(
        const math::CVector4& pt0,
        const math::CVector4& pt1,
        const math::CVector4& pt2,
        math::CVector4& retNml)
    {
        math::CVector4 dir0 = pt1 - pt0;
        math::CVector4 dir1 = pt2 - pt0;

        math::SVector4::Cross(retNml, dir0, dir1);
        retNml.Normalize();

        IZ_FLOAT a = retNml.x;
        IZ_FLOAT b = retNml.y;
        IZ_FLOAT c = retNml.z;

        IZ_FLOAT d = -(a * pt0.x + b * pt0.y + c * pt0.z);

        return d;
    }

    // 実効半径を計算.
    IZ_FLOAT Triangle::computeRadius(const math::SVector4& normal) const
    {
        // 三角形に外接する球の半径を返す.

        // 外心.
        auto center = getCenter();

        math::CVector4 pt;
        math::SMatrix44::Apply(pt, m_pt[0], m_L2W);

        // 外心と三角形の点の距離 = 半径.
        auto radius = math::SVector4::Length2(center, pt);

        return radius;
    }

    // 実効半径を計算.
    IZ_FLOAT Triangle::computeRadius(
        const math::SMatrix44& mtxW2V,
        const math::SVector4& normal) const
    {
        auto radius = computeRadius(normal);
        return radius;
    }

    // 中心座標を取得.
    const math::SVector4 Triangle::getCenter() const
    {
        // NOTE
        // 外心座標の証明.
        // https://www.google.co.jp/url?sa=t&rct=j&q=&esrc=s&source=web&cd=2&cad=rja&uact=8&ved=0ahUKEwjTvoa0zczOAhUCjpQKHdTBDkkQFggjMAE&url=http%3A%2F%2Fwww.jikkyo.co.jp%2Fcontents%2Fdownload%2F9992655233&usg=AFQjCNEa2crr-haymhuOdRSM5N87MSp-1w&bvm=bv.129759880,d.dGo

        // �價BCについて考える.
        // 点Jは円の中心で、点Aは円周上にある点なので、円周角の定理により、中心角 = 2 * 円周角.
        // ∠BJC = 2∠BAC

        // 三角形の面積の公式より
        // �價BC = 1/2 * bc * sin∠BJC
        //   b = c = R（半径）
        //   ∠BJC = 2∠BAC
        // p = �價BC = 1/2 * R^2 * sin2A
        // q = 1/2 * R^2 * sin2B
        // r = 1/2 * R^2 * sin2C

        // p / (p + q + r) = (1/2 * R^2 * sin2A) / (1/2 * R^2 * (sin2A + sin2B + sin2C))
        //                 = sin2A / (sin2A + sin2B + sin2C)
        // q / (p + q + r) = sin2B / (sin2A + sin2B + sin2C)
        // r / (p + q + r) = sin2C / (sin2A + sin2B + sin2C)

        // NOTE
        //     pa + qb + rc   a * sin2A + b * sin2B + c * sin2C
        // o = ------------ = ----------------------------------
        //     p + q + r        sin2A + sin2B + sin2C

        math::CVector4 pt[3];
        math::SMatrix44::Apply(pt[0], m_pt[0], m_L2W);
        math::SMatrix44::Apply(pt[1], m_pt[1], m_L2W);
        math::SMatrix44::Apply(pt[2], m_pt[2], m_L2W);

        math::CVector4 nml;
        computePlane(
            pt[0], pt[1], pt[2],
            nml);

        const auto& a = pt[0];
        const auto& b = pt[1];
        const auto& c = pt[2];

        auto ab = b - a;
        auto ac = c - a;

        auto ba = -ab;
        auto bc = c - b;

        auto ca = -ac;
        auto cb = -bc;

        IZ_FLOAT cosA = math::SVector4::Dot(ab, ac);
        IZ_FLOAT cosB = math::SVector4::Dot(ba, bc);
        IZ_FLOAT cosC = math::SVector4::Dot(ca, cb);

        IZ_FLOAT sinA = sqrtf(1.0f - cosA * cosA);
        IZ_FLOAT sinB = sqrtf(1.0f - cosB * cosB);
        IZ_FLOAT sinC = sqrtf(1.0f - cosC * cosC);

        // 加法定理.
        // sin(A + B) = sinAcosB + cosAsinB
        // -> sin2A = sin(A + A) = sinAcosA + cosAsinA = 2sinAcosA

        IZ_FLOAT sin2A = 2.0f * sinA * cosA;
        IZ_FLOAT sin2B = 2.0f * sinB * cosB;
        IZ_FLOAT sin2C = 2.0f * sinC * cosC;

        auto center = a * sin2A + b * sin2B + c * sin2C;
        center /= (sin2A + sin2B + sin2C);

        center.w = 1.0f;

        return std::move(center);
    }

    static inline IZ_BOOL IsIn(
        const math::CVector4& p,
        const math::CVector4& base,
        const math::CVector4& pos,
        const math::CVector4& normal,
        IZ_BOOL isFlipped = IZ_FALSE)
    {
        math::CVector4 d0 = p - base;

        math::CVector4 d1 = pos - base;

        math::SVector4 c;

        if (isFlipped) {
            math::SVector4::Cross(c, d0, d1);
        }
        else {
            math::SVector4::Cross(c, d1, d0);
        }

        IZ_FLOAT f = math::SVector4::Dot(c, normal);

        if (f < 0) {
            return IZ_FALSE;
        }

        return IZ_TRUE;
    }

    // Get if the ray is hit.
    IZ_BOOL Triangle::isHit(const Ray& ray, HitResult& res)
    {
        // NOTE
        // http://t-pot.com/program/93_RayTraceTriangle/index.html

        /*
            レイの方程式 : p = x + t v
            ３角形の作る平面の方程式 : (p - p0)・n = 0
            x  : レイの出る点
            v  : レイの方向
            p0 : ３角形の１点
            n  : ３角形の法線ベクトル

            連立した結果、レイの進んだ距離tは

                (x - p0)・n
            t = ------------
                    v・n

            v・n=0 の時は、レイと３角形の面が平行に進んでいるので、交わらない.
            t<0の時は、視線の後ろ側に交点があるので、やはり交わることがない.

            交点が３角形の内部にあるかどうかの判定をする.

            交点と３角形の点を結ぶベクトルd0と、３角形の１辺d1との外積を計算
            外積によってできたベクトルは、３角形の法線と同じ方向か反対の方向を向く.
            この向きは、交点が３角形の中にあるか外にあるかで符号が変わるので、全ての辺に関して、符号が同じならば、交点は３角形の中にあることになる.
        */

        math::CVector4 pt[3];
        math::SMatrix44::Apply(pt[0], m_pt[0], m_L2W);
        math::SMatrix44::Apply(pt[1], m_pt[1], m_L2W);
        math::SMatrix44::Apply(pt[2], m_pt[2], m_L2W);

        math::CVector4 nml;
        computePlane(
            pt[0], pt[1], pt[2],
            nml);

#if 0
        // 線分との判定
        math::CVector4 xp = pt[0] - ray.p;

        float xpn = math::SVector4::Dot(xp, nml);
        float vn = math::SVector4::Dot(ray.v, nml);

        // カリングと発散を外す
        if (-0.00001f <= vn) {
            return IZ_FALSE;
        }

        IZ_FLOAT t = xpn / vn;

        // 後ろ向きのレイは無効
        if (t < 0) {
            return IZ_FALSE;
        }

        // ３角形の平面への射影
        auto p = ray.p + t * ray.v;

        if (!IsIn(p, pt[0], pt[1], nml)) {
            return IZ_FALSE;
        }
        if (!IsIn(p, pt[1], pt[2], nml)) {
            return IZ_FALSE;
        }
        if (!IsIn(p, pt[2], pt[0], nml)) {
            return IZ_FALSE;
        }
#else
        math::CVector4 p;
        IZ_FLOAT t = 0.0f;

        IZ_BOOL hit = IZ_FALSE;

        hit = isHit(
            ray,
            pt, nml,
            IZ_FALSE,
            p, t);

        if (!hit && isBothSides()) {
            nml = -nml;
            hit = isHit(
                ray,
                pt, nml,
                IZ_TRUE,
                p, t);
        }

        if (!hit) {
            return IZ_FALSE;
        }
#endif

        res.pt = p;
        res.normal = nml;
        res.t = t;

        return IZ_TRUE;
    }

    IZ_BOOL Triangle::isHit(
        const Ray& ray, 
        const math::CVector4* pt,
        const math::CVector4& nml,
        IZ_BOOL isFlipped,
        math::CVector4& retP,
        IZ_FLOAT& retT)
    {
        // 線分との判定
        math::CVector4 xp = pt[0] - ray.p;

        float xpn = math::SVector4::Dot(xp, nml);
        float vn = math::SVector4::Dot(ray.v, nml);

        // カリングと発散を外す
        if (-0.00001f <= vn) {
            return IZ_FALSE;
        }

        IZ_FLOAT t = xpn / vn;

        // 後ろ向きのレイは無効
        if (t < 0) {
            return IZ_FALSE;
        }

        // ３角形の平面への射影
        auto p = ray.p + t * ray.v;

        if (!IsIn(p, pt[0], pt[1], nml, isFlipped)) {
            return IZ_FALSE;
        }
        if (!IsIn(p, pt[1], pt[2], nml, isFlipped)) {
            return IZ_FALSE;
        }
        if (!IsIn(p, pt[2], pt[0], nml, isFlipped)) {
            return IZ_FALSE;
        }

        retP = p;
        retT = t;

        return IZ_TRUE;
    }
}   // namespace math
}   // namespace izanagi
