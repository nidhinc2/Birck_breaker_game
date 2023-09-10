#pragma once

#include <cinder/app/KeyEvent.h>
#include "cinder/gl/gl.h"
using glm::vec2;
using std::string;

namespace brickbreaker {
    class Brick {
        public:

        /**
         * Default Constructor
         */
        Brick();

        /**
         * Constructor to create brick object
         * @param set_lower_dim
         * @param set_upper_dim
         * @param set_color
         */
        Brick(const glm::vec2& set_lower_dim, const glm::vec2& set_upper_dim, ci::Color set_color);

        /**
         * Displays the brick object
         */
        void BrickDisplay() const;

        /**
         * Returns the Lower Left coordinates of the brick
         * @return vector with the lower left coordinates
         */
        glm::vec2& GetBrickLowerPosition();

        /**
         * Retturns the Upper Right Coordinates of the brick
         * @return vector with the Upper Right coordinates
         */
        glm::vec2& GetBrickUpperPosition();
        ci::Color GetBrickColor();
        void SetBrickColor(ci::Color color);
    private:
        glm::vec2 upper_dimensions_;
        glm::vec2 lower_dimensions;
        ci::Color color_;
    };
}  // namespace brickbreaker
