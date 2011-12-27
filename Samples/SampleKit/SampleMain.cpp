#include "SampleMain.h"
#include "SampleWindow.h"
#include "SampleApp.h"

IZ_BOOL SampleMainLoop(izanagi::sample::SSampleParam& params)
{
	IZ_BOOL ret = IZ_TRUE;

	// ���s�t�@�C�����猻�݂̃p�X���擾
	izanagi::CSysUtil::SetCurrentDirectoryFromExe();

	izanagi::sample::CSampleWndProc wndProc;
	void* nativeWndHandle = IZ_NULL;

	// �E�C���h�E�쐬�p�p�����[�^
	izanagi::WindowParams wndParam = {
		params.width,
		params.height,
		params.isWindowed,
		params.title,
		params.platformParam,
		&wndProc,
	};

	// �A�v���������p�p�����[�^
	izanagi::sample::SSampleAppParams appParam = {
		params.allocator,
		0,			// TODO
		IZ_NULL,	// TODO
		params.width,
		params.height,
		&wndProc,
		nativeWndHandle,
		nativeWndHandle,
		params.platformParam,
	};

	// �E�C���h�E�쐬
	izanagi::WindowHandle wndHandle = izanagi::CSysWindow::Create(
										params.allocator,
										wndParam);
	VGOTO(ret = (wndHandle != IZ_NULL), __EXIT__);

	// �v���b�g�t�H�[�����Ƃ̃E�C���h�E�n���h�����擾
	nativeWndHandle = izanagi::CSysWindow::GetNativeWindowHandle(wndHandle);
	VGOTO(ret = (nativeWndHandle != IZ_NULL), __EXIT__);

	// �A�v��������
	ret = params.app->Init(appParam);
	VGOTO(ret, __EXIT__);

	izanagi::CSysWindow::RunLoop(wndHandle);

__EXIT__:
	params.app->Release();

	izanagi::CSysWindow::Destroy(wndHandle);

	return ret;
}