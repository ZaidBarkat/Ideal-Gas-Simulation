#include "gas_container.h"

#include <iostream>

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer() {
  for (int i = 0; i < kNumberOfParticles; i++) {
    Particle particle(
        kRadius,
        vec2(RandomFloat(kRectangleXMin + kRadius, kRectangleXMax - kRadius),
             RandomFloat(kRectangleYMin + kRadius, kRectangleYMax - kRadius)),
        vec2(kInitialXVelocity, kInitialYVelocity));
    particles_.push_back(particle);
  }
}

void GasContainer::Display() const {
  DrawCircles();
  DrawRectangle();
}

void GasContainer::AdvanceOneFrame() {
  for (size_t particle = 0; particle < kNumberOfParticles; particle++) {
    BounceOffWall(particle);

    BounceOffAnotherParticle(particle);

    particles_[particle].AddVelocityToPosition();
  }
}

void GasContainer::DrawCircles() const {
  for (size_t i = 0; i < kNumberOfParticles; i++) {
    ci::gl::color(ci::Color("orange"));
    ci::gl::drawSolidCircle(
        vec2(particles_[i].getPosition().x, particles_[i].getPosition().y),
        particles_[i].getRadius());
  }
}

void GasContainer::DrawRectangle() const {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(kRectangleXMin, kRectangleYMin),
                                    vec2(kRectangleXMax, kRectangleYMax)));
}

void GasContainer::BounceOffWall(size_t particle) {
  float velocity_x = particles_[particle].getVelocity().x;
  float velocity_y = particles_[particle].getVelocity().y;

  if (abs(particles_[particle].getPosition().x) -
              particles_[particle].getRadius() <=
          kRectangleXMin ||
      abs(particles_[particle].getPosition().x) +
              particles_[particle].getRadius() >=
          kRectangleXMax) {
    particles_[particle].setVelocity(vec2(-velocity_x, velocity_y));
  } else if (abs(particles_[particle].getPosition().y) -
                     particles_[particle].getRadius() <=
                 kRectangleYMin ||
             abs(particles_[particle].getPosition().y) +
                     particles_[particle].getRadius() >=
                 kRectangleYMax) {
    particles_[particle].setVelocity(vec2(velocity_x, -velocity_y));
  }
}

void GasContainer::BounceOffAnotherParticle(size_t particle) {
  for (size_t j = particle + 1; j < kNumberOfParticles; j++) {
    if (distance(abs(particles_[particle].getPosition()),
                 abs(particles_[j].getPosition())) <=
        particles_[particle].getRadius() + particles_[j].getRadius()) {
      vec2 velocity_of_particle_one = particles_[particle].getVelocity();
      vec2 position_of_particle_one = particles_[particle].getPosition();
      vec2 velocity_of_particle_two = particles_[j].getVelocity();
      vec2 position_of_particle_two = particles_[j].getPosition();

      if (dot((velocity_of_particle_one - velocity_of_particle_two),
              (position_of_particle_one - position_of_particle_two)) < 0) {
        SetVelocityOfParticles(
            particle, velocity_of_particle_one, velocity_of_particle_two,
            position_of_particle_one, position_of_particle_two);

        SetVelocityOfParticles(
            j, velocity_of_particle_two, velocity_of_particle_one,
            position_of_particle_two, position_of_particle_one);

        particles_[j].AddVelocityToPosition();
        break;
      }
    }
  }
}

void GasContainer::SetVelocityOfParticles(size_t particle,
                                          vec2 velocity_of_particle_one,
                                          vec2 velocity_of_particle_two,
                                          vec2 position_of_particle_one,
                                          vec2 position_of_particle_two) {
  particles_[particle].setVelocity(
      velocity_of_particle_one -
      ((dot((velocity_of_particle_one - velocity_of_particle_two),
            (position_of_particle_one - position_of_particle_two))) /
       (length(position_of_particle_one - position_of_particle_two) *
        length(position_of_particle_one - position_of_particle_two))) *
          (position_of_particle_one - position_of_particle_two));
}

// Code from Stack OverFlow, to create a random float between two numbers
float GasContainer::RandomFloat(float min, float max) {
  assert(max > min);
  float random = ((float)rand()) / (float)RAND_MAX;
  float range = max - min;

  return (random * range) + min;
}

}  // namespace idealgas
