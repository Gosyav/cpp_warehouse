#pragma once
#include <Interfaces/IDepartment.hpp>
#include <Interfaces/IProduct.hpp>

namespace warehouseInterface
{
class IWarehouse
{
protected:
    std::vector<IDepartmentPtr> departments_{};

public:
    virtual ~IWarehouse() = default;

    /**
     * @brief Adds new department to warehouse.
     * @return None.
     */
    virtual void addDepartment(IDepartmentPtr) = 0;

    /**
     * @brief Adds new elements to the warehouse. The warehouse should check if the proper departments exist and if there is
     * enough space to store new products. Delivered products should be stored in the very first department which can store the
     * particular product type and which has enough space.
     * @return Delivery report - a serialized JSON string that contains information about the delivery state of every single
     * product from the delivery vector.
     */
    virtual DeliveryReportJson newDelivery(std::vector<IProductPtr>) = 0;

    /**
     * @brief Iterates over requested products (as serialized JSON object) and checks if every product exists in one of the
     * available departments (using the department getItem method). If a product exists, it is added to the product vector.
     * @return Order - see Order struct definition in Warehouse/include/Interfaces/IProduct.hpp.
     */
    virtual Order newOrder(const OrderJson &) = 0;

    /**
     * @brief Gets the warehouse occupancy report.
     * @return Warehouse occupancy as serialized JSON object.
     */
    virtual OccupancyReportJson getOccupancyReport() const = 0;

    /**
     * @brief Saves the warehouse state (departments with their products) to serialized JSON structure.
     * @return Warehouse state as serialized JSON object.
     */
    virtual WarehouseStateJson saveWarehouseState() const = 0;

    /**
     * @brief Creates warehouse (adds departments with their products) based on saved warehouse state.
     * @return true if the saved warehouse state is valid (contains all required fields), false otherwise.
     */
    virtual bool loadWarehouseState(const WarehouseStateJson &) = 0;
};
}  // namespace warehouseInterface