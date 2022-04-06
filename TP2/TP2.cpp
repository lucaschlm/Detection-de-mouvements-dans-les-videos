#include <opencv2/opencv.hpp>
#include "functions.h"
using namespace cv;
int main()
{
	VideoCapture video("video/111.mp4");

	if (!video.isOpened()) {
		std::cerr << "Error opening video stream or file" << std::endl;
		exit(EXIT_FAILURE);
	}        
    
    Mat firstFrame;
    // On recupere la premiere frame qui correspond à l'image de fond
    video >> firstFrame;

    while (true) {

        Mat frame;
        // On recupere une frame
        video >> frame;

        // On vérifie qu'on est pas a la fin de la video
        if (frame.empty())
            break;

        // On calcul l'image seuillé
        Mat tresholdFrame = imgTreshold(frame, firstFrame, 40);

        // On affiche la frame
        imshow("Frame", frame);

        //On affiche la frame seuillé
        imshow("Tresholded frame", tresholdFrame);

        // On ferme la video lors de l'appuie sur la touche ESC
        char c = (char)waitKey(25);
        if (c == 27)
            break;
    }

    // On ferme la video
    video.release();

    destroyAllWindows();

	return 0;
}