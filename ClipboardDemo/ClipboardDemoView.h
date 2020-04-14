
// ClipboardDemoView.h : interface of the CClipboardDemoView class
//

#pragma once


class CClipboardDemoView : public CView
{
protected: // create from serialization only
	CClipboardDemoView() noexcept;
	DECLARE_DYNCREATE(CClipboardDemoView)

// Attributes
public:
	CClipboardDemoDoc* GetDocument() const;

// Operations
public:
	CSize m_objectSize;

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CClipboardDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnCancelEditSrvr();
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // debug version in ClipboardDemoView.cpp
inline CClipboardDemoDoc* CClipboardDemoView::GetDocument() const
   { return reinterpret_cast<CClipboardDemoDoc*>(m_pDocument); }
#endif

