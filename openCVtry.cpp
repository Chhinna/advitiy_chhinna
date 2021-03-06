#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<fstream>


using namespace std;

using namespace cv;

int main()

{

	int row; // no. of row

	int col; // no. of column

	int hex_1; // 1st digit of hex

	int hex_2; // 2nd digit of hex

	int hex_3; // 3rd digit of hex

	vector<vector<double>> y(256); // vector to store y value of each pixel

	vector<vector<double>> ry(256);// vector to store ry value of each pixel

	vector < vector < double >> by(256);// vector to store by value of each pixel

	

	cv::Mat img = imread("image18.jpg"); // this is your image name which should be in same folder in which your cpp file is

	cv::namedWindow("image", WINDOW_NORMAL);

	cv::imshow("image", img);

	ofstream file_;

	file_.open("freq18_char.txt"); // this is your text file

	for (int col = 0; col < 256; col++) {

		y[col] = vector<double>(320);

		ry[col] = vector<double>(320);

		by[col] = vector<double>(320);

		for (int row = 0; row < 320; row++) {

			Vec3b intensity = img.at<Vec3b>(col, row);

			Scalar bluecol = intensity.val[0];

			Scalar greencol = intensity.val[1];

			Scalar redcol = intensity.val[2];

			y[col][row] = (16.0 + (.003906 * ((65.738 * redcol[0]) + (129.057 * greencol[0]) + (25.064 * bluecol[0])))) ;

			ry[col][row] = (128.0 + (.003906 * ((112.439 * redcol[0]) + (-94.154 * greencol[0]) + (-18.285 * bluecol[0])))) ;

			by[col][row] = (128.0 + (.003906 * ((-37.945 * redcol[0]) + (-74.494 * greencol[0]) + (112.439 * bluecol[0])))) ;

			

		}

	}
	
	for (int col = 0; col < 256; col++) {
		
		for (int row = 0; row < 320; row++) {
			int hex_1 = (y[col][row]);

			if (y[col][row] - hex_1 > 0.5) {
				hex_1 = hex_1 + 1;
			}
			
			file_ << char(hex_1);
			
		
		}
		for (int row = 0; row < 320; row++) {
			int hex_1 = ((ry[col][row] + ry[col + 1][row])/2);
			if (((ry[col][row] + ry[col + 1][row]) / 2) - hex_1 > 0.5) {
				hex_1 = hex_1 + 1;
			}
			file_ << char(hex_1);

			

		}
		for (int row = 0; row < 320; row++) {
			int hex_1 = ((by[col][row] + by[col + 1][row])/2);

			if (((by[col][row] + by[col + 1][row]) / 2) - hex_1 > 0.5) {
				hex_1 = hex_1 + 1;
			}

			file_ << char(hex_1);

		}
		for (int row = 0; row < 320; row++) {
			int hex_1 = (y[col + 1][row]);

			if ((y[col + 1][row]) - hex_1 > 0.5) {
				hex_1 = hex_1 + 1;
			}

			file_ << char(hex_1);

		}
		col = col + 1;

	}
	file_.close();

	waitKey(0);

	return (0);


}

