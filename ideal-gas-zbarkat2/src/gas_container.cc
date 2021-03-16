#include "gas_container.h"

#include <iostream>

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(size_t radius, size_t number_of_particles) {
  //for loop used to go through the number of particles in a container instance, and add
  // that many Particle objects into a vector.
  for (size_t i = 0; i < number_of_particles; i++) {
    //particle objects have a radius, initial position, and initial velocity
    Particle particle(
        radius,
        vec2(RandomFloat(kRectangleXMin + radius, kRectangleXMax - radius),
             RandomFloat(kRectangleYMin + radius, kRectangleYMax - radius)),
        vec2(kInitialXVelocity, kInitialYVelocity));
    particles_.push_back(particle);
  }
}

void GasContainer::Display() const {
  //drawing the circles and the rectangular border
  DrawCircles();
  DrawRectangle();
}

void GasContainer::AdvanceOneFrame() {
  //for loop needed to go through every Particle in the vector, to then change
  for (size_t particle = 0; particle < particles_.size(); particle++) {
    BounceOffAnotherParticle(particle);

    BounceOffWall(particle);

    //changed velocity in both helper methods, not add that velocity to the position
    //for every particle
    particles_[particle].AddVelocityToPosition();
  }
}

void GasContainer::DrawCircles() const {
  //draws as many circles as Particle objects, also where the new position is put in
  for (size_t i = 0; i < particles_.size(); i++) {
    ci::gl::color(ci::Color("orange"));
    ci::gl::drawSolidCircle(
        vec2(particles_[i].getPosition().x, particles_[i].getPosition().y),
        (float)particles_[i].getRadius());
  }
}

void GasContainer::DrawRectangle() const {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(kRectangleXMin, kRectangleYMin),
                                    vec2(kRectangleXMax, kRectangleYMax)));
}

void GasContainer::BounceOffWall(size_t particle) {
  //variables created to make code readable
  float velocity_x = particles_[particle].getVelocity().x;
  float velocity_y = particles_[particle].getVelocity().y;
  float position_x = particles_[particle].getPosition().x;
  float position_y = particles_[particle].getPosition().y;
  size_t radius = particles_[particle].getRadius();

  //if the position in the x direction is either hitting the left or right wall
  if (position_x - radius <= kRectangleXMin ||
      position_x + radius >= kRectangleXMax) {
    particles_[particle].setVelocity(vec2(-velocity_x, velocity_y));
  }
  //if the position in the y direction is hitting the top or bottom wall
  else if (position_y - radius <= kRectangleYMin ||
             position_y + radius >= kRectangleYMax) {
    particles_[particle].setVelocity(vec2(velocity_x, -velocity_y));
  }
}

void GasContainer::BounceOffAnotherParticle(size_t particle) {
  //goes through a for loop to go through every particle against one another
  for (size_t colliding_particle = particle + 1;
       colliding_particle < particles_.size(); colliding_particle++) {
    //variables created to make code more readable
    vec2 position_particle = particles_[particle].getPosition();
    vec2 position_colliding_particle =
        particles_[colliding_particle].getPosition();
    size_t radius_particle = particles_[particle].getRadius();
    size_t radius_colliding_particle =
        particles_[colliding_particle].getRadius();

    //if the distance between two particles is less then there radius, they are colliding
    if (distance(position_particle, position_colliding_particle) <=
        radius_particle + radius_colliding_particle) {
      //variables to make code more readable
      vec2 velocity_one = particles_[particle].getVelocity();
      vec2 position_one = particles_[particle].getPosition();
      vec2 velocity_two = particles_[colliding_particle].getVelocity();
      vec2 position_two = particles_[colliding_particle].getPosition();

      //if the dot product of the velocity/position of the two is less then 0
      //then they are not moving away from each other.
      if (dot((velocity_one - velocity_two), (position_one - position_two)) <
          0) {
        //sets the velocity of one particle
        SetVelocityOfParticles(particle, velocity_one, velocity_two,
                               position_one, position_two);

        //sets the velocity of the colliding particle
        SetVelocityOfParticles(colliding_particle, velocity_two, velocity_one,
                               position_two, position_one);

        //if they are colliding, break out of the for loop
        break;
      }
    }
  }
}

void GasContainer::SetVelocityOfParticles(size_t particle,
                                          const vec2& velocity_one,
                                          const vec2& velocity_two,
                                          const vec2& position_one,
                                          const vec2& position_two) {
  particles_[particle].setVelocity(
      velocity_one -
      ((dot((velocity_one - velocity_two), (position_one - position_two))) /
       (length(position_one - position_two) *
        length(position_one - position_two))) *
          (position_one - position_two));
}

// Code from Stack OverFlow, to create a random float between two numbers
float GasContainer::RandomFloat(float min, float max) {
  assert(max > min);
  float random = (static_cast<float>(rand())) / static_cast<float>(RAND_MAX);
  float range = max - min;

  return (random * range) + min;
}

const std::vector<Particle>& GasContainer::getParticles() const {
  return particles_;
}

void GasContainer::setParticles(const std::vector<Particle>& particles) {
  particles_ = particles;
}

}  // namespace idealgas
