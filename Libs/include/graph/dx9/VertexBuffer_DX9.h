#ifdef __IZ_DX9__
#if !defined(__IZANAGI_GRAPH_VERTEX_BUFFER_DX9_H__)
#define __IZANAGI_GRAPH_VERTEX_BUFFER_DX9_H__

#include "izDX9Defs.h"
#include "graph/VertexBuffer.h"

namespace izanagi
{
namespace graph
{
    class CGraphicsDeviceDX9;

    // 頂点バッファ
    class CVertexBufferDX9 : public CVertexBuffer
    {
        friend class CGraphicsDeviceDX9;

    private:
        // インスタンス作成
        static CVertexBufferDX9* CreateVertexBuffer(
            CGraphicsDeviceDX9* device,
            IMemoryAllocator* allocator,
            IZ_UINT stride,
            IZ_UINT vtxNum,
            E_GRAPH_RSC_USAGE usage);

    private:
        inline CVertexBufferDX9();
        virtual inline ~CVertexBufferDX9();

    private:
        // 本体作成
        IZ_BOOL CreateBody(
            CGraphicsDeviceDX9* device,
            IZ_UINT stride,
            IZ_UINT vtxNum,
            E_GRAPH_RSC_USAGE usage);

    public:
        // ロック
        virtual IZ_BOOL Lock(
            CGraphicsDevice* device,
            IZ_UINT offset,
            IZ_UINT size,
            void** data,
            IZ_BOOL isReadOnly,
            IZ_BOOL isDiscard = IZ_FALSE);

        // アンロック
        virtual IZ_BOOL Unlock(CGraphicsDevice* device);

    public:
        virtual IZ_BOOL IsPrepared() const;

        virtual IZ_BOOL Disable();

        virtual IZ_BOOL Restore();

    public:
        D3D_VB* GetRawInterface() { return m_VB; }

    private:
        CGraphicsDeviceDX9* m_Device;

        // 本体
        D3D_VB* m_VB;

        CVertexBufferDX9* m_Next;
    };
}   // namespace graph
}   // namespace izanagi

#endif  // #if !defined(__IZANAGI_GRAPH_VERTEX_BUFFER_DX9_H__)
#endif  // #ifdef __IZ_DX9__
