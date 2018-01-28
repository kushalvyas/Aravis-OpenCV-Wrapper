#include "unistd.h"
#include "arv.h"
#include "opencv2/opencv.hpp"


class Camera{

public:
	Camera(bool automode=false);
	Camera(std::string camera_id, bool automode=false);
	~Camera();
	
	void setProperties(std::string property_name, double property_value);
	
	IplImage* readFrameIPL();
	cv::Mat readFrameMat();
	void disconnect();
	void start_video(int buffer_queue_size=50);
	
private:
	
	ArvCamera *camera = NULL;
	ArvStream *stream = NULL;
	ArvBuffer *buffer = NULL;
	void* framebuffer;

	//ArvBuffer *acquire();
	ArvBuffer* readFrame();
	void disable_auto();



	
};