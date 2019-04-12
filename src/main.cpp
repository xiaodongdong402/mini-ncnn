/*************************************************************************
	> File Name: main.cpp
	> Author: dzhang
	> Mail: dong.zhang@ingenic.com 
	> Created Time: Fri 12 Apr 2019 11:24:56 AM CST
 ************************************************************************/

#include<iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "platform.h"
#include "net.h"
#if NCNN_VULKAN
#include "gpu.h"
#endif // NCNN_VULKAN

#include "logger.h"
#include "squeezenet_v1.h"


using namespace std;



void binary_add(const ncnn::Mat& a, const ncnn::Mat& b, ncnn::Mat& c)
{

    ncnn::Layer* op = ncnn::create_layer("BinaryOp");
    ncnn::ParamDict pd;
    pd.set(0, 0);// op_type
    op->load_param(pd);
    std::vector<ncnn::Mat> bottoms(2);
    bottoms[0] = a;
    bottoms[1] = b;
    std::vector<ncnn::Mat> tops(1);
    op->forward(bottoms, tops);
    c = tops[0];
    delete op;
}


int main()
{

    LOGCC << "hello word from log!!!" <<endl;
    cout<<"hello word!!!"<<endl;
    
    string imagepath = "/home/dzhang/rnet_test_img.jpg";
    run_squeezenet_model(imagepath);
    
    return 0;
}
