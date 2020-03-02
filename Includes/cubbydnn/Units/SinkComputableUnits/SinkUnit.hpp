// Copyright (c) 2019 Chris Ohk, Justin Kim

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.


#ifndef CUBBYDNN_SINKUNIT_HPP
#define CUBBYDNN_SINKUNIT_HPP

#include <cubbydnn/Units/ComputableUnit.hpp>
#include <functional>

namespace CubbyDNN
{
//! Unit that has no output, but has inputs
//! This type of unit plays role as sink of the computable graph
class SinkUnit : public ComputableUnit
{
public:
    //! Constructor
    //! \param inputTensorInfoVector : vector of tensorInfo to accept
    explicit SinkUnit(std::vector<TensorInfo> inputTensorInfoVector);

    //! SinkUnit is not copy-assignable
    SinkUnit(const SinkUnit& sinkUnit) = delete;

    //! SinkUnit is not copy-assignable
    SinkUnit& operator=(const SinkUnit& sinkUnit) = delete;

    //! Brings back if executableUnit is ready to be executed
    //! \return : whether corresponding unit is ready to be executed
    bool IsReady() final;

    void Compute() override;
};

class SinkTestUnit : public SinkUnit
{
public:
    //! Constructor
    //! \param inputTensorInfo : tensorInfo of the input to be tested
    //! \param testFunction : lambda for testing the output
    explicit SinkTestUnit(TensorInfo inputTensorInfo,
                          std::function<void(const Tensor&, size_t)>
                          testFunction);

    //! SinkUnit is not copy-assignable
    SinkTestUnit(const SinkTestUnit& sinkUnit) = delete;

    //! SinkUnit is not copy-assignable
    SinkTestUnit& operator=(const SinkTestUnit& sinkUnit) = delete;

    void Compute() override;

private:
    //! Lambda used for testing
    std::function<void(const Tensor&, size_t)> m_testFunction;
};
} // namespace CubbyDNN

#endif  // CUBBYDNN_SINKUNIT_HPP
