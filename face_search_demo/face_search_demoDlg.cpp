
// face_search_demoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "face_search_demo.h"
#include "face_search_demoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cface_search_demoDlg 对话框



Cface_search_demoDlg::Cface_search_demoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cface_search_demoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



BEGIN_MESSAGE_MAP(Cface_search_demoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONOPENCAMERA, &Cface_search_demoDlg::OnBnClickedButtonopencamera)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTONCATCH, &Cface_search_demoDlg::OnBnClickedButtoncatch)
	ON_BN_CLICKED(IDC_BUTTONSEARCH, &Cface_search_demoDlg::OnBnClickedButtonsearch)
	ON_BN_CLICKED(IDC_BUTTONOPENFILE, &Cface_search_demoDlg::OnBnClickedButtonopenfile)
	ON_BN_CLICKED(IDC_RADIO1, &Cface_search_demoDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &Cface_search_demoDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &Cface_search_demoDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &Cface_search_demoDlg::OnBnClickedRadio4)
END_MESSAGE_MAP()


// Cface_search_demoDlg 消息处理程序

BOOL Cface_search_demoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CheckDlgButton(IDC_RADIO2, 1);
	OnBnClickedRadio2();

	CheckDlgButton(IDC_RADIO3, 1);
	OnBnClickedRadio3();




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cface_search_demoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cface_search_demoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	int i = 0;
	UINT dst[] = { IDC_STATICRESULT1, IDC_STATICRESULT2, IDC_STATICRESULT3, IDC_STATICRESULT4, IDC_STATICRESULT5 };
	for (int &temp_image_number : images_sequence_array)
	{
		if (i < 5)
		{
			ShowImageTo(images_data_set[temp_image_number - 1], dst[i]);
		}
	
		i++;

	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cface_search_demoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cface_search_demoDlg::OnBnClickedButtonopencamera()
{
	// TODO:  在此添加控件通知处理程序代码
	camera_capture.open(0);
	SetTimer(1, 10, NULL);

}


void Cface_search_demoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	camera_capture >> current_camera_frame;
	imwrite("F:\\reserve_camera_frame.jpg", current_camera_frame);//输出未经人脸检测的图片
	current_camera_frame = DetectFace(current_camera_frame, faces);
	ShowImageTo(current_camera_frame, IDC_STATICSHOWCURRENTCAMERA);


	CDialogEx::OnTimer(nIDEvent);
}

void   Cface_search_demoDlg::ShowImageTo(Mat image, UINT dst)
{
	CvvImage cvvImg; //CvvImage类

	CWnd *pwnd = GetDlgItem(dst);
	HDC hdc = pwnd->GetDC()->GetSafeHdc();
	CRect rect;
	pwnd->GetClientRect(&rect);

	IplImage img = image;
	cvvImg.CopyOf(&img);//复制图像到当前的CvvImage对象中  
	cvvImg.DrawToHDC(hdc, &rect);
}

Mat  Cface_search_demoDlg::DetectFace(Mat frame, vector<Rect>& faces)
{
	faces.clear();
	CascadeClassifier face_cascade;
	face_cascade.load("E:\\opencv\\sources\\data\\lbpcascades\\lbpcascade_frontalface.xml");

	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++)
	{
		cv::rectangle(frame, faces[i], Scalar(0, 255, 0), 3);

	}
	//-- Show what you got
	return frame;
}



void Cface_search_demoDlg::OnBnClickedButtoncatch()
{
	// TODO:  在此添加控件通知处理程序代码

	KillTimer(1);

	imwrite("F:\\reserve_camera_normal_face_image.jpg", camera_normal_face_image);
	camera_normal_face_image = current_camera_frame(faces[0]);
	
	ShowImageTo(camera_normal_face_image, IDC_STATICSHOWCAMERACATCHFACE);
}


void Cface_search_demoDlg::OnBnClickedButtonsearch()
{
	images_data_set.clear();

	

	Mat test_image;


	switch (normal_image_source_choose)
	{
	case 0:
		test_image = camera_normal_face_image;
		break;

	case 1:
		test_image = file_normal_face_image;
		break;

	default:
		break;
	}

	// TODO:  在此添加控件通知处理程序代码
	images_sequence_array = search(test_image, images_data_set, weight_or_not);//输入参数为视频截图，图片库，检索方法s
	CString result = NULL, b;
	int i = 0;
	UINT dst[] = { IDC_STATICRESULT1, IDC_STATICRESULT2,IDC_STATICRESULT3, IDC_STATICRESULT4, IDC_STATICRESULT5};
	for (int &temp_image_number : images_sequence_array)
	{
		if (i < 5)
		{
			ShowImageTo(images_data_set[temp_image_number - 1], dst[i]);
		}
		b.Format(L"%d", temp_image_number);
		result += b;
		result += ",";
		i++;

	}
	SetDlgItemText(IDC_EDITRESULT, result);

}


void Cface_search_demoDlg::OnBnClickedButtonopenfile()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(
		TRUE, _T("*.jpg"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files(*.jpg;*.png)|*.jpg;*.png|All Files (*.*)|*.*||"), NULL
		);										// 选项图片的约定
	dlg.m_ofn.lpstrTitle = _T("Open Image");	// 打开文件对话框的标题名
	if (dlg.DoModal() != IDOK)					// 判断是否获得图片
		return;

	CString mPath = dlg.GetPathName();			// 获取图片路径
	USES_CONVERSION;
	LPSTR Test = T2A(mPath);
	file_nomal_image = imread(Test);
	ShowImageTo(file_nomal_image, IDC_STATICFILENORMALIMAGE);
	file_normal_face_image = DetectFace(file_nomal_image, faces);
	file_normal_face_image = file_normal_face_image(faces[0]);

}


void Cface_search_demoDlg::OnBnClickedRadio1()
{
	// TODO:  在此添加控件通知处理程序代码
	normal_image_source_choose = 0;
}


void Cface_search_demoDlg::OnBnClickedRadio2()
{
	// TODO:  在此添加控件通知处理程序代码
	normal_image_source_choose = 1;
}


void Cface_search_demoDlg::OnBnClickedRadio3()
{
	// TODO:  在此添加控件通知处理程序代码
	weight_or_not = 0;
}


void Cface_search_demoDlg::OnBnClickedRadio4()
{
	// TODO:  在此添加控件通知处理程序代码
	weight_or_not = 1;
}
