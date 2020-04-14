// Dialog1.cpp : implementation file
//

#include "pch.h"
#include "ClipboardDemo.h"
#include "ClipboardDemoDoc.h"
#include "Dialog1.h"
#include "afxdialogex.h"


// CDialog1 dialog

IMPLEMENT_DYNAMIC(CDialog1, CDialogEx)

CDialog1::CDialog1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_DemoMethod(0)
{

}

CDialog1::~CDialog1()
{
}

void CDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_DemoMethod);
	if (pDX->m_bSaveAndValidate)
		m_pDoc->m_method = m_DemoMethod;
}

void CDialog1::OnOK() {
	//m_pDoc->m_bDemoMethodDialogActive = false;
	//CDialogEx::OnOK();
	UpdateData();
	m_pDoc->UpdateAllViews(NULL);
}

void CDialog1::OnCancel() {
	m_pDoc->m_bDemoMethodDialogActive = false;
	CDialogEx::OnCancel();
}

BEGIN_MESSAGE_MAP(CDialog1, CDialogEx)
END_MESSAGE_MAP()


// CDialog1 message handlers
