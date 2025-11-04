#include "villageRNG_Interface.h"
#include <gtest/gtest.h>

#include "raylib.h"

// Generates a reasonably "random" seed using raylib time and system randomness.
static int GenerateSeed() {
    // Combine raylib's time and the standard C random source
    double t = GetTime();
    int systemPart = static_cast<int>(time(nullptr)); // seconds since epoch
    int raylibPart = static_cast<int>(t * 1000000.0); // microsecond-ish resolution
    return (systemPart ^ raylibPart) & 0x7FFFFFFF; // keep positive 31-bit seed
}

TEST(VillageRNGTest, BasicUsage) {
    auto rng = GetVillageRNGInterface();

    // Check default name
    EXPECT_EQ(rng->name(), "Unamed");

    // Set a new name and check
    rng->name("MyRNG");
    EXPECT_EQ(rng->name(), "MyRNG");

    // Call next() and next(min,max) to make sure they return values
    EXPECT_NO_THROW(rng->next());
    EXPECT_NO_THROW(rng->next(1, 10));

    // Check initial seed and times used
    EXPECT_EQ(rng->getSeed(), 0);
    EXPECT_EQ(rng->getNumberOfTimesUsed(), 2);
}

TEST(VillageRNGTest, FixedSeedConsistency) {
    int seed = 12345;
    auto rng1 = GetVillageRNGInterface(seed);
    auto rng2 = GetVillageRNGInterface(seed);

    // Call next several times and store results
    std::vector<int> results1;
    std::vector<int> results2;
    for (int i = 0; i < 10; ++i) {
        results1.push_back(rng1->next(0, 100));
        results2.push_back(rng2->next(0, 100));
    }

    // The sequences should be identical
    EXPECT_EQ(results1, results2);

    // Check that the number of times used matches
    EXPECT_EQ(rng1->getNumberOfTimesUsed(), 10);
    EXPECT_EQ(rng2->getNumberOfTimesUsed(), 10);
}

TEST(VillageRNGTest, AdvanceToPosition) {
    int seed = 999;
    auto rng = GetVillageRNGInterface(seed);

    // Generate first 5 numbers
    std::vector<int> firstPart;
    for (int i = 0; i < 5; ++i) {
        firstPart.push_back(rng->next(0, 100));
    }

    // Save seed and times used
    int timesUsed = rng->getNumberOfTimesUsed();

    // Generate 5 more numbers
    std::vector<int> secondPart;
    for (int i = 0; i < 5; ++i) {
        secondPart.push_back(rng->next(0, 100));
    }

    // Create a new RNG and advance it to the same position
    auto rng2 = GetVillageRNGInterface(seed);
    rng2->advanceTo(seed, timesUsed);

    // The next 5 numbers should match the second part of the first RNG
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(rng2->next(0, 100), secondPart[i]);
    }
}

TEST(VillageRNGTest, SufficientlyRandomDistribution) {
    double tollerance = 0.1; // as a Percentage so 0.2 = 20%
    
    // how many times is acceptable to get the same number in a row
    // 1123445 would be a score of 2
    // APPARENTLY the average (for 0-9 1000 times) is 99 and change with a SD of 8.91
    // so within 2 SD's is ok
    int unacceptableRepeats = 117;
    int seed = GenerateSeed();
    auto rng = GetVillageRNGInterface(seed);

    const int sampleCount = 10000;
    const int minVal = 0;
    const int maxVal = 9;
    std::array<int, 10> counts = {0};

    for (int i = 0; i < sampleCount; ++i) {
        int value = rng->next(minVal, maxVal);
        ASSERT_GE(value, minVal) << "(seed " << seed << ")";
        ASSERT_LE(value, maxVal) << "(seed " << seed << ")";
        counts[value - minVal]++;
    }

    // Each bucket should have roughly the same number of hits (±20%)
    double expected = sampleCount / 10.0;
    for (int count : counts) {
        EXPECT_NEAR(count, expected, expected * tollerance) << "(seed " << seed << ")";
    }

    // Should not be too repetitive
    rng->advanceTo(seed, 0);
    int repeats = 0;
    int last = rng->next(minVal, maxVal);
    for (int i = 1; i < 1000; ++i) {
        int val = rng->next(minVal, maxVal);
        if (val == last) repeats++;
        last = val;
    }
    EXPECT_LT(repeats, unacceptableRepeats) << "(seed " << seed << ")"; // sanity check: no excessive repetition
}

TEST(VillageRNGTest, LongestIdenticalRunIsReasonable) {
    int seed = GenerateSeed();
    auto rng = GetVillageRNGInterface(seed);

    const int sampleCount = 10000;
    const int minVal = 0;
    const int maxVal = 9;

    int longestRun = 1;
    int currentRun = 1;
    int last = rng->next(minVal, maxVal);

    for (int i = 1; i < sampleCount; ++i) {
        int val = rng->next(minVal, maxVal);
        if (val == last) {
            currentRun++;
            if (currentRun > longestRun)
                longestRun = currentRun;
        } else {
            currentRun = 1;
            last = val;
        }
    }

    // For 10,000 draws and 10 possible outcomes, the expected max run length
    // is around 4–6 with high probability. Anything over ~8 is suspicious.
    EXPECT_LT(longestRun, 8) << "(seed " << seed << ")";
}

TEST(VillageRNGTest, IndependentStreams) {
    auto rng1 = GetVillageRNGInterface(111);
    auto rng2 = GetVillageRNGInterface(222);
    for (int i = 0; i < 100; ++i)
        EXPECT_NE(rng1->next(0, 100), rng2->next(0, 100));
}
