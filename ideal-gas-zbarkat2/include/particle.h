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
  Particle(float radius, float particle_x, float particle_y);

  float getRadius() const;

  float getXPosition() const;

  float getYPosition() const;

  float GetXVelocity() const;

  float GetYVelocity() const;

  std::vector<float> GetPosition() const;

  void SetXPosition(float xPosition);

  void SetYPosition(float yPosition);

  void SetXVelocity(float x_velocity);

  void SetYVelocity(float y_velocity);

  //Particle CreateParticle(size_t particle_x, size_t particle_y);

 private:
  float radius_;
  float x_position_;
  float y_position_;
  float x_velocity_;
  float y_velocity_;
};

}  // namespace idealgas
