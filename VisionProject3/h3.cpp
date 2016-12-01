//
//  h3.cpp
//  VisionProj3
//
//  Created by Elizabeth Kelly on 10/1/16.
//  Copyright © 2016 Elizabeth Kelly. All rights reserved.
//

#include <stdio.h>
#include "Image.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

bool houghTransform(string in_file, string out_file, string voting_file) {
    Image orig_img;

    if (!ReadImage(in_file, &orig_img)) {
        cout <<"Can't open file " << in_file << endl;
        return false;
    }
    size_t rows = orig_img.num_rows();
    size_t cols = orig_img.num_columns();
    
    Image hough_img;
    int rho_max = sqrt((rows*rows) + (cols*cols));
    int theta_max = 180;

    int r = 0;
    double theta_radians = 0.0;
    int accumulator[rho_max][theta_max];
    
    for (int i = 0; i < rho_max; i++) {
        for (int j = 0; j < theta_max; j++) {
            accumulator[i][j] = 0; //initialize array to all 0s
        }
    }
    
    hough_img.AllocateSpaceAndSetSize(rho_max, theta_max);
    hough_img.SetNumberGrayLevels(255);
    ofstream outfile;
    outfile.open(voting_file);
    
    int max = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (orig_img.GetPixel(i, j) != 0) {
                for (int theta = 0; theta < theta_max-1; theta++) {
                    
                    theta_radians = (theta / 180.0) * M_PI;
                    r = i*cos(theta_radians) + j*sin(theta_radians);
                    int rho = round(r);
                    //if rho is out of bounds, skip it
                    if (rho < 0 || rho >= rho_max) {
                        continue;
                    }
                    accumulator[rho][theta]++;
                    if (accumulator[rho][theta] > max) {
                        max = accumulator[rho][theta];

                    }
                }
            }
            
        }
    }
    //output the accumulator array to file
    //scale the pixel t * 255/M

    int new_pixel = 0;
    for (int r = 0; r < rho_max; r++) {
        for (int t = 0; t < theta_max-1; t++) {
            if (accumulator[r][t] >= 0) {
            outfile << accumulator[r][t] << " ";
            new_pixel = ((double)accumulator[r][t]/max)*255;
            hough_img.SetPixel(r, t, new_pixel);
            }
            
        }
        outfile << endl;
    }
    
    outfile.close();

    if (!WriteImage(out_file, hough_img)){
        cout << "Can't write to file " << out_file << endl;
        return false;
    }
    return true;
}

int main(int argc, char **argv){
    
    if (argc!=4) {
        cout << "Usage: <input binary image> <output gray-level edge Hough image> <output Hough voting array> " << endl;
        return 0;
    }
    const string input_file(argv[1]);
    const string output_file(argv[2]);
    const string voting_file(argv[3]);
    
    houghTransform(input_file, output_file, voting_file);
    
    return 0;
}
