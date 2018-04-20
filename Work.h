#pragma once
#include "resource.h"

// Work dialog

class Work : public CDialog
{
	DECLARE_DYNAMIC(Work)

public:
	Work(CWnd* pParent = NULL);   // standard constructor
	virtual ~Work();

// Dialog Data
	enum { IDD = IDD_ABOUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
