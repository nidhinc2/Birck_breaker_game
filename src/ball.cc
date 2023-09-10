#include <ball.h>

namespace brickbreaker {
    Ball::Ball() {
        radius_ = 0;
    }

    Ball::Ball(const glm::vec2& center, float radius, const glm::vec2& initial_velocity) {
        center_ = center;
        radius_ = radius;
        velocity_ = initial_velocity;
    }

    void Ball::BallDisplay() const {
        ci::gl::color(color_);
        ci::gl::drawSolidCircle(center_, radius_);
    }

    glm::vec2& Ball::GetBallPosition() {
        return center_;
    }

    glm::vec2& Ball::GetBallVelocity() {
        return velocity_;
    }

    float Ball::GetBallRadius() const {
        return radius_;
    }

    void Ball::MoveBall() {
        center_.x+= velocity_.x;
        center_.y-= velocity_.y;
    }

    void Ball::SetBallRadius(float radius) {
        radius_ = radius;
    }

} // namespace brickbreaker


