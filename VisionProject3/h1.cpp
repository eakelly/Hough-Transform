//
//  h1.cpp
//  VisionProj3
//
//  Created by Elizabeth Kelly on 10/1/16.
//  Copyright © 2016 Elizabeth Kelly. All rights reserved.
//
// Locates edges in a gray-level image and generates an "edge" image
// where the intensity at each point is proportional to edge magnitude

#include <stdio.h>
#include "Image.h"
#include <cstdio>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

bool locateEdges(string in_file, string out_file) {
    Image orig_img;
    
    if (!ReadImage(in_file, &orig_img)) {
        cout <<"Can't open file " << in_file << endl;
        return false;
    }
    
    Image blur_img;
    blur_img.AllocateSpaceAndSetSize(orig_img.num_rows(), orig_img.num_columns());
    blur_img.SetNumberGrayLevels(255);
    
    Image edge_img;
    edge_img.AllocateSpaceAndSetSize(orig_img.num_rows(), orig_img.num_columns());
    edge_img.SetNumberGrayLevels(255);
    
    int magnitude = 0;
    double squared_gradient = 0.0;
    //Sobel convolution kernels/masks
    int delta1[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}; //computes gradient in x-direction
    int delta2[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}}; //computes gradient in y-direction
    
    //Gaussian blur filter
    int gaussianFilter[5][5] = {{1, 4, 6, 4, 1},
                                {4, 16, 24, 16, 4},
                                {6, 24, 36, 24, 6},
                                {4, 16, 24, 16, 4},
                                {1, 4, 6, 4, 1}};
    
    //blur the image
    int blurred_pixel = 0;
    
    for (int i = 2; i < orig_img.num_rows()-2; i++) {
        for (int j = 2; j < orig_img.num_columns()-2; j++) {
            blurred_pixel = ((gaussianFilter[0][0]*orig_img.GetPixel(i-2, j-2)) +
                             (gaussianFilter[0][1]*orig_img.GetPixel(i-1, j-2)) +
                             (gaussianFilter[0][2]*orig_img.GetPixel(i, j-2)) +
                             (gaussianFilter[0][3]*orig_img.GetPixel(i+1, j-2)) +
                             (gaussianFilter[0][4]*orig_img.GetPixel(i+2, j-2)) +
                             
                             (gaussianFilter[1][0]*orig_img.GetPixel(i-2, j-1)) +
                             (gaussianFilter[1][1]*orig_img.GetPixel(i-1, j-1)) +
                             (gaussianFilter[1][2]*orig_img.GetPixel(i, j-1)) +
                             (gaussianFilter[1][3]*orig_img.GetPixel(i+1, j-1)) +
                             (gaussianFilter[1][4]*orig_img.GetPixel(i+2, j-1)) +
                             
                             (gaussianFilter[2][0]*orig_img.GetPixel(i-2, j)) +
                             (gaussianFilter[2][1]*orig_img.GetPixel(i-1, j)) +
                             (gaussianFilter[2][2]*orig_img.GetPixel(i, j)) +
                             (gaussianFilter[2][3]*orig_img.GetPixel(i+1, j)) +
                             (gaussianFilter[2][4]*orig_img.GetPixel(i+2, j)) +
                             
                             (gaussianFilter[3][0]*orig_img.GetPixel(i-2, j+1)) +
                             (gaussianFilter[3][1]*orig_img.GetPixel(i-1, j+1)) +
                             (gaussianFilter[3][2]*orig_img.GetPixel(i, j+1)) +
                             (gaussianFilter[3][3]*orig_img.GetPixel(i+1, j+1)) +
                             (gaussianFilter[3][4]*orig_img.GetPixel(i+2, j+1)) +
                             
                             (gaussianFilter[4][0]*orig_img.GetPixel(i-2, j+2)) +
                             (gaussianFilter[4][1]*orig_img.GetPixel(i-1, j+2)) +
                             (gaussianFilter[4][2]*orig_img.GetPixel(i, j+2)) +
                             (gaussianFilter[4][3]*orig_img.GetPixel(i+1, j+2)) +
                             (gaussianFilter[4][4]*orig_img.GetPixel(i+2, j+2)));
            blurred_pixel = blurred_pixel/256;
            blur_img.SetPixel(i, j, blurred_pixel);
        }
    }
    //Apply the Sobel masks
    int gradient1 = 0, gradient2 = 0;
    
    for (int i = 1; i < blur_img.num_rows()-1; i++) {
        for (int j = 1; j < blur_img.num_columns()-1; j++) {
            
            gradient1 = (delta1[0][0] * blur_img.GetPixel(i-1, j-1)) + (delta1[0][1] * blur_img.GetPixel(i, j-1)) +
                        (delta1[0][2] * blur_img.GetPixel(i+1, j-1)) + (delta1[1][0] * blur_img.GetPixel(i-1, j)) +
                        (delta1[1][1] * blur_img.GetPixel(i, j)) + (delta1[1][2] * blur_img.GetPixel(i+1, j)) +
                        (delta1[2][0] * blur_img.GetPixel(i-1, j+1)) + (delta1[2][1] * blur_img.GetPixel(i, j+1)) +
                        (delta1[2][2] * blur_img.GetPixel(i+1, j+1));
            
            gradient2 = (delta2[0][0] * blur_img.GetPixel(i-1, j-1)) + (delta2[0][1] * blur_img.GetPixel(i, j-1)) +
                        (delta2[0][2] * blur_img.GetPixel(i+1, j-1)) + (delta2[1][0] * blur_img.GetPixel(i-1, j)) +
                        (delta2[1][1] * blur_img.GetPixel(i, j)) + (delta2[1][2] * blur_img.GetPixel(i+1, j)) +
                        (delta2[2][0] * blur_img.GetPixel(i-1, j+1)) + (delta2[2][1] * blur_img.GetPixel(i, j+1)) +
                        (delta2[2][2] * blur_img.GetPixel(i+1, j+1));
            
            // I(x1, y1)^2 + I(x2, y2)^2 = squared gradient
            squared_gradient = ceil(gradient1*gradient1 + gradient2*gradient2);
            //sqrt(squared_gradient) = magnitude
            magnitude = sqrt(squared_gradient);
            edge_img.SetPixel(i, j, magnitude);
        }
    }
    
    if (!WriteImage(out_file, edge_img)){
        cout << "Can't write to file " << out_file << endl;
        return false;
    }
    return true;
}

int main(int argc, char **argv){
    
    if (argc!=3) {
        cout << "Usage: <input gray-level image> <output gray-level edge image> " << endl;
        return 0;
    }
    const string input_file(argv[1]);
    const string output_file(argv[2]);
    
    locateEdges(input_file, output_file);
    
    return 0;
}
