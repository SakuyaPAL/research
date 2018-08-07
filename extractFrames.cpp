char buff[200];
	CvCapture* capture;
	capture = cvCaptureFromAVI("/media/新增磁碟區/research/video for training/1/1.avi");
	if(!capture){
		printf("\nCouldn't open the video\n");
	}
	return -1;
	for(int i = 0; i < 10000; i++){
		IplImage *img = cvQueryFrame(capture);
		sprintf(buff, "/media/新增磁碟區/research/video for training/1/%03d.jpg", i);
		cvSaveImage(buff, img);
		cvReleaseImage(&img);
	}
