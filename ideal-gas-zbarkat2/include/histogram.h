#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

namespace idealgas {

using glm::vec2;

/**
 * The graph of all the particles depending on mass and velocity.
 */
class Histogram {
 public:
  /**
   * Use to set an individual Histogram's position and color.
   *
   * @param top left of the rectangle of the Histogram
   * @param bottom right of the rectangle of the Histogram
   * @param color of the histogram
   */
  Histogram(vec2 top_left, vec2 bottom_right, ci::Color color);


  void Draw();

  void Add(std::vector<Particle> particles);

  /**
   * Used for testing.
   *
   * @return set of particles from one interval
   */
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

  static constexpr float speed_string_position_x_ = 200;
  static constexpr float speed_string_position_y_ = 40;
  static constexpr float speed_string_font_ = 50.0f;
  static constexpr float speed_number_font_ = 40.0f;
  static constexpr float particle_number_font_ = 20.0f;
  static constexpr float particle_number_centering_ = 15;

  static constexpr float particle_number_interval_one = 75;
  static constexpr float particle_number_interval_two = 50;
  static constexpr float particle_number_interval_three = 25;

  vec2 top_left_rectangle_;
  vec2 bottom_right_rectangle_;
  ci::Color color_;

  void UpdateNumberOfParticles();

  void Reset();
};

}  // namespace idealgas
