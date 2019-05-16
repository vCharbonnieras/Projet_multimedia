#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

// main function
int main( int argc, char** argv )
{
   // load our image
   Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
   
   // declaration of our modified image
   Mat new_image;
   // case if not enough or too much arguments given
   if (argc < 3 or argc > 4) {
   	cout << "Wrong number of arguments" << endl;
   	cout << "Check the manuel with 'man cv_resize' to verify" << endl;
   	return 0;
   	}
   
   // case resizing with a factor
   else if (argc == 3) {
   	float X = atof(argv[2]);
   	float xe = image.cols*X;
   	float ye = image.rows*X;
   	resize(image, new_image, Size(int(xe),int(ye)));
   }
   
   // case resizing with a scalar
   else if (argc == 4) {
   	int x = strtol(argv[2], nullptr, 0);
   	int y = strtol(argv[3], nullptr, 0);
   
   	resize(image, new_image, Size(x, y));
   }
  
    namedWindow( "image originale", WINDOW_AUTOSIZE);
    namedWindow( "image modifiée", WINDOW_AUTOSIZE);
    
    // show original and new image
 
    imshow( "image originale", image);
    imshow( "image modifiée", new_image);
    string name = string(argv[1]);
    int k = 0;
  while (1) {
  
  k= waitKey(0) & 0xFF;
  // if 'S' or 's' is pressed, save the image and quit
 if(k = 115)
{
    imwrite("./resized"+name, new_image);
}
 if(k = 83)
{
    imwrite("./resized"+name, new_image);
}
 if(k = 27) {  // if esc key is pressed, quit
 return 0;
 }
} 
}
