#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

/// Global variables

Mat source, source_gray;
Mat dst, detected_edges;

int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int size_kernel = 3;
char* window_name = "Canny Edges";


void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( source_gray, detected_edges, Size(size_kernel,size_kernel) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, size_kernel );

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);

  source.copyTo( dst, detected_edges);
  imshow( window_name, dst );
 }


// main function
int main( int argc, char** argv )
{
  /// Load an image
  source = imread( argv[1], CV_LOAD_IMAGE_COLOR);

  if( !source.data )
  { 
  cout << "No Source provided" << endl;
  
  return 0; 
  }

  /// Create a matrix of the same type and size as source (for dst)
  //dst.create( source.size(), source.type() );

  /// Convert the image to grayscale
  cvtColor( source, source_gray, CV_BGR2GRAY );

  /// Create a window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

  /// Show the image
  CannyThreshold(0, 0);
  
  string name = string(argv[1]);
  cout << name << endl;
  int k = 0;
  while (1) {
  
  k= waitKey(0) & 0xFF;
  cout << k << endl;
  /// Wait until user exit program by pressing a key
 if(k = 115)
{
    imwrite("./canned"+name, dst);
}
 if(k = 83)
{
    imwrite("./canned"+name, dst);
}
 if(k = 27) {
 return 0;
 }
} 


  }