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
  /**
   * Constructor used to initialize the amount of particles needed and radius of
   * those particles.
   *
   * @param radius of each particle
   * @param number_of_particles in the container
   */
  GasContainer(size_t radius, size_t number_of_particles);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  const std::vector<Particle>& getParticles() const;

  void setParticles(const std::vector<Particle>& particles);

 private:
  static constexpr float kRectangleXMin = 50;
  static constexpr float kRectangleYMin = 50;
  static constexpr float kRectangleXMax = 800;
  static constexpr float kRectangleYMax = 600;
  static constexpr float kInitialXVelocity = 3;
  static constexpr float kInitialYVelocity = 3;

  std::vector<Particle> particles_;

  /**
   * Use to draw the circles of the particles.
   */
  void DrawCircles() const;

  /**
   * Use to draw the rectangle of the container.
   */
  void DrawRectangle() const;

  /**
   * Use to change the velocity depending on the position of the
   * particle with the wall.
   *
   * @param particle index being used to to find the particle in the
   * vector
   */
  void BounceOffWall(size_t particle);

  /**
   * Use to change the velocity of two particles depending on the position of
   * the particle with the colliding particle.
   *
   * @param particle index being used to find the particle in the
   * vector
   */
  void BounceOffAnotherParticle(size_t particle);

  /**
   * Use to set the velocity of the particles when they are colliding with
   * each other.
   *
   * @param particle index to find the particle in the vector
   * @param velocity_one first particle's velocity
   * @param velocity_two  second particle's velocity
   * @param position_one first particle's position
   * @param position_two  second particle's position
   */
  void SetVelocityOfCollidingParticles(size_t particle,
                                       const vec2& velocity_one,
                                       const vec2& velocity_two,
                                       const vec2& position_one,
                                       const vec2& position_two);

  /**
   * Code from stack overflow, use to find a random float depending on a min and
   * max number.
   *
   * @param min number
   * @param max number
   * @return a random float between the min and max.
   */
  float RandomFloat(float min, float max);
};

}  // namespace idealgas
