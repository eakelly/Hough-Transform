//
//  h4.cpp
//  VisionProj3
//
//  Created by Elizabeth Kelly on 10/11/16.
//  Copyright © 2016 Elizabeth Kelly. All rights reserved.
//

#include <stdio.h>
#include "Image.h"
#include <cstdio>
#include <cmath>
#include <cstring>
#include <fstream>
#include <string>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;


bool detectLines (string in_file, string voting_file, int threshold, string out_file) {
    Image orig_img;
    
    if (!ReadImage(in_file, &orig_img)) {
        cout <<"Can't open file " << in_file << endl;
        return false;
    }
    
    ifstream voting_array;
    voting_array.open(voting_file);
    
    if (!voting_array.is_open()) {
        cout << "Error: Can't open voting array" << endl;
    }

    
    size_t rows = orig_img.num_rows();
    size_t cols = orig_img.num_columns();
    
    
    Image line_img;
    line_img.AllocateSpaceAndSetSize(rows, cols);
    line_img.SetNumberGrayLevels(255);
    
    //copy original image
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            line_img.SetPixel(i, j, orig_img.GetPixel(i, j));
        }
    }
    
    int rho_max = sqrt((rows*rows) + (cols*cols));
    int theta_max = 180;
    int votes[rho_max][theta_max];
    
    //export the votes from file into array
    for (int i = 0; i < rho_max; i++) {
        for (int j = 0; j < theta_max-1; j++) {
            voting_array >> votes[i][j];
        }
    }
    //a bool to check if the center of the 3x3 neighbor array is the maximum of its neighbors
    bool isLocalMax = false;
    
    for (int r = 0; r < rho_max; r++) {
        for (int t = 0; t < theta_max-1; t++) {
            if (votes[r][t] > threshold) { //index has many votes
                isLocalMax = true;
                for (int i = -1; i < 2; i++) {
                    for (int j = -1; j < 2; j++) {
                        //check to make sure that the i+r and j+t offsets are within bounds
                        if (i+r >=0 && i+r < rows && j+t >= 0 && j+t < cols) {
                            if (votes[i+r][j+t] > votes[r][t]) {
                                //the center, votes[r][t] is not a local maximum
                                isLocalMax = false;
                            }
                        }
                    }
                }
                //if the center was a local max
                if (isLocalMax) {
                    
                    double theta_rad = (t / 180.0) * M_PI;
                    //check if theta is within bounds
                    if (t > 45 && t <= 135) {
                        int x1 = 0;
                        int y1 = abs((r - (x1 * cos(theta_rad)))/sin(theta_rad));
                        int x2 = (int)rows-1;
                        int y2 = abs((r - (x2 * cos(theta_rad)))/sin(theta_rad));
                        //bound check for computed y values
                        if (y1 < cols && y2 < cols) {
                            DrawLine(x1, y1, x2, y2, 255, &line_img);
                        }
                    }
                    else {
                        int y1 = 0;
                        int x1 = abs((r - (y1 * sin(theta_rad)))/cos(theta_rad));
                        int y2 = (int)cols-1;
                        int x2 = abs((r - (y2 * sin(theta_rad)))/cos(theta_rad));
                        //bound check for computed x values
                        if (x1 < rows && x2 < rows) {
                            DrawLine(x1, y1, x2, y2, 255, &line_img);
                        }

                    }
                }
                
            }
        }
    }
    

    if (!WriteImage(out_file, line_img)){
        cout << "Can't write to file " << out_file << endl;
        return false;
    }
    return true;
}


int main(int argc, char **argv){
    
    if (argc!=5) {
        cout << "Usage: <input original gray-level image> <input Hough voting array> <input Hough threshold value> <output gray-level line image> " << endl;
        return 0;
    }
    const string input_file(argv[1]);
    const string voting_array(argv[2]);
    const string number(argv[3]);
    const string output_file(argv[4]);
    int threshold = atoi(number.c_str());
    
    detectLines(input_file, voting_array, threshold, output_file);
    
    return 0;
}
