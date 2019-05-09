#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;
void callbackButton(int state, void *pointer){

	printf("ok");

}

int main(int argc, char* argv[]){

	Mat img,e;
	img = imread("mark.jpg");

 	// Check for failure
  	if(!img.data){
   		printf( " No image data \n " );
   		return -1;
  	}

  	String window1 = "Image";
  	String window2 = "Edit";
  	namedWindow(window1);
  	namedWindow(window2);

  	//MANIP//
  	createTrackbar("Brightness", window2,0, 200);
  	createTrackbar("TEST", window2,0, 200);
  	createTrackbar("azd", window2,0, 200);
	// Wait for any key stroke
  	
	while (true){
		b = cv2.getTrackbarPos('B','image')
		imshow(window1,img);
		//wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
        if (waitKey(10) == 27){
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break;
        }
    }
    //destroy all open windows
    destroyAllWindows();
    return 0;
}