#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

using glm::vec2;

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
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

  void DrawParticle();

  void BounceOffWall(float x_min, float y_min, float x_max, float y_max);

  bool BounceOff(Particle particle);

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
