#pragma once

#include "cinder/gl/gl.h"
#include "histogram.h"
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
  GasContainer(float largest_radius, size_t number_of_particles);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display();

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

  static constexpr float kInitialXVelocity = 2;
  static constexpr float kInitialYVelocity = 2;

  static constexpr float kSmallMass = 5;
  static constexpr float kMediumMass = 10;
  static constexpr float kLargeMass = 15;

  Histogram histogram_large_mass_ =
      Histogram(vec2(900, 400), vec2(1400, 500), "orange");
  Histogram histogram_medium_mass_ =
      Histogram(vec2(900, 600), vec2(1400, 700), "blue");
  Histogram histogram_small_mass_ =
      Histogram(vec2(900, 800), vec2(1400, 900), "green");

  std::vector<Particle> particles_;

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
