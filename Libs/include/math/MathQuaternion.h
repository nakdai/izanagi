#if !defined(__IZANAGI__MATH_QUATERNION_H__)
#define __IZANAGI__MATH_QUATERNION_H__

#include <math.h>
#include <memory.h>
#include "izDefs.h"
#include "MathVector.h"
#include "MathMatrix.h"

namespace izanagi
{
namespace math
{
    struct SMatrix;

    struct SQuat : public SVector {
        void Set(IZ_FLOAT _x, IZ_FLOAT _y, IZ_FLOAT _z, IZ_FLOAT _w = 1.0f)
        {
            x = _x; y = _y; z = _z; w = _w;
        }

        void Set(const SVector& rhs)
        {
            x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w;
        }

        // クオータニオンを設定する
        static void Set(SQuat& quat, IZ_FLOAT x, IZ_FLOAT y, IZ_FLOAT z, IZ_FLOAT w)
        {
            quat.x = x;
            quat.y = y;
            quat.z = z;
            quat.w = w;
        }

        // 全成分０のクオータニオンを設定する
        static void SetZero(SQuat& quat)
        {
            quat.x = 0.0f;
            quat.y = 0.0f;
            quat.z = 0.0f;
            quat.w = 0.0f;
        }

        static inline void SetIdentity(SQuat& quat);

        // クオータニオンをコピー
        static void Copy(SQuat& dst, const SQuat& src)
        {
            dst.x = src.x;
            dst.y = src.y;
            dst.z = src.z;
            dst.w = src.w;
        }

        static void Copy(SVector& dst, const SQuat& src)
        {
            dst.x = src.x;
            dst.y = src.y;
            dst.z = src.z;
            dst.w = src.w;
        }

        // ２つのクオータニオンをスワップする。
        static void Swap(SQuat& q1, SQuat& q2)
        {
            SQuat q;
            Copy(q, q1);
            Copy(q1, q2);
            Copy(q2, q);
        }

        // クオータニオンを加算する
        // dst = src1 + src2
        static void Add(SQuat& dst, const SQuat& src1, const SQuat& src2)
        {
            dst.x = src1.x + src2.x;
            dst.y = src1.y + src2.y;
            dst.z = src1.z + src2.z;
            dst.w = src1.w + src2.w;
        }

        // クオータニオンを減算する
        // dst = src1 - src2
        static void Sub(SQuat& dst, const SQuat& src1, const SQuat& src2)
        {
            dst.x = src1.x - src2.x;
            dst.y = src1.y - src2.y;
            dst.z = src1.z - src2.z;
            dst.w = src1.w - src2.w;
        }

        // クオータニオンを乗算する
        // dst = src1 * src2
        static inline void Mul(SQuat& dst, const SQuat& src1, const SQuat& src2);

        // クオータニオンをスケーリングする
        // dst = fQ * src
        static void Scale(SQuat& dst, const SQuat& src, IZ_FLOAT fQ)
        {
            dst.x = fQ * src.x;
            dst.y = fQ * src.y;
            dst.z = fQ * src.z;
            dst.w = fQ * src.w;
        }

        // クオータニオンをスケーリング（除算）する
        // dst = (src.x / fQ, src.y / fQ, src.z / fQ, src.w / fQ)
        static void Div(SQuat& dst, const SQuat& src, IZ_FLOAT fQ)
        {
#if 0
            dst.x = src.x / fQ;
            dst.y = src.y / fQ;
            dst.z = src.z / fQ;
            dst.w = src.w / fQ;
#else
            Scale(dst, src, 1.0f / fQ);
#endif
        }

        // クオータニオンの大きさ(絶対値)を計算する
        static inline IZ_FLOAT Length(const SQuat& quat);

        // クオータニオンを正規化する
        static inline void Normalize(SQuat& dst, const SQuat& src);

        // 共役クオータニオンを求める
        static inline void Conjugate(SQuat& dst, const SQuat& src);

        // 逆クオータニオンを求める
        static inline void Inverse(SQuat& dst, const SQuat& src);

        // 球面線形補間
        static inline void Slerp(SQuat& dst, const SQuat& quat1, const SQuat& quat2, IZ_FLOAT t);

        static void Slerp(SVector& dst, const SQuat& quat1, const SQuat& quat2, IZ_FLOAT t)
        {
            Slerp(
                *(reinterpret_cast<SQuat*>(&dst)),
                quat1, quat2,
                t);
        }

        // 角度と軸からクオータニオンを設定する
        static void SetQuatFromRadAxis(SQuat& quat, IZ_FLOAT rad, IZ_FLOAT fAxisX, IZ_FLOAT fAxisY, IZ_FLOAT fAxisZ)
        {
            SVector vAxis;
            vAxis.Set(fAxisX, fAxisY, fAxisZ, 0.0f);

            SetQuatFromRadAxis(quat, rad, vAxis);
        }

        // 角度と軸からクオータニオンを設定する
        static inline void SetQuatFromRadAxis(SQuat& quat, IZ_FLOAT rad, const SVector& vAxis);

        // クオータニオンから行列を計算する
        static inline void MatrixFromQuat(SMatrix& mtx, const SQuat& quat);

        // 行列からクオータニオンを計算する
        static inline void QuatFromMatrix(SQuat& quat, const SMatrix& mtx);

        // オイラー角からクオータニオンを計算する
        static inline void QuatFromEuler(SQuat& quat, IZ_FLOAT x, IZ_FLOAT y, IZ_FLOAT z);

        // 二つのベクトルv0,v1が与えられたときに
        // q  * v0 == v1 となるクオータニオンqを計算する
        static void RotationArc(SQuat& quat, const SVector& from, const SVector& to)
        {
            // 念のため
            SVector v0, v1;
            SVector::Normalize(v0, from);
            SVector::Normalize(v1, to);

            SVector c;
            SVector::Cross(c, v0, v1);

            IZ_FLOAT d = SVector::Dot(v0, v1);
            IZ_FLOAT s = sqrtf(2.0f * (1.0f + d));

            quat.x = c.x / s;
            quat.y = c.y / s;
            quat.z = c.z / s;

            quat.w = s * 0.5f;
        }

        // クオータニオンからオイラー角を計算する
        static void GetEuler(SVector& angle, const SQuat& quat)
        {
            SMatrix mtx;
            MatrixFromQuat(mtx, quat);

            // TODO
            // MatrixFromQuatの結果はZXYの回転順番であることを常に保障する？
            SMatrix::GetEulerFromMatrix(angle, mtx, E_MATH_ROTATION_ORDER_ZXY);
        }

        // オイラー角からクオータニオンを計算する
        static void QuatFromEuler(SQuat& quat, const SVector& angle)
        {
            QuatFromEuler(
                quat,
                angle.x, angle.y, angle.z);
        }
    };
}   // namespace math
}    // namespace izanagi

#ifdef __USE_D3D_MATH__
    #include "math/dx9/MathQuaternion_DX9.h"
#else   // #ifdef __USE_D3D_MATH__
    #include "math/noplatform/MathQuaternion_NoPlatform.h"
#endif

#endif    // #if !defined(__IZANAGI__MATH_QUATERNION_H__)
