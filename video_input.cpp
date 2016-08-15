#include <opencv2/opencv.hpp>
#include "face_detection.cpp"
using namespace cv;

int main(int argc, char** argv)
{
	//opencv video datatype
	VideoCapture cap;
	//opencv image datatype
	Mat frame;
	//open video by name
	cap.open(argv[1]);
	//check if video is opened
	if(!cap.isOpened())
		return -1;
	//open window to play video
	namedWindow("edges",1);
	for(;;)
	{

		// get a frame from video
		cap >> frame;
		
		//check if video is finished
		if(!frame.data)
			break;
		
		//get face marked image
		frame = detect_face(frame);
		
		//display frame on video
		imshow("edges", frame);
		
		//wait for key press on the opencv window
		if(waitKey(30) >= 0)
			break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
