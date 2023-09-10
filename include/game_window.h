#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "brick.h"
#include "ball.h"
#include "paddle.h"

using glm::vec2;

namespace brickbreaker {

/**
 * The game window in which all of the bricks and balls and the paddle are contained.
 */
    class GameWindow {
    public:
        /**
         * default constructor
         */
        GameWindow();
        GameWindow(int radom);

        /**
         * Displays the game window.
         */
        void Display();

        /**
         * Updates the position of the paddle to the right.
         */
        void AdvanceOneFrameRight();

        /**
         * Updates the position of the paddle to the left.
         */
        void AdvanceOneFrameLeft();

        /**
         * Calls all functions that handle collisions
         */
        void AdvanceOneFrame();

        /**
         * Handles the collisions of the Bricks with the ball
         */
        void HandleBrickBallCollision();

        /**
         * Handles the collisions of the Walls and the Ball
         */
        void HandleBallWallCollision();

        /**
         * Handles the collisions of the Paddle with the Ball
         */
        void HandleBallPaddleCollision();

        /**
         * Destroys the brick at given position
         * @param position of the brick
         */
        void DestroyBrick(std::vector<Brick>& vector, size_t position);

        /**
         * Destroys all bricks when the ball leaves the screen
         */
        void EndGame();

        /**
         * Takes in the angle and sends the ball in the direction of that angle
         */
        void GiveBallVelocity(int angle);

        /**
         * Handles the collisions between ball and power up
         */
        void HandleBallPowerUpCollision();

        /**
         * Returns the velocity of the ball
         * @return ball velocity
         */
        glm::vec2& GetBallVelocity();
        /**
         * Returns the position of the ball
         * @return ball position
         */
        glm::vec2& GetBallPosition();

        //returns number of bricks destroyed
        int GetNumBricksDestroyed() const;

        /**
         * Lower Left coordinates of the paddle
         * @return paddle coordinates
         */
        glm::vec2& GetPaddleLowerPosition();

        /**
         * Upper Right coordinates of the paddle
         * @return upper right coordinates
         */
        glm::vec2& GetPaddleUpperPosition();

        /**
         * Returns list of power Ups
         * @return power up list
         */
        std::vector<Brick>& GetListOfPowerUps();

        //ball radius
        float GetBallRadius();
    private:
        /**
         * upper_left_ describes the coordinates of the upper left of the paddle.
         * lower_right_ describes the coordinates of the lower right of the paddle.
         */
        glm::vec2 upper_left_ = glm::vec2(300, 800);
        glm::vec2 lower_right_ = glm::vec2(500, 750);
        glm::vec2 ball_center = glm::vec2(400, 725);
        float ball_radius = 25;
        glm::vec2 initial_velocity = glm::vec2(0,0);
        size_t kLeftEdge = 0;
        size_t kRightEdge = 875;
        size_t kTopEdge = 0;
        int k_num_bricks_ = 27;
        int k_num_columns_ = 3;
        Paddle paddle_;
        Ball ball_;
        std::vector<Brick> bricks_;
        std::vector<Brick> powerUps_;
        int num_bricks_destroyed = 0;
        Brick brick2_;
        Brick brick3_;
        std::vector<glm::vec2> vector_of_angles;
        bool flag = false;
    };

}  // namespace brickbreaker