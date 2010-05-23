#if !defined(__URANUS_DEBUGUTIL_DEBUG_UI_FONT_RENDERER_H__)
#define __URANUS_DEBUGUTIL_DEBUG_UI_FONT_RENDERER_H__

#include "unStd.h"

namespace uranus {
	class CGraphicsDevice;

	/**
	*/
	class IDebugUIFontRenderer : public CObject {
		friend class CDebugUIFontLayout;

	protected:
		IDebugUIFontRenderer();
		virtual ~IDebugUIFontRenderer();

		IDebugUIFontRenderer(const IDebugUIFontRenderer& rhs);
		const IDebugUIFontRenderer& operator=(const IDebugUIFontRenderer& rhs);

	protected:
		// 文字列描画
		virtual void RenderText(
			CGraphicsDevice* pDevice,
			UN_INT nX, UN_INT nY,
			UN_COLOR nColor,
			UN_PCSTR pszStr) = 0;

		// 文字列幅取得
		virtual UN_UINT GetTextWidth(UN_PCSTR* pszStr) const = 0;

		// フォント高さ取得
		virtual UN_UINT GetFontHeight() const = 0;
	};
}	// namespace uranus

#endif	// #if !defined(__URANUS_DEBUGUTIL_DEBUG_UI_FONT_RENDERER_H__)
