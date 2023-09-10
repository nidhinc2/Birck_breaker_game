
#include <brick.h>

namespace brickbreaker {
    Brick::Brick() = default;

    Brick::Brick(const glm::vec2& set_lower_dim, const glm::vec2& set_upper_dim, ci::Color set_color) {
        lower_dimensions = set_lower_dim;
        upper_dimensions_ = set_upper_dim;
        color_ = set_color;
    }

    void Brick::BrickDisplay() const {
        ci::gl::color(color_);
        ci::gl::drawSolidRect(ci::Rectf(lower_dimensions, upper_dimensions_));
    }

    glm::vec2& Brick::GetBrickLowerPosition() {
        return lower_dimensions;
    }
    glm::vec2& Brick::GetBrickUpperPosition()  {
        return upper_dimensions_;
    }

    ci::Color Brick::GetBrickColor() {
        return color_;
    }

    void Brick::SetBrickColor(ci::Color color) {
        color_ = color;
    }


} // namespace brickbreaker
