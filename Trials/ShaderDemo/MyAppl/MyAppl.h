#if !defined(__IZ_APPL_H__)
#define __IZ_APPL_H__

#include "izDefs.h"

#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	720

namespace izanagi {
	class graph::CTexture;
}

class CMyAppl {
private:
	static CMyAppl s_cInstance;

public:
	static CMyAppl& GetInstance() { return s_cInstance; }

private:
	CMyAppl();
	~CMyAppl() {}

public:
	// 初期化
	IZ_BOOL Init(
		HINSTANCE hInst,
		HWND hDeviceWindow,
		HWND hFocusWindow);

	// 開放
	void Release();

	IZ_BOOL Update();
	IZ_BOOL Render();

	IZ_BOOL IsOnShader() { return m_IsOnShader; }

protected:
	izanagi::graph::CTexture* m_pRT;

	IZ_BOOL m_IsOnShader;
};

#endif	// #if !defined(__IZ_APPL_H__)
