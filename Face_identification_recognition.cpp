
// Created by Louisdecaslou on 5/09/19.

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;

/** Declaration des fonctions */
void indentificationandrecognition( Mat frame, Mat frame_gray);

/** Initialisation des variables globales */
String face_cascade_name = "../haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "../haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";

/** Fonction main */
int main( int argc, const char** argv )
{
    VideoCapture capture;
    Mat frame;

    /**Chargement des cascade qui serve de reference pour detecter les visages et les yeux */
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return -1;

    /** Chargement image et vérification de celle-ci */
    String imageName(« Louis/image.jpg");
    if (argc > 1) {
        imageName = argv[1];
    }
    Mat colorImage;
    colorImage = imread(imageName, IMREAD_COLOR);
    if (colorImage.empty()) {
        cout << "Image non trouvée" << std::endl;
        return -1;
    }

    /** Preparation de l'image au traitement. Mise en niveau de gris pour un traitement plus rapide */
    Mat grayImage;
    cvtColor(colorImage, grayImage, CV_BGR2GRAY);
    equalizeHist(grayImage, grayImage);

    /** Appel de la fonction de détection de visage et des yeux */
    identificationandrecognition(colorImage, grayImage);

    return 0;
}

/** Fonction de detection et d’identification */

void identificationandrecognition(Mat frame, Mat frame_gray)
{
    /**Creation du vecteur "face" qui va stocker les coordonnées du visage */
    std::vector<Rect> faces;

    /** Lancement de la detection */
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(60, 60) );

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        /** Detection visage et dessin d'une ellipse autour de ce dernier */
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        /** Pour chaque visage, on detecte les yeux */
       ( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            /** Detection des yeux, et dessin d'une ellipse autour de ces dernier */
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }

    /** Visualisation de l'image avec les ellipses autour des visages et des yeux */
    namedWindow( window_name, WINDOW_AUTOSIZE );
    imshow( window_name, frame);
    waitKey(0);

}

