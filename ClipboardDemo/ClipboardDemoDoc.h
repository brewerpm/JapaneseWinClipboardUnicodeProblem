
// ClipboardDemoDoc.h : interface of the CClipboardDemoDoc class
//


#pragma once


class CClipboardDemoSrvrItem;

class CClipboardDemoDoc : public COleServerDoc
{
protected: // create from serialization only
	CClipboardDemoDoc() noexcept;
	DECLARE_DYNCREATE(CClipboardDemoDoc)

// Attributes
public:
	CClipboardDemoSrvrItem* GetEmbeddedItem()
		{ return reinterpret_cast<CClipboardDemoSrvrItem*>(COleServerDoc::GetEmbeddedItem()); }

// Operations
public:

// Overrides
protected:
	virtual COleServerItem* OnGetEmbeddedItem();
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CClipboardDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual CDocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();

	CString m_s1, m_s2;
};
