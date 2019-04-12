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

    float a_data[] = {0.0,1.0,2.0,3.0,4.0};
    float b_data[] = {4.0,3.0,2.0,1.0,0.0};
    ncnn::Mat a(2,2,(void*)a_data);
    ncnn::Mat b(2,2,(void*)b_data);
    ncnn::Mat c(2,2);
    binary_add(a,b,c);
    float* c_data = (float*)c.data;
    LOGCC << c_data[0] << endl;




    
    return 0;
}
