# Aravis-OpenCV-Wrapper
Wrapper for accessing GigE cameras using Aravis, yielding OpenCV Mat and IplImage

Requirements (tested on OpenCV 3.4, Aravis 0.6):
1. OpenCV (3.X)
2. Aravis (Preferably >= 0.4) 
3. Glib 2.0

Implementation phase ongoing. As of now, at `Mono8` - `IPL_DEPTH_8U` phase.

## TODO:
- [x] Basic IplImage from ArvBuffer
- [x] cv::Mat from ArvBuffer
- [x] Capture Video
- [x] Set GigE Camera Properties (will keep adding to list)
    - [x] FPS, Gain, Exposure Time
    - [ ] Contrast, Brightness, etc.
- [ ] Image ROI 
- [ ] Binning
- [ ] Add Numpy::NDArray support
- [ ] Link with Boost.Python and Boost.Numpy
- [ ] Examples