// Copyright (c) 2019 Chris Ohk, Justin Kim

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef CUBBYDNN_INITIALIZER_HPP
#define CUBBYDNN_INITIALIZER_HPP

#include <cubbydnn/Computations/Initializers/InitializerOp.hpp>
#include <cubbydnn/Tensors/Tensor.hpp>

namespace CubbyDNN
{

class Initializer
{
    void XavierNormal(Tensor& tensorInfo);

    void LecunNormal(Tensor& tensorInfo);

    void HeNormal(Tensor& tensorInfo);

    void Zeros(Tensor& tensor);

    void Ones(Tensor& tensor);

};
}

#endif
