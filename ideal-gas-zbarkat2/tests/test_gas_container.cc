#include <gas_container.h>

#include <catch2/catch.hpp>

using glm::vec2;
using idealgas::GasContainer;
using idealgas::Particle;

TEST_CASE("Particle wall tests") {
  GasContainer container(10, 1);
  std::vector<Particle> particles = container.getParticles();

  SECTION("Particle is on the left wall") {
    particles[0].SetVelocity(vec2(-1, 1));
    particles[0].SetPosition(vec2(50, 100));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(1, 1) == container.getParticles()[0].GetVelocity());
  }
  SECTION("Particle is on the right wall") {
    particles[0].SetVelocity(vec2(1, 1));
    particles[0].SetPosition(vec2(800, 100));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(-1, 1) == container.getParticles()[0].GetVelocity());
  }
  SECTION("Particle is on the top wall") {
    particles[0].SetVelocity(vec2(1, 1));
    particles[0].SetPosition(vec2(100, 50));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(1, -1) == container.getParticles()[0].GetVelocity());
  }
  SECTION("Particle is on the bottom wall") {
    particles[0].SetVelocity(vec2(1, -1));
    particles[0].SetPosition(vec2(100, 600));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(1, 1) == container.getParticles()[0].GetVelocity());
  }
}

TEST_CASE("Particle moving tests") {
  GasContainer container(10, 1);
  std::vector<Particle> particles = container.getParticles();

  SECTION("Particle moves up") {
    particles[0].SetVelocity(vec2(0, 1));
    particles[0].SetPosition(vec2(100, 400));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(100, 401) == container.getParticles()[0].GetPosition());
  }
  SECTION("Particle moves down") {
    particles[0].SetVelocity(vec2(0, -1));
    particles[0].SetPosition(vec2(100, 400));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(100, 399) == container.getParticles()[0].GetPosition());
  }
  SECTION("Particle moves right") {
    particles[0].SetVelocity(vec2(1, 0));
    particles[0].SetPosition(vec2(100, 400));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(101, 400) == container.getParticles()[0].GetPosition());
  }
  SECTION("Particle moves left") {
    particles[0].SetVelocity(vec2(-1, 0));
    particles[0].SetPosition(vec2(100, 400));
    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(99, 400) == container.getParticles()[0].GetPosition());
  }
}

TEST_CASE("Particle colliding with another particle tests") {
  GasContainer container(10, 2);
  std::vector<Particle> particles = container.getParticles();

  SECTION("Particles velocity and position without mass") {
    particles[0].SetVelocity(vec2(1, 0));
    particles[0].SetPosition(vec2(100, 550));

    particles[1].SetVelocity(vec2(-1, 0));
    particles[1].SetPosition(vec2(120, 550));

    container.setParticles(particles);
    container.AdvanceOneFrame();

    SECTION("Particle_one velocity after colliding") {
      REQUIRE(vec2(1, 0) == container.getParticles()[0].GetVelocity());
    }
    SECTION("Particle_two velocity after colliding") {
      REQUIRE(vec2(-1, 0) == container.getParticles()[1].GetVelocity());
    }
    SECTION("Particle_one position after colliding") {
      REQUIRE(vec2(101, 550) == container.getParticles()[0].GetPosition());
    }
    SECTION("Particle_two position after colliding") {
      REQUIRE(vec2(119, 550) == container.getParticles()[1].GetPosition());
    }
  }
  SECTION("Particles velocity and position with mass") {
    GasContainer container(10, 2);
    std::vector<Particle> particles = container.getParticles();

    particles[0].SetVelocity(vec2(1, 0));
    particles[0].SetPosition(vec2(100, 550));
    particles[0].SetMass(2);

    particles[1].SetVelocity(vec2(-1, 0));
    particles[1].SetPosition(vec2(120, 550));
    particles[1].SetMass(1);

    container.setParticles(particles);
    container.AdvanceOneFrame();

    SECTION("Particle_one velocity after colliding") {
      REQUIRE(vec2(1, 0) == container.getParticles()[0].GetVelocity());
    }
    SECTION("Particle_two velocity after colliding") {
      REQUIRE(vec2(-1, 0) == container.getParticles()[1].GetVelocity());
    }
    SECTION("Particle_one position after colliding") {
      REQUIRE(vec2(101, 550) == container.getParticles()[0].GetPosition());
    }
    SECTION("Particle_two position after colliding") {
      REQUIRE(vec2(119, 550) == container.getParticles()[1].GetPosition());
    }
  }
  SECTION("Particles moving away from each other, but colliding") {
    particles[0].SetVelocity(vec2(-1, 0));
    particles[0].SetPosition(vec2(100, 550));

    particles[1].SetVelocity(vec2(1, 0));
    particles[1].SetPosition(vec2(110, 550));

    container.setParticles(particles);
    container.AdvanceOneFrame();
    REQUIRE(vec2(111, 550) == container.getParticles()[1].GetPosition());
  }
}

TEST_CASE("Three Particles colliding with each other tests") {
  GasContainer container(10, 3);
  std::vector<Particle> particles = container.getParticles();

  SECTION("Particles velocity and position without mass") {
    particles[0].SetVelocity(vec2(-1, 0));
    particles[0].SetPosition(vec2(205, 200));

    particles[1].SetVelocity(vec2(1, 0));
    particles[1].SetPosition(vec2(200, 200));

    particles[2].SetVelocity(vec2(0, -1));
    particles[2].SetPosition(vec2(202.5, 205));

    container.setParticles(particles);
    container.AdvanceOneFrame();

    SECTION("Particle_one velocity in x direction after colliding") {
      REQUIRE(0.74f == Approx(container.getParticles()[0].GetVelocity().x));
    }
    SECTION("Particle_one velocity in y direction after colliding") {
      REQUIRE(-0.28f == Approx(container.getParticles()[0].GetVelocity().y));
    }
    SECTION("Particle_two velocity in x direction after colliding") {
      REQUIRE(-1.4f == Approx(container.getParticles()[1].GetVelocity().x));
    }
    SECTION("Particle_two velocity in y direction after colliding") {
      REQUIRE(0.0f == Approx(container.getParticles()[1].GetVelocity().y));
    }
    SECTION("Particle_three velocity in x direction after colliding") {
      REQUIRE(-0.42f == Approx(container.getParticles()[2].GetVelocity().x));
    }
    SECTION("Particle_three velocity in y direction after colliding") {
      REQUIRE(-0.16f == Approx(container.getParticles()[2].GetVelocity().y));
    }
  }
  SECTION("Particles velocity and position with mass") {
    particles[0].SetVelocity(vec2(-1, 0));
    particles[0].SetPosition(vec2(205, 200));
    particles[0].SetMass(3);

    particles[1].SetVelocity(vec2(1, 0));
    particles[1].SetPosition(vec2(200, 200));
    particles[0].SetMass(2);

    particles[2].SetVelocity(vec2(0, -1));
    particles[2].SetPosition(vec2(202.5, 205));
    particles[0].SetMass(1);

    container.setParticles(particles);
    container.AdvanceOneFrame();

    SECTION("Particle_one velocity in x direction after colliding") {
      REQUIRE(2.6363637447f ==
              Approx(container.getParticles()[0].GetVelocity().x));
    }
    SECTION("Particle_one velocity in y direction after colliding") {
      REQUIRE(0.0f == Approx(container.getParticles()[0].GetVelocity().y));
    }
    SECTION("Particle_two velocity in x direction after colliding") {
      REQUIRE(0.2848484814f ==
              Approx(container.getParticles()[1].GetVelocity().x));
    }
    SECTION("Particle_two velocity in y direction after colliding") {
      REQUIRE(-0.7030302882f ==
              Approx(container.getParticles()[1].GetVelocity().y));
    }
    SECTION("Particle_three velocity in x direction after colliding") {
      REQUIRE(0.7030302882f ==
              Approx(container.getParticles()[2].GetVelocity().x));
    }
    SECTION("Particle_three velocity in y direction after colliding") {
      REQUIRE(0.4060605764f ==
              Approx(container.getParticles()[2].GetVelocity().y));
    }
  }
}
