


// animation-Dialogfeld

#include "afxcmn.h"
#include "afxwin.h"
class animation : public CDialogEx
{
	DECLARE_DYNAMIC(animation)

public:
	animation(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~animation();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ANIMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();

private:
	static const int balkenhoehe = 12;
	static const int balkenabstand = 4;
	static const int abstand = 4;
	static const int minbreite = 340;	int running;	int pause;	int position;	CRect rec_spalte;	CRect rec_animation;	int hoehe;
public:
	CProgressCtrl m_progress;
	CSliderCtrl m_speed;
	CStatic m_animation;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedStart();
	CButton m_start;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CStatic m_spalte;
};
