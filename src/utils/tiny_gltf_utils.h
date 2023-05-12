//
// TinyGLTF utility functions
//
//
// The MIT License (MIT)
//
// Copyright (c) 2015 - 2018 Syoyo Fujita, Aurélien Chatelain and many
// contributors.
//

// From branch "anim-dump"

#include <iostream>
#include "tiny_gltf.h"

namespace tinygltf::util {

const uint8_t* GetBufferAddress(const int i, const Accessor& accessor, const BufferView& bufferViewObject, const Buffer& buffer);

std::string PrintComponentType(int ty);

int GetAnimationSamplerInputCount(const tinygltf::AnimationSampler& sampler, const tinygltf::Model& model);

int GetAnimationSamplerOutputCount(const tinygltf::AnimationSampler& sampler, const tinygltf::Model& model);

// Utility function for decoding animation value
float DecodeAnimationChannelValue(int8_t c);
float DecodeAnimationChannelValue(uint8_t c);
float DecodeAnimationChannelValue(int16_t c);
float DecodeAnimationChannelValue(uint16_t c);

bool DecodeScalarAnimationValue(const size_t i, const tinygltf::Accessor& accessor, const tinygltf::Model& model, float* scalar);

bool DecodeTranslationAnimationValue(const size_t i, const tinygltf::Accessor& accessor, const tinygltf::Model& model, float* xyz);

bool DecodeScaleAnimationValue(const size_t i, const tinygltf::Accessor& accessor, const tinygltf::Model& model, float* xyz);

bool DecodeRotationAnimationValue(const size_t i, const tinygltf::Accessor& accessor, const tinygltf::Model& model, float* xyzw);



} // namespace tinygltf::util