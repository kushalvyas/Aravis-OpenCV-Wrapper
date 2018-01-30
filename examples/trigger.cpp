#include "Camera.hpp"

int main(int argc, char *argv[]){

    Camera cam("TIS-11714131", false);
    cam.setProperties("GAIN", 0.0);
    cam.setProperties("EXP_TIME", 50000.0);
    cam.setProperties("FPS", 30);
    cam.setTrigger(true);
    cam.start_video();
    IplImage* image;
    cvNamedWindow("Image");
    while(true){
        image = cam.readFrameIPL();
        if(image != NULL){
        	// cv::Mat tmp = cv::cvarrToMat(image);
        	// cv::imshow("frame", tmp);
	        printf("Image Acquired\n");
        }
        cvShowImage("Image", image);
        int keypress = cvWaitKey(1) & 0xFF;
        // cv::Mat m;
        // m = cam.readFrameMat();
        // cv::imshow("frame", m);
        // int keypress = cv::waitKey(1) & 0xFF;
        if(keypress == 27){
            break;
        }else if (keypress == 115){
            
        }
    }

    cvDestroyAllWindows();
    // cv::destroyAllWindows();
    cam.disconnect();

    return 0;
}

