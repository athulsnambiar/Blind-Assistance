#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace dlib;
using namespace std;
using namespace cv;

Mat detect_face(Mat image, frontal_face_detector detector)
{  
	Mat face(image);
	
	try
	{
		cv_image<bgr_pixel> cimg(image);

		//pyramid_up(cimg);

		
		
		std::vector<dlib::rectangle> dets = detector(cimg);
				
		for(int i = 0; i < dets.size(); i++)
		{
			cv::rectangle(face, Point(dets[i].left(),dets[i].top()), Point(dets[i].right(),dets[i].bottom()), Scalar(255,0,0));
		}

	}
	catch (exception& e)
	{
		cout << "\nexception thrown!" << endl;
		cout << e.what() << endl;
	}
	
	return face;
}

