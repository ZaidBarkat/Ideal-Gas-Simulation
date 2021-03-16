#include <catch2/catch.hpp>

#include <gas_container.h>

using idealgas::GasContainer;
using idealgas::Particle;
using glm::vec2;

TEST_CASE("Particle wall tests") {
  GasContainer container(10, 1);
  std::vector<Particle> particles = container.getParticles();

  SECTION("Particle is on the left wall") {
    particles[0].setVelocity(vec2 (-1, 1));
    particles[0].setPosition(vec2 (50, 100));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2 (1, 1) == container.getParticles()[0].getVelocity());
  }
  SECTION("Particle is on the right wall") {
    particles[0].setVelocity(vec2 (1, 1));
    particles[0].setPosition(vec2 (800, 100));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2 (-1, 1) == container.getParticles()[0].getVelocity());
  }
  SECTION("Particle is on the top wall") {
    particles[0].setVelocity(vec2 (1, 1));
    particles[0].setPosition(vec2 (100, 50));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2 (1, -1) == container.getParticles()[0].getVelocity());
  }
  SECTION("Particle is on the bottom wall") {
    particles[0].setVelocity(vec2 (1, -1));
    particles[0].setPosition(vec2 (100, 600));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2 (1, 1) == container.getParticles()[0].getVelocity());
  }
}

TEST_CASE("Particle moving tests") {
  GasContainer container(10, 1);
  std::vector<Particle> particles = container.getParticles();

  SECTION("Particle moves up") {
    particles[0].setVelocity(vec2 (0, 1));
    particles[0].setPosition(vec2 (100, 400));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2 (100, 401) == container.getParticles()[0].getPosition());
  }
  SECTION("Particle moves down") {
    particles[0].setVelocity(vec2 (0, -1));
    particles[0].setPosition(vec2 (100, 400));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2 (100, 399) == container.getParticles()[0].getPosition());
  }
  SECTION("Particle moves right") {
    particles[0].setVelocity(vec2 (1, 0));
    particles[0].setPosition(vec2 (100, 400));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2 (101, 400) == container.getParticles()[0].getPosition());
  }
  SECTION("Particle moves left") {
    particles[0].setVelocity(vec2 (-1, 0));
    particles[0].setPosition(vec2 (100, 400));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2 (99, 400) == container.getParticles()[0].getPosition());
  }
}

TEST_CASE("Particle colliding with another particle tests") {
  GasContainer container(10, 2);
  std::vector<Particle> particles = container.getParticles();

  SECTION("Particles velocity and position") {
    particles[0].setVelocity(vec2 (1, 0));
    particles[0].setPosition(vec2 (100, 550));

    particles[1].setVelocity(vec2 (-1, 0));
    particles[1].setPosition(vec2 (120, 550));

    container.setParticles(particles);
    container.AdvanceOneFrame();

    SECTION("Particle_one velocity after colliding") {
      REQUIRE(vec2 (-1, 0) == container.getParticles()[0].getVelocity());
    }
    SECTION("Particle_two velocity after colliding") {
      REQUIRE(vec2 (1, 0) == container.getParticles()[1].getVelocity());
    }
    SECTION("Particle_one position after colliding") {
      REQUIRE(vec2 (99, 550) == container.getParticles()[0].getPosition());
    }
    SECTION("Particle_two position after colliding") {
      REQUIRE(vec2 (121, 550) == container.getParticles()[1].getPosition());
    }

  }
  SECTION("Particles moving away from each other, but colliding") {
    particles[0].setVelocity(vec2 (-1, 0));
    particles[0].setPosition(vec2 (100, 550));

    particles[1].setVelocity(vec2 (1, 0));
    particles[1].setPosition(vec2 (110, 550));

    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2 (111, 550) == container.getParticles()[1].getPosition());
  }
}
