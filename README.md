Camera Calibration
=====

Brief description
-----------
Sometimes when we have to deal with the distortion of images we are not able to take a set of photographs with a pattern in them (for example a chess pattern), using the same camera and lens, in order to get the distortion coefficients and intrinsic data of it. 

In this scenario this tool helps you get this information. See below to know how it works.

Install
-----------
* OpenCV and Qt5 need to be installed first

```
$ qmake
$ make install
```

How to use it
-----------
* Move to portable folder.
* Select/take a representative image and save it as resources/test.bmp. Open it with *GIMP* or *Photoshop* or another good image manipulation program you like.
* Undistort the image using the distortion filters among others, writing down everything you do. Do not save the changes.
* Do the same inverted on the image resources/undistorted_pattern.bmp, saving it as resources/pattern.bmp
* Execute the tool:
```
$ ./cameraCalibration
```
* Two files will be generated: *len_config.xml*, the file with all the information you need to undistort further images from the same camera. *result.bmp*, the result of undistorting "test.bmp".


Tip
-----------
* *sample.project* and *sample.cproject* can be used removing the "sample" part to import easily the project into eclipse.

