#include <gtest/gtest.h>
#include <stdio.h>
#include <POSTerminal.h>

GTEST_API_ int main(int argc, char **argv)
{
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST (POSTerminalTest, EmptyTerminal)
{
    POSTerminal posTerm; 
    EXPECT_DOUBLE_EQ(posTerm.getTotal(), 0.0);
}

TEST (POSTerminalTest, OnlyPricingTable)
{
    POSTerminal posTerm; 
    posTerm.setPrice('A', 1.2, 10, 10.0);
    posTerm.setPrice('B', 2.2, 10, 21.0);
    EXPECT_DOUBLE_EQ(posTerm.getTotal(), 0.0);
}

TEST (POSTerminalTest, OnlyScanNoPricingTable)
{
    POSTerminal posTerm; 
    posTerm.scanItem('A');
    posTerm.scanItem('A');
    posTerm.scanItem('A');
    EXPECT_DOUBLE_EQ(posTerm.getTotal(), 0.0);
}

TEST (POSTerminalTest, SimpleLooseUnits)
{
    POSTerminal posTerm; 
    posTerm.setPrice('A', 1.2, 10, 10.0);
    posTerm.scanItem('A');
    EXPECT_DOUBLE_EQ(posTerm.getTotal(), 1.2);
    posTerm.scanItem('A');
    EXPECT_DOUBLE_EQ(posTerm.getTotal(), 2.4);
}

TEST (POSTerminalTest, BoundaryUnitAndVolumeQuantities)
{
    POSTerminal posTerm; 
    posTerm.setPrice('A', 1.2, 4, 4.0);

    posTerm.scanItem('A');
    posTerm.scanItem('A');
    posTerm.scanItem('A');
    EXPECT_DOUBLE_EQ(posTerm.getTotal(), 3.6); //3 items loose

    posTerm.scanItem('A');
    EXPECT_DOUBLE_EQ(posTerm.getTotal(), 4.0); //4 items 1 volume

    posTerm.scanItem('A');
    EXPECT_DOUBLE_EQ(posTerm.getTotal(), 5.2); //5 items 1 volume + 1 loose
}

class POSTerminalInputTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            d_posTerm.setPrice('A', 2.0, 4, 7.0);
            d_posTerm.setPrice('B', 12.0, 0, 0.0);
            d_posTerm.setPrice('C', 1.25, 6, 6.0);
            d_posTerm.setPrice('D', 0.15, 0, 0.0);
        }

        //virtual void TearDown() {}

        POSTerminal d_posTerm; 
};


TEST_F (POSTerminalInputTest, RequestedInput1)
{
    d_posTerm.scanMultipleItems("ABCDABAA");
    EXPECT_DOUBLE_EQ(d_posTerm.getTotal(), 32.40);
}

TEST_F (POSTerminalInputTest, RequestedInput2)
{
    d_posTerm.scanMultipleItems("CCCCCCC");
    EXPECT_DOUBLE_EQ(d_posTerm.getTotal(), 7.25);
}

TEST_F (POSTerminalInputTest, RequestedInput3)
{
    d_posTerm.scanMultipleItems("ABCD");
    EXPECT_DOUBLE_EQ(d_posTerm.getTotal(), 15.40);
}

// vim:tw=78:ts=4:ft=cpp:et:


