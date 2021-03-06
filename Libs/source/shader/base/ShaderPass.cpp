﻿#include "shader/base/ShaderPass.h"
#include "shader/base/table/ShaderSamplerTable.h"

namespace izanagi
{
namespace shader
{
    // コンストラクタ
    CShaderPass::CShaderPass()
    {
        m_nIdx = 0;
        m_pDesc = IZ_NULL;
        m_Program = IZ_NULL;
    }

    // デストラクタ
    CShaderPass::~CShaderPass()
    {
        Clear();
    }

    // 初期化
    void CShaderPass::Init(
        IZ_UINT idx, 
        const S_SHD_PASS* pDesc)
    {
        m_nIdx = idx;
        m_pDesc = pDesc;

        m_Program = IZ_NULL;
    }

    // 初期化
    void CShaderPass::InitParam(
        IZ_UINT idx,
        IZ_UINT nParamIdx,
        IZ_PCSTR name)
    {
        IZ_ASSERT(m_pDesc != IZ_NULL);

        IZ_BOOL result = InitInfo<SParamInfo>(
            m_Params, 
            idx, 
            nParamIdx, 
            name);
    }

    // 初期化
    IZ_BOOL CShaderPass::InitSampler(
        const CShaderSamplerTable& samplerTbl,
        graph::CGraphicsDevice* device,
        IZ_UINT idx,
        IZ_UINT nSmplIdx,
        IZ_PCSTR name)
    {
        IZ_BOOL ret = InitInfo<SSamplerInfo>(
                        m_Samplers, 
                        idx, 
                        nSmplIdx, 
                        name);

        if (!ret) {
            // TODO
            // OpenGLの場合は、ShaderCompile でサンプラ名が強制的に sN にリネームされている.

            const S_SHD_SAMPLER* samplerDesc = samplerTbl.GetDesc(nSmplIdx);

            if (samplerDesc->resource_id >= 0) {
                static const char* smplNames[] = {
                    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
                };
                IZ_ASSERT(samplerDesc->resource_id < COUNTOF(smplNames));

                ret = InitInfo<SSamplerInfo>(m_Samplers, idx, nSmplIdx, smplNames[samplerDesc->resource_id]);
            }
        }
        
        if (ret) {
#if 0
            IZ_INT samplerDescIdx = samplerTbl.GetIdxByName(name);
            const S_SHD_SAMPLER* samplerDesc = samplerTbl.GetDesc(samplerDescIdx);
#else
            const S_SHD_SAMPLER* samplerDesc = samplerTbl.GetDesc(nSmplIdx);
#endif

            m_Samplers.list[idx].resource_id = samplerDesc->resource_id;

#if 0
            // NOTE
            // サンプラレジスタ 0 - 7 の８個まで
            ret = (m_Samplers.list[idx].resource_id < 8);
            IZ_ASSERT(ret);
#endif
        }

        return ret;
    }

    void CShaderPass::Clear()
    {
        SAFE_RELEASE(m_Program);
    }
}   // namespace shader
}   // namespace izanagi
