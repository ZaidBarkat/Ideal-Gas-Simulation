#include "gas_container.h"

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(Particle particle) {
  std::vector<Particle> particles;
  for (int i = 0; i < 2; i++) {
    Particle particle(10, 200, 200);
    particles.push_back(particle);
    position_ = vec2 (particle.getXPosition(), particle.getYPosition());
  }
  //particle_ = Particle(10, 200, 200);

}

void GasContainer::Display() const {
  ci::gl::color(ci::Color("orange"));
  ci::gl::drawSolidCircle(vec2(position_.x, position_.y), particles[0].getRadius());
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(kRectangleXMin, kRectangleYMin), vec2(kRectangleXMax, kRectangleYMax)));
}

void GasContainer::AdvanceOneFrame() {
  float velocity_x;
  float velocity_y;
  //position_ = vec2 (particle_.getXPosition(), particle_.getYPosition());
  vec2 velocity(particle_.GetXVelocity(), particle_.GetYVelocity());

  position_ += velocity;



//  float position_x = particle_.getXPosition();
//  float velocity_x = particle_.GetXVelocity();
//  position_x += velocity_x;
//  particle_.SetXPosition(++particle_x);
//
//  float position_y = particle_.getYPosition();
//  particle_.SetYPosition(++particle_y);
}

}  // namespace idealgas
