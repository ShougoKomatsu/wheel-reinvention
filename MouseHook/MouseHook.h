// MouseHook.h : MouseHook.DLL �̃��C�� �w�b�_�[ �t�@�C��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��


// CMouseHookApp
// ���̃N���X�̎����Ɋւ��Ă� MouseHook.cpp ���Q�Ƃ��Ă��������B
//

class CMouseHookApp : public CWinApp
{
public:
	CMouseHookApp();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
