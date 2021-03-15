#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class Particle {
 public:
  /**
   * TODO: Add more parameters to this constructor, and add documentation.
   */
  Particle(float radius, vec2 position, vec2 velocity);

  const vec2& getPosition() const;

  const vec2& getVelocity() const;

  float getRadius() const;

  void setVelocity(const vec2& velocity);

  void AddVelocityToPosition();

 private:
  float radius_;
  vec2 position_;
  vec2 velocity_;
};

}  // namespace idealgas
