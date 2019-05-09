#include <opencv2/opencv.hpp>
#include <iostream>
//https://remotedesktop.google.com/
using namespace cv;
using namespace std;


Mat lightImgBrightness(Mat img, int valBrightness){
    Mat newImg =  img.clone();

    for (int x = 0; x < img.rows; x++){
        for(int y = 0; y < img.cols; y++){
            for( int c = 0; c < img.channels(); c++ ) {
                newImg.at<Vec3b>(x,y)[c] =
                  saturate_cast<uchar>( img.at<Vec3b>(x,y)[c] + valBrightness );
            }
        }
    }

    return newImg;
}

Mat lightImgContrast(Mat img, int valContrast){
    if (valContrast <= 0){
        return img;
    }
    Mat newImg =  img.clone();

    for (int x = 0; x < img.rows; x++){
        for(int y = 0; y < img.cols; y++){
            for( int c = 0; c < img.channels(); c++ ) {
                newImg.at<Vec3b>(x,y)[c] =
                  saturate_cast<uchar>( valContrast*img.at<Vec3b>(x,y)[c]);
            }
        }
    }

    return newImg;
}

Mat lightImg(Mat img, int valContrast, int valBrightness){
    return lightImgBrightness(lightImgContrast(img,valContrast),valBrightness);
}

int main(int argc, char** argv)
{
    // Read the image file
  Mat image_eco, image_eco_1, image_eco_2, image_eco_3, image_eco_4, image_eco_5, image_eco_6, image_eco_7;
  image_eco = imread("eco.jpg");

    // Check for failure
  if(!image_eco.data){
   printf( " No image data \n " );
   return -1;
  }

    //test
    image_eco.convertTo(image_eco_1,image_eco.type(),0.5, 100);
    image_eco_2 = lightImg(image_eco, 0.5,100);

    //Defining window names for above images
    String window1 = "default";
    String window2 = "using convertTo";
    String window3 = "using lightImg";
     namedWindow(window1);
     namedWindow(window2);
     namedWindow(window3);

    
    //Create and open windows for above images

    //Show above images inside the created windows.
     imshow(window1,image_eco);
     imshow(window2,image_eco_1);
     imshow(window3,image_eco_2);

     // Wait for any key stroke
     waitKey(0);

     //destroy all open windows
    destroyAllWindows();
    return 0;
}