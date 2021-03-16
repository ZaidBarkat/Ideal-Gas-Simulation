#include <catch2/catch.hpp>

#include <gas_container.h>

using idealgas::GasContainer;
using idealgas::Particle;
using glm::vec2;

TEST_CASE("Quick particle tests") {
  Particle particle(5, vec2 (300, 100), vec2 (1, 1));

  SECTION("particle radius is correct") {
    REQUIRE(5 == particle.getRadius());
  }
  SECTION("Particle position is correct") {
    REQUIRE(vec2 (300,100) == particle.getPosition());
  }
  SECTION("Particle velocity is correct") {
    REQUIRE(vec2 (1, 1) == particle.getVelocity());
  }
  SECTION("Particle adds velocity to position correctly") {
    particle.AddVelocityToPosition();
    REQUIRE(vec2 (301, 101) == particle.getPosition());
  }
  SECTION("Invalid positions") {
    REQUIRE_THROWS_AS(Particle(5, vec2 (-1, 100), vec2 (1, 1)), std::invalid_argument);
  }
}
