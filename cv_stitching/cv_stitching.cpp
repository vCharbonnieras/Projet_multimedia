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

int usage() {
	cout << "Stitching: Stitches images which borders are similar and with the ";
	cout << "same extensions(expected multiple images in args). ";
	cout << "See the flags below to change options." << endl;
	cout << "--s: enable separator between images." << endl;
	cout << "--o: change the image result name. Write the name after this flag." << endl;
	cout << "--m: change the method of stitching by writing either \"panorama\" ";
	cout << "or \"scans\" following this flag. " << endl;
	cout << "--d: load images from the directory written following this flag. ";
	cout << "Those images need to be in the same extensions to perform stitching. ";
	cout << "Supported extensions: {jpeg, jpg, png}." << endl;
	cout << "Other arguments should be images only "
}

int loadImage(String name, bool sep) {
	Mat image = imread(name, IMREAD_COLOR);
	if(image.empty()) {
		cout << "Can't find or open image '" << name << "'" << endl;
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
	return 0;
}

int parseCmdArgs(vector<string> opt) {
	if(argc==1) {
		return -1;
	}
	else {
		for(int i=1; i<opt.size(); ++i) {
			// Use this flag to show use of stitching
			if(string(opt[i]) == "?" or string(opt[i]) == "help") {
				usage();
				return -2;
			}
			// Use this flag to show the separation between each image
			else if(string(opt[i]) == "--s") {
				bool sep = true;
			}
			// Use this flag to change result name
			else if(string(opt[i]) == "--o") {
				result_name = opt[i+1];
				i++;
			}
			// Use this flag to set mode
			else if(string(opt[i]) == "--m") {
				if(string(opt[i+1]) == "panorama") {
					mode = Stitcher::PANORAMA;
					i++;
				}
				else if(string(opt[i+1]) == "scans") {
					mode = Stitcher::SCANS;
					i++;
				}
				else {
					cout << "Unrecognized value for flag mode, try panorama or scans" << endl;
					return -1;
				}
			}
			// Use this flag to load all images from a directory
			else if(string(opt[i]) == "--d") {
				String folder = opt[i+1];
				vector<cv::String> imagesNames;
				vector<cv::String> extension = {"jpeg", "jpg", "png"};
				for(int i=0; i<extension.size(); i++) {
					glob("./" + folder + "/*." + extension[i], imagesNames, false);
					if(imagesNames.size()>0) {
						break;
					}
				}
				for(int i=0; i<imagesNames.size(); i++) {
					cout << imagesNames[i] << endl;
					int failure = loadImage(imagesNames[i], sep);
					if(failure) {
						return -1;
					}
				}
				return 0; // Supposedly, there is no arguments left after this flag
			}
			// Remaining arguments should be image only
			else {
				int failure = loadImage(opt[i], sep);
				if(failure) {
					return -1;
				}
			}
			
		}
	}
	return 0;
}

int stitching(vector<string> opt) {
	// Check if arguments parsing went well
	int failure = parseCmdArgs(vector<string> opt);
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
		namedWindow("Result", WINDOW_AUTOSIZE);
		imshow("Result", result);
		imwrite(result_name, result);
		cout << "Stitching completed successfully" << endl;
		cout << result_name << "saved." << endl;
		waitKey();
		return 0;
	} 
}
