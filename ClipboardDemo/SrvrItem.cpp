
// SrvrItem.cpp : implementation of the CClipboardDemoSrvrItem class
//

#include "pch.h"
#include "framework.h"
#include "ClipboardDemo.h"

#include "ClipboardDemoDoc.h"
#include "ClipboardDemoView.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClipboardDemoSrvrItem implementation

IMPLEMENT_DYNAMIC(CClipboardDemoSrvrItem, COleServerItem)

CClipboardDemoSrvrItem::CClipboardDemoSrvrItem(CClipboardDemoDoc* pContainerDoc)
	: COleServerItem(pContainerDoc, TRUE)
{
	// TODO: add one-time construction code here
	//  (eg, adding additional clipboard formats to the item's data source)
}

CClipboardDemoSrvrItem::~CClipboardDemoSrvrItem()
{
	// TODO: add cleanup code here
}

void CClipboardDemoSrvrItem::Serialize(CArchive& ar)
{
	// CClipboardDemoSrvrItem::Serialize will be called by the framework if
	//  the item is copied to the clipboard.  This can happen automatically
	//  through the OLE callback OnGetClipboardData.  A good default for
	//  the embedded item is simply to delegate to the document's Serialize
	//  function.  If you support links, then you will want to serialize
	//  just a portion of the document.

	if (!IsLinkedItem())
	{
		CClipboardDemoDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (pDoc)
			pDoc->Serialize(ar);
	}
}

BOOL CClipboardDemoSrvrItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// Most applications, like this one, only handle drawing the content
	//  aspect of the item.  If you wish to support other aspects, such
	//  as DVASPECT_THUMBNAIL (by overriding OnDrawEx), then this
	//  implementation of OnGetExtent should be modified to handle the
	//  additional aspect(s).

	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	// CClipboardDemoSrvrItem::OnGetExtent is called to get the extent in
	//  HIMETRIC units of the entire item.  The default implementation
	//  here simply returns a hard-coded number of units.

	// TODO: replace this arbitrary size

	//rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC units
	CClipboardDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CView* pView = NULL;
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = pDoc->GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CClipboardDemoView)))
			break;
		else {
			pView = NULL; //keep looking
		}
	}
	rSize = ((CClipboardDemoView*)pView)->m_objectSize;
	CClientDC dc(NULL);
	dc.SetMapMode(MM_ANISOTROPIC);
	//dc.SetViewportExt(dc.GetDeviceCaps(LOGPIXELSX), dc.GetDeviceCaps(LOGPIXELSY));
	//dc.SetWindowExt(rSize);
	dc.LPtoHIMETRIC(&rSize);

	return TRUE;
}

BOOL CClipboardDemoSrvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
	if (!pDC)
		return FALSE;

	// Remove this if you use rSize
	//UNREFERENCED_PARAMETER(rSize);

	// TODO: set mapping mode and extent
	//  (The extent is usually the same as the size returned from OnGetExtent)

	// TODO: add drawing code here.  Optionally, fill in the HIMETRIC extent.
	//  All drawing takes place in the metafile device context (pDC).
	CClipboardDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CView* pView = NULL;
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = pDoc->GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CClipboardDemoView)))
			break;
		else {
			pView = NULL; //keep looking
		}
	}
	if (pView != NULL) {
		//CSize size = ((CClipboardDemoView*)pView)->m_objectSize;
		rSize = ((CClipboardDemoView*)pView)->m_objectSize;

		pDC->SetMapMode(MM_ANISOTROPIC);
		pDC->SetWindowOrg(0,0);
		pDC->SetWindowExt(rSize);
		pDC->SetViewportExt(rSize);  // Note: only affects the m_hAttribDC

		pDC->DPtoHIMETRIC(&rSize);   // convert pixels to HIMETRIC
		((CClipboardDemoView*)pView)->OnDraw(pDC);
	}

	return TRUE;
}


// CClipboardDemoSrvrItem diagnostics

#ifdef _DEBUG
void CClipboardDemoSrvrItem::AssertValid() const
{
	COleServerItem::AssertValid();
}

void CClipboardDemoSrvrItem::Dump(CDumpContext& dc) const
{
	COleServerItem::Dump(dc);
}
#endif

