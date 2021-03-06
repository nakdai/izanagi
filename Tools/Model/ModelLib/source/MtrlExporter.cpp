#include "MtrlExporter.h"
#include "izToolkit.h"

CMtrlExporter CMtrlExporter::s_cInstance;

CMtrlExporter::CMtrlExporter()
{
}

CMtrlExporter::~CMtrlExporter()
{
    m_Out.Finalize();
}

IZ_BOOL CMtrlExporter::Export(
    IZ_PCSTR lpszOutFile,
    IImporter* pImporter,
    IZ_UINT nMtrlIdx)
{
    IZ_BOOL ret = IZ_TRUE;

    VRETURN(pImporter->BeginMaterial());

    IZ_UINT nMtrlNum = pImporter->GetMaterialNum();
    IZ_ASSERT(nMtrlIdx < nMtrlNum);

    // Open file.
    VRETURN(m_Out.Open(lpszOutFile));

    izanagi::S_MTRL_HEADER sHeader;
    {
        FILL_ZERO(&sHeader, sizeof(sHeader));

        sHeader.sizeHeader = sizeof(sHeader);

        // TODO
        // magic number, version...
    }

    // Blank for file's header and jump table.
    izanagi::tool::CIoStreamSeekHelper cSeekHelper(&m_Out);
#if 0
    VRETURN(cSeekHelper.Skip(sizeof(sHeader) + sizeof(IZ_UINT) * nMtrlNum));

    // Jump table
    std::vector<IZ_UINT> tvJumpTbl;

    for (IZ_UINT i = 0; i < nMtrlNum; i++) {
        // Add position to jump table.,
        tvJumpTbl.push_back(m_Out.GetCurPos());

        VRETURN(ExportMaterial(i, pImporter));
    }
#else
    VRETURN(cSeekHelper.Skip(sizeof(sHeader)));
    VRETURN(ExportMaterial(nMtrlIdx, pImporter));
#endif

    VRETURN(pImporter->EndMaterial());

    // Export files's header and jump table.
    {
#if 0
        sHeader.numMtrl = nMtrlNum;
#endif

        sHeader.sizeFile = m_Out.GetCurPos();

        // Return to file's top.
        VRETURN(cSeekHelper.Return());

        // Export files' header.
        IZ_OUTPUT_WRITE_VRETURN(&m_Out, &sHeader, 0, sizeof(sHeader));

#if 0
        // Export jump table.
        IZ_OUTPUT_WRITE_VRETURN(&m_Out, &tvJumpTbl[0], 0, sizeof(IZ_UINT) * nMtrlNum);
#endif
    }

    m_Out.Finalize();

    return IZ_TRUE;
}

IZ_BOOL CMtrlExporter::ExportMaterial(
    IZ_UINT nMtrlIdx,
    IImporter* pImporter)
{
    izanagi::S_MTRL_MATERIAL sMtrl;
    FILL_ZERO(&sMtrl, sizeof(sMtrl));

    VRETURN(
        pImporter->GetMaterial(
            nMtrlIdx,
            sMtrl));

    IZ_OUTPUT_WRITE_VRETURN(&m_Out, &sMtrl, 0, sizeof(sMtrl));

    // Export textrure's info.
    for (IZ_UINT i = 0; i < sMtrl.numTex; i++) {
        izanagi::S_MTRL_TEXTURE sTex;
        FILL_ZERO(&sTex, sizeof(sTex));

        sTex.idx = i;

        pImporter->GetMaterialTexture(
            nMtrlIdx,
            i,
            sTex);

        IZ_OUTPUT_WRITE_VRETURN(&m_Out, &sTex, 0, sizeof(sTex));
    }

    // Export shader's info.
    //for (IZ_UINT i = 0; i < sMtrl.numShader; i++) {

    // NOTE
    // Material has only one shader.
    for (IZ_UINT i = 0; i < 1; i++) {
        izanagi::S_MTRL_SHADER sShader;
        FILL_ZERO(&sShader, sizeof(sShader));

        pImporter->GetMaterialShader(
            nMtrlIdx,
            i,
            sShader);

        IZ_OUTPUT_WRITE_VRETURN(&m_Out, &sShader, 0, sizeof(sShader));
    }

    std::vector<izanagi::S_MTRL_PARAM> tvParam(sMtrl.numParam);

    // Export parameter's info.
    for (IZ_UINT i = 0; i < sMtrl.numParam; i++) {
        izanagi::S_MTRL_PARAM& sParam = tvParam[i];
        FILL_ZERO(&sParam, sizeof(sParam));

        pImporter->GetMaterialParam(
            nMtrlIdx,
            i,
            sParam);

        sParam.idx = i;

        IZ_OUTPUT_WRITE_VRETURN(&m_Out, &sParam, 0, sizeof(sParam));
    }

    // Export parameter's value.
    for (IZ_UINT i = 0; i < sMtrl.numParam; i++) {
        const izanagi::S_MTRL_PARAM& sParam = tvParam[i];

        if (sParam.elements > 0) {
            std::vector<IZ_FLOAT> tvValue;
            pImporter->GetMaterialParamValue(
                nMtrlIdx,
                i,
                tvValue);

            switch (sParam.type) {
            case izanagi::E_MTRL_PARAM_TYPE_FLOAT:
            case izanagi::E_MTRL_PARAM_TYPE_VECTOR:
            case izanagi::E_MTRL_PARAM_TYPE_MATRIX:
            {
                IZ_OUTPUT_WRITE_VRETURN(&m_Out, &tvValue[0], 0, sParam.bytes);
                break;
            }
            case izanagi::E_MTRL_PARAM_TYPE_UINT:
            case izanagi::E_MTRL_PARAM_TYPE_BOOL:
                // TODO
                IZ_ASSERT(IZ_FALSE);
                break;
            }
        }
    }

    return IZ_TRUE;
}
