
// KeyMove.h : KeyMove ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CKeyMoveApp:
// �� Ŭ������ ������ ���ؼ��� KeyMove.cpp�� �����Ͻʽÿ�.
//

class CKeyMoveApp : public CWinAppEx
{
public:
	CKeyMoveApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKeyMoveApp theApp;
