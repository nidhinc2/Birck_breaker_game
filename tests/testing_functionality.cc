#include <catch2/catch.hpp>

#include <game_window.h>

using brickbreaker::GameWindow;
using brickbreaker::Ball;
using brickbreaker::Brick;

TEST_CASE("Testing initial state of the game") {
    GameWindow window(5);
    SECTION("1) Testing that angles are initialized correctly") {
        window.GiveBallVelocity(0);
        REQUIRE(window.GetBallVelocity().x == -2);
    }
    SECTION("2) Testing initial position of the ball") {
        REQUIRE(window.GetBallPosition().x == 400);
    }
    SECTION("3) Testing initial score") {
        REQUIRE(window.GetNumBricksDestroyed() == 0);
    }
}
TEST_CASE("Testing paddle movements") {
    GameWindow window(5);
    SECTION("1) Testing paddle movement to the right") {
        window.AdvanceOneFrameRight();
        REQUIRE(window.GetPaddleLowerPosition().x == 505);
    }
    SECTION("2) Testing paddle movement to the left") {
        window.AdvanceOneFrameLeft();
        REQUIRE(window.GetPaddleUpperPosition().x == 295);
    }
    SECTION("3) Testing that paddle doesnt cross the left boundary of screen") {
        while (window.GetPaddleUpperPosition().x != 0) {
            window.AdvanceOneFrameLeft();
        }
        REQUIRE(window.GetPaddleUpperPosition().x == 0);
    }
    SECTION("4) Testing that paddle doesn't cross the right boundary of the screen") {
        while (window.GetPaddleLowerPosition().x != 875) {
            window.AdvanceOneFrameRight();
        }
        REQUIRE(window.GetPaddleLowerPosition().x == 875);
    }
}
TEST_CASE("Testing collision of ball with a regular brick") {
    GameWindow window(5);
    window.GiveBallVelocity(2);
    while (abs(window.GetBallPosition().y -  420) > 25) {
        window.AdvanceOneFrame();
    }
    window.HandleBrickBallCollision();
    SECTION("1) Checking that the ball's velocity changes after collision and becomes negative") {
        REQUIRE(window.GetBallVelocity().y == -3);
    }
    SECTION("2) Checking that the brick gets destroyed on collision with the ball") {
        REQUIRE(window.GetNumBricksDestroyed() == 1);
    }
}
TEST_CASE("Testing collision of ball and paddle") {
    GameWindow window(5);
    window.GiveBallVelocity(2);
    while (abs(window.GetBallPosition().y -  420) > 25) {
        window.AdvanceOneFrame();
    }
    window.HandleBrickBallCollision();
    window.AdvanceOneFrameRight();
    while (abs(window.GetBallPosition().y - 750) >= 25) {
        window.AdvanceOneFrame();
    }
    window.HandleBallPaddleCollision();
    SECTION("Checking that velocity changes") {
        REQUIRE(window.GetBallVelocity().y == 3);
    }
    SECTION("Checking that 1 brick is already destroyed") {
        REQUIRE(window.GetNumBricksDestroyed() == 1);
    }
}
TEST_CASE("Testing collision of bricks with power ups") {
    GameWindow window(4);
    window.GiveBallVelocity(1);
    std::vector<Brick>& powerUps = window.GetListOfPowerUps();
    int count = 0;
    SECTION("1) Testing first power up that increases speed") {
        while (abs(window.GetBallPosition().y - powerUps[count].GetBrickLowerPosition().y) > 25) {
            window.AdvanceOneFrame();
        }
        window.HandleBallPowerUpCollision();
        REQUIRE(window.GetBallVelocity().y == -7);
    }
    count++;
    SECTION("2) Testing second power up that increases paddle length") {
        while (abs(window.GetBallPosition().y - powerUps[count].GetBrickLowerPosition().y) > 25) {
            window.AdvanceOneFrame();
        }
        for (int i = 0; i < 9; i++) {
            window.AdvanceOneFrameLeft();
        }
        window.HandleBallPowerUpCollision();
        REQUIRE(window.GetPaddleLowerPosition().x == 570);
    }
    count++;
    SECTION("3) Testing third power up that increases ball radius") {
        while (abs(window.GetBallPosition().y - powerUps[count].GetBrickLowerPosition().y) > 25) {
            window.AdvanceOneFrame();
        }
        window.HandleBallPowerUpCollision();
        REQUIRE(window.GetBallRadius() == 40);
    }
    count++;
    SECTION("4) Testing fourth power up that lowers the paddle") {
        while (abs(window.GetBallPosition().y - powerUps[count].GetBrickLowerPosition().y) > 25) {
            window.AdvanceOneFrame();
        }
        window.HandleBallPowerUpCollision();
        REQUIRE(window.GetPaddleLowerPosition().y == 800);
    }
}
TEST_CASE("Testing collision of ball and wall") {
    GameWindow window(9);
    window.GiveBallVelocity(4);
    SECTION("Check for horizontal collision") {
        while (abs(window.GetBallPosition().x - 875) > 25) {
            window.AdvanceOneFrame();
        }
        window.HandleBallWallCollision();
        REQUIRE(window.GetBallVelocity().x == -2);
    }
    SECTION("Check for vertical collision") {
        while (abs(window.GetBallPosition().y - 0) > 25) {
            window.AdvanceOneFrame();
        }
        window.HandleBallWallCollision();
        REQUIRE(window.GetBallVelocity().y == -3);
    }

}
