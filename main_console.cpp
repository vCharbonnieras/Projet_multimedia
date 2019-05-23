#include <iostream>
#include <sstream>
#include "string"
#include <vector>
#include <opencv2/opencv.hpp>
#include "Lighten_darken.cpp"
#include "cv_canny_edge.cpp"
//#include "cv_stitching/cv_stitching.cpp"
#include "Dilatation_erosion.cpp"
#include "Face_identification_recognition.cpp"

using namespace std;
using namespace cv;


Mat img = imread("mark.jpg");
Mat e = img;

String window1 = "Image";

/**Load an image*/
int loadImage(string path) {
    img = imread(path);
    // Check for failure
    if (!img.data) {
        printf(" No image data \n");
        return 1;
    }
    e = img;
    cout << path << " successfully loaded\n";

    return 0;
}

/**Split line by Character*/
vector<string> splitByChar(string &str, char delim) {
    string buf;                 // Have a buffer string
    stringstream ss(str);       // Insert the string into a stream

    vector<string> tokens; // Create vector to hold our words

    while (getline(ss, buf, delim)) {
        tokens.push_back(buf);
    }
    return tokens;


}

/**Resize function*/
int resize(vector<string> opt) {
    int Xf;
    int xy[2] = {};
    if (opt.size() == 1) {
        Xf = stod(opt[0]);
        resize(img, e, Size(int(img.cols * Xf), int(img.cols * Xf)));
        return 0;
    } else if (opt.size() == 2) {
        int i = 0;
        while (i < 2) {
            xy[i] = stod(opt[i]);
            i += 1;
        }
        resize(img, e, Size(xy[0], xy[1]));
    } else {
        return 1;
    }
}


int darken(vector<string> opt) {
    //lighten/darken
    float valContrast = stof(opt[1]);
    float valBrightness = stof(opt[2]);
    e = lightImg(e,valContrast,valBrightness);
    return 0;
}

int erosion(vector<string> opt) {
    return 0;
}

int stitching(vector<string> opt) {
	// Should make another image?
	//e = cv_stitching(opt);
}

int main() {
    /**Variables*/
    ofstream log;
    log.open("log.txt");
    vector<string> line;
    string input;
    string command;

    /**Starting loop*/
    cout << "Enter command line\n";
    while (true) {
        /**print the edit image*/
        imshow(window1, e);
        waitKey();
        cout << ">>";
        /**get inputed line*/
        getline(cin, input);
        /**split line*/
        if (!input.empty()) {
            line = splitByChar(input, ' ');
            //get the command
            command = line[0];

            /**Register to log*/
            log << command << endl;

            /**Switch according to command entered*/
            if (command == "resize") {
                line.erase(line.begin());
                resize(line);
            } else if (command == "load") {
                if (line.size() == 2) {
                    loadImage(line[1]);
                }
            } else if (command == "darken" or command == "lighten") {
                darken(line);
            } else if (command == "erosion" or command=="dilatation") {
                dilatation_erosion(img);
            } else if (command == "stiching") {
	    //		 stitching(line);
            } else if (command == "face") {
                face(e,"Image");
            } else if (command == "canny") {
                //to do
            } else if (command == "save") {
                /**save changes of edit to image*/
                img = e;
            } else if (command == "exit") {
                break;
            } else if (command == "help") {
                //print all command
                cout << "\t darken [contrast] [brightness] \t change the brightness and the contrast of the document" <<endl;
                cout << "\t dilatation \t\t\t\t not implemented" <<endl;
                cout << "\t erosion \t\t\t\t not implemented" <<endl;
                cout << "\t exit \t\t\t\t\t exit the program" <<endl;
                cout << "\t help \t\t\t\t\t print all commands" <<endl;
                cout << "\t lighten [contrast] [brightness] \t same as darken" <<endl;
                cout << "\t load [path] \t\t\t\t load a documment from the path" <<endl;
                cout << "\t resize [newXValue] [newYValue] \t resize the document to set the lenght to X and the height to Y" <<endl;
                cout << "\t save \t\t\t\t\t not implemented" <<endl;
                cout << "\t stiching \t\t\t\t Stitches images with similar border. To see usage type ? or \"help\" " <<endl;
            } else {
                /**unknown command message*/
                cout << "'" << input << "'" << "is an unknown command.help for information.\n";
            }
        }
    }
    log.close();
    destroyAllWindows();


    return 0;
}