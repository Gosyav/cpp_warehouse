#pragma once

#include <Products/BaseProduct.hpp>

namespace warehouse
{

class BasicProduct : public BaseProduct
{
public:
    BasicProduct(const std::string &name, float size, warehouseInterface::ProductLabelFlags flags) :
            BaseProduct(name, size, flags)
    {}

protected:
    std::string getClassName() const override { return "BasicProduct"; }
};

}  // namespace warehouse