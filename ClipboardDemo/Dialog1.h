#pragma once


// CDialog1 dialog

class CClipboardDemoDoc;

class CDialog1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog1)

public:
	CDialog1(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialog1();
	void OnOK();
	void OnCancel();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// 0=ServrItem, Unicode  1=ServrItem, ASCII  2=Manual, Unicode
	int m_DemoMethod;
	CClipboardDemoDoc* m_pDoc;
};
