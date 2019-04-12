/*************************************************************************
	> File Name: op.h
	> Author: dzhang
	> Mail: dong.zhang@ingenic.com 
	> Created Time: Fri 12 Apr 2019 06:17:57 PM CST
 ************************************************************************/

#include<iostream>
#include "layer.h"

namespace ncnn{

#define DEFINE_LAYER_CREATORD(name) \
    ::ncnn::Layer* name##_layer_creator() { return new name; }

#define DEFINE_LAYER_CREATORI(name) \
    ::ncnn::Layer* name##_layer_creator();

} //namespace ncnn
