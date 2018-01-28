#include "Camera.hpp"

Camera::Camera(bool automode){

    arv_g_type_init();
    // captures NULL env camera. if fake-enabled captures Aravis-GV01 (running at 127.0.0.1)
    camera = arv_camera_new(NULL);
    if(camera != NULL){
        std::cout << "Initialized ArvCamera@"<<camera << std::endl;
        std::cout << "AUTO Prop Mode : " << automode << std::endl;
        if(!automode){
            disable_auto();
        }
        return;
    }
    camera = NULL;
    return;
}

Camera::~Camera(){}

Camera::Camera(std::string camera_id, bool automode){
    /*
        params : camera_id : type string
        camera_id : e.g. Aravis-GV01, TIS-11714131 (for The Imaging Source <Serial No> Cameras)

        params : automode : type bool
        automode: bool flag to enable or disable auto mode. (automode = true) for enabling auto mode. 
    */
    
    arv_g_type_init();
    camera = arv_camera_new(camera_id.c_str());
    if(camera != NULL){
        std::cout << "Initialized ArvCamera@"<<camera << std::endl;
        std::cout << "AUTO Prop Mode : " << automode << std::endl;
        if(!automode){
            disable_auto();
        }
        return;
    }
    camera = NULL;
    return;
}

void Camera::disable_auto(){
    printf("Disable Auto Property\n");
    arv_camera_set_exposure_time_auto(camera, ARV_AUTO_OFF);
    arv_camera_set_gain_auto(camera, ARV_AUTO_OFF);

    // write support for other properties
}

void Camera::setProperties(std::string property_name, double property_value){
    if(property_name == "GAIN"){
        arv_camera_set_gain(camera, property_value);
    }else if(property_name == "EXP_TIME"){
        arv_camera_set_exposure_time(camera, property_value);
    }else if(property_name == "FPS"){
        arv_camera_set_frame_rate(camera, property_value);
    }
    return ;
}

void Camera::start_video(int buffer_queue_size){
    
    std::cout << "ARV Camera Check " << camera << std::endl;
    stream = arv_camera_create_stream(camera, NULL, NULL);
    std::cout << "ARVSTREAM stream created at "<< stream << std::endl;
    std::cout << "Buffer Queue Size set at " << buffer_queue_size << std::endl;
    if( stream == NULL){
        printf("STREAM CREATION ERROR.\n");
        return;
    }
    gint payload =   arv_camera_get_payload(camera);
    for(int i=0; i < buffer_queue_size; i++){
        arv_stream_push_buffer(stream, arv_buffer_new(payload, NULL));
    }
    arv_camera_start_acquisition(camera);

    usleep(1);

    return ;
}

ArvBuffer* Camera::readFrame(){
    ArvBuffer *_buffer;
    _buffer = arv_stream_pop_buffer(stream);
    return _buffer;
}

IplImage* Camera::readFrameIPL(){
    ArvBuffer* _buffer;
    IplImage* src;
    size_t buffer_size;

    // get buffer data
    _buffer = arv_stream_pop_buffer(stream);
    if (_buffer != NULL){
        // copy buffer data
        framebuffer = (void*)arv_buffer_get_data(_buffer, &buffer_size);
        
        arv_stream_push_buffer(stream, _buffer);
        // create IplImage
        src = cvCreateImage( cvSize(1280, 960), IPL_DEPTH_8U, 1);
        cvInitImageHeader(src, cvSize(1280, 960), IPL_DEPTH_8U, 1, IPL_ORIGIN_TL, 4);
        cvSetData(src, framebuffer, src->widthStep);

        return src;
    }
    return NULL;
}

// ArvBuffer* Camera::acquire(){
//     ArvBuffer* _buffer;
//     _buffer = arv_stream_pop_buffer(stream);
//     if(arv_buffer_get_status(buffer) == ARV_BUFFER_STATUS_SUCCESS){
//         return _buffer;
//     }
//     return _buffer;
// }

cv::Mat Camera::readFrameMat(){
    IplImage* frame;
    IplImage* src;
    src = readFrameIPL();
    if(src == NULL){
        return cv::Mat();
    }
    frame = cvCreateImage(cvGetSize( src), src->depth, 1);
    return cv::cvarrToMat(src, frame);
}



void Camera::disconnect(){
    arv_camera_stop_acquisition(camera);

}