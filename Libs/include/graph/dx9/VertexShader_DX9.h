#ifdef __IZ_DX9__
#if !defined(__IZANAGI_GRAPH_VERTEX_SHADER_DX9_H__)
#define __IZANAGI_GRAPH_VERTEX_SHADER_DX9_H__

#include "izDX9Defs.h"
#include "graph/VertexShader.h"
#include "graph/dx9/ShaderProxy_DX9.h"

namespace izanagi
{
namespace graph
{
    class CGraphicsDeviceDX9;

    // 頂点シェーダ
    class CVertexShaderDX9 : public CShaderProxy<CVertexShader>
    {
        friend class CGraphicsDeviceDX9;

    private:
        // インスタンス作成
        static CVertexShader* CreateVertexShader(
            CGraphicsDeviceDX9* device,
            IMemoryAllocator* allocator,
            const void* program);

    protected:
        inline CVertexShaderDX9();
        virtual inline ~CVertexShaderDX9();

    public:
        D3D_VS* GetRawInterface() { return m_VS; }

    protected:
        // 本体
        D3D_VS* m_VS;
    };
}   // namespace graph
}   // namespace izanagi

#endif  // #if !defined(__IZANAGI_GRAPH_VERTEX_SHADER_DX9_H__)
#endif  // #ifdef __IZ_DX9__
