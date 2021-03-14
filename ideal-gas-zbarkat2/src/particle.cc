#include "particle.h"

namespace idealgas {

using glm::vec2;

Particle::Particle(float radius, float x_position, float y_position) {
  radius_ = radius;
  x_position_ = x_position;
  y_position_ = y_position;
  y_velocity_ = 1;
  x_velocity_ = 1;
}
float Particle::getRadius() const {return radius_; }

float Particle::getXPosition() const {return x_position_; }

float Particle::getYPosition() const {return y_position_; }

std::vector<float> Particle::GetPosition() const {
  std::vector<float> position_return;
  vec2 position(x_position_, y_position_);
  position_return.push_back(position.x);
  position_return.push_back(position.y);
  return position_return;
}

void Particle::SetXPosition(float xPosition) {
  x_position_ = xPosition;
}
void Particle::SetYPosition(float yPosition) {
  y_position_ = yPosition;
}
float Particle::GetXVelocity() const {
  return x_velocity_;
}
float Particle::GetYVelocity() const {
  return y_velocity_;
}
void Particle::SetXVelocity(float x_velocity) {
  x_velocity_ = x_velocity;
}
void Particle::SetYVelocity(float y_velocity) {
  y_velocity_ = y_velocity;
}

}  // namespace idealgas
