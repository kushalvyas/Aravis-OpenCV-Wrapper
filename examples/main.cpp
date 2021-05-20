#include "Camera.hpp"

int main(int argc, char *argv[]){

    Camera cam("TIS-11714131", false);
    cam.setProperties("GAIN", 15.0);
    cam.setProperties("EXP_TIME", 50000.0);
    cam.setProperties("FPS", 30);
    cam.start_video();
    while(true){
//        IplImage* image;
//        image = cam.readFrameIPL();
        cv::Mat image = cam.readFrameMat();
//        cvShowImage("Image", image);
//        int keypress = cvWaitKey(1) & 0xFF;
        cv::imshow("Image", image);
        int keypress = cv::waitKey(1) & 0xFF;

        /***** TO USE WITH OPENCV C++ MAT CONTAINER ****/

        // cv::Mat m;
        // m = cam.readFrameMat();
        // cv::imshow("frame", m);
        // int keypress = cv::waitKey(1) & 0xFF;
        
        if(keypress == 27){
            break;
        }else if (keypress == 115){
            
        }
    }

//    cvDestroyAllWindows();
     cv::destroyAllWindows();
    cam.disconnect();

    return 0;
}

