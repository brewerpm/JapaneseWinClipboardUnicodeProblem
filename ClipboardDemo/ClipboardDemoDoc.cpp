
// ClipboardDemoDoc.cpp : implementation of the CClipboardDemoDoc class
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
#include "SrvrItem.h"

#include <propkey.h>
#include <mbctype.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CClipboardDemoDoc

IMPLEMENT_DYNCREATE(CClipboardDemoDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CClipboardDemoDoc, COleServerDoc)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CClipboardDemoDoc::OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_COPY, &CClipboardDemoDoc::OnEditCopy)
END_MESSAGE_MAP()


// CClipboardDemoDoc construction/destruction

CClipboardDemoDoc::CClipboardDemoDoc() noexcept
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

}

CClipboardDemoDoc::~CClipboardDemoDoc()
{
}

BOOL CClipboardDemoDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_s1 = L"Do a ctrl-c and then paste into WordPad on Japanese OS.";
	m_s2 = L"Here's some extended chars from Symbol font: ";

	return TRUE;
}


// CClipboardDemoDoc server implementation

COleServerItem* CClipboardDemoDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CClipboardDemoSrvrItem* pItem = new CClipboardDemoSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}


// CClipboardDemoDoc Active Document server implementation

CDocObjectServer *CClipboardDemoDoc::GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite)
{
	return new CDocObjectServer(this, pDocSite);
}




// CClipboardDemoDoc serialization

void CClipboardDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_s1;
		ar << m_s2;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_s1;
		ar >> m_s2;
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CClipboardDemoDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CClipboardDemoDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CClipboardDemoDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CClipboardDemoDoc diagnostics

#ifdef _DEBUG
void CClipboardDemoDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CClipboardDemoDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG


// CClipboardDemoDoc commands


void CClipboardDemoDoc::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}


void CClipboardDemoDoc::OnEditCopy()
{
	// TODO: Add your command handler code here

	//setting code page does not help with clipboard problem on Eastern OS
	//int codePage = _getmbcp(); // save original code page
	//_setmbcp(1252); // set to western; Japanese is 932 (if I remember correctly)

	//Using COleServerItem::CopyToClipboard causes chars > 127 to render improperly (wrong font)
	//If you comment out the next two lines and uncomment the code below, the it works!!
	CClipboardDemoSrvrItem* pItem = GetEmbeddedItem();
	pItem->CopyToClipboard(FALSE);

	//******** Uncomment this code to see that it works if one doesn't use OLE *************
	//CView* pView = NULL;
	//POSITION pos = GetFirstViewPosition();
	//while (pos != NULL)	{
	//	pView = GetNextView(pos);
	//	if (pView->IsKindOf(RUNTIME_CLASS(CClipboardDemoView)))
	//		break;
	//	else {
	//		pView = NULL; //keep looking
	//	}
	//}
	//if (pView == NULL)
	//	return; // or do something that's helpful
	//HWND hwnd = pView->GetSafeHwnd();
	//CDC* pDC = pView->GetDC();
	//CMetaFileDC mfdc;
	//if (mfdc.CreateEnhanced(NULL, NULL, NULL, NULL)) {
	//	mfdc.SetAttribDC(pDC->m_hAttribDC); // do this or get an assert when doing attribute GDI calls like GetTextExtent or GetDeviceCaps
	//	((CClipboardDemoView*)pView)->OnDraw(&mfdc); // Draw to the metafile dc
	//	HENHMETAFILE hmf;
	//	if ((hmf = mfdc.CloseEnhanced())) {
	//		if (OpenClipboard(hwnd)) {
	//			EmptyClipboard();
	//			SetClipboardData(CF_ENHMETAFILE, hmf); // then put it on the clipboard
	//			CloseClipboard();
	//		}
	//		else {
	//			/*
	//			 * The metafile is deleted only
	//			 * when it has not been set in
	//			 * the clipboard.
	//			 */
	//			::DeleteEnhMetaFile(hmf);
	//		}
	//	}
	//}
	// *******************************************************************

	// ************ The following code sets the locale to "en-US" in the clipboard but does help ***********************
	//// set locale info even though this doesn't help the
	//char locale[] = "en-US"; // did this as regular ascii instead of unicode (tried unicode with the Japan problem but no work either)
	//OpenClipboard(NULL);
	//size_t ls = sizeof(locale);
	//HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, ls);
	//if (!hg) {
	//	CloseClipboard();
	//}
	//else {
	//	memcpy(GlobalLock(hg), locale, ls);
	//	GlobalUnlock(hg);
	//	SetClipboardData(CF_LOCALE, hg);
	//	CloseClipboard();
	//	GlobalFree(hg);
	//}
}
