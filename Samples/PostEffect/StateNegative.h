#if !defined(__STATE_NEGATIVE_H__)
#define __STATE_NEGATIVE_H__

#include "izSceneGraph.h"
#include "izDebugUtil.h"
#include "StatePostEffect.h"

class CStateNegative : public CStatePostEffect {
public:
	CStateNegative(
		izanagi::sample::CSampleApp* app,
		izanagi::SCameraParam& camera);
	virtual ~CStateNegative();

public:
	// 描画.
	virtual IZ_BOOL Render(izanagi::CGraphicsDevice* device);

	// 開始
	virtual IZ_BOOL Enter(
		izanagi::IMemoryAllocator* allocator,
		void* val);
};

#endif	// #if !defined(__STATE_NEGATIVE_H__)