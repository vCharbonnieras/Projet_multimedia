#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

/// Global variables

Mat source, source_gray;
Mat new_image, detected_edges;

int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int size_kernel = 3;
String window_name = "Canny Edges";


void CannyThreshold(int, void*)
{
  // Reduction of the noise with a kernel 3x3
  blur( source_gray, detected_edges, Size(size_kernel,size_kernel) );

  // Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, size_kernel );

 
  new_image = Scalar::all(0);

  source.copyTo( new_image, detected_edges);
  imshow( window_name, new_image );
 }


// main function
/*
int main( int argc, char** argv )
{
  // Load our image passed on argument
  source = imread( argv[1], CV_LOAD_IMAGE_COLOR);
  
  // case if no image is given
  if( !source.data )
  { 
  cout << "No Source provided" << endl;
  
  return 0; 
  }

  cvtColor( source, source_gray, CV_BGR2GRAY );

  // Create a window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  // Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

  // Show the image
  CannyThreshold(0, 0);
  
  string name = string(argv[1]);
  int k = 0;
  while (1) {
  
  k= waitKey(0) & 0xFF;
  //if key pressed is 'S' or 's', save the image and quit
 if(k = 115)
{
    imwrite("./canned"+name, new_image);
}
 if(k = 83)
{
    imwrite("./canned"+name, new_image);
}
 if(k = 27) {  //if esc key is pressed, quit
 return 0;
 }
} 


  }

  */