#include "histogram.h"

#include <glm/vec2.hpp>

namespace idealgas {

using glm::vec2;

Histogram::Histogram(vec2 top_left, vec2 bottom_right, ci::Color color) {
  top_left_rectangle_ = top_left;
  bottom_right_rectangle_ = bottom_right;
  color_ = color;
}

void Histogram::Add(std::vector<Particle> particles) {
  particles_of_certain_mass_ = particles;

  UpdateNumberOfParticles();
}

void Histogram::UpdateNumberOfParticles() {
  for (Particle particle : particles_of_certain_mass_) {
    if (length(particle.GetVelocity()) <= max_velocity_one_) {
      particles_in_interval_one_ += y_increase_;
    } else if (length(particle.GetVelocity()) <= max_velocity_two_) {
      particles_in_interval_two_ += y_increase_;
    } else if (length(particle.GetVelocity()) <= max_velocity_three_) {
      particles_in_interval_three_ += y_increase_;
    } else if (length(particle.GetVelocity()) <= max_velocity_four_) {
      particles_in_interval_four_ += y_increase_;
    } else {
      particles_in_interval_five_ += y_increase_;
    }
  }
}

void Histogram::Reset() {
  particles_in_interval_one_ = 0;
  particles_in_interval_two_ = 0;
  particles_in_interval_three_ = 0;
  particles_in_interval_four_ = 0;
  particles_in_interval_five_ = 0;
  particles_of_certain_mass_.clear();
}

void Histogram::Draw() {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(
      ci::Rectf(top_left_rectangle_, bottom_right_rectangle_));
  ci::gl::drawStringCentered(
      "0", vec2(top_left_rectangle_.x, bottom_right_rectangle_.y), "cyan",
      ci::Font("Arial", speed_number_font_));
  ci::gl::drawStringCentered(
      "50",
      vec2(top_left_rectangle_.x - particle_number_centering_,
           top_left_rectangle_.y),
      "cyan", ci::Font("Arial", particle_number_font_));
  ci::gl::color(color_);
  ci::gl::drawSolidRect(
      ci::Rectf(vec2(top_left_rectangle_.x,
                     bottom_right_rectangle_.y - particles_in_interval_one_),
                vec2(first_interval_ + top_left_rectangle_.x,
                     bottom_right_rectangle_.y)));
  ci::gl::drawStringCentered(
      "1.6",
      vec2(top_left_rectangle_.x + first_interval_, bottom_right_rectangle_.y),
      "cyan", ci::Font("Arial", speed_number_font_));
  ci::gl::color(color_);
  ci::gl::drawSolidRect(
      ci::Rectf(vec2(max_velocity_one_ + top_left_rectangle_.x,
                     bottom_right_rectangle_.y - particles_in_interval_two_),
                vec2(second_interval_ + top_left_rectangle_.x,
                     bottom_right_rectangle_.y)));
  ci::gl::drawStringCentered(
      "37",
      vec2(top_left_rectangle_.x - particle_number_centering_,
           top_left_rectangle_.y + particle_number_interval_three),
      "cyan", ci::Font("Arial", particle_number_font_));
  ci::gl::drawStringCentered(
      "3.2",
      vec2(top_left_rectangle_.x + second_interval_, bottom_right_rectangle_.y),
      "cyan", ci::Font("Arial", speed_number_font_));
  ci::gl::color(color_);
  ci::gl::drawSolidRect(
      ci::Rectf(vec2(max_velocity_two_ + top_left_rectangle_.x,
                     bottom_right_rectangle_.y - particles_in_interval_three_),
                vec2(third_interval_ + top_left_rectangle_.x,
                     bottom_right_rectangle_.y)));
  ci::gl::drawStringCentered(
      "25",
      vec2(top_left_rectangle_.x - particle_number_centering_,
           top_left_rectangle_.y + particle_number_interval_two),
      "cyan", ci::Font("Arial", particle_number_font_));
  ci::gl::drawStringCentered(
      "4.8",
      vec2(top_left_rectangle_.x + third_interval_, bottom_right_rectangle_.y),
      "cyan", ci::Font("Arial", speed_number_font_));
  ci::gl::color(color_);
  ci::gl::drawSolidRect(
      ci::Rectf(vec2(max_velocity_three_ + top_left_rectangle_.x,
                     bottom_right_rectangle_.y - particles_in_interval_four_),
                vec2(fourth_interval_ + top_left_rectangle_.x,
                     bottom_right_rectangle_.y)));
  ci::gl::drawStringCentered(
      "12",
      vec2(top_left_rectangle_.x - particle_number_centering_,
           top_left_rectangle_.y + particle_number_interval_one),
      "cyan", ci::Font("Arial", particle_number_font_));
  ci::gl::drawStringCentered(
      "6.4",
      vec2(top_left_rectangle_.x + fourth_interval_, bottom_right_rectangle_.y),
      "cyan", ci::Font("Arial", speed_number_font_));
  ci::gl::color(color_);
  ci::gl::drawSolidRect(
      ci::Rectf(vec2(max_velocity_four_ + top_left_rectangle_.x,
                     bottom_right_rectangle_.y - particles_in_interval_five_),
                vec2(fifth_interval_ + top_left_rectangle_.x,
                     bottom_right_rectangle_.y)));
  ci::gl::drawStringCentered(
      "8",
      vec2(top_left_rectangle_.x + fifth_interval_, bottom_right_rectangle_.y),
      "cyan", ci::Font("Arial", speed_number_font_));
  ci::gl::drawStringCentered(
      "Speed",
      vec2(top_left_rectangle_.x + speed_string_position_x_,
           bottom_right_rectangle_.y + speed_string_position_y_),
      "cyan", ci::Font("", speed_string_font_));

  Reset();
}

int Histogram::GetParticlesInIntervalOne() const {
  return particles_in_interval_one_;
}
}  // namespace idealgas
