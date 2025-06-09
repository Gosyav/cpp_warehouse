
#include <PicoJson/picojson.h>
#include <gtest/gtest.h>

#include <Products/ProductsList.hpp>
#include <iostream>

namespace warehouse
{
TEST(TVTest, SerializesToJson)
{
    warehouse::TV tv("Sony Bravia", 50.0f);

    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, tv.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Sony Bravia");
    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Sony Bravia");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), "[\"fragile\",\"keepDry\"]");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "TV");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 50.0);
}

TEST(TVTest, ReturnsCorrectFlags)
{
    warehouse::TV tv("Sony Bravia", 50.0f);
    auto flags = tv.itemFlags();

    using namespace magic_enum::bitwise_operators;
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::fragile) == warehouseInterface::ProductLabelFlags::fragile);
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::keepDry) == warehouseInterface::ProductLabelFlags::keepDry);
}

TEST(TVTest, NameAndSizeTest)
{
    const std::string name{"Sony Bravia"};
    const float size{50.0};

    warehouse::TV tv{name, size};
    EXPECT_EQ(tv.name(), name);
    EXPECT_EQ(tv.itemSize(), size);
}

TEST(AcetoneBarrelTest, SerializesToJson)
{
    AcetoneBarrel barrel("Acetone Barrel", 200.0f);

    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, barrel.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Acetone Barrel");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), "[\"fireHazardous\",\"esdSensitive\"]");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "AcetoneBarrel");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 200.0);
}

TEST(AcetoneBarrelTest, ReturnsCorrectFlags)
{
    AcetoneBarrel barrel("Acetone Barrel", 200.0f);
    auto flags = barrel.itemFlags();

    using namespace magic_enum::bitwise_operators;
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::fireHazardous) ==
                warehouseInterface::ProductLabelFlags::fireHazardous);
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::esdSensitive) ==
                warehouseInterface::ProductLabelFlags::esdSensitive);
}

TEST(AcetoneBarrelTest, NameAndSizeTest)
{
    const std::string name{"Acetone Barrel"};
    const float size{200.0};

    AcetoneBarrel barrel{name, size};
    EXPECT_EQ(barrel.name(), name);
    EXPECT_EQ(barrel.itemSize(), size);
}

TEST(AstronautsIceCreamTest, SerializesToJson)
{
    warehouse::AstronautsIceCream astronautsIceCream("Chocolate", 0.5f);

    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, astronautsIceCream.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Chocolate");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), "[\"keepDry\",\"keepFrozen\"]");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "AstronautsIceCream");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 0.5f);
}

TEST(AstronautsIceCreamTest, ReturnsCorrectFlags)
{
    warehouse::AstronautsIceCream astronautsIceCream("Vanilla", 0.5f);
    auto flags = astronautsIceCream.itemFlags();

    using namespace magic_enum::bitwise_operators;
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::keepFrozen) ==
                warehouseInterface::ProductLabelFlags::keepFrozen);
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::keepDry) == warehouseInterface::ProductLabelFlags::keepDry);
}

TEST(AstronautsIceCreamTest, NameAndSizeTest)
{
    const std::string name{"Strawberry"};
    const float size{1.5f};

    warehouse::AstronautsIceCream astronautsIceCream{name, size};
    EXPECT_EQ(astronautsIceCream.name(), name);
    EXPECT_EQ(astronautsIceCream.itemSize(), size);
}

TEST(ElectronicPartsTest, SerializesToJson)
{
    ElectronicParts electronicParts("Resistor", 0.01f);

    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, electronicParts.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Resistor");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), "[\"keepDry\",\"esdSensitive\"]");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "ElectronicParts");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 0.01f);
}

TEST(ElectronicPartsTest, ReturnsCorrectFlags)
{
    ElectronicParts electronicParts("Resistor", 0.01f);
    auto flags = electronicParts.itemFlags();

    using namespace magic_enum::bitwise_operators;
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::keepDry) == warehouseInterface::ProductLabelFlags::keepDry);
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::esdSensitive) ==
                warehouseInterface::ProductLabelFlags::esdSensitive);
}

TEST(ElectronicPartsTest, NameAndSizeTest)
{
    const std::string name{"Resistor"};
    const float size{0.01f};

    ElectronicParts electronicParts{name, size};
    EXPECT_EQ(electronicParts.name(), name);
    EXPECT_EQ(electronicParts.itemSize(), size);
}
TEST(ExplosiveBarrelTest, SerializesToJson)
{
    warehouse::ExplosiveBarrel explosiveBarrel("TNT", 1.5f);

    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, explosiveBarrel.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "TNT");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), "[\"explosives\",\"handleWithCare\"]");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "ExplosiveBarrel");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 1.5f);
}

TEST(ExplosiveBarrelTest, ReturnsCorrectFlags)
{
    warehouse::ExplosiveBarrel explosiveBarrel("Dynamite", 2.5f);
    auto flags = explosiveBarrel.itemFlags();

    using namespace magic_enum::bitwise_operators;
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::explosives) ==
                warehouseInterface::ProductLabelFlags::explosives);
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::handleWithCare) ==
                warehouseInterface::ProductLabelFlags::handleWithCare);
}

TEST(ExplosiveBarrelTest, NameAndSizeTest)
{
    const std::string name{"C4"};
    const float size{3.5f};

    warehouse::ExplosiveBarrel explosiveBarrel{name, size};
    EXPECT_EQ(explosiveBarrel.name(), name);
    EXPECT_EQ(explosiveBarrel.itemSize(), size);
}
TEST(GlassWareTest, SerializesToJson)
{
    warehouse::GlassWare glassWare("Wine Glass", 0.2f);

    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, glassWare.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Wine Glass");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), "[\"fragile\",\"upWard\"]");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "GlassWare");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 0.2f);
}

TEST(GlassWareTest, ReturnsCorrectFlags)
{
    warehouse::GlassWare glassWare("Water Glass", 0.1f);
    auto flags = glassWare.itemFlags();

    using namespace magic_enum::bitwise_operators;
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::fragile) == warehouseInterface::ProductLabelFlags::fragile);
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::upWard) == warehouseInterface::ProductLabelFlags::upWard);
}

TEST(GlassWareTest, NameAndSizeTest)
{
    const std::string name{"Beer Glass"};
    const float size{0.3f};

    warehouse::GlassWare glassWare{name, size};
    EXPECT_EQ(glassWare.name(), name);
    EXPECT_EQ(glassWare.itemSize(), size);
}

TEST(IndustrialServerRackTest, SerializesToJson)
{
    warehouse::IndustrialServerRack rack("Rack01", 2.5f);

    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, rack.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Rack01");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), "[\"upWard\",\"keepDry\",\"handleWithCare\",\"esdSensitive\"]");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "IndustrialServerRack");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 2.5f);
}

TEST(IndustrialServerRackTest, ReturnsCorrectFlags)
{
    warehouse::IndustrialServerRack rack("Rack02", 3.0f);
    auto flags = rack.itemFlags();

    using namespace magic_enum::bitwise_operators;
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::handleWithCare) ==
                warehouseInterface::ProductLabelFlags::handleWithCare);
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::esdSensitive) ==
                warehouseInterface::ProductLabelFlags::esdSensitive);
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::upWard) == warehouseInterface::ProductLabelFlags::upWard);
    EXPECT_TRUE((flags & warehouseInterface::ProductLabelFlags::keepDry) == warehouseInterface::ProductLabelFlags::keepDry);
}

TEST(IndustrialServerRackTest, NameAndSizeTest)
{
    const std::string name{"Rack03"};
    const float size{4.0f};

    warehouse::IndustrialServerRack rack{name, size};
    EXPECT_EQ(rack.name(), name);
    EXPECT_EQ(rack.itemSize(), size);
}

}  // namespace warehouse