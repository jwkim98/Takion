// Copyright (c) 2019 Chris Ohk, Justin Kim

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef CUBBYDNN_UNITID_HPP
#define CUBBYDNN_UNITID_HPP
#include <cubbydnn/Utils/SharedPtr.hpp>
#include <unordered_map>

namespace CubbyDNN::Graph
{
enum class UnitBaseType
{
    Source,
    Hidden,
    Sink,
    Copy,
};


class UnitType
{
public:
    UnitType(UnitBaseType type, std::string_view typeName);
    UnitType(UnitBaseType type, std::string_view name,
             SharedPtr<UnitType> baseUnit);
    ~UnitType() = default;

    UnitType(const UnitType& unitType) = default;
    UnitType(UnitType&& unitType) noexcept = default;
    UnitType& operator=(const UnitType& unitType) = default;
    UnitType& operator=(UnitType&& unitType) noexcept = default;

    bool operator==(const UnitType& unitType) const;
    bool operator!=(const UnitType& unitType) const;

    [[nodiscard]] const std::string& Name() const
    {
        return m_typeName;
    }

    [[nodiscard]] bool IsBaseOf(const UnitType& derivedUnit) const
    {
        return IsBaseOf(*this, derivedUnit);
    }

    [[nodiscard]] bool IsDerivedFrom(const UnitType& baseUnit) const
    {
        return IsBaseOf(baseUnit, *this);
    }

    static bool IsBaseOf(const UnitType& baseUnit, const UnitType& derivedUnit);

    SharedPtr<UnitType> BaseUnit;
    UnitBaseType BaseType;

private:
    std::string m_typeName;
};

struct UnitId
{
    bool operator==(const UnitId& unitId) const
    {
        return Type == unitId.Type && Id == unitId.Id &&
               UnitName == unitId.UnitName;
    }

    bool operator!=(const UnitId& unitId) const
    {
        return !(*this == unitId);
    }

    UnitType Type;
    std::size_t Id;
    std::string UnitName;
};
} // namespace CubbyDNN

//! Add template specialization for UnitId hash
namespace std
{
template <>
struct hash<CubbyDNN::Graph::UnitId>
{
    std::size_t operator()(CubbyDNN::Graph::UnitId const& s) const noexcept
    {
        const std::size_t h1 = std::hash<std::string>{}(s.UnitName);
        const std::size_t h2 = std::hash<std::size_t>{}(s.Id);
        return h1 ^ (h2 << 1); // or use boost::hash_combine
    }
};
}; // namespace std
#endif