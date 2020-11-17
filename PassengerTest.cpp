/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <string>

#include "../src/passenger_loader.h"
#include "../src/passenger_unloader.h"
#include "../src/passenger.h"
#include "../src/stop.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class PassengerTests : public ::testing::Test {
protected:
    PassengerLoader* pass_loader;
    PassengerUnloader* pass_unloader;
    Passenger* passenger, * passenger1, * passenger2;

    virtual void SetUp() {
        pass_loader = new PassengerLoader();
        pass_unloader = new PassengerUnloader();
    }

    virtual void TearDown() {
        delete pass_loader;
        delete pass_unloader;
        delete passenger;
        passenger = NULL;
        pass_loader = NULL;
        pass_unloader = NULL;
    }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(PassengerTests, Constructor) {
    passenger = new Passenger();
    EXPECT_EQ(passenger->IsOnBus(), false);
    passenger->GetOnBus();
    EXPECT_EQ(passenger->IsOnBus(), true);
};

// Tests for Update

TEST_F(PassengerTests, TimeOnBus) {
    passenger1->GetOnBus();
    int i = 0;
    while ( i < 10) {
        passenger1->Update();
    }
    EXPECT_EQ(passenger1->GetTotalWait(), 11);
};
TEST_F(PassengerTests, TimeWaiting) {
   
    int i = 0;
    while (i < 10) {
        passenger1->Update();
    }
    EXPECT_EQ(passenger1->GetTotalWait(), 11);
};

//Test for GetTotalWait

TEST_F(PassengerTests, GetTotalWait) {
    EXPECT_EQ(passenger->GetTotalWait(), 0);
};

TEST_F(PassengerTests, GetDestinationID) {
    passenger1 = new Passenger(20, "Joe");
    passenger2 = new Passenger(22, "Mira");
    
    EXPECT_EQ(passenger1->GetDestination(), 20);
    EXPECT_EQ(passenger2->GetDestination(), 22);
};


TEST_F(PassengerTests, NameCheck) {
    passenger1 = new Passenger(12, "John Doe");
    passenger2 = new Passenger(12, "Apple Bee");
    std::string expected_output_1 = "Name: John Doe";
    std::string expected_output_2 = "Name: Apple Bee";
    testing::internal::CaptureStdout();
    passenger1->Report(std::cout);
    std::string output1 = testing::internal::GetCapturedStdout();
    testing::internal::CaptureStdout();
    passenger2->Report(std::cout);
    std::string output2 = testing::internal::GetCapturedStdout();
    int p1 = output1.find(expected_output_1);
    int p2 = output2.find(expected_output_2);
    EXPECT_GE(p1, 0);
    EXPECT_GE(p2, 0);
};



