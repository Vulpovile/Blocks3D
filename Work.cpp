// Work.cpp : implementation file
//
#define WINVER	0x0400
#include "stdafx.h"
#include "Work.h"


// Work dialog

IMPLEMENT_DYNAMIC(Work, CDialog)

Work::Work(CWnd* pParent /*=NULL*/)
	: CDialog(Work::IDD, pParent)
{

}

Work::~Work()
{
}

void Work::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Work, CDialog)
	ON_BN_CLICKED(IDOK, &Work::OnBnClickedOk)
END_MESSAGE_MAP()


// Work message handlers

void Work::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	this->DestroyWindow();
	OnOK();
}
