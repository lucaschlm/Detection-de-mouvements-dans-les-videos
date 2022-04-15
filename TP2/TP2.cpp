#include <opencv2/opencv.hpp>
#include "functions.h"
#include <chrono>
#include <iomanip>
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

    //On recupere le nombre d'images dans la video pour calculer la moyenne de temps d'execution
    auto frameNb = video.get(CAP_PROP_FRAME_COUNT);

    std::chrono::milliseconds simpleTime(0);
    std::chrono::milliseconds gaussianTime(0);

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
        auto start = std::chrono::high_resolution_clock::now();
        // On calcul l'image seuillé
        Mat tresholdFrame = imgTreshold(frame, firstFrame, 40);
        auto stop = std::chrono::high_resolution_clock::now();
        simpleTime += std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        //On affiche la frame seuillé
        imshow("Tresholded frame (Simple)", tresholdFrame);

        ///////////////////////////////////////////////////////
        //                 MODELE GAUSSIEN                  //
        /////////////////////////////////////////////////////
        // On applique le masque
        start = std::chrono::high_resolution_clock::now();
        Mat fgMask;
        pBackSub->apply(frame, fgMask);
        stop = std::chrono::high_resolution_clock::now();
        gaussianTime += std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        //On affiche la frame seuillé 
        imshow("Tresholded frame (MOG2)", fgMask);


        char c = (char)waitKey(25);
        // On ferme la video lors de l'appuie sur la touche ESC
        if (c == 27)
            break;
    }

    // On ferme la video
    video.release();
    cv::destroyAllWindows();

    std::cout << "Temps d'execution moyen pour le seuillage simple : \x1B[1;32m" << (simpleTime / frameNb).count() << "ms\x1B[0m.\n";
    std::cout << "Temps d'execution moyen pour le seuillage gaussien : \x1B[1;32m" << (gaussianTime / frameNb).count() << "ms\x1B[0m.\n";
    std::cout << "Le temps d'execution du seuillage simple est environ \x1B[1;32m";
    std::cout << std::setprecision(2) << (simpleTime / frameNb).count() / (gaussianTime / frameNb).count()
        << "x\x1B[0m superieur au temps d'execution du seuillage gaussien.\n";

	return 0;
}

