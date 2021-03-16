#include "particle.h"

namespace idealgas {

using glm::vec2;

Particle::Particle(size_t radius, const vec2& position, const vec2& velocity) {
  if (position.x < 0 || position.y < 0) {
    throw std::invalid_argument("Impossible positions");
  }

  radius_ = radius;
  position_ = position;
  velocity_ = velocity;
}

void Particle::AddVelocityToPosition() {
  position_ += velocity_;
}

const vec2& Particle::getPosition() const {
  return position_;
}

const vec2& Particle::getVelocity() const {
  return velocity_;
}

void Particle::setVelocity(const vec2& velocity) {
  velocity_ = velocity;
}

void Particle::setPosition(const vec2& position) {
  position_ = position;
}

size_t Particle::getRadius() const {
  return radius_;
}

}  // namespace idealgas
