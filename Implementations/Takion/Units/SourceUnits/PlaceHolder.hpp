// Copyright (c) 2020, Jaewoo Kim

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef TAKION_GRAPH_PLACEHOLDER_HPP
#define TAKION_GRAPH_PLACEHOLDER_HPP

#include <Takion/Units/SourceUnits/PlaceHolderDecl.hpp>

namespace Takion::Graph
{
template <typename T>
PlaceHolder<T>::PlaceHolder(const UnitId& unitId, Tensor<T> forwardOutput,
                            std::function<std::vector<T>()> loader,
                            std::size_t batchSize)
    : ComputableUnit<T>(unitId, {}, {}, std::move(forwardOutput), {}, {},
                        batchSize),
      m_loader(std::move(loader))
{
}

template <typename T>
PlaceHolder<T> PlaceHolder<T>::CreateUnit(
    const FrontEnd::UnitMetaData<T>& unitMetaData,
    std::function<std::vector<T>()> loader)
{
    const auto unitId = unitMetaData.Id();
    const auto shape = unitMetaData.GetOutputShape();
    const auto batchSize = unitMetaData.BatchSize();
    const auto device = unitMetaData.Device;

    if (device.Type() != DeviceType::CPU)
        throw std::runtime_error(
            "CreateUnit - Device type of placeHolder must be CPU");

    Tensor<T> placeHolder(shape, batchSize, device);
    return PlaceHolder<T>(unitId, placeHolder, loader, batchSize);
}

template <typename T>
void PlaceHolder<T>::Forward()
{
    auto vector = m_loader();
    if (vector.size() != ForwardOutput.TensorShape.Size())
    {
        const std::string errorMessage =
            std::string("Loaded vector mismatches expected size ") +
            "Given size : " + std::to_string(vector.size()) +
            " Expected size : " +
            std::to_string(ForwardOutput.TensorShape.Size());
        throw std::runtime_error(errorMessage);
    }

    VectorInitializer<T> initializer(std::move(vector));
    initializer.Initialize(ForwardOutput);
}

template <typename T>
void PlaceHolder<T>::AsyncForward(std::promise<bool> promise)
{
    auto vector = m_loader();
    if (vector.size() != ForwardOutput.TensorShape.Size())
    {
        const std::string errorMessage =
            std::string("Loaded vector mismatches expected size ") +
            "Given size : " + std::to_string(vector.size()) +
            " Expected size : " +
            std::to_string(ForwardOutput.TensorShape.Size());
        throw std::runtime_error(errorMessage);
    }

    Compute::VectorInitializer<T> initializer(std::move(vector));
    initializer.Initialize(ForwardOutput);
    promise.set_value(true);
}

template <typename T>
void PlaceHolder<T>::Backward()
{
    // Do nothing
}

template <typename T>
void PlaceHolder<T>::AsyncBackward(std::promise<bool> promise)
{
    // Do nothing
    promise.set_value(true);
}
}

#endif
