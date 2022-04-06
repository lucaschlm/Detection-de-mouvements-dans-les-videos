#include <opencv2/opencv.hpp>
#include "functions.h"
using namespace cv;
int main()
{

	VideoCapture video("video/111.mp4");

	if (!video.isOpened()) 
    {
		std::cerr << "Error opening video stream or file" << std::endl;
		exit(EXIT_FAILURE);
	}        
    
    //On crée notre backgroundSubstractor
    Ptr<BackgroundSubtractorMOG2> pBackSub = createBackgroundSubtractorMOG2();
    pBackSub->setVarThreshold(100);
    pBackSub->setDetectShadows(true);
    pBackSub->setNMixtures(3);
    pBackSub->setShadowValue(0);
    pBackSub->setBackgroundRatio(.5);

    Mat firstFrame;
    // On recupere la premiere frame qui correspond à l'image de fond
    video >> firstFrame;

    while (true) 
    {
        Mat frame;
        // On recupere une frame
        video >> frame;

        // On vérifie qu'on est pas a la fin de la video
        if (frame.empty())
            break;

        // On affiche la frame
        imshow("Frame", frame);

        ///////////////////////////////////////////////////////
        //                 SEUILLAGE SIMPLE                 //
        /////////////////////////////////////////////////////
        // On calcul l'image seuillé
        Mat tresholdFrame = imgTreshold(frame, firstFrame, 40);
        //On affiche la frame seuillé
        imshow("Tresholded frame (Simple)", tresholdFrame);

        ///////////////////////////////////////////////////////
        //                 MODELE GAUSSIEN                  //
        /////////////////////////////////////////////////////
        // On applique le masque
        Mat fgMask;
        pBackSub->apply(frame, fgMask);
        //On affiche la frame seuillé 
        imshow("Tresholded frame (MOG2)", fgMask);


        char c = (char)waitKey(25);
        // On ferme la video lors de l'appuie sur la touche ESC
        if (c == 27)
            break;
    }

    // On ferme la video
    video.release();

    destroyAllWindows();

	return 0;
}


//TODO : QUESTION 2.3 : Recuperer pour chaque pixel dans un fichier csv et analyser avec graphique Excel