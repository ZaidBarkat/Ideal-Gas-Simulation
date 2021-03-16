#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

namespace idealgas {

using glm::vec2;

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  GasContainer();

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  void setNumberOfParticles(size_t numberOfParticles);

  void setRadius(float radius);

  const std::vector<Particle>& getParticles() const;

 private:
  static constexpr float kRectangleXMin = 50;
  static constexpr float kRectangleYMin = 50;
  static constexpr float kRectangleXMax = 800;
  static constexpr float kRectangleYMax = 600;
  static constexpr float kInitialXVelocity = 3;
  static constexpr float kInitialYVelocity = 3;

  std::vector<Particle> particles_;
  size_t number_of_particles;
  float radius;

  void DrawCircles() const;

  void DrawRectangle() const;

  void BounceOffWall(size_t particle);

  void BounceOffAnotherParticle(size_t particle);

  void SetVelocityOfParticles(size_t particle, const vec2& velocity_of_particle_one,
                              const vec2& velocity_of_particle_two,
                              const vec2& position_of_particle_one,
                              const vec2& position_of_particle_two);

  float RandomFloat(float min, float max);
};

}  // namespace idealgas
