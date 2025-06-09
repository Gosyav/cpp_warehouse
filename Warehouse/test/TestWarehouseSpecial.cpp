
#include <PicoJson/picojson.h>
#include <Warehouse/Warehouse.h>
#include <gtest/gtest.h>

#include <Departments/DepartmentsList.hpp>
#include <Factory/ProductFactory.hpp>
#include <Products/ProductsList.hpp>
#include <iostream>

namespace warehouse
{
TEST(WarehouseTest, ProductNotFound)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<SmallElectronicDepartment>(1000.0));

    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("ElectronicParts", "MacBook Pro", 2.0f));
    products.emplace_back(productFactory.createProduct("ElectronicParts", "Dell XPS", 2.0f));
    EXPECT_EQ(warehouse.newDelivery(std::move(products)),
              "{\"deliveryReport\":[{\"assignedDepartment\":\"SmallElectronicDepartment\",\"errorLog\":\"\",\"productName\":"
              "\"MacBook "
              "Pro\",\"status\":\"Success\"},{\"assignedDepartment\":\"SmallElectronicDepartment\",\"errorLog\":\"\","
              "\"productName\":\"Dell XPS\",\"status\":\"Success\"}]}");

    auto order = warehouse.newOrder("{'class':'ElectronicParts','name':'Lenovo ThinkPad'}");
    EXPECT_EQ(order.products.size(), 0);
    EXPECT_EQ(warehouse.getOccupancyReport(),
              "{\"departmentsOccupancy\":[{\"departmentName\":\"SmallElectronicDepartment\",\"maxOccupancy\":1000,"
              "\"occupancy\":4}]}");
}

TEST(WarehouseTest, ProductCannotBeStored)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<SmallElectronicDepartment>(3.0));

    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("ElectronicParts", "MacBook Pro", 2.0f));
    products.emplace_back(productFactory.createProduct("ElectronicParts", "Dell XPS", 2.0f));
    products.emplace_back(productFactory.createProduct("ExplosiveBarrel", "Explosive Barrel", 100.0f));

    EXPECT_EQ(warehouse.newDelivery(std::move(products)),
              "{\"deliveryReport\":[{\"assignedDepartment\":\"SmallElectronicDepartment\",\"errorLog\":\"\",\"productName\":"
              "\"MacBook Pro\",\"status\":\"Success\"},{\"assignedDepartment\":\"None\",\"errorLog\":\"Warehouse cannot store "
              "this product. Lack of space in departments.\",\"productName\":\"Dell "
              "XPS\",\"status\":\"Fail\"},{\"assignedDepartment\":\"None\",\"errorLog\":\"Warehouse cannot store this product. "
              "Lack of required department.\",\"productName\":\"Explosive Barrel\",\"status\":\"Fail\"}]}");
}

TEST(WarehouseTest, saveLoad)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<SpecialDepartment>(1000.0));
    warehouse.addDepartment(std::make_unique<ColdRoomDepartment>(1000.0));
    warehouse.addDepartment(std::make_unique<HazardousDepartment>(1000.0));
    warehouse.addDepartment(std::make_unique<SmallElectronicDepartment>(1000.0));
    warehouse.addDepartment(std::make_unique<OverSizeElectronicDepartment>(1000.0));

    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("IndustrialServerRack", "Server Rack", 2.0f));
    products.emplace_back(productFactory.createProduct("GlassWare", "Glass Plate", 0.5f));
    products.emplace_back(productFactory.createProduct("ElectronicParts", "Transistor", 0.5f));
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "0", 2.0f));
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "1", 2.0f));
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "2", 2.0f));
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "3", 2.0f));
    products.emplace_back(productFactory.createProduct("GlassWare", "Glass Plate", 0.5f));
    products.emplace_back(productFactory.createProduct("ElectronicParts", "Transistor", 0.5f));
    products.emplace_back(productFactory.createProduct("ElectronicParts", "STM", 6.0f));
    products.emplace_back(productFactory.createProduct("IndustrialServerRack", "Server Rack", 2.0f));
    products.emplace_back(productFactory.createProduct("AcetoneBarrel", "1 gal", 50.0f));
    products.emplace_back(productFactory.createProduct("ExplosiveBarrel", "100l", 100.0f));
    products.emplace_back(productFactory.createProduct("TV", "Brave", 40.0f));
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "2", 2.0f));
    warehouse.newDelivery(std::move(products));

    EXPECT_EQ(warehouse.saveWarehouseState(),
              "{\"warehouseState\":[{\"class\":\"SpecialDepartment\",\"items\":[{\"class\":\"GlassWare\",\"flags\":["
              "\"fragile\",\"upWard\"],\"name\":\"Glass "
              "Plate\",\"size\":0.5},{\"class\":\"GlassWare\",\"flags\":[\"fragile\",\"upWard\"],\"name\":\"Glass "
              "Plate\",\"size\":0.5},{\"class\":\"TV\",\"flags\":[\"fragile\",\"keepDry\"],\"name\":\"Brave\",\"size\":40}],"
              "\"maxOccupancy\":1000,\"occupancy\":41},{\"class\":\"ColdRoomDepartment\",\"items\":[{\"class\":"
              "\"AstronautsIceCream\",\"flags\":[\"keepDry\",\"keepFrozen\"],\"name\":\"0\",\"size\":2},{\"class\":"
              "\"AstronautsIceCream\",\"flags\":[\"keepDry\",\"keepFrozen\"],\"name\":\"1\",\"size\":2},{\"class\":"
              "\"AstronautsIceCream\",\"flags\":[\"keepDry\",\"keepFrozen\"],\"name\":\"2\",\"size\":2},{\"class\":"
              "\"AstronautsIceCream\",\"flags\":[\"keepDry\",\"keepFrozen\"],\"name\":\"3\",\"size\":2},{\"class\":"
              "\"AstronautsIceCream\",\"flags\":[\"keepDry\",\"keepFrozen\"],\"name\":\"2\",\"size\":2}],\"maxOccupancy\":1000,"
              "\"occupancy\":10},{\"class\":\"HazardousDepartment\",\"items\":[{\"class\":\"AcetoneBarrel\",\"flags\":["
              "\"fireHazardous\",\"esdSensitive\"],\"name\":\"1 "
              "gal\",\"size\":50},{\"class\":\"ExplosiveBarrel\",\"flags\":[\"explosives\",\"handleWithCare\"],\"name\":"
              "\"100l\",\"size\":100}],\"maxOccupancy\":1000,\"occupancy\":150},{\"class\":\"SmallElectronicDepartment\","
              "\"items\":[{\"class\":\"IndustrialServerRack\",\"flags\":[\"upWard\",\"keepDry\",\"handleWithCare\","
              "\"esdSensitive\"],\"name\":\"Server "
              "Rack\",\"size\":2},{\"class\":\"ElectronicParts\",\"flags\":[\"keepDry\",\"esdSensitive\"],\"name\":"
              "\"Transistor\",\"size\":0.5},{\"class\":\"ElectronicParts\",\"flags\":[\"keepDry\",\"esdSensitive\"],\"name\":"
              "\"Transistor\",\"size\":0.5},{\"class\":\"IndustrialServerRack\",\"flags\":[\"upWard\",\"keepDry\","
              "\"handleWithCare\",\"esdSensitive\"],\"name\":\"Server "
              "Rack\",\"size\":2}],\"maxOccupancy\":1000,\"occupancy\":5},{\"class\":\"OverSizeElectronicDepartment\","
              "\"items\":[{\"class\":\"ElectronicParts\",\"flags\":[\"keepDry\",\"esdSensitive\"],\"name\":\"STM\",\"size\":6}]"
              ",\"maxOccupancy\":1000,\"occupancy\":6}]}");

    auto save = warehouse.saveWarehouseState();
    {
        Warehouse warehouse2{};
        warehouse2.loadWarehouseState(save);
        EXPECT_EQ(warehouse2.saveWarehouseState(), save);
    }
}
}  // namespace warehouse