
// face_search_demoDlg.h : 头文件
//

#pragma once
#include <opencv2/opencv.hpp>

#include <iostream>  
#include <fstream> 

#include "CvvImage.h"
#include "stdafx.h"
#include "afxwin.h"
#include "search.h"
using namespace cv;
//using namespace search;

// Cface_search_demoDlg 对话框
class Cface_search_demoDlg : public CDialogEx
{
// 构造
public:
	Cface_search_demoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FACE_SEARCH_DEMO_DIALOG };



// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonopencamera();

	void ShowImageTo(Mat image, UINT dst);
	Mat  DetectFace(Mat frame, vector<Rect>& faces);

	//变量定义
private:
	VideoCapture camera_capture;
	Mat current_camera_frame, camera_normal_face_image;//current_camera_frame是摄像头实时画面， camera_normal_face_image是捕捉后经人脸检测的图片

	vector<Rect> faces;
	Mat file_certificate_image, file_certificate_face_image;//file_certificate_image是未经人脸检测的证件照,file_certificate_face_image是检测之后的人脸照

	Mat file_nomal_image, file_normal_face_image;//file_nomal_image是未经人脸检测的普通照，file_nomal_face_image是检测之后的人脸照

	vector<Mat> images_data_set;
	vector<int> images_sequence_array;
	bool normal_image_source_choose;
	bool weight_or_not;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtoncatch();
	afx_msg void OnBnClickedButtonsearch();

	afx_msg void OnBnClickedButtonopenfile();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
};
