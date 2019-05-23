#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int erosion_elem = 0;
int erosion_size = 0;
int dilatation_elem = 0;
int dilatation_size = 0;
int const max_elem = 2;
int max_kernel_size=0;
char ero,dil,E,D;


Mat image,image_1,image_2;

void Erosion( int, void* );
void Dilatation( int, void* );


int dilatation_erosion(Mat img)
{
    image=img;
    // Enter max_kernel_size
	cout << "Enter max_kernel_size" << endl;
	cin >> max_kernel_size;
    // Choose between Erode Dilate or both
	cout << "If you want to erode type E else Esc ";cin >>ero;
	cout << "If you want to dilate type D else Esc ";cin>>dil;
/*
    // Read the image file

	image = imread("mark.jpg");

    // Check for failure
	if(!image.data){
	printf( " No image data \n " );
	return -1;
}
*/
    //Define names of the windows and show
	namedWindow("image original");
        imshow("image original",image);

if (ero=='E'){
    // Read the image file

	/*image = imread("mark.jpg");

    // Check for failure
	if(!image.data){
	printf( " No image data \n " );
	return -1;
}
	 */
	namedWindow("image erosion");

    // Create Erosion Trackbar
 	createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "image erosion",
                  &erosion_elem, max_elem,
                  Erosion );

	createTrackbar( "Kernel size:\n 2n +1", "image erosion",
                  &erosion_size, max_kernel_size,
                  Erosion );
    // Default start
	Erosion( 0, 0 );
}


if (dil=='D'){
// Read the image file
/*
	image = imread("mark.jpg");

    // Check for failure
	if(!image.data){
	printf( " No image data \n " );
	return -1;
}
*/

	namedWindow("image dilatation");

    // Create Dilatation Trackbar
 	createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "image dilatation",
                  &dilatation_elem, max_elem,
                  Dilatation );

	createTrackbar( "Kernel size:\n 2n +1", "image dilatation",
                  &dilatation_size, max_kernel_size,
                  Dilatation );

    // Default start
	Dilatation( 0, 0 );
}

   // Wait for any keystroke in the window
waitKey(0);
    //destroy all opened windows
    return 0;
}

/**  @function Erosion  */
void Erosion( int, void* )
{
int erosion_type;
  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }
    //Erosion of the image
	Mat element2 = getStructuringElement( erosion_type,Size( 2*erosion_size + 1, 2*erosion_size+1 ),Point( erosion_size, erosion_size ) );
	erode(image,image_1,element2);
	imshow("image erosion",image_1);
}

/**  @function Dilataion  */
void Dilatation( int, void* )
{
int dilatation_type;
  if( dilatation_elem == 0 ){ dilatation_type = MORPH_RECT; }
  else if( dilatation_elem == 1 ){ dilatation_type = MORPH_CROSS; }
  else if( dilatation_elem == 2) { dilatation_type = MORPH_ELLIPSE; }
    //Dilatation of the image
        Mat element1 = getStructuringElement( dilatation_type,Size( 2*dilatation_size + 1, 2*dilatation_size+1 ),Point( dilatation_size, dilatation_size ) );
	dilate(image,image_2,element1);
	imshow("image dilatation",image_2);
}

