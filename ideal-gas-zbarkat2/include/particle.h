#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

using glm::vec2;

/**
 * The class that creates particles based on given constraints.
 *
 */
class Particle {
 public:
  /**
   * Use to set an individual particle's radius, initial position, and initial
   * velocity.
   *
   * @param radius of a particle
   * @param position of a particle
   * @param velocity of a particle
   */
  Particle(float mass, float radius, const vec2& position, const vec2& velocity, ci::Color color);

  /**
   * Use to draw the Particle into the container.
   */
  void DrawParticle();

  /**
   * Checks and changes velocity if particle bounces off the wall.
   *
   * @param x_min wall dimension
   * @param y_min wall dimension
   * @param x_max wall dimension
   * @param y_max wall dimension
   */
  void BounceOffWall(float x_min, float y_min, float x_max, float y_max);

  /**
   * Check if a particle bounces off another particle.
   *
   * @param particle to check against
   * @return true if bouncing off
   */
  bool BounceOff(Particle particle);

  /**
   * Updates the velocity of both particles if they are bouncing off each other.
   *
   * @param velocity_two of the second particle
   * @param position_two of the second particle
   * @param mass_two of the second mass
   */
  void UpdateVelocityCollision(
                               const vec2& velocity_two,
                               const vec2& position_two,
                               const float& mass_two);

  /**
   * Use to add the velocity to the position of a particle.
   */
  void UpdatePosition();

  const vec2& GetPosition() const;

  const vec2& GetVelocity() const;

  float GetRadius() const;

  float GetMass() const;

  void SetVelocity(const vec2& velocity);

  void SetPosition(const vec2& position);

  void SetMass(const float& mass);

 private:
  float radius_;
  vec2 position_;
  vec2 velocity_;
  ci::Color color_;
  float mass_;
};

}  // namespace idealgas
