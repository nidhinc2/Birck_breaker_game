#include "game_window.h"
#include "brick.h"
#include <iostream>
#include <utility>

namespace brickbreaker {

    using glm::vec2;

    GameWindow::GameWindow() = default;
    GameWindow::GameWindow(int random) {
        Ball ball(ball_center, ball_radius, initial_velocity);
        Paddle paddle(upper_left_, lower_right_, ci::Color("teal"));
        ball_ = ball;
        paddle_ = paddle;
        num_bricks_destroyed = 0;
        int col_count = 0;
        int add_factor = 0;
        for (int j = 0; j < k_num_columns_; ++j) {
            for (int i = 0; i < k_num_columns_; ++i) {
                Brick brick(glm::vec2(0 + add_factor, 70 + col_count), glm::vec2(100 + add_factor, 50 + col_count), ci::Color("yellow"));
                Brick brick2(glm::vec2(100 + add_factor, 70 + col_count), glm::vec2(200 + add_factor, 50 + col_count), ci::Color("green"));
                Brick brick3(glm::vec2(200 + add_factor, 70 + col_count), glm::vec2(300 + add_factor, 50 + col_count), ci::Color("orange"));
                bricks_.push_back(brick);
                bricks_.push_back(brick2);
                bricks_.push_back(brick3);
                col_count += 70;
            }
            add_factor += 300;
        }
        Brick powerUp1(glm::vec2(0, 280), glm::vec2(100, 260), ci::Color("blue"));
        Brick powerUp2(glm::vec2(300, 210), glm::vec2(400, 190), ci::Color("pink"));
        Brick powerUp3(glm::vec2(600, 280), glm::vec2(700, 260), ci::Color("white"));
        Brick powerUp4(glm::vec2(300, 490), glm::vec2(400, 470), ci::Color("brown"));
        powerUps_.push_back(powerUp1);
        powerUps_.push_back(powerUp2);
        powerUps_.push_back(powerUp3);
        powerUps_.push_back(powerUp4);
    }

    void GameWindow::Display() {
        if (num_bricks_destroyed == k_num_bricks_) {
            ci::Color background_color("black");
            ci::gl::clear(background_color);
            ci::gl::drawStringCentered("GAME WON", glm::vec2(437.5, 437.5), ci::Color("white"));
        } else {
            ci::gl::drawStringCentered("Score: " + std::to_string(num_bricks_destroyed), glm::vec2(700,100), ci::Color("white"));
            for (Brick& brick : bricks_) {
                brick.BrickDisplay();
            }
            for (Brick& brick : powerUps_) {
                brick.BrickDisplay();
            }
            ball_.BallDisplay();
            paddle_.DisplayPaddle();
            brick2_.BrickDisplay();
            brick3_.BrickDisplay();
        }

    }

    void GameWindow::AdvanceOneFrameRight() {
        if (paddle_.GetPaddleLowerPosition().x == kRightEdge) {
            return;
        } else {
            paddle_.MovePaddleRight();
        }

    }
    void GameWindow::AdvanceOneFrameLeft() {
        if (paddle_.GetPaddleUpperPosition().x == kLeftEdge) {
            return;
        } else {
            paddle_.MovePaddleLeft();
        }
    }

    void GameWindow::HandleBrickBallCollision() {
        glm::vec2& ball_position = ball_.GetBallPosition();
        glm::vec2& ball_velocity = ball_.GetBallVelocity();

        for (size_t i = 0; i < bricks_.size(); i++) {
            Brick brick = bricks_[i];
            glm::vec2& brick_lower_position = brick.GetBrickLowerPosition();
            glm::vec2& brick_upper_position = brick.GetBrickUpperPosition();

            if ((abs(ball_position.y - brick_lower_position.y) < ball_.GetBallRadius())
                && (brick_lower_position.x < ball_position.x)
                && (ball_position.x < brick_upper_position.x)) {
                ball_velocity.y = -ball_velocity.y;
                DestroyBrick(bricks_, i);
                num_bricks_destroyed += 1;
            } else if ((abs(ball_position.y - brick_upper_position.y) < ball_.GetBallRadius())
                       && (brick_lower_position.x < ball_position.x)
                       && (ball_position.x < brick_upper_position.x)) {
                ball_velocity.y = -ball_velocity.y;
                DestroyBrick(bricks_, i);
                num_bricks_destroyed += 1;
            } else if ((abs(ball_position.x - brick_upper_position.x) < ball_.GetBallRadius())
                       && (brick_upper_position.y < ball_position.y)
                       && (ball_position.y < brick_lower_position.y)) {
                ball_velocity.y = -ball_velocity.y;

                DestroyBrick(bricks_, i);
                num_bricks_destroyed += 1;
            }
        }
    }

    void GameWindow::HandleBallWallCollision() {
        glm::vec2 current_position = ball_.GetBallPosition();
        glm::vec2& current_velocity = ball_.GetBallVelocity();
        float radius = ball_.GetBallRadius();
        if ((abs(current_position.x - kLeftEdge) < radius) ||
            (abs(current_position.x - kRightEdge) < radius)) {
            current_velocity.x = -current_velocity.x;
        }
        if ((abs(current_position.y - kTopEdge) < radius)) {
            current_velocity.y = -current_velocity.y;
        }
    }

    void GameWindow::HandleBallPaddleCollision() {
        glm::vec2& ball_position = ball_.GetBallPosition();
        glm::vec2& current_velocity = ball_.GetBallVelocity();
        glm::vec2& paddle_lower_position = paddle_.GetPaddleLowerPosition();
        glm::vec2& paddle_upper_position = paddle_.GetPaddleUpperPosition();
        if(((abs(ball_position.y - paddle_lower_position.y) < ball_.GetBallRadius())
            && (paddle_upper_position.x < ball_position.x)
            && (ball_position.x < paddle_lower_position.x))) {
            current_velocity.y = -current_velocity.y;
        }
    }

    void GameWindow::AdvanceOneFrame() {
        HandleBallWallCollision();
        HandleBrickBallCollision();
        ball_.MoveBall();
        HandleBallPaddleCollision();
        HandleBallPowerUpCollision();
        EndGame();

    }

    void GameWindow::DestroyBrick(std::vector<Brick>& vector, size_t position) {
        vector.erase(vector.begin() + position);
    }

    void GameWindow::EndGame() {
        if (ball_.GetBallPosition().y > kRightEdge) {
            for (size_t i = 0; i < bricks_.size(); ++i) {
                DestroyBrick(bricks_, i);
            }
            for (size_t i = 0; i < powerUps_.size(); ++i) {
                DestroyBrick(powerUps_, i);
            }
        }
    }


    void GameWindow::GiveBallVelocity(int angle) {
        vector_of_angles.emplace_back(-2,3);
        vector_of_angles.emplace_back(-1, 3);
        vector_of_angles.emplace_back(0.5, 3);
        vector_of_angles.emplace_back(1,3);
        vector_of_angles.emplace_back(2, 3);
        glm::vec2& velocity = ball_.GetBallVelocity();
        velocity = vector_of_angles.at(angle);
    }

    void GameWindow::HandleBallPowerUpCollision() {
        glm::vec2 ball_position = ball_.GetBallPosition();
        glm::vec2& current_velocity = ball_.GetBallVelocity();

        for (size_t i = 0; i < powerUps_.size(); i++) {
            Brick& powerUp = powerUps_[i];
            glm::vec2& powerUp_lower_position = powerUp.GetBrickLowerPosition();
            glm::vec2& powerUp_upper_position = powerUp.GetBrickUpperPosition();
            glm::vec2& paddle_lower_position = paddle_.GetPaddleLowerPosition();
            glm::vec2& paddle_upper_position = paddle_.GetPaddleUpperPosition();
            if((abs(ball_position.y - powerUp_lower_position.y) < ball_.GetBallRadius())
               && (powerUp_lower_position.x < ball_position.x)
               && (ball_position.x < powerUp_upper_position.x) && powerUp.GetBrickColor() == ci::Color("blue")) {
                DestroyBrick(powerUps_, i);
                current_velocity.y = -current_velocity.y;
                current_velocity.y -= 2;
            } else if ((abs(ball_position.y - powerUp_lower_position.y) < ball_.GetBallRadius())
                       && (powerUp_lower_position.x < ball_position.x)
                       && (ball_position.x < powerUp_upper_position.x) && powerUp.GetBrickColor() == ci::Color("pink")) {
                DestroyBrick(powerUps_, i);
                current_velocity.y = -current_velocity.y;

                paddle_.SetPaddleLowerPosition(glm::vec2(paddle_lower_position.x + 70, paddle_lower_position.y));
            } else if ((abs(ball_position.y - powerUp_lower_position.y) < ball_.GetBallRadius())
                       && (powerUp_lower_position.x < ball_position.x)
                       && (ball_position.x < powerUp_upper_position.x) && powerUp.GetBrickColor() == ci::Color("white")) {
                DestroyBrick(powerUps_, i);
                current_velocity.y = -current_velocity.y;
                ball_.SetBallRadius(40);
            } else if ((abs(ball_position.y - powerUp_lower_position.y) < ball_.GetBallRadius())
                       && (powerUp_lower_position.x < ball_position.x)
                       && (ball_position.x < powerUp_upper_position.x) && powerUp.GetBrickColor() == ci::Color("brown")) {
                DestroyBrick(powerUps_, i);
                current_velocity.y = -current_velocity.y;
                paddle_.SetPaddleLowerPosition(glm::vec2(paddle_lower_position.x, lower_right_.y + 50));
                paddle_.SetPaddleUpperPosition(glm::vec2(paddle_upper_position.x, upper_left_.y + 50));
            }
        }
    }

    glm::vec2& GameWindow::GetBallVelocity() {
        glm::vec2& ball_velocity = ball_.GetBallVelocity();
        return ball_velocity;
    }

    glm::vec2& GameWindow::GetBallPosition() {
        return ball_.GetBallPosition();
    }

    int GameWindow::GetNumBricksDestroyed() const {
        return num_bricks_destroyed;
    }

    glm::vec2& GameWindow::GetPaddleLowerPosition() {
        return paddle_.GetPaddleLowerPosition();
    }

    glm::vec2& GameWindow::GetPaddleUpperPosition() {
        return paddle_.GetPaddleUpperPosition();
    }

    std::vector<Brick>& GameWindow::GetListOfPowerUps() {
        return powerUps_;
    }

    float GameWindow::GetBallRadius() {
        return ball_.GetBallRadius();
    }


}  // namespace brickbreaker