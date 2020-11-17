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
#include "../src/passenger_generator.h"
#include "../src/random_passenger_generator.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class BusTests : public ::testing::Test {
protected:
    PassengerLoader* pass_loader;
    PassengerUnloader* pass_unloader;
    Bus* myBus;
    Passenger *passenger1, * passenger2;
    std::list<Passenger*> passengers;
    Stop** stops;
    virtual void SetUp() {
        pass_loader = new PassengerLoader();
        pass_unloader = new PassengerUnloader();

        passengers= { passenger1,passenger2 };

        std::string BusName = "bus";
        std::string RouteName = "myroute";
        double* distances = new double[3];
        for (int i = 0; i < 3; i++) {
            distances[i] = 3.0;
        }
        stops = new Stop * [3];
        for (int i = 0; i < 3; i++) {
            stops[i] = new Stop(i, 44.97, -93.2);
        }
        std::list<Stop*> stopList;
        for (int i = 0; i < 3; i++) {
            stopList.push_back(stops[i]);
        }
        int numStops = 3;
        std::list<double> probs = { 0.5,0.5,0.5 };
        RandomPassengerGenerator* myGenerator = new RandomPassengerGenerator(probs, stopList);
        Route* in = new Route(RouteName, stops, distances, numStops, myGenerator);

        Route* out = in->Clone();


        Bus* myBus = new Bus(BusName, out, in, 60, 3.0);

    }

    virtual void TearDown() {
        delete pass_loader;
        delete pass_unloader;
        delete myBus;
        myBus = NULL;
        pass_loader = NULL;
        pass_unloader = NULL;
    }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(BusTests, Constructor) {
    //Bus bus = new Bus();
    EXPECT_EQ(myBus->Move(), false);
    myBus->Move();
    EXPECT_EQ(myBus->Move(), true);
};

TEST_F(BusTests, IsTripComplete) {
    EXPECT_EQ(myBus->IsTripComplete(), false);
    myBus->Move();
    myBus->Move();
    myBus->Move();
    EXPECT_EQ(myBus->IsTripComplete(), true);
};

TEST_F(BusTests, LoadPassenger) {

    EXPECT_EQ(myBus->LoadPassenger(passenger1) , true);
};

TEST_F(BusTests, UnloadPassenger) {
    //Bus bus = new Bus();
    myBus->LoadPassenger(passenger1);
    myBus->LoadPassenger(passenger2);
    EXPECT_EQ(pass_unloader->UnloadPassengers(passengers,stops[0]), 1);
};

TEST_F(BusTests, Move) {
    //Bus bus = new Bus();

    EXPECT_EQ(myBus->LoadPassenger(passenger1), 1);
};

TEST_F(BusTests, Report) {
    std::string expected_output_1 = "myBus";
    testing::internal::CaptureStdout();
    myBus->Report(std::cout);
    std::string output1 = testing::internal::GetCapturedStdout();
    int p1 = output1.find(expected_output_1);
    EXPECT_GE(p1, 0);
    
};
