#include "gas_container.h"

#include <iostream>

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(float largest_radius, size_t number_of_particles) {
  float medium_radius = (largest_radius / 3) * 2;
  float small_radius = largest_radius / 3;

  for (size_t i = 0; i < number_of_particles; i++) {
    float random_x_position = RandomFloat(kRectangleXMin + largest_radius,
                                          kRectangleXMax - largest_radius);
    float random_y_position = RandomFloat(kRectangleYMin + largest_radius,
                                          kRectangleYMax - largest_radius);

    if (i < number_of_particles / 3) {
      particles_.push_back(Particle(kLargeMass, largest_radius,
                                    vec2(random_x_position, random_y_position),
                                    vec2(kInitialXVelocity, kInitialYVelocity),
                                    "orange"));
    } else if (i < (number_of_particles / 3) * 2) {
      particles_.push_back(Particle(kMediumMass, medium_radius,
                                    vec2(random_x_position, random_y_position),
                                    vec2(kInitialXVelocity, kInitialYVelocity),
                                    "blue"));
    } else {
      particles_.push_back(Particle(
          kSmallMass, small_radius, vec2(random_x_position, random_y_position),
          vec2(kInitialXVelocity, kInitialYVelocity), "green"));
    }
  }
}

void GasContainer::Display() {
  for (Particle particle : particles_) {
    particle.DrawParticle();
  }

  histogram_small_mass_.Draw();
  histogram_large_mass_.Draw();
  histogram_medium_mass_.Draw();

  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(kRectangleXMin, kRectangleYMin),
                                    vec2(kRectangleXMax, kRectangleYMax)));
}

void GasContainer::AdvanceOneFrame() {
  std::vector<Particle> particles_large_mass;
  std::vector<Particle> particles_medium_mass;
  std::vector<Particle> particles_small_mass;

  for (size_t particle = 0; particle < particles_.size(); particle++) {
    Particle& current_particle = particles_[particle];
    for (size_t colliding_particle = particle + 1;
         colliding_particle < particles_.size(); colliding_particle++) {
      Particle& other_particle = particles_[colliding_particle];
      if (current_particle.BounceOff(other_particle)) {
        vec2 velocity_particle = current_particle.GetVelocity();
        vec2 velocity_other_particle = other_particle.GetVelocity();
        vec2 position_particle = current_particle.GetPosition();
        vec2 position_other_particle = other_particle.GetPosition();

        float mass_particle = current_particle.GetMass();
        float mass_other_particle = other_particle.GetMass();

        current_particle.UpdateVelocityCollision(velocity_other_particle,
                                                 position_other_particle,
                                                 mass_other_particle);

        other_particle.UpdateVelocityCollision(
            velocity_particle, position_particle, mass_particle);
      }
    }

    current_particle.BounceOffWall(kRectangleXMin, kRectangleYMin,
                                   kRectangleXMax, kRectangleYMax);

    if (current_particle.GetMass() == kLargeMass) {
      particles_large_mass.push_back(current_particle);
    } else if (current_particle.GetMass() == kMediumMass) {
      particles_medium_mass.push_back(current_particle);
    } else if (current_particle.GetMass() == kSmallMass) {
      particles_small_mass.push_back(current_particle);
    }

    current_particle.UpdatePosition();
  }

  histogram_large_mass_.Add(particles_large_mass);
  histogram_medium_mass_.Add(particles_medium_mass);
  histogram_small_mass_.Add(particles_small_mass);
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
