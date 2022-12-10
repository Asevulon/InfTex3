
// MyDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "InfTex3.h"
#include "MyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно MyDlg



MyDlg::MyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFTEX3_DIALOG, pParent)
	, A(1)
	, f(100)
	, y(0)
	, nlmin(0)
	, nlmax(10)
	, steps(50)
	, fd(400)
	, N(512)
	, GN(1000)
	, wlen(12)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, A);
	DDX_Text(pDX, IDC_EDIT2, f);
	DDX_Text(pDX, IDC_EDIT3, y);
	DDX_Text(pDX, IDC_EDIT4, nlmin);
	DDX_Text(pDX, IDC_EDIT5, nlmax);
	DDX_Text(pDX, IDC_EDIT6, steps);
	DDX_Text(pDX, IDC_EDIT7, fd);
	DDX_Text(pDX, IDC_EDIT8, N);
	DDX_Text(pDX, IDC_EDIT9, GN);
	DDX_Text(pDX, IDC_EDIT10, wlen);
}

BEGIN_MESSAGE_MAP(MyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &MyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &MyDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений MyDlg

BOOL MyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	sgn.SetSngDrwHWND(GetDlgItem(IDC_SGN)->GetSafeHwnd());
	sgn.SetSpdDrwHWND(GetDlgItem(IDC_SPD)->GetSafeHwnd());
	sgn.SetDispDrwHWND(GetDlgItem(IDC_DISP)->GetSafeHwnd());

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void MyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		sgn.Redraw();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR MyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void MyDlg::OnBnClickedOk()
{
	UpdateData();


	sgn.SetFD(fd);
	sgn.SetN(N);
	sgn.SetStartNoiseLevel(nlmin);
	sgn.SetFinalNoiseLevel(nlmax);
	sgn.SetNoiseSteps(steps);
	sgn.SetGenNum(GN);
	sgn.SetSinParam(A, f, y);
	sgn.SetWlen(wlen);

	th = CreateThread(NULL, 0, thfunc, this, 0, NULL);

}


DWORD WINAPI thfunc(LPVOID lp)
{
	MyDlg* dlg = (MyDlg*)lp;
	dlg->sgn.GenerateStats();
	return 0;
}
DWORD WINAPI thfunc2(LPVOID lp)
{
	MyDlg* dlg = (MyDlg*)lp;
	dlg->sgn.GenerateStatsOnce();
	return 0;
}

void MyDlg::OnBnClickedButton1()
{
	UpdateData();


	sgn.SetFD(fd);
	sgn.SetN(N);
	sgn.SetStartNoiseLevel(nlmin);
	sgn.SetFinalNoiseLevel(nlmax);
	sgn.SetNoiseSteps(steps);
	sgn.SetGenNum(GN);
	sgn.SetSinParam(A, f, y);
	sgn.SetWlen(wlen);

	th = CreateThread(NULL, 0, thfunc2, this, 0, NULL);
}
