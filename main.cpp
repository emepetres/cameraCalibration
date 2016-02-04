/*****************************************************************************
Copyright (c) 2016 Javi Carnero

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*****************************************************************************/

#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;

int main(int argc, char *argv[]) {
  std::cout << "Calibrando..." << std::endl;

  vector<vector<Point3f>> object_points;
  vector<vector<Point2f>> image_points;

  int square_size = 108;
  Size board_size(23, 17); //esquinas interiores
  vector<Point3f> chessboard_corners;
  for( int i = 0; i < board_size.height; ++i )
      for( int j = 0; j < board_size.width; ++j )
        chessboard_corners.push_back(Point3f(float( j*square_size ), float( i*square_size ), 0));



  //////////SE REPITE PARA CADA IMAGEN QUE QUERAMOS USAR PARA CALIBRAR////////////////////
  Mat distorted_board = imread("patron.bmp");
  vector<Point2f> corners;

  bool found = findChessboardCorners(distorted_board, board_size, corners,
                                     //CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE
                                     CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
                                     );

  Mat distorted_board_gray;
  cvtColor(distorted_board, distorted_board_gray, CV_BGR2GRAY);

  if(found) {
    cornerSubPix(distorted_board_gray, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
    drawChessboardCorners(distorted_board_gray, board_size, corners, found);

    image_points.push_back(corners);
    object_points.push_back(chessboard_corners);

    std::cout << "..¡tablero encontrado!..." << std::endl;
  } else {
    std::cout << "..tablero no encontrado :-(" << std::endl;
    return 0;
  }
  ////////////////////////////////////////////////////////////////////////////////////////

  Mat intrinsic = Mat(3, 3, CV_32FC1);
  Mat distCoeffs;
  vector<Mat> rvecs;
  vector<Mat> tvecs;

  intrinsic.ptr<float>(0)[0] = 1;
  intrinsic.ptr<float>(1)[1] = 1;

  calibrateCamera(object_points, image_points, distorted_board.size(), intrinsic, distCoeffs, rvecs, tvecs);

  FileStorage fs("len_config.xml", FileStorage::WRITE);
  fs << "intrinsic" << intrinsic;
  fs << "distCoeffs" << distCoeffs;
  fs.release();

//  Mat intrinsic;
//  Mat distCoeffs;
//  FileStorage fs;
//  fs.open("len_config.xml", FileStorage::READ);

  fs["intrinsic"] >> intrinsic;
  fs["distCoeffs"] >> distCoeffs;

  fs.release();

  Mat distorted_image = imread("background.bmp");
  Mat imageUndistorted;
  undistort(distorted_image, imageUndistorted, intrinsic, distCoeffs);

  imwrite("result.bmp", imageUndistorted);
  std::cout << "..imagen no distorsionada!" << std::endl;

	return 0;
}
