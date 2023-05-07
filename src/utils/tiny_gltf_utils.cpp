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

#include "tiny_gltf_utils.h"

namespace tinygltf::util {

const uint8_t* GetBufferAddress(const int i, const Accessor& accessor, const BufferView& bufferViewObject, const Buffer& buffer)
{
    if (i >= int(accessor.count))
        return nullptr;

    int byte_stride = accessor.ByteStride(bufferViewObject);
    if (byte_stride == -1)
    {
        return nullptr;
    }

    const uint8_t* base_addr = buffer.data.data() + bufferViewObject.byteOffset + accessor.byteOffset;
    const uint8_t* addr      = base_addr + i * byte_stride;
    return addr;
}

std::string PrintMode(int mode)
{
    if (mode == TINYGLTF_MODE_POINTS)
    {
        return "POINTS";
    }
    else if (mode == TINYGLTF_MODE_LINE)
    {
        return "LINE";
    }
    else if (mode == TINYGLTF_MODE_LINE_LOOP)
    {
        return "LINE_LOOP";
    }
    else if (mode == TINYGLTF_MODE_TRIANGLES)
    {
        return "TRIANGLES";
    }
    else if (mode == TINYGLTF_MODE_TRIANGLE_FAN)
    {
        return "TRIANGLE_FAN";
    }
    else if (mode == TINYGLTF_MODE_TRIANGLE_STRIP)
    {
        return "TRIANGLE_STRIP";
    }
    return "**UNKNOWN**";
}

std::string PrintTarget(int target)
{
    if (target == 34962)
    {
        return "GL_ARRAY_BUFFER";
    }
    else if (target == 34963)
    {
        return "GL_ELEMENT_ARRAY_BUFFER";
    }
    else
    {
        return "**UNKNOWN**";
    }
}

std::string PrintType(int ty)
{
    if (ty == TINYGLTF_TYPE_SCALAR)
    {
        return "SCALAR";
    }
    else if (ty == TINYGLTF_TYPE_VECTOR)
    {
        return "VECTOR";
    }
    else if (ty == TINYGLTF_TYPE_VEC2)
    {
        return "VEC2";
    }
    else if (ty == TINYGLTF_TYPE_VEC3)
    {
        return "VEC3";
    }
    else if (ty == TINYGLTF_TYPE_VEC4)
    {
        return "VEC4";
    }
    else if (ty == TINYGLTF_TYPE_MATRIX)
    {
        return "MATRIX";
    }
    else if (ty == TINYGLTF_TYPE_MAT2)
    {
        return "MAT2";
    }
    else if (ty == TINYGLTF_TYPE_MAT3)
    {
        return "MAT3";
    }
    else if (ty == TINYGLTF_TYPE_MAT4)
    {
        return "MAT4";
    }
    return "**UNKNOWN**";
}

std::string PrintComponentType(int ty)
{
    if (ty == TINYGLTF_COMPONENT_TYPE_BYTE)
    {
        return "BYTE";
    }
    else if (ty == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
    {
        return "UNSIGNED_BYTE";
    }
    else if (ty == TINYGLTF_COMPONENT_TYPE_SHORT)
    {
        return "SHORT";
    }
    else if (ty == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
    {
        return "UNSIGNED_SHORT";
    }
    else if (ty == TINYGLTF_COMPONENT_TYPE_INT)
    {
        return "INT";
    }
    else if (ty == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
    {
        return "UNSIGNED_INT";
    }
    else if (ty == TINYGLTF_COMPONENT_TYPE_FLOAT)
    {
        return "FLOAT";
    }
    else if (ty == TINYGLTF_COMPONENT_TYPE_DOUBLE)
    {
        return "DOUBLE";
    }

    return "**UNKNOWN**";
}

std::string PrintWrapMode(int mode)
{
    if (mode == TINYGLTF_TEXTURE_WRAP_REPEAT)
    {
        return "REPEAT";
    }
    else if (mode == TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE)
    {
        return "CLAMP_TO_EDGE";
    }
    else if (mode == TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT)
    {
        return "MIRRORED_REPEAT";
    }

    return "**UNKNOWN**";
}

std::string PrintFilterMode(int mode)
{
    if (mode == TINYGLTF_TEXTURE_FILTER_NEAREST)
    {
        return "NEAREST";
    }
    else if (mode == TINYGLTF_TEXTURE_FILTER_LINEAR)
    {
        return "LINEAR";
    }
    else if (mode == TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST)
    {
        return "NEAREST_MIPMAP_NEAREST";
    }
    else if (mode == TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR)
    {
        return "NEAREST_MIPMAP_LINEAR";
    }
    else if (mode == TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST)
    {
        return "LINEAR_MIPMAP_NEAREST";
    }
    else if (mode == TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR)
    {
        return "LINEAR_MIPMAP_LINEAR";
    }
    return "**UNKNOWN**";
}

int GetAnimationSamplerInputCount(const tinygltf::AnimationSampler& sampler, const tinygltf::Model& model)
{
    const tinygltf::Accessor& accessor = model.accessors[sampler.input];
    return accessor.count;
}

int GetAnimationSamplerOutputCount(const tinygltf::AnimationSampler& sampler, const tinygltf::Model& model)
{
    const tinygltf::Accessor& accessor = model.accessors[sampler.output];
    return accessor.count;
}

bool GetAnimationSamplerInputMinMax(const tinygltf::AnimationSampler& sampler, const tinygltf::Model& model, float* min_value, float* max_value)
{
    const tinygltf::Accessor& accessor = model.accessors[sampler.input];

    // Assume scalar value.
    if ((accessor.minValues.size() > 0) && (accessor.maxValues.size() > 0))
    {
        (*min_value) = accessor.minValues[0];
        (*max_value) = accessor.maxValues[0];
        return true;
    }
    else
    {
        (*min_value) = 0.0f;
        (*max_value) = 0.0f;
        return false;
    }
}

// Utility function for decoding animation value
float DecodeAnimationChannelValue(int8_t c)
{
    return std::max(float(c) / 127.0f, -1.0f);
}
float DecodeAnimationChannelValue(uint8_t c)
{
    return float(c) / 255.0f;
}
float DecodeAnimationChannelValue(int16_t c)
{
    return std::max(float(c) / 32767.0f, -1.0f);
}
float DecodeAnimationChannelValue(uint16_t c)
{
    return float(c) / 65525.0f;
}

bool DecodeScalarAnimationValue(const size_t i, const tinygltf::Accessor& accessor, const tinygltf::Model& model, float* scalar)
{
    const BufferView& bufferView = model.bufferViews[accessor.bufferView];
    const Buffer&     buffer     = model.buffers[bufferView.buffer];

    const uint8_t* addr = GetBufferAddress(i, accessor, bufferView, buffer);
    if (addr == nullptr)
    {
        std::cerr << "Invalid glTF data?" << std::endl;
        return false;
    }

    float value = 0.0f;

    if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_BYTE)
    {
        value = DecodeAnimationChannelValue(*(reinterpret_cast<const int8_t*>(addr)));
    }
    else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
    {
        value = DecodeAnimationChannelValue(*(reinterpret_cast<const uint8_t*>(addr)));
    }
    else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_SHORT)
    {
        value = DecodeAnimationChannelValue(*(reinterpret_cast<const int16_t*>(addr)));
    }
    else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
    {
        value = DecodeAnimationChannelValue(*(reinterpret_cast<const uint16_t*>(addr)));
    }
    else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT)
    {
        value = *(reinterpret_cast<const float*>(addr));
    }
    else
    {
        std::cerr << "??? Unknown componentType : " << PrintComponentType(accessor.componentType) << std::endl;
        return false;
    }

    (*scalar) = value;

    return true;
}

bool DecodeTranslationAnimationValue(const size_t i, const tinygltf::Accessor& accessor, const tinygltf::Model& model, float* xyz)
{
    if (accessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT)
    {
        std::cerr << "`translation` must be float type." << std::endl;
        return false;
    }

    const BufferView& bufferView = model.bufferViews[accessor.bufferView];
    const Buffer&     buffer     = model.buffers[bufferView.buffer];

    const uint8_t* addr = GetBufferAddress(i, accessor, bufferView, buffer);
    if (addr == nullptr)
    {
        std::cerr << "Invalid glTF data?" << std::endl;
        return 0.0f;
    }

    const float* ptr = reinterpret_cast<const float*>(addr);

    xyz[0] = *(ptr + 0);
    xyz[1] = *(ptr + 1);
    xyz[2] = *(ptr + 2);

    return true;
}

bool DecodeScaleAnimationValue(const size_t i, const tinygltf::Accessor& accessor, const tinygltf::Model& model, float* xyz)
{
    if (accessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT)
    {
        std::cerr << "`scale` must be float type." << std::endl;
        return false;
    }

    const BufferView& bufferView = model.bufferViews[accessor.bufferView];
    const Buffer&     buffer     = model.buffers[bufferView.buffer];

    const uint8_t* addr = GetBufferAddress(i, accessor, bufferView, buffer);
    if (addr == nullptr)
    {
        std::cerr << "Invalid glTF data?" << std::endl;
        return 0.0f;
    }

    const float* ptr = reinterpret_cast<const float*>(addr);

    xyz[0] = *(ptr + 0);
    xyz[1] = *(ptr + 1);
    xyz[2] = *(ptr + 2);

    return true;
}

bool DecodeRotationAnimationValue(const size_t i, const tinygltf::Accessor& accessor, const tinygltf::Model& model, float* xyzw)
{
    const BufferView& bufferView = model.bufferViews[accessor.bufferView];
    const Buffer&     buffer     = model.buffers[bufferView.buffer];

    const uint8_t* addr = GetBufferAddress(i, accessor, bufferView, buffer);
    if (addr == nullptr)
    {
        std::cerr << "Invalid glTF data?" << std::endl;
        return false;
    }

    float value = 0.0f;

    if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_BYTE)
    {
        xyzw[0] = DecodeAnimationChannelValue(*(reinterpret_cast<const int8_t*>(addr) + 0));
        xyzw[1] = DecodeAnimationChannelValue(*(reinterpret_cast<const int8_t*>(addr) + 1));
        xyzw[2] = DecodeAnimationChannelValue(*(reinterpret_cast<const int8_t*>(addr) + 2));
        xyzw[3] = DecodeAnimationChannelValue(*(reinterpret_cast<const int8_t*>(addr) + 3));
    }
    else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
    {
        xyzw[0] = DecodeAnimationChannelValue(*(reinterpret_cast<const uint8_t*>(addr) + 0));
        xyzw[1] = DecodeAnimationChannelValue(*(reinterpret_cast<const uint8_t*>(addr) + 1));
        xyzw[2] = DecodeAnimationChannelValue(*(reinterpret_cast<const uint8_t*>(addr) + 2));
        xyzw[3] = DecodeAnimationChannelValue(*(reinterpret_cast<const uint8_t*>(addr) + 3));
    }
    else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_SHORT)
    {
        xyzw[0] = DecodeAnimationChannelValue(*(reinterpret_cast<const int16_t*>(addr) + 0));
        xyzw[1] = DecodeAnimationChannelValue(*(reinterpret_cast<const int16_t*>(addr) + 1));
        xyzw[2] = DecodeAnimationChannelValue(*(reinterpret_cast<const int16_t*>(addr) + 2));
        xyzw[3] = DecodeAnimationChannelValue(*(reinterpret_cast<const int16_t*>(addr) + 3));
    }
    else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
    {
        xyzw[0] = DecodeAnimationChannelValue(*(reinterpret_cast<const uint16_t*>(addr) + 0));
        xyzw[1] = DecodeAnimationChannelValue(*(reinterpret_cast<const uint16_t*>(addr) + 1));
        xyzw[2] = DecodeAnimationChannelValue(*(reinterpret_cast<const uint16_t*>(addr) + 2));
        xyzw[3] = DecodeAnimationChannelValue(*(reinterpret_cast<const uint16_t*>(addr) + 3));
    }
    else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT)
    {
        xyzw[0] = *(reinterpret_cast<const float*>(addr) + 0);
        xyzw[1] = *(reinterpret_cast<const float*>(addr) + 1);
        xyzw[2] = *(reinterpret_cast<const float*>(addr) + 2);
        xyzw[3] = *(reinterpret_cast<const float*>(addr) + 3);
    }
    else
    {
        std::cerr << "??? Unknown componentType : " << PrintComponentType(accessor.componentType) << std::endl;
        return false;
    }

    return true;
}

} // namespace tinygltf::util