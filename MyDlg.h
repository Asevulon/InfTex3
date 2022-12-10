
// MyDlg.h: файл заголовка
//

#pragma once
#include"Sgn.h"

// Диалоговое окно MyDlg
class MyDlg : public CDialogEx
{
// Создание
public:
	MyDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFTEX3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	Sgn sgn;
	double A;
	double f;
	double y;
	double nlmin;
	double nlmax;
	int steps;
	double fd;
	int N;
	int GN;
	int wlen;


	HANDLE th;
	afx_msg void OnBnClickedButton1();
};


DWORD WINAPI thfunc(LPVOID lp);
DWORD WINAPI thfunc2(LPVOID lp);
