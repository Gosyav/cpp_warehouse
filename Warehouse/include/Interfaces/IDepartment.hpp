#pragma once
#include <PicoJson/picojson.h>

#include <Interfaces/Aliases.hpp>
#include <Interfaces/IProduct.hpp>
#include <MagicEnum/magic_enum.hpp>

namespace warehouseInterface
{
class IDepartment;
using IDepartmentPtr = std::unique_ptr<IDepartment>;

class IDepartment
{
protected:
    float occupancy_{};
    float maxOccupancy_{};
    float maxItemSize_{};

public:
    virtual ~IDepartment() = default;

    /**
     * @brief Adds new elements to department space if possible.
     * @return Return true if the item size meets department conditions and added item pointer is not nullptr, false otherwise.
     */
    virtual bool addItem(IProductPtr) = 0;

    /**
     * @brief Gets new elements from the department if possible. Only the class and name of the requested product should be
     * considered in object finding. If only a class or name is specified, the other parameter should be skipped in object
     * finding.
     * @return Return a valid pointer if the object exists and is accessible in the department, nullptr otherwise.
     */
    virtual IProductPtr getItem(const ProductDescriptionJson &) = 0;

    /**
     * @brief Get the actual occupancy of the department.
     * @return A float representing the occupancy of the department.
     */
    virtual float getOccupancy() const = 0;

    /**
     * @brief Get the maximal occupancy of the department.
     * @return A float representing the maximal occupancy of the department.
     */
    virtual float getMaxOccupancy() const = 0;

    /**
     * @brief Get the maximal element size that can be stored in the department.
     * @return A float representing the maximal element size that can be stored in the department.
     */
    virtual float getMaxItemSize() const = 0;

    /**
     * @brief Get the flags associated with the department.
     * @return A ProductLabelFlags enum value representing all the flags associated with the products that can be stored in the
     * department.
     */
    virtual ProductLabelFlags getSupportedFlags() const = 0;

    /**
     * @brief The function converts department parameters and stored objects to JSON object.
     * @return A JSON representing the department.
     */
    virtual picojson::object asJson() const = 0;

    /**
     * @brief Serialize the department to a JSON string.
     * @return A JSON string representing the serialized department.
     */
    virtual DepartmentStateJson serialize() const = 0;

    /**
     * @brief The function converts stored objects in deparments to JSON array object.
     * @return A JSON array representing the department objects.
     */
    virtual picojson::array serializedItems() const = 0;

    /**
     * @brief Get the department class name.
     * @return A string representing the department class name.
     */
    virtual std::string departmentName() const = 0;
};

}  // namespace warehouseInterface
