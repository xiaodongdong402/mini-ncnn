/*************************************************************************
	> File Name: low_precision_convolution.h
	> Author: dzhang
	> Mail: dong.zhang@ingenic.com 
	> Created Time: Fri 12 Apr 2019 04:49:12 PM CST
 ************************************************************************/
#ifndef LOW_PRECISION_CONVOLUTION_H
#define LOW_PRECISION_CONVOLUTION_H

#include<iostream>

#include "layer.h"
#include "op.h"

namespace ncnn {

class LPConvolution : public Layer
{
public:
    LPConvolution();
    ~LPConvolution();

    virtual int load_param(const ParamDict& pd);

    virtual int load_model(const ModelBin& mb);

    virtual int forward(const Mat& bottom_blob, Mat& top_blob, const Option& opt) const;

#if NCNN_VULKAN
    virtual int upload_model(VkTransfer& cmd);

    virtual int create_pipeline();
    virtual int destroy_pipeline();

    virtual int forward(const VkMat& bottom_blob, VkMat& top_blob, VkCompute& cmd, const Option& opt) const;
#endif // NCNN_VULKAN

public:
    // param
    int num_output;
    int kernel_w;
    int kernel_h;
    int dilation_w;
    int dilation_h;
    int stride_w;
    int stride_h;
    int pad_w;
    int pad_h;
    int bias_term;

    int weight_data_size;

    int int8_scale_term;

    // model
    Mat weight_data;
    Mat bias_data;

#if NCNN_VULKAN
    ncnn::Layer* padding;

    VkMat weight_data_gpu;
    VkMat bias_data_gpu;

    Pipeline* pipeline_convolution;
    Pipeline* pipeline_convolution_1x1s1d1;

    VkMat bias_data_gpu_pack4;

    // pack4
    VkMat weight_data_gpu_pack4;
    Pipeline* pipeline_convolution_pack4;

    // pack1to4
    VkMat weight_data_gpu_pack1to4;
    Pipeline* pipeline_convolution_pack1to4;

    // pack4to1
    VkMat weight_data_gpu_pack4to1;
    Pipeline* pipeline_convolution_pack4to1;

    // convolution as fc
    Pipeline* pipeline_innerproduct;
    Pipeline* pipeline_innerproduct_pack4;
    Pipeline* pipeline_innerproduct_pack1to4;
    Pipeline* pipeline_innerproduct_pack4to1;
#endif // NCNN_VULKAN

    float weight_data_int8_scale;
    float bottom_blob_int8_scale;

    bool use_int8_inference;

    ncnn::Layer* quantize;
    ncnn::Layer* dequantize;
};

DEFINE_LAYER_CREATORI(LPConvolution)

//Layer* LPConvolution_layer_creator();

} // namespace ncnn

#endif // LOW_PRECISION_CONVOLUTION_H
