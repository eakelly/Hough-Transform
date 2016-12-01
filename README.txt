*******************************
* Elizabeth Kelly		*	
* Computational Vision HW 3	*			
* CSCI 493			*	
* Professor Stamos		*
* October 14, 2016		*
*******************************

*******************************************************************************
This program is a vision system that detects lines in an image using the 
Hough Transform.	 

i. All parts of the assignment were completed.
ii. No bugs were encountered.
iii. & iv. Complete instructions of how to run this program and the 
needed input and output files are listed below.

Before running this program, please issue the following in the command 
line:

1) make clean
2) make all

*******************************************************************************
This program is separated into four parts:
*******************************************************************************
Program 1: Locates edges in a gray-level image (using a Gaussian blur to 
smooth the image and Sobel mask) and generates an image that displays the 
edge points where the intensity of each point is proportional to the edge 
magnitude.

To run this program, enter the following on the command line:

./h1 <input gray-level image> <output gray-level edge image>

** The threshold values that work best for the each input file:
hough_simple_1.pgm 35
hough_simple_2.pgm 25
hough_complex.pgm 40

The filename for the output edge image is edge_image.pgm

*******************************************************************************
Program 2: Takes an edge image as input and thresholds the image to 
produce a binary image with only strong edges.

To run this program, enter the following on the command line:

./h2 <input gray-level edge image> <input gray-level threshold> <output binary image>

The filename for the input edge image is edge_image.pgm
The filename for the output binary image is binary_image.pgm

*******************************************************************************
Program 3: Performs a Hough Transform to detect lines in the binary image 
and produces a gray-level image to visualize the sinusoids produced by 
the detected edge points. 

To run this program, enter the following on the command line:

./h3 <input binary edge image> <output gray-level Hough image> <output Hough voting array>

The filename for the input binary edge image is binary_image.pgm
The filename for the output Hough image is hough_output.pgm
The filename for the output voting array is votes.txt

*******************************************************************************
Program 4: Takes the original input image from h1, the Hough voting 
array, and threshold as input and detects lines in the original image 
from its Hough Transform space using a given threshold. The lines are 
then drawn onto a copy of the original input image from h1.

To run this program, enter the following on the command line:

./h4 <input original gray-level image> <input Hough voting array> <input Hough threshold> <output gray-level line image>

The filename for the input original gray-level image is: hough_simple_1.pgm or hough_simple_2.pgm or hough_complex.pgm
The filename for the input Hough voting array is votes.txt
The filename for the output gray-level line image is line_image.pgm

** The threshold values that work best for the each input file:
hough_simple_1.pgm 340
hough_simple_2.pgm 345
hough_complex.pgm 228


*******************************************************************************
File list:
*******************************************************************************
Makefile	Makefile with ‘make clean’ and ‘make all’ commands
h1.cpp		Locates edges in a gray-level image.
h2.cpp		Thresholds an image to produce a binary image with strong edges.
h3.cpp		Performs a Hough Transform to detect lines.
h4.cpp		Detects lines and draws them on the original input image.
Image.h		Header for a class representing a 2D gray-scale image.
Image.cpp 	Implementation of representing 2D gray-scale image.
*******************************************************************************