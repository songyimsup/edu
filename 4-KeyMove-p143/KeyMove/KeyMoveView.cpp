
// KeyMoveView.cpp : CKeyMoveView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_SYSKEYDOWN()
END_MESSAGE_MAP()

// CKeyMoveView 생성/소멸

CKeyMoveView::CKeyMoveView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CKeyMoveView::~CKeyMoveView()
{
}

BOOL CKeyMoveView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CKeyMoveView 그리기

void CKeyMoveView::OnDraw(CDC* /*pDC*/)
{
	CKeyMoveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CKeyMoveView 인쇄

BOOL CKeyMoveView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CKeyMoveView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CKeyMoveView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CKeyMoveView 진단

#ifdef _DEBUG
void CKeyMoveView::AssertValid() const
{
	CView::AssertValid();
}

void CKeyMoveView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKeyMoveDoc* CKeyMoveView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKeyMoveDoc)));
	return (CKeyMoveDoc*)m_pDocument;
}
#endif //_DEBUG


// CKeyMoveView 메시지 처리기


int CKeyMoveView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_wndChild.Create(TEXT("STATIC"), TEXT("KeyMove"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
		CRect(100, 100, 200, 200), this, 1234);

	return 0;
}


void CKeyMoveView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPoint ptChild;			// 차일드 윈도우의 좌표 
	CPoint ptParent;		// 부모 윈도우의 끝 좌표
	CRect Rect;				// 차일드 윈도우의 좌표 및 크기
	int width;

	// 차일드 윈도우의 좌표 및 크기 정보 알아옴
	m_wndChild.GetWindowRect(&Rect);
	ptChild.x = Rect.left;
	ptChild.y = Rect.top;
	width = Rect.right - Rect.left;

	// 뷰 윈도우의 좌표 및 크기 정보를 알아옴
	//AfxGetMainWnd()->GetWindowRect(&Rect);			// 메인윈도우의 핸들을 얻고 윈도우의 좌표 및 크기를 가져옴
	this->GetWindowRect(&Rect);					// View Window의 크기를 가져옴
	//ptParent = Rect.BottomRight();
	ptParent.x = Rect.right;
	ptParent.y = Rect.bottom;

	// 스크린 기준 좌표를 클라이언트 뷰 기준의 좌표로 환산
	ScreenToClient(&ptChild);
	ScreenToClient(&ptParent);

	switch (nChar)
	{
	case VK_LEFT:		// 왼쪽 화살표 눌린 경우
		if (ptChild.x - 10 > 0)
			ptChild.x -= 10;
		else
			ptChild.x = 0;
		break;
	case VK_RIGHT:		// 오른쪽 화살표 눌린 경우
		if (ptChild.x + 10 + width < ptParent.x)
			ptChild.x += 10;
		else
			ptChild.x = ptParent.x - width;
		break;
	}

	// 변경된 새좌표로 차일드 윈도우를 다시 그려줌
	m_wndChild.SetWindowPos(&CWnd::wndTop, ptChild.x, ptChild.y, 0, 0,
		SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);



	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CKeyMoveView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// CString strText = TEXT("");
	// strText.Format(TEXT("%c"), nChar);

	static CString strText = TEXT("");

	if (nChar != VK_RETURN && nChar != VK_BACK && nChar != VK_ESCAPE)
	{
		strText.AppendFormat(TEXT("%c"), nChar);	
		m_wndChild.SetWindowText(strText);				// SetWindowText는 인자로 전달받은 문자열을 윈도우 텍스트로 변경
	}
	if (nChar == VK_BACK && !strText.IsEmpty())
	{
		//strText.Delete(strText.GetLength() - 1, 3);
		strText.Delete(strText.GetLength() - 1, 3);		// 3개이나 1개이나 1개만 삭제되는 버그 발생
		m_wndChild.SetWindowText(strText);				// SetWindowText는 인자로 전달받은 문자열을 윈도우 텍스트로 변경
	}

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CKeyMoveView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString strMessage = TEXT("");

	WORD wResult = ::GetKeyState(VK_SPACE);
	BYTE byHigh = HIBYTE(wResult);

	// nFlag에서 상위바이트의 1번 비트가 1이면 -> alt가 눌러진 상태
	if (byHigh & 0x01)
	{
		strMessage += TEXT("Alt + Space, ");
	}


	CView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}
