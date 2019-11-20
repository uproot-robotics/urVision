#ifndef PLANT_DETECTOR_H
#define PLANT_DETECTOR_H

#include "../include/PlantFilter.h"

#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Some constants
const int MAX_EDGE_THRESHOLD = 200;
const int max_value_H = 360 / 2;
const int max_value = 255;

const int morph_type = MORPH_ELLIPSE;

const int max_kernel_size = 21;

const String window_capture_name = "Current Frame";
const String window_color_threshold_name = "Color Threshold";
const String window_edge_detection = "Edge Detection";
const String window_test = "Window Test";
const String window_morphs = "Morphological Output";

// Trackbar callback prototypes
static void on_edge_thresh1_trackbar(int, void *);
static void on_low_H_thresh_trackbar(int, void *);
static void on_high_H_thresh_trackbar(int, void *);
static void on_low_S_thresh_trackbar(int, void *);
static void on_high_S_thresh_trackbar(int, void *);
static void on_low_V_thresh_trackbar(int, void *);
static void on_high_V_thresh_trackbar(int, void *);

class PlantDetector
{
public:
	PlantDetector(int showWindows, Size frameSize);
	~PlantDetector();

	int init(float minWeedSize, float maxWeedSize);
	int processFrame(Mat frame);

	vector<KeyPoint> getWeedList();

	vector<KeyPoint> m_lastObjectsFound;
	vector<KeyPoint> m_weedList;
	vector<KeyPoint> m_cropList;

	int m_showWindows;
	int m_inited;

	PlantFilter* m_plantFilter;

	// Blob detector parameters (dynamic)
	SimpleBlobDetector::Params m_blobParams;
	Size m_frameSize;

private:
	vector<KeyPoint> DetectBlobs(Mat srcFrame);
	Mat ColorThresholding(Mat srcFrame);

	// Various image holders
	Mat scaledFrame;
	Mat greenFrame;
	Mat blurFrame;
	Mat colorMask;
	Mat hsvFrame;
	Mat morphFrame;
};

#endif PLANT_DETECTOR_H
