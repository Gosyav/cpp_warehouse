
#include <PicoJson/picojson.h>
#include <Warehouse/Warehouse.h>
#include <gtest/gtest.h>

#include <Departments/DepartmentsList.hpp>
#include <Factory/ProductFactory.hpp>
#include <Products/ProductsList.hpp>
#include <iostream>

namespace warehouse
{
TEST(WarehouseTest, ThreeProducts)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<SpecialDepartment>(10.0));
    warehouse.addDepartment(std::make_unique<SmallElectronicDepartment>(10.0));

    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("IndustrialServerRack", "Server Rack", 2.0f));
    auto rawProductPtr1 = products.back().get();
    products.emplace_back(productFactory.createProduct("GlassWare", "Glass Plate", 0.5f));
    auto rawProductPtr2 = products.back().get();
    products.emplace_back(productFactory.createProduct("ElectronicParts", "Transistor", 0.5f));
    auto rawProductPtr3 = products.back().get();
    EXPECT_EQ(warehouse.newDelivery(std::move(products)),
              "{\"deliveryReport\":[{\"assignedDepartment\":\"SmallElectronicDepartment\",\"errorLog\":\"\",\"productName\":"
              "\"Server "
              "Rack\",\"status\":\"Success\"},{\"assignedDepartment\":\"SpecialDepartment\",\"errorLog\":\"\",\"productName\":"
              "\"Glass "
              "Plate\",\"status\":\"Success\"},{\"assignedDepartment\":\"SmallElectronicDepartment\",\"errorLog\":\"\","
              "\"productName\":\"Transistor\",\"status\":\"Success\"}]}");

    EXPECT_EQ(warehouse.getOccupancyReport(),
              "{\"departmentsOccupancy\":[{\"departmentName\":\"SpecialDepartment\",\"maxOccupancy\":10,\"occupancy\":0.5},{"
              "\"departmentName\":\"SmallElectronicDepartment\",\"maxOccupancy\":10,\"occupancy\":2.5}]}");

    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"IndustrialServerRack\"}]}");
        EXPECT_EQ(order.receipt, "{\"order\": [{\"class\":\"IndustrialServerRack\"}]}");
        EXPECT_EQ(order.products.back().get(), rawProductPtr1);
    }

    {
        auto order = warehouse.newOrder("{\"order\": [{\"name\":\"Glass Plate\"}]}");
        EXPECT_EQ(order.receipt, "{\"order\": [{\"name\":\"Glass Plate\"}]}");
        EXPECT_EQ(order.products.back().get(), rawProductPtr2);
    }

    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"ElectronicParts\",\"name\":\"Transistor\"}]}");
        EXPECT_EQ(order.receipt, "{\"order\": [{\"class\":\"ElectronicParts\",\"name\":\"Transistor\"}]}");
        EXPECT_EQ(order.products.back().get(), rawProductPtr3);
    }
}

TEST(WarehouseTest, IceCreams)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<ColdRoomDepartment>(10.0));

    std::vector<warehouseInterface::IProductPtr> products{};
    std::vector<warehouseInterface::IProduct *> productsRawPtrs{};
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "0", 2.0f));
    productsRawPtrs.emplace_back(products.back().get());
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "1", 2.0f));
    productsRawPtrs.emplace_back(products.back().get());
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "2", 2.0f));
    productsRawPtrs.emplace_back(products.back().get());
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "3", 2.0f));
    productsRawPtrs.emplace_back(products.back().get());

    EXPECT_EQ(warehouse.newDelivery(std::move(products)),
              "{\"deliveryReport\":[{\"assignedDepartment\":\"ColdRoomDepartment\",\"errorLog\":\"\",\"productName\":\"0\","
              "\"status\":\"Success\"},{\"assignedDepartment\":\"ColdRoomDepartment\",\"errorLog\":\"\",\"productName\":\"1\","
              "\"status\":\"Success\"},{\"assignedDepartment\":\"ColdRoomDepartment\",\"errorLog\":\"\",\"productName\":\"2\","
              "\"status\":\"Success\"},{\"assignedDepartment\":\"ColdRoomDepartment\",\"errorLog\":\"\",\"productName\":\"3\","
              "\"status\":\"Success\"}]}");

    EXPECT_EQ(warehouse.getOccupancyReport(),
              "{\"departmentsOccupancy\":[{\"departmentName\":\"ColdRoomDepartment\",\"maxOccupancy\":10,\"occupancy\":8}]}");
    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"AstronautsIceCream\"}]}");
        EXPECT_EQ(order.products.back().get(), productsRawPtrs[0]);
    }

    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"AstronautsIceCream\"}]}");
        EXPECT_EQ(order.products.back().get(), productsRawPtrs[1]);
    }
    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"AstronautsIceCream\"}]}");
        EXPECT_EQ(order.products.back().get(), productsRawPtrs[2]);
    }
    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"AstronautsIceCream\"}]}");
        EXPECT_EQ(order.products.back().get(), productsRawPtrs[3]);
        EXPECT_EQ(
                warehouse.getOccupancyReport(),
                "{\"departmentsOccupancy\":[{\"departmentName\":\"ColdRoomDepartment\",\"maxOccupancy\":10,\"occupancy\":0}]}");
    }
    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"AstronautsIceCream\"}]}");
        EXPECT_EQ(order.products.size(), 0);
    }
}

TEST(WarehouseTest, ProductAll)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<SpecialDepartment>(1000.0));
    warehouse.addDepartment(std::make_unique<ColdRoomDepartment>(1000.0));
    warehouse.addDepartment(std::make_unique<HazardousDepartment>(1000.0));
    warehouse.addDepartment(std::make_unique<SmallElectronicDepartment>(1000.0));
    warehouse.addDepartment(std::make_unique<OverSizeElectronicDepartment>(1000.0));

    std::vector<warehouseInterface::IProductPtr> products{};
    std::vector<warehouseInterface::IProduct *> productsRawPtrs{};

    products.push_back(productFactory.createProduct("GlassWare", "Glass Plate", 0.5f));
    productsRawPtrs.push_back(products.back().get());
    products.push_back(productFactory.createProduct("ElectronicParts", "Transistor", 0.5f));
    productsRawPtrs.push_back(products.back().get());
    products.push_back(productFactory.createProduct("IndustrialServerRack", "Server Rack", 6.0f));
    productsRawPtrs.push_back(products.back().get());
    products.push_back(productFactory.createProduct("AcetoneBarrel", "1 gal", 50.0f));
    productsRawPtrs.push_back(products.back().get());
    products.push_back(productFactory.createProduct("ExplosiveBarrel", "100l", 100.0f));
    productsRawPtrs.push_back(products.back().get());
    products.push_back(productFactory.createProduct("TV", "Brave", 40.0f));
    productsRawPtrs.push_back(products.back().get());
    products.push_back(productFactory.createProduct("AstronautsIceCream", "2", 2.0f));
    productsRawPtrs.push_back(products.back().get());

    EXPECT_EQ(warehouse.newDelivery(std::move(products)),
              "{\"deliveryReport\":[{\"assignedDepartment\":\"SpecialDepartment\",\"errorLog\":\"\",\"productName\":\"Glass "
              "Plate\",\"status\":\"Success\"},{\"assignedDepartment\":\"SmallElectronicDepartment\",\"errorLog\":\"\","
              "\"productName\":\"Transistor\",\"status\":\"Success\"},{\"assignedDepartment\":\"OverSizeElectronicDepartment\","
              "\"errorLog\":\"\",\"productName\":\"Server "
              "Rack\",\"status\":\"Success\"},{\"assignedDepartment\":\"HazardousDepartment\",\"errorLog\":\"\","
              "\"productName\":\"1 "
              "gal\",\"status\":\"Success\"},{\"assignedDepartment\":\"HazardousDepartment\",\"errorLog\":\"\",\"productName\":"
              "\"100l\",\"status\":\"Success\"},{\"assignedDepartment\":\"SpecialDepartment\",\"errorLog\":\"\","
              "\"productName\":\"Brave\",\"status\":\"Success\"},{\"assignedDepartment\":\"ColdRoomDepartment\",\"errorLog\":"
              "\"\",\"productName\":\"2\",\"status\":\"Success\"}]}");

    EXPECT_EQ(warehouse.getOccupancyReport(),
              "{\"departmentsOccupancy\":[{\"departmentName\":\"SpecialDepartment\",\"maxOccupancy\":1000,\"occupancy\":40.5},{"
              "\"departmentName\":\"ColdRoomDepartment\",\"maxOccupancy\":1000,\"occupancy\":2},{\"departmentName\":"
              "\"HazardousDepartment\",\"maxOccupancy\":1000,\"occupancy\":150},{\"departmentName\":"
              "\"SmallElectronicDepartment\",\"maxOccupancy\":1000,\"occupancy\":0.5},{\"departmentName\":"
              "\"OverSizeElectronicDepartment\",\"maxOccupancy\":1000,\"occupancy\":6}]}");

    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"ElectronicParts\"}]}");
        EXPECT_EQ(order.products.back().get(), productsRawPtrs[1]);
    }
    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"IndustrialServerRack\"}]}");
        EXPECT_EQ(order.products.back().get(), productsRawPtrs[2]);
    }
    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"AcetoneBarrel\"}]}");
        EXPECT_EQ(order.products.back().get(), productsRawPtrs[3]);
    }
    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"ExplosiveBarrel\"}]}");
        EXPECT_EQ(order.products.back().get(), productsRawPtrs[4]);
    }
    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"TV\"}]}");
        EXPECT_EQ(order.products.back().get(), productsRawPtrs[5]);
    }
    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"GlassWare\"}]}");
        EXPECT_EQ(order.products.back().get(), productsRawPtrs[0]);
    }
    {
        auto order = warehouse.newOrder("{\"order\": [{\"class\":\"AstronautsIceCream\"}]}");
        EXPECT_EQ(order.products.back().get(), productsRawPtrs[6]);
    }
}

}  // namespace warehouse