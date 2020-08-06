// Copyright (c) 2020, Jaewoo Kim

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef TAKION_COMPUTE_COMPUTATIONS_HPP
#define TAKION_COMPUTE_COMPUTATIONS_HPP

#include <Takion/Tensors/Tensor.hpp>
#include <Takion/Computations/GEMM/MathKernel.hpp>

namespace Takion::Compute
{
template <typename T>
void MultiplyAdd(const Tensor<T>& A, const Tensor<T>& B, const Tensor<T>& C,
                 Tensor<T>& out)
{
    const auto device = out.Device;
    const auto outputShape = out.TensorShape;
    const auto inputShapeA = A.TensorShape;

    if (device.Type() == DeviceType::Cpu)
    {
        if (A.BatchSize == B.BatchSize)
            CPU::MultiplyCpu(A.Data, B.Data, out.Data, outputShape.NumRows,
                             out.ColumnElementSize(), inputShapeA.NumCols,
                             out.BatchSize);
        else if (A.BatchSize == 1)
        {
            CPU::MultiplyWithBroadcastCpu(
                A.Data, B.Data, out.Data, outputShape.NumRows(),
                out.ColumnElementSize(), inputShapeA.NumCols, out.BatchSize,
                true);
        }
        else if (B.BatchSize == 1)
        {
            CPU::MultiplyWithBroadcastCpu(
                A.Data, B.Data, out.Data, outputShape.NumRows(),
                out.ColumnElementSize(), inputShapeA.NumCols, out.BatchSize,
                false);
        }
        else
        {
            throw std::invalid_argument(
                "Both of the given tensors have batch size greater than 1");
        }

        CPU::AddCpu(out.Data, C.Data, out.Data, out.ElementSize(),
                    out.BatchSize);
    }
    else
    {
        std::runtime_error("Not implemented");
    }
}

template <typename T>
void Multiply(const Tensor<T>& A, const Tensor<T>& B, Tensor<T>& out)
{
    const auto device = out.Device;
    const auto outputShape = out.TensorShape;
    const auto inputShapeA = A.TensorShape;

    if (device.Type() == DeviceType::Cpu)
    {
        if (A.BatchSize == B.BatchSize)
            CPU::MultiplyCpu(A.Data, B.Data, out.Data, outputShape.NumRows,
                             out.ColumnElementSize(), inputShapeA.NumCols,
                             out.BatchSize);
        else if (A.BatchSize == 1)
        {
            CPU::MultiplyWithBroadcastCpu(
                A.Data, B.Data, out.Data, outputShape.NumRows(),
                out.ColumnElementSize(), inputShapeA.NumCols, out.BatchSize,
                true);
        }
        else if (B.BatchSize == 1)
        {
            CPU::MultiplyWithBroadcastCpu(
                A.Data, B.Data, out.Data, outputShape.NumRows(),
                out.ColumnElementSize(), inputShapeA.NumCols, out.BatchSize,
                false);
        }
        else
        {
            throw std::invalid_argument(
                "Batch size mismatch between given tensors");
        }
    }
}

template <typename T>
void Transpose(const Tensor<T>& input, Tensor<T>& output)
{
    const auto device = output.Device;
    const auto inputShape = input.TensorShape;

    if (device.Type() == DeviceType::Cpu)
    {
        CPU::CpuTranspose(input, output, inputShape.NumRows,
                          input.ColumnElementSize());
    }
    else
        throw std::runtime_error("Not implemented");
}

template <typename T>
void Shrink(const Tensor<T>& input, Tensor<T>& output)
{
    const auto device = output.Device;
    const auto size = output.ElementSize();
    if (device.Type() == DeviceType::Cpu)
    {
        CPU::ShrinkCpu(input.Data, output.Data, size, output.BatchSize);
    }
    else
        throw std::runtime_error("Not implemented");
}

template <typename T>
void Add(const Tensor<T>& A, const Tensor<T>& B, Tensor<T>& out)
{
    const auto device = out.Device;
    if (device.Type() == DeviceType::Cpu)
    {
        if (A.BatchSize == B.BatchSize)
            CPU::AddCpu(A.Data, B.Data, out.Data,
                                     out.ElementSize(), out.BatchSize);
        else if (B.BatchSize == 1)
            CPU::AddWithBroadcastCpu(A.Data, B.Data, out.Data, out.ElementSize(),
                        out.BatchSize);
        else
            throw std::invalid_argument(
                "Batch size mismatch between given tensors");
    }
    else
        throw std::runtime_error("Not implemented");
}

template <typename T>
void Dot(const Tensor<T>& A, const Tensor<T>& B, Tensor<T>& out)
{
    const auto device = out.Device;
    if (device.Type() == DeviceType::Cpu)
    {
        CPU::DotCpu(A.Data, B.Data, out.Data, out.ElementSize(), out.BatchSize);
    }
    else
        throw std::runtime_error("Not implemented");
}

template <typename T>
void ScalarMul(const Tensor<T>& input, T toMul, Tensor<T>& output)
{
    const auto device = output.Device;
    if (device.Type() == DeviceType::Cpu)
    {
        CPU::ScalarMulCpu(input.Data, toMul, output.Data, output.ElementSize(),
                          output.BatchSize);
    }
    else
        throw std::runtime_error("Not implemented");
}
}

#endif