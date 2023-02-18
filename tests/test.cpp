#include <catch2/catch_test_macros.hpp>
#define CONFIG_CATCH_MAIN

#include "quaternion.hpp"
#include "world_point.hpp"
#include "pixel.hpp"
#include "directional_light.hpp"


TEST_CASE("Quaternion")
{
    Quaternion q{1,0,0,0};

    WorldPoint p1{1,0,0};
    WorldPoint p2 = q * p1;

    REQUIRE((p1.x == p2.x && p1.y == p2.y && p1.z == p2.z));
}

TEST_CASE("Color")
{
    Pixel p{0xFF0000};

    p.setBrightness(1);


    REQUIRE((p.r == 255));
    REQUIRE((p.g == 0));
    REQUIRE((p.b == 0));


}

TEST_CASE("Lighting")
{
    
}

