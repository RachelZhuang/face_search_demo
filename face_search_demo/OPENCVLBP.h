
#include <iostream>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

template <typename _Tp> static
inline void elbp_(InputArray _src, OutputArray _dst, int radius, int neighbors);


static void elbp(InputArray src, OutputArray dst, int radius, int neighbors);

static Mat
histc_(const Mat& src, int minVal = 0, int maxVal = 255, bool normed = false);

static Mat histc(InputArray _src, int minVal, int maxVal, bool normed);

static Mat spatial_histogram(InputArray _src, int numPatterns,
	int grid_x, int grid_y, bool /*normed*/);

static Mat elbp(InputArray src, int radius, int neighbors); 

Mat GetLBPHist(Mat& src);
