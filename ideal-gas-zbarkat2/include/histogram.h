#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

namespace idealgas {

using glm::vec2;

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class Histogram {
 public:
  /**
   * Use to set an individual particle's radius, initial position, and initial
   * velocity.
   *
   * @param radius of a particle
   * @param position of a particle
   * @param velocity of a particle
   */
  Histogram(vec2 top_left, vec2 bottom_right, ci::Color color);

  void Draw();

  void Add(std::vector<Particle> particles);

  int GetParticlesInIntervalOne() const;

 private:
  int particles_in_interval_one_ = 0;
  int particles_in_interval_two_ = 0;
  int particles_in_interval_three_ = 0;
  int particles_in_interval_four_ = 0;
  int particles_in_interval_five_ = 0;

  std::vector<Particle> particles_of_certain_mass_;
  static constexpr float max_velocity_five_ = 8;
  static constexpr float max_velocity_one_ = max_velocity_five_ / 5;
  static constexpr float max_velocity_two_ = (max_velocity_five_ / 5) * 2;
  static constexpr float max_velocity_three_ = (max_velocity_five_ / 5) * 3;
  static constexpr float max_velocity_four_ = (max_velocity_five_ / 5) * 4;

  static constexpr float fifth_interval_ = 500;
  static constexpr float first_interval_ = fifth_interval_ / 5;
  static constexpr float second_interval_ = (fifth_interval_ / 5) * 2;
  static constexpr float third_interval_ = (fifth_interval_ / 5) * 3;
  static constexpr float fourth_interval_ = (fifth_interval_ / 5) * 4;

  static constexpr int y_increase_ = 2;

  vec2 top_left_rectangle_;
  vec2 bottom_right_rectangle_;
  ci::Color color_;

  void UpdateNumberOfParticles();

  void Reset();
};

}  // namespace idealgas
