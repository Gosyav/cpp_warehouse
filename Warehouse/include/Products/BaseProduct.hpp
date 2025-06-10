#pragma once

#include <PicoJson/picojson.h>

#include <Interfaces/IProduct.hpp>
#include <string>

namespace warehouse
{

/**
 * @brief Base class for all warehouse products
 *
 * Provides common functionality for all products including:
 * - Name and size management
 * - Product flags handling
 * - JSON serialization
 */
class BaseProduct : public warehouseInterface::IProduct
{
protected:
    std::string _name;                             ///< Product name
    float _size;                                   ///< Product size
    warehouseInterface::ProductLabelFlags _flags;  ///< Product flags

public:
    /**
     * @brief Construct a new Base Product
     * @param name Product name
     * @param size Product size
     * @param flags Product flags
     */
    BaseProduct(const std::string &name, float size, warehouseInterface::ProductLabelFlags flags) :
            _name(name), _size(size), _flags(flags)
    {}

    std::string name() const override { return _name; }
    float itemSize() const override { return _size; }
    warehouseInterface::ProductLabelFlags itemFlags() const override { return _flags; }

    picojson::object asJson() const override
    {
        picojson::object obj;
        obj["name"] = picojson::value(_name);
        obj["size"] = picojson::value(_size);

        picojson::array flagsArray;
        const auto flags = static_cast<int>(_flags);

        // Check each flag and add to array if set
        if (flags & static_cast<int>(warehouseInterface::ProductLabelFlags::fragile))
            flagsArray.push_back(picojson::value("fragile"));
        if (flags & static_cast<int>(warehouseInterface::ProductLabelFlags::keepDry))
            flagsArray.push_back(picojson::value("keepDry"));
        if (flags & static_cast<int>(warehouseInterface::ProductLabelFlags::keepFrozen))
            flagsArray.push_back(picojson::value("keepFrozen"));
        if (flags & static_cast<int>(warehouseInterface::ProductLabelFlags::esdSensitive))
            flagsArray.push_back(picojson::value("esdSensitive"));
        if (flags & static_cast<int>(warehouseInterface::ProductLabelFlags::fireHazardous))
            flagsArray.push_back(picojson::value("fireHazardous"));
        if (flags & static_cast<int>(warehouseInterface::ProductLabelFlags::explosives))
            flagsArray.push_back(picojson::value("explosives"));
        if (flags & static_cast<int>(warehouseInterface::ProductLabelFlags::handleWithCare))
            flagsArray.push_back(picojson::value("handleWithCare"));
        if (flags & static_cast<int>(warehouseInterface::ProductLabelFlags::upWard))
            flagsArray.push_back(picojson::value("upWard"));

        obj["flags"] = picojson::value(flagsArray);
        return obj;
    }

    warehouseInterface::ProductDescriptionJson serialize() const override
    {
        picojson::object obj = asJson();
        obj["class"] = picojson::value(getClassName());
        return picojson::value(obj).serialize();
    }

    /**
     * @brief Get the class name of the product
     * @return String containing the product's class name
     */
    virtual std::string getClassName() const = 0;
};

}  // namespace warehouse