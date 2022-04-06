#include "functions.h"
#include <iostream>
#include <cmath>

Mat imgTreshold(Mat img, Mat baseImg, int T)
{
	cvtColor(img, img, COLOR_BGR2GRAY);
	cvtColor(baseImg, baseImg, COLOR_BGR2GRAY);

	if ((img.rows != baseImg.rows) || (img.cols != baseImg.cols))
	{
		std::cerr << "La taille des deux images ne correpond pas\n";
		exit(EXIT_FAILURE);
	}

	Mat output(img.rows, img.cols, CV_8UC1);

	for (size_t i = 0; i < img.rows; i++)
		for (size_t j = 0; j < img.cols; j++)
			output.at<unsigned char>(i, j) = std::abs(baseImg.at<unsigned char>(i, j) - img.at<unsigned char>(i, j)) > T ? 255 : 0;
	return output;
}
