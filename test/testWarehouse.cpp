
#include "include/catch.hpp"
#include "../src/include/warehouse.hpp"
#include "../src/include/employee.hpp"
#include "../src/include/pallet.hpp"
#include "../src/include/shelf.hpp"
#include <iostream>

///////////////////////////////////////////////////////////////
//                                                           //
//                    Warehouse unittests                    //
//                                                           //
///////////////////////////////////////////////////////////////
//                                                           //
// This file contains all testcases for the Warehouse class. //
// Currently it only contains tests for the rearranging of   //
// shelves. All other Warehouse functions will also need to  //
// be tested. You will have to do this yourself.             //
//                                                           //
// For information on how to write testcases with catch2,    //
// see https://github.com/catchorg/Catch2.                   //
//                                                           //
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
//                Functions used in testcases                //
///////////////////////////////////////////////////////////////

/// \brief
/// Creates a mock Warehouse.
/// \return Warehouse with shelf of books.
/// \details
/// Creates a Warehouse with 3 unsorted shelves with a total of 100 Books, 60 Boxes, and 60 Toy Bears.
/// \n Adds forklift certified employee Bob.
/// \n This function can be used in testcases to avoid the repeated construction of Warehouse objects.
Warehouse createMockWarehouse(){
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
            Pallet("Books", 100, 40),
            Pallet("Boxes", 100, 10),
            Pallet("Books", 100, 20),
            Pallet("Books", 100, 20)
    };

    Shelf shelf2 = Shelf();
    shelf2.pallets = {
            Pallet("Books", 100, 15),
            Pallet("Boxes", 100, 20),
            Pallet("Books", 100, 5),
            Pallet("Boxes", 100, 30)
    };

    Shelf shelf3 = Shelf();
    shelf3.pallets = {
            Pallet("Toy Bears", 100, 20),
            Pallet("Toy Bears", 100, 10),
            Pallet(),
            Pallet("Toy Bears", 100, 30)
    };

    warehouse.shelf_add(shelf1);
    warehouse.shelf_add(shelf2);
    warehouse.shelf_add(shelf3);

    warehouse.employee_add(Employee("Bob", true));

    return warehouse;
}


///////////////////////////////////////////////////////////////
//           Warehouse::shelf_rearrange test cases            //
///////////////////////////////////////////////////////////////

TEST_CASE("Rearrange empty shelf", "Warehouse::shelf_rearrange"){
    // Construct empty warehouse and add empty shelf and forklift certified Employee.
    Warehouse warehouse = Warehouse();
    warehouse.shelf_add(Shelf());
    warehouse.employee_add(Employee("Bob", true));

    // Check if shelf is already arranged.
    // Empty shelf should already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].get_item_count() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].get_item_count() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].get_item_count() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].get_item_count() == 0);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.shelf_rearrange(warehouse.shelves[0]);
    // Should be successful
    REQUIRE(successful);

    // Check if shelf is now correctly arranged.
    // Empty shelf should still be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].get_item_count() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].get_item_count() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].get_item_count() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].get_item_count() == 0);
}

TEST_CASE("Rearrange full shelf", "Warehouse::shelf_rearrange"){
    // Construct warehouse with unsorted shelf of books.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
            Pallet("Books", 100, 20),
            Pallet("Books", 100, 40),
            Pallet("Books", 100, 30),
            Pallet("Books", 100, 10)
    };

    warehouse.employee_add(Employee("Bob", true));
    warehouse.shelf_add(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].get_item_count() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].get_item_count() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].get_item_count() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].get_item_count() == 10);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.shelf_rearrange(warehouse.shelves[0]);
    // Should be successful
    REQUIRE(successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].get_item_count() == 10);
    REQUIRE(warehouse.shelves[0].pallets[1].get_item_count() == 20);
    REQUIRE(warehouse.shelves[0].pallets[2].get_item_count() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].get_item_count() == 40);
}

TEST_CASE("Rearrange half filled shelf", "Warehouse::shelf_rearrange"){
    // Construct empty warehouse and unsorted shelf of books.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
            Pallet("Books", 100, 40),
            Pallet("Books", 100, 20),
            Pallet(),
            Pallet()
    };

    warehouse.employee_add(Employee("Bob", true));
    warehouse.shelf_add(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].get_item_count() == 40);
    REQUIRE(warehouse.shelves[0].pallets[1].get_item_count() == 20);
    REQUIRE(warehouse.shelves[0].pallets[2].get_item_count() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].get_item_count() == 0);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.shelf_rearrange(warehouse.shelves[0]);
    // Should be successful
    REQUIRE(successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].get_item_count() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].get_item_count() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].get_item_count() == 20);
    REQUIRE(warehouse.shelves[0].pallets[3].get_item_count() == 40);
}

TEST_CASE("Rearrange shelf without qualified employee", "Warehouse::shelf_rearrange"){
    // Construct warehouse with unsorted shelf of books.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
            Pallet("Books", 100, 20),
            Pallet("Books", 100, 40),
            Pallet("Books", 100, 30),
            Pallet("Books", 100, 10)
    };

    warehouse.employee_add(Employee("Bert", false));
    warehouse.shelf_add(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].get_item_count() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].get_item_count() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].get_item_count() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].get_item_count() == 10);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.shelf_rearrange(warehouse.shelves[0]);
    // Should fail
    REQUIRE(!successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now still not be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].get_item_count() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].get_item_count() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].get_item_count() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].get_item_count() == 10);
}

TEST_CASE("Rearrange shelf with quallified, but busy, employee", "Warehouse::shelf_rearrange"){
    // Construct warehouse with unsorted shelf of books.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
            Pallet("Books", 100, 20),
            Pallet("Books", 100, 40),
            Pallet("Books", 100, 30),
            Pallet("Books", 100, 10)
    };

    Employee bert = Employee("Bert", true);
    bert.set_busy(true);

    warehouse.employee_add(bert);
    warehouse.shelf_add(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].get_item_count() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].get_item_count() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].get_item_count() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].get_item_count() == 10);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.shelf_rearrange(warehouse.shelves[0]);
    // Should fail
    REQUIRE(!successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now still not be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].get_item_count() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].get_item_count() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].get_item_count() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].get_item_count() == 10);
}

