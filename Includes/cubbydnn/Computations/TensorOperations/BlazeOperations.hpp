// Copyright (c) 2019 Chris Ohk, Justin Kim

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef CUBBYDNN_BLAZEOPERATIONS_HPP
#define CUBBYDNN_BLAZEOPERATIONS_HPP

#include <cubbydnn/Tensors/Tensor.hpp>
#include <cubbydnn/Computations/TensorOperations/TensorOperations.hpp>

namespace CubbyDNN
{
class BlazeOperation : public TensorOperation
{
public:
    BlazeOperation();

    void Multiply(const Tensor& inputA, const Tensor& inputB, Tensor& output) override;

    void Add(const Tensor& inputA, const Tensor& inputB, Tensor& output) override;

    void Transpose(const Tensor& input, Tensor& output) override;
};
} // namespace CubbyDNN

#endif