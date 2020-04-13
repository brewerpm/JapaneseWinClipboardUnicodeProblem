
// SrvrItem.h : interface of the CClipboardDemoSrvrItem class
//

#pragma once

class CClipboardDemoSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CClipboardDemoSrvrItem)

// Constructors
public:
	CClipboardDemoSrvrItem(CClipboardDemoDoc* pContainerDoc);

// Attributes
	CClipboardDemoDoc* GetDocument() const
		{ return reinterpret_cast<CClipboardDemoDoc*>(COleServerItem::GetDocument()); }

// Overrides
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);

// Implementation
public:
	~CClipboardDemoSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

