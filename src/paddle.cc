
#include <paddle.h>

namespace brickbreaker {
    Paddle::Paddle() = default;

    Paddle::Paddle(glm::vec2& set_lower_left, glm::vec2& set_upper_right, const ci::Color& set_color) {
        upper_left_ = set_lower_left;
        lower_right_ = set_upper_right;
        color_ = set_color;
    }

    void Paddle::DisplayPaddle() {
        ci::gl::color(color_);
        ci::gl::drawSolidRect(ci::Rectf(upper_left_, lower_right_));
    }

    void Paddle::MovePaddleRight() {
        upper_left_.x+= 5;
        lower_right_.x+= 5;
    }

    void Paddle::MovePaddleLeft() {
        upper_left_.x-= 5;
        lower_right_.x-= 5;
    }

    glm::vec2& Paddle::GetPaddleLowerPosition() {
        return lower_right_;
    }

    glm::vec2& Paddle::GetPaddleUpperPosition() {
        return upper_left_;
    }

    void Paddle::SetPaddleLowerPosition(const glm::vec2& position) {
        lower_right_ = position;
    }

    void Paddle::SetPaddleUpperPosition(const glm::vec2& position) {
        upper_left_ = position;
    }


} // namespace brickbreaker