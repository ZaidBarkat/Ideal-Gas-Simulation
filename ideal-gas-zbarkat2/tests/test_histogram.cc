#include <gas_container.h>

#include <catch2/catch.hpp>

using glm::vec2;
using idealgas::GasContainer;
using idealgas::Particle;

TEST_CASE("Histogram tests") {
  Particle particle(1, 5, vec2(300, 100), vec2(1, 1), "orange");
  std::vector<Particle> particles;
  particles.push_back(particle);
  idealgas::Histogram histogram(vec2(0, 0), vec2(0, 0), "blue");

  SECTION("UpdateNumberOfParticles method") {
    histogram.Add(particles);
    REQUIRE(2 == histogram.GetParticlesInIntervalOne());
  }
}
