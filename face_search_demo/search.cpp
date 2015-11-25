#include "search.h"



static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator ) {
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty()) {
			images.push_back(imread(path));
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}

bool strict_weak_ordering(const pair<int, double> a, const pair<int, double> b)
{
	return a.second > b.second;
}

vector<int> search(Mat &m,  vector<Mat> &imageset,const bool& weight_or_not)
{
	vector<int> a;
//	string fn_csv = "F:\\test.csv";

	ifstream finPos("F:\\test.txt");

	string ImgName;

	Mat temp_image;
	vector<int> labels;
	int j = 1;
	while (getline(finPos, ImgName))
	{
		temp_image = imread(ImgName);
		imageset.push_back(temp_image);
		labels.push_back(j++);
	}
	Mat sourceimage=m;

	Mat hist1 = GetWholeHistLBPWay(sourceimage);

	double hist_array1[2891], hist_array2[2891];

	//hist1 = hist1.t();
	hist1 = hist1.reshape(1, 1);
	for (int i = 0; i < hist1.cols; i++)
	{
		hist_array1[i] = hist1.at<double>(0, i);
	}

	//
	//Mat hist1 = GetLBPHist(sourceimage);

	double simil;

	// These vectors hold the images and corresponding labels.

	

	pair<int, double> temp;
	vector<pair<int, double>> store;
	// Read in the data. This can fail if no valid
	// input filename is given.
	//read_csv(fn_csv, imageset, labels);

//	imshow("test",imageset[0]);
	
	int t = 0;
	Mat hist2;

	//vector<double> temphist;


	//imshow("1213", imageset[1]);
	
	vector<Rect> faces;
	for (Mat &m : imageset)
	{

		temp_image = DetectFace(m, faces);

		if (faces.size()>0)
		{
			temp_image = temp_image(faces[0]);

			//	temphist = getLBPhist(m,rad, pts, mapping);

			hist2 = GetWholeHistLBPWay(temp_image);

			//hist2 = hist2.t();
			hist2 = hist2.reshape(1, 1);
			for (int i = 0; i < hist2.cols; i++)
			{
				hist_array2[i] = hist2.at<double>(0, i);
			}
			//	hist2 = GetLBPHist(temp_image);

			//	simil = compareHist(hist1, hist2, CV_COMP_CHISQR);
			//	simil = compareHist(temphist, originalhist, compare_method);
			/*switch (weight_or_not)
			{
			case 0:
				simil = GetWeightedChiSquare(hist_array1, hist_array2);
				break;
			case 1:
				simil = GetNonWeightedChiSquare(hist_array1, hist_array2);
			}*/

			simil = GetCosAngle(hist_array1,hist_array2);
		

			temp = make_pair(labels[t++], simil);

			store.push_back(temp);

		}
	}
	sort(store.begin(), store.end(), strict_weak_ordering);
	
	
	for (pair<int, double>	&m : store) 
	a.push_back(m.first);

	return a;
}
Mat GetWholeHistLBPWay(Mat imgOrg)
{
	cvtColor(imgOrg, imgOrg, CV_BGR2GRAY);
	resize(imgOrg, imgOrg, Size(130, 150));

	int XStep = 18;
	int YStep = 21;

	Mat TempImage,  FinalHist = Mat::zeros(59, 49, CV_64F);
	vector<double> TempHist;

	int j = 0;
	for (int YLocation = 0; YLocation < 7; YLocation++)
	for (int XLocation = 0; XLocation < 7; XLocation++)
	{
		TempImage = imgOrg(cv::Rect(XLocation*XStep, YLocation*YStep, XStep, YStep));
		TempHist = GetPartHistLBPWay(TempImage);
		
		for (int i = 0; i < TempHist.size(); i++)
		{
			FinalHist.at<double>(i, j) = TempHist[i];
		};
		j++;
	}
	//FinalHist.t();
	 FinalHist.reshape(1,1);


	return FinalHist;
	//cvtColor(imgOrg, imgOrg, CV_BGR2GRAY);
	//resize(imgOrg, imgOrg, Size(130, 150));



}

vector<double> GetPartHistLBPWay(Mat imgOrg)
{
	int rad = 2;
	int pts = 8;
	std::string mapping = "u2";
	bool outputHist = 1, normalizeHist = 1;

	imgOrg.convertTo(imgOrg, CV_64F);

	Mat lbpImg = Mat(imgOrg.size(), CV_8UC1, Scalar(0));

	// Create an LBP instance of type "mapping" using "pts" support points
	LBP lbp(pts, LBP::strToType(mapping));

	for (int i = 0; i < imgOrg.channels(); i++) {
		// Copy channel i
		Mat img(imgOrg.size(), imgOrg.depth(), 1);
		const int from_to1[] = { i, 0 };
		mixChannels(&imgOrg, 1, &img, 1, from_to1, 1);

		// Calculate the descriptor
		lbp.calcLBP(img, rad, true);

		// Copy lbp image
		const int from_to2[] = { 0, i };
		Mat tmpImg = lbp.getLBPImage();
		mixChannels(&tmpImg, 1, &lbpImg, 1, from_to2, 1);
	}
	

	vector<double> part_hist = lbp.calcHist().getHist(normalizeHist);

	return part_hist;

}

Mat DetectFace(Mat frame, vector<Rect>& faces)
{
	faces.clear();
	CascadeClassifier face_cascade;
	face_cascade.load("F:\\opencv\\sources\\data\\lbpcascades\\lbpcascade_frontalface.xml");

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