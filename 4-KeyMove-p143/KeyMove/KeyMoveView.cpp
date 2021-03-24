
// KeyMoveView.cpp : CKeyMoveView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "KeyMove.h"
#endif

#include "KeyMoveDoc.h"
#include "KeyMoveView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKeyMoveView

IMPLEMENT_DYNCREATE(CKeyMoveView, CView)

BEGIN_MESSAGE_MAP(CKeyMoveView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_SYSKEYDOWN()
END_MESSAGE_MAP()

// CKeyMoveView ����/�Ҹ�

CKeyMoveView::CKeyMoveView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CKeyMoveView::~CKeyMoveView()
{
}

BOOL CKeyMoveView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CKeyMoveView �׸���

void CKeyMoveView::OnDraw(CDC* /*pDC*/)
{
	CKeyMoveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CKeyMoveView �μ�

BOOL CKeyMoveView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CKeyMoveView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CKeyMoveView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CKeyMoveView ����

#ifdef _DEBUG
void CKeyMoveView::AssertValid() const
{
	CView::AssertValid();
}

void CKeyMoveView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKeyMoveDoc* CKeyMoveView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKeyMoveDoc)));
	return (CKeyMoveDoc*)m_pDocument;
}
#endif //_DEBUG


// CKeyMoveView �޽��� ó����


int CKeyMoveView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_wndChild.Create(TEXT("STATIC"), TEXT("KeyMove"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
		CRect(100, 100, 200, 200), this, 1234);

	return 0;
}


void CKeyMoveView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CPoint ptChild;			// ���ϵ� �������� ��ǥ 
	CPoint ptParent;		// �θ� �������� �� ��ǥ
	CRect Rect;				// ���ϵ� �������� ��ǥ �� ũ��
	int width;

	// ���ϵ� �������� ��ǥ �� ũ�� ���� �˾ƿ�
	m_wndChild.GetWindowRect(&Rect);
	ptChild.x = Rect.left;
	ptChild.y = Rect.top;
	width = Rect.right - Rect.left;

	// �� �������� ��ǥ �� ũ�� ������ �˾ƿ�
	//AfxGetMainWnd()->GetWindowRect(&Rect);			// ������������ �ڵ��� ��� �������� ��ǥ �� ũ�⸦ ������
	this->GetWindowRect(&Rect);					// View Window�� ũ�⸦ ������
	//ptParent = Rect.BottomRight();
	ptParent.x = Rect.right;
	ptParent.y = Rect.bottom;

	// ��ũ�� ���� ��ǥ�� Ŭ���̾�Ʈ �� ������ ��ǥ�� ȯ��
	ScreenToClient(&ptChild);
	ScreenToClient(&ptParent);

	switch (nChar)
	{
	case VK_LEFT:		// ���� ȭ��ǥ ���� ���
		if (ptChild.x - 10 > 0)
			ptChild.x -= 10;
		else
			ptChild.x = 0;
		break;
	case VK_RIGHT:		// ������ ȭ��ǥ ���� ���
		if (ptChild.x + 10 + width < ptParent.x)
			ptChild.x += 10;
		else
			ptChild.x = ptParent.x - width;
		break;
	}

	// ����� ����ǥ�� ���ϵ� �����츦 �ٽ� �׷���
	m_wndChild.SetWindowPos(&CWnd::wndTop, ptChild.x, ptChild.y, 0, 0,
		SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);



	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CKeyMoveView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// CString strText = TEXT("");
	// strText.Format(TEXT("%c"), nChar);

	static CString strText = TEXT("");

	if (nChar != VK_RETURN && nChar != VK_BACK && nChar != VK_ESCAPE)
	{
		strText.AppendFormat(TEXT("%c"), nChar);	
		m_wndChild.SetWindowText(strText);				// SetWindowText�� ���ڷ� ���޹��� ���ڿ��� ������ �ؽ�Ʈ�� ����
	}
	if (nChar == VK_BACK && !strText.IsEmpty())
	{
		//strText.Delete(strText.GetLength() - 1, 3);
		strText.Delete(strText.GetLength() - 1, 3);		// 3���̳� 1���̳� 1���� �����Ǵ� ���� �߻�
		m_wndChild.SetWindowText(strText);				// SetWindowText�� ���ڷ� ���޹��� ���ڿ��� ������ �ؽ�Ʈ�� ����
	}

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CKeyMoveView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CString strMessage = TEXT("");

	WORD wResult = ::GetKeyState(VK_SPACE);
	BYTE byHigh = HIBYTE(wResult);

	// nFlag���� ��������Ʈ�� 1�� ��Ʈ�� 1�̸� -> alt�� ������ ����
	if (byHigh & 0x01)
	{
		strMessage += TEXT("Alt + Space, ");
	}


	CView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}
