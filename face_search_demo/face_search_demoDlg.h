
// face_search_demoDlg.h : ͷ�ļ�
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

// Cface_search_demoDlg �Ի���
class Cface_search_demoDlg : public CDialogEx
{
// ����
public:
	Cface_search_demoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FACE_SEARCH_DEMO_DIALOG };



// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonopencamera();

	void ShowImageTo(Mat image, UINT dst);
	Mat  DetectFace(Mat frame, vector<Rect>& faces);

	//��������
private:
	VideoCapture camera_capture;
	Mat current_camera_frame, camera_normal_face_image;//current_camera_frame������ͷʵʱ���棬 camera_normal_face_image�ǲ�׽����������ͼƬ

	vector<Rect> faces;
	Mat file_certificate_image, file_certificate_face_image;//file_certificate_image��δ����������֤����,file_certificate_face_image�Ǽ��֮���������

	Mat file_nomal_image, file_normal_face_image;//file_nomal_image��δ������������ͨ�գ�file_nomal_face_image�Ǽ��֮���������

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
