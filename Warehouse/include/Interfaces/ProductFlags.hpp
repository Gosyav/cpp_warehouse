#pragma once

namespace warehouseInterface
{
enum class ProductLabelFlags
{
    fireHazardous = 1 << 0,
    explosives = 1 << 1,
    fragile = 1 << 2,
    upWard = 1 << 3,
    keepDry = 1 << 4,
    handleWithCare = 1 << 5,
    keepFrozen = 1 << 6,
    esdSensitive = 1 << 7
};

}