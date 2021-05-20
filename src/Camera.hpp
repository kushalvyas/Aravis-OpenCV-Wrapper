#include "unistd.h"
#include "arv.h"
#include "opencv2/opencv.hpp"


class Camera{

public:
	Camera(bool automode=false);
	Camera(std::string camera_id, bool automode=false);
	~Camera();
	
	void setProperties(std::string property_name, double property_value);
	
//	IplImage* readFrameIPL();
	cv::Mat readFrameMat();
	void disconnect();
	void start_video(int buffer_queue_size=50);
	void setTrigger(bool val);
	
private:
	
	ArvCamera *camera = NULL;
	ArvStream *stream = NULL;
	ArvBuffer *buffer = NULL;
	ArvBuffer *_buffer = NULL;
	GError *error = NULL;
	void* framebuffer = NULL;
	bool issetTrigger = false;

	//ArvBuffer *acquire();
	ArvBuffer* readFrame();
	void disable_auto();



	
};
