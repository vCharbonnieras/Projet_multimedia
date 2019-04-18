// Inspired by https://docs.opencv.org/trunk/d8/d19/tutorial_stitcher.html
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/stitching.hpp>

#include <iostream>

using namespace std;
using namespace cv;

// Variable used by both functions
bool sep = false;
Stitcher::Mode mode = Stitcher::PANORAMA;
vector<Mat> imageArray;
String result_name = "result.jpg";

int parseCmdArgs(int argc, char** argv) {
	if(argc==1) {
		return -1;
	}
	else {
		for(int i=1; i<argc; ++i) {
			// Use balise to show the separation between each image
			if(string(argv[i]) == "--d") {
				bool sep = true;
			}
			// Use balise to change result name
			else if(string(argv[i]) == "--o") {
				result_name = argv[i + 1];
				i++;
			}
			// Use balise to set mode
			else if(string(argv[i]) == "--m") {
				if(string(argv[i+1]) == "panorama") {
					mode = Stitcher::PANORAMA;
				}
				else if(string(argv[i+1]) == "scans") {
					mode = Stitcher::SCANS;
				}
				else {
					cout << "Unrecognized value for flag mode, try panorama or scans" << endl;
					return -1;
				}
			}
			// Remaining arguments should be image only
			else {
				Mat image = imread(argv[i], IMREAD_COLOR);
				if(image.empty()) {
					cout << "Can't find or open image '" << argv[i] << "'" << endl;
					return -1;
				}
				if(sep) {
					Rect rect(0, 0, image.cols/2, image.rows);
					imageArray.push_back(image(rect).clone());
					rect.x = image.cols/3;
					imageArray.push_back(image(rect).clone());
					rect.x = image.cols/2;
					imageArray.push_back(image(rect).clone());
				}
				else {
					imageArray.push_back(image);
				}
			}
			
		}
	}
	return 0;
}

int main(int argc, char** argv) {
	
	// Check if arguments parsing went well
	int failure = parseCmdArgs(argc, argv);
	if(failure) {
		return -1;
	}
	
	// Stitching
	Mat result;
	Ptr<Stitcher> stitcher = Stitcher::create(mode);
	Stitcher::Status status = stitcher->stitch(imageArray, result);
	
	// Check Stitcher's status (works like HTTP?)
	if(status != Stitcher::OK) {
		cout << "Can't stitch images, error code = " << int(status) << endl;
		return -1;
	}
	else {
		imwrite(result_name, result);
		cout << "Stitching completed successfully" << endl;
		cout << result_name << "saved." << endl;
		return 0;
	} 
}