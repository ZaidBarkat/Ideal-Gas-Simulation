#include "particle.h"

namespace idealgas {

using glm::vec2;

Particle::Particle(float radius, vec2 position, vec2 velocity) {
  radius_ = radius;
  position_ = position;
  velocity_ = velocity;
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

void Particle::AddVelocityToPosition() {
  position_ += velocity_;
}
float Particle::getRadius() const {
  return radius_;
}

}  // namespace idealgas
