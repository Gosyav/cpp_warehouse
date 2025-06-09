
#include <PicoJson/picojson.h>
#include <gtest/gtest.h>

#include <Factory/ProductFactory.hpp>
#include <Products/ProductsList.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
namespace warehouse
{
class ProductFactoryTest : public testing::TestWithParam<std::tuple<std::string, std::string, float>>
{
protected:
    warehouse::ProductFactory factory{};
};

TEST_P(ProductFactoryTest, CreateProduct)
{
    std::string className, name;
    float size;
    std::tie(className, name, size) = GetParam();

    warehouseInterface::IProductPtr productPtr = factory.createProduct(className, name, size);

    ASSERT_NE(nullptr, productPtr);
    EXPECT_EQ(name, productPtr->name());
    EXPECT_FLOAT_EQ(size, productPtr->itemSize());
}

TEST_F(ProductFactoryTest, UnknownProduct)
{
    EXPECT_THROW(factory.createProduct("Unknown class", "nope", -1.0), std::runtime_error);
}

INSTANTIATE_TEST_SUITE_P(ProductFactoryTestInstantiation,
                         ProductFactoryTest,
                         testing::Values(std::make_tuple("IndustrialServerRack", "Server Rack 1", 10.0),
                                         std::make_tuple("GlassWare", "Wine Glass 2", 0.2),
                                         std::make_tuple("ExplosiveBarrel", "Barrel of C4", 50.0),
                                         std::make_tuple("ElectronicParts", "PCB Board", 0.01),
                                         std::make_tuple("AstronautsIceCream", "Neapolitan Ice Cream", 0.5),
                                         std::make_tuple("AcetoneBarrel", "Barrel of Acetone", 100.0),
                                         std::make_tuple("TV", "Smart TV 55\"", 15.0)));
}  // namespace warehouse