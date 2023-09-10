#pragma once

#include <cinder/app/KeyEvent.h>
#include "cinder/gl/gl.h"
using glm::vec2;
using std::string;

namespace brickbreaker {
    class Ball {
    public:
        /**
         * Default Constructor
         */
        Ball();

        /**
         * Constructor to create the ball object
         * @param center
         * @param radius
         * @param initial_velocity
         */
        Ball(const glm::vec2& center, float radius, const glm::vec2& initial_velocity);

        /**
         * Displays the ball object
         */
        void BallDisplay() const;

        /**
         * Gives the co-ordinates of the center of the ball
         * @return the center coordinates
         */
        glm::vec2& GetBallPosition();

        /**
         * Gives the co-ordinates of the velocity of the ball
         * @return velocity vector
         */
        glm::vec2& GetBallVelocity();

        /**
         * returns radius of ball
         * @return radius
         */
        float GetBallRadius() const;

        /**
         * Moves the ball according to the change in velocity
         */
        void MoveBall();
        void SetBallRadius(float radius);
    private:
        ci::Color color_ = "purple";
        glm::vec2 center_;
        float radius_;
        glm::vec2 velocity_;
    };
}  // namespace brickbreaker

