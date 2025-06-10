#pragma once

#include <PicoJson/picojson.h>

#include <Interfaces/IProduct.hpp>
#include <Interfaces/ProductFlags.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Products/BaseProduct.hpp>

using namespace magic_enum::bitwise_operators;

namespace warehouse
{
class TV : public BaseProduct
{
public:
    /**
     * @brief Construct a new TV product
     * @param name Name of the TV
     * @param size Size of the TV
     */
    TV(const std::string &name, float size) :
            BaseProduct(name,
                        size,
                        warehouseInterface::ProductLabelFlags::fragile | warehouseInterface::ProductLabelFlags::keepDry)
    {}

    std::string getClassName() const override { return "TV"; }
};
}  // namespace warehouse