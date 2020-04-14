
// ClipboardDemoView.cpp : implementation of the CClipboardDemoView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ClipboardDemo.h"
#endif

#include "ClipboardDemoDoc.h"
#include "ClipboardDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClipboardDemoView

IMPLEMENT_DYNCREATE(CClipboardDemoView, CView)

BEGIN_MESSAGE_MAP(CClipboardDemoView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, &CClipboardDemoView::OnCancelEditSrvr)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CClipboardDemoView construction/destruction

CClipboardDemoView::CClipboardDemoView() noexcept
{
	// TODO: add construction code here
}

CClipboardDemoView::~CClipboardDemoView()
{
}

BOOL CClipboardDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CClipboardDemoView drawing

void CClipboardDemoView::OnDraw(CDC* pDC)
{
	CClipboardDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: add draw code for native data here
	const CString method11 = L"Using MFC COleServerItem::CopyToClipboard method with Unicode strings";
	const CString method12 = L"This does not work for enhanced metafile with extended ASCII characters > 127 on Japanese OS.";
	const CString method21 = L"Using MFC COleServerItem::CopyToClipboard method with ASCII strings (char instead of wchar_t)";
	const CString method22 = L"This does work for enhanced metafile with extended ASCII characters > 127 on Japanes OS.";
	const CString method31 = L"Using C++ clipboard functions (like OpenClipboard, EmptyClipboard,";
	const CString method32 = L"SetClipboardData, CloseClipboard) with Unicode strings. This also works on Japanese OS.";

	CFont font1, symbolFont;
	CFont* pOldFont;
	double fontSizePoints = 14;
	LOGFONT lf;
	TEXTMETRIC tm1;
	memset(( void * )&lf, 0, sizeof( LOGFONT ));
	lf.lfCharSet = ANSI_CHARSET;
	lf.lfWeight = 400; //normal
	_tcscpy_s( lf.lfFaceName, L"Times New Roman" );
	lf.lfHeight = (int)(fabs(fontSizePoints) * pDC->GetDeviceCaps(LOGPIXELSY) / 72);
	font1.CreateFontIndirect(&lf);
	pDC->GetTextMetrics(&tm1);
	// symbol font
	_tcscpy_s(lf.lfFaceName, L"Symbol");
	symbolFont.CreateFontIndirect(&lf);

	CRect rect;
	GetClientRect(&rect);
	CPen pen;
	COLORREF color = RGB(255, 0, 0); //gray
	pen.CreatePen(PS_SOLID, 2, color);
	CRect rectangle = CRect(CPoint(26, 26), CPoint(rect.Width() / 2 + 100, rect.Height() / 2 + 25));
	pDC->SelectObject(&pen);
	pDC->Rectangle(&rectangle);
	pDC->Ellipse(&rectangle);
	int x = 50;
	int y = 100;
	int lineHeight = 2 * tm1.tmExternalLeading + tm1.tmHeight + 5;
	pOldFont = pDC->SelectObject(&font1);
	//pDC->TextOut(x, y, s1);
	HDC hdc = pDC->GetSafeHdc();
	ExtTextOutW(hdc, x, y, 0, NULL, pDoc->m_s1, pDoc->m_s1.GetLength(), NULL); // tried bot TextOut and ExtTextOut
	y += lineHeight;
	pDC->TextOut(x, y, pDoc->m_s2);
	//*** NOTE: If the following string is changed CStringA and output using TextOutA or ExtTextOutA, then it works !!!
	CString s3 = L"À Ã Å Ç É Ì Î"; // extended chars in slots > 127 ascii *** change to StringA and it works !!!
	CStringA s4 = "À Ã Å Ç É Ì Î";
	pDC->SelectObject(&symbolFont); // ** use Symbol font extended chars
	y += lineHeight;
	if(pDoc->m_method == 0 || pDoc->m_method == 2)
		pDC->TextOutW(x, y, s3);
	else
		TextOutA(hdc, x, y, s4, s4.GetLength());
	pDC->SelectObject(&font1);
	y += 125;
	x = 25;
	switch (pDoc->m_method) {
	case 0:
		pDC->TextOut(x, y, method11);
		y += lineHeight;
		pDC->TextOut(x, y, method12);
		m_objectSize.cx = x + max(pDC->GetTextExtent(method11).cx, pDC->GetTextExtent(method12).cx);
		break;
	case 1:
		pDC->TextOut(x, y, method21);
		y += lineHeight;
		pDC->TextOut(x, y, method22);
		m_objectSize.cx = x + max(pDC->GetTextExtent(method21).cx, pDC->GetTextExtent(method22).cx);
		break;
	case 2:
		pDC->TextOut(x, y, method31);
		y += lineHeight;
		pDC->TextOut(x, y, method32);
		m_objectSize.cx = x + max(pDC->GetTextExtent(method31).cx, pDC->GetTextExtent(method32).cx);
		break;
	}
	m_objectSize.cx += 10;
	m_objectSize.cy = y + lineHeight;
	pDC->SelectObject(pOldFont);
	font1.DeleteObject();
	symbolFont.DeleteObject();
}


// CClipboardDemoView printing

BOOL CClipboardDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CClipboardDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CClipboardDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation
void CClipboardDemoView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}


// CClipboardDemoView diagnostics

#ifdef _DEBUG
void CClipboardDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CClipboardDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClipboardDemoDoc* CClipboardDemoView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClipboardDemoDoc)));
	return (CClipboardDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CClipboardDemoView message handlers


void CClipboardDemoView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportExt(CSize(1,1));
	pDC->SetWindowExt(CSize(1, 1));
	CView::OnPrepareDC(pDC, pInfo);
}


void CClipboardDemoView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: Add your specialized code here and/or call the base class
	Invalidate();
}
