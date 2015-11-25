#include "getLBPhist.h"

vector<double> getLBPhist(Mat &imgOrg, int rad, int pts, string mapping)
{
	bool outputHist = 1, normalizeHist = 1;

	imgOrg.convertTo(imgOrg, CV_64F);

	Mat lbpImg;
	switch (imgOrg.channels()) {
	case 1:
		lbpImg = Mat(imgOrg.size(), CV_8UC1, Scalar(0));
		break;
	case 3:
		lbpImg = Mat(imgOrg.size(), CV_8UC3, Scalar(0));
		break;

	}

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
	return lbp.calcHist().getHist(normalizeHist);
}