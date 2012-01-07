#if !defined(__STATE_C_H__)
#define __STATE_C_H__

#include "StateBase.h"

class CStateC : public CStateBase {
public:
	CStateC() {}
	virtual ~CStateC() {}

public:
	// �X�V.
	virtual IZ_BOOL Update();

	virtual IZ_UINT GetIndex();

	// For Windows

	// �L�[����
	virtual IZ_BOOL OnKeyDown(IZ_UINT nChar);
};

#endif	// #if !defined(__STATE_C_H__)