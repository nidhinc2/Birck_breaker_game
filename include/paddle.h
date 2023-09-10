#pragma once

#include <cinder/app/KeyEvent.h>
#include "cinder/gl/gl.h"
using glm::vec2;
using std::string;

namespace brickbreaker {
    class Paddle {
    public:
        /**
         * Default Constructor
         */
        Paddle();

        /**
         * Constructor to se the co-ordinates, and color of the paddle
         * @param set_lower_left
         * @param set_upper_right
         * @param set_color
         */
        Paddle(glm::vec2& set_lower_left, glm::vec2& set_upper_right, const ci::Color& set_color);

        /**
         * Displays the Paddle
         */
        void DisplayPaddle();

        /**
         * Moves the paddle to the right according to user input
         */
        void MovePaddleRight();

        /**
         * Moves the paddle left according to user input
         */
        void MovePaddleLeft();

        /**
         * Returns the Lower Left co-ordinates of the paddle
         * @return lower coordinates of paddle
         */
        glm::vec2& GetPaddleLowerPosition();

        /**
         * Returns the Lower Left co-ordinates of the paddle
         * @return upper coordinates of paddle
         */
        glm::vec2& GetPaddleUpperPosition();
        void SetPaddleLowerPosition(const glm::vec2& position);
        void SetPaddleUpperPosition(const glm::vec2& position);

    private:
        glm::vec2 upper_left_;
        glm::vec2 lower_right_;
        ci::Color color_;

    };
}  // namespace brickbreaker
