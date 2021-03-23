#include <gas_container.h>

#include <catch2/catch.hpp>

using glm::vec2;
using idealgas::GasContainer;
using idealgas::Particle;

TEST_CASE("Simple particle tests") {
  Particle particle(1, 5, vec2(300, 100), vec2(1, 1), "orange");

  SECTION("particle radius is correct") {
    REQUIRE(5 == particle.GetRadius());
  }
  SECTION("Particle position is correct") {
    REQUIRE(vec2(300, 100) == particle.GetPosition());
  }
  SECTION("Particle velocity is correct") {
    REQUIRE(vec2(1, 1) == particle.GetVelocity());
  }
  SECTION("Particle adds velocity to position correctly") {
    particle.UpdatePosition();
    REQUIRE(vec2(301, 101) == particle.GetPosition());
  }
  SECTION("Invalid positions") {
    REQUIRE_THROWS_AS(Particle(1, 5, vec2(-1, 100), vec2(1, 1), "orange"),
                      std::invalid_argument);
  }
}
TEST_CASE("Helper method particle tests") {
  Particle particle(1, 5, vec2(300, 100), vec2(1, 1), "orange");

  SECTION("BounceOffWall method") {
    particle.BounceOffWall(100, 100, 100, 100);
    REQUIRE(-1 == particle.GetVelocity().x);
  }
  SECTION("BounceOff method") {
    Particle other_particle(1, 5, vec2(300, 100), vec2(-1, -1), "orange");

    REQUIRE(particle.BounceOff(other_particle));
  }
}
