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
  Particle(size_t radius, const vec2& position, const vec2& velocity);

  /**
   * Use to add the velocity to the position of a particle.
   */
  void AddVelocityToPosition();

  const vec2& getPosition() const;

  const vec2& getVelocity() const;

  size_t getRadius() const;

  void setVelocity(const vec2& velocity);

  void setPosition(const vec2& position);

 private:
  size_t radius_;
  vec2 position_;
  vec2 velocity_;
};

}  // namespace idealgas
