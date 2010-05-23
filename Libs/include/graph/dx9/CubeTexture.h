#if !defined(__URANUS_GRAPH_CUBE_TEXTURE_H__)
#define __URANUS_GRAPH_CUBE_TEXTURE_H__

#include "BaseTexture.h"

namespace uranus {
	class CGraphicsDevice;

	class CCubeTexture : public CBaseTexture {
		friend class CGraphicsDevice;

	private:
		// ファイルからテクスチャ作成
		static CCubeTexture* CreateCubeTextureFromFile(
			CGraphicsDevice* pDevice,
			IMemoryAllocator* pAllocator,
			UN_PCSTR lpszPathName,
			E_GRAPH_PIXEL_FMT fmt);

		// テクスチャ作成
		static CCubeTexture* CreateCubeTexture(
			CGraphicsDevice* pDevice,
			IMemoryAllocator* pAllocator,
			UN_UINT nWidth,
			UN_UINT nHeight,
			UN_UINT nMipLevel,
			E_GRAPH_PIXEL_FMT fmt);

	private:
		typedef UN_BOOL (CCubeTexture::*CreateTexFunc)(UN_PCSTR, UN_UINT, UN_UINT, UN_UINT, E_GRAPH_PIXEL_FMT);

		static CCubeTexture* CreateInternal(
			CGraphicsDevice* pDevice,
			IMemoryAllocator* pAllocator,
			UN_PCSTR lpszPathName,
			UN_UINT nWidth,
			UN_UINT nHeight,
			UN_UINT nMipLevel,
			E_GRAPH_PIXEL_FMT fmt,
			CreateTexFunc pCreateTexFunc);

	private:
		inline CCubeTexture();
		inline ~CCubeTexture();

		CCubeTexture(const CCubeTexture& rhs);
		const CCubeTexture& operator=(const CCubeTexture& rhs);

	private:
		// 解放
		void InternalRelease();

		// ファイルからテクスチャ作成
		UN_BOOL CreateTextureFromFileImpl(
			UN_PCSTR lpszPathName,
			UN_UINT nWidth,
			UN_UINT nHeight,
			UN_UINT nMipLevel,
			E_GRAPH_PIXEL_FMT nFmt);

		// テクスチャ作成
		UN_BOOL CreateTextureImpl(
			UN_PCSTR lpszPathName,
			UN_UINT nWidth,
			UN_UINT nHeight,
			UN_UINT nMipLevel,
			E_GRAPH_PIXEL_FMT nFmt);

		// テクスチャ情報取得
		void GetTextureInfo();

	public:
		// ロック
		UN_UINT Lock(
			E_GRAPH_CUBE_TEX_FACE nFace,
			UINT nLevel,
			void** data,
			UN_BOOL bIsReadOnly,
			UN_BOOL bIsDiscard = UN_FALSE);

		// アンロック
		UN_BOOL Unlock(
			E_GRAPH_CUBE_TEX_FACE nFace,
			UN_UINT nLevel);

	public:
		inline TEX_HANDLE GetTexHandle();

	public:
		D3D_CUBETEXTURE* GetRawInterface() { return m_pTexture; }

	private:
		// 本体
		D3D_CUBETEXTURE* m_pTexture;
	};

	// inline ***********************************************
	
	// コンストラクタ
	CCubeTexture::CCubeTexture()
	{
		m_pTexture = UN_NULL;
	}

	// デストラクタ
	CCubeTexture::~CCubeTexture()
	{
		SAFE_RELEASE(m_pTexture);
	}

	TEX_HANDLE CCubeTexture::GetTexHandle()
	{
		return m_pTexture;
	}
}	// namespace uranus

#endif	// #if !defined(__URANUS_GRAPH_CUBE_TEXTURE_H__)
