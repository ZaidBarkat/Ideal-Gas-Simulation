#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * TODO: Add more parameters to this constructor, and add documentation.
   */
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

 private:
  static constexpr float kRectangleXMin = 50;
  static constexpr float kRectangleYMin = 50;
  static constexpr float kRectangleXMax = 800;
  static constexpr float kRectangleYMax = 600;
  static constexpr int kNumberOfParticles = 20;
  static constexpr float kRadius = 10;
  static constexpr float kInitialXVelocity = 0;
  static constexpr float kInitialYVelocity = 3;

  std::vector<Particle> particles_;

  void DrawCircles() const;

  void DrawRectangle() const;

  void BounceOffWall(size_t particle);

  void BounceOffAnotherParticle(size_t particle);

  void SetVelocityOfParticles(size_t particle, vec2 velocity_of_particle_one,
                              vec2 velocity_of_particle_two,
                              vec2 position_of_particle_one,
                              vec2 position_of_particle_two);

  float RandomFloat(float min, float max);
};

}  // namespace idealgas
