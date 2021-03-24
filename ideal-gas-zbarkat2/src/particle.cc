#include "particle.h"

namespace idealgas {

using glm::vec2;

Particle::Particle(float mass, float radius, const vec2& position,
                   const vec2& velocity, ci::Color color) {
  if (position.x < 0 || position.y < 0) {
    throw std::invalid_argument("Impossible positions");
  }

  color_ = color;
  radius_ = radius;
  position_ = position;
  velocity_ = velocity;
  mass_ = mass;
}

void Particle::DrawParticle() {
  ci::gl::color(ci::Color(color_));
  ci::gl::drawSolidCircle(vec2(position_.x, position_.y), (float)radius_);
}

void Particle::BounceOffWall(float x_min, float y_min, float x_max,
                             float y_max) {
  // if the position in the x direction is either hitting the left or right wall
  if (position_.x - radius_ <= x_min || position_.x + radius_ >= x_max) {
    velocity_ = vec2(-velocity_.x, velocity_.y);
  }
  // if the position in the y direction is hitting the top or bottom wall
  else if (position_.y - radius_ <= y_min || position_.y + radius_ >= y_max) {
    velocity_ = vec2(velocity_.x, -velocity_.y);
  }
}

bool Particle::BounceOff(Particle particle) {
  return distance(position_, particle.GetPosition()) <=
             radius_ + particle.GetRadius() &&
         dot((velocity_ - particle.GetVelocity()),
             (position_ - particle.GetPosition())) < 0;
}

void Particle::UpdateVelocityCollision(const vec2& velocity_two,
                                       const vec2& position_two,
                                       const float& mass_two) {
  velocity_ =
      velocity_ -
      (2 * mass_two / (mass_ + mass_two)) *
          ((dot((velocity_ - velocity_two), (position_ - position_two))) /
           (length(position_ - position_two) *
            length(position_ - position_two))) *
          (position_ - position_two);
}

void Particle::UpdatePosition() {
  position_ += velocity_;
}

const vec2& Particle::GetPosition() const {
  return position_;
}

const vec2& Particle::GetVelocity() const {
  return velocity_;
}

void Particle::SetVelocity(const vec2& velocity) {
  velocity_ = velocity;
}

void Particle::SetPosition(const vec2& position) {
  position_ = position;
}

void Particle::SetMass(const float& mass) {
  mass_ = mass;
}

float Particle::GetRadius() const {
  return radius_;
}

float Particle::GetMass() const {
  return mass_;
}

}  // namespace idealgas
