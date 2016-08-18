#include <opencv2/opencv.hpp>
#include "face_detection.cpp"
using namespace cv;

int main(int argc, char** argv)
{	
	//opencv video datatype
	VideoCapture cap;
	//opencv image datatype
	Mat frame;
	//dlib face detection object
	frontal_face_detector detector = get_frontal_face_detector();
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
		
		Mat temp(frame);
		
		
		//check if video is finished
		if(!frame.data)
			break;
		
		//get face marked image
		std::vector<dlib::rectangle> faces = detect_face_rectangles(frame,detector);
		
		for(int i = 0; i< faces.size(); i++)
			cv::rectangle(frame, Point(faces[i].left(),faces[i].top()), Point(faces[i].right(),faces[i].bottom()), Scalar(255,0,0));
		//display frame on video
		imshow("edges", frame);
		
		std::vector<correlation_tracker> trackers(faces.size());
		
		cv_image<bgr_pixel> ctemp(temp);
		for(int i = 0; i < faces.size(); i++)
		{
			trackers[i].start_track(ctemp, faces[i]);
		}

		for(int j = 0; j < 30; j++)
		{
			cap >> frame;
			
			cv_image<bgr_pixel> cimg(frame);
			
			for(int i = 0; i < trackers.size(); i++)
			{
				trackers[i].update(cimg);
				drectangle face = trackers[i].get_position();
				cv::rectangle(frame, Point((int)face.left(),(int)face.top()), Point((int)face.right(),(int)face.bottom()), Scalar(255,0,0));
			}
			imshow("edges", frame);
			waitKey(30);			
		}
		
		//wait for key press on the opencv window
		if(waitKey(30) >= 0)
			break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
