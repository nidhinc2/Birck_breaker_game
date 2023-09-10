#include "brick_breaker_app.h"

namespace brickbreaker {

    BrickBreakerClass::BrickBreakerClass() {
        ci::app::setWindowSize(kWindowSize, kWindowSize);
        auto gameWindow = GameWindow(9);
        window_ = gameWindow;
    }


    void BrickBreakerClass::draw() {
        ci::Color background_color("black");
        ci::gl::clear(background_color);
        window_.Display();
    }

    void BrickBreakerClass::keyDown(ci::app::KeyEvent event) {
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_RIGHT:
                window_.AdvanceOneFrameRight();
                break;

            case ci::app::KeyEvent::KEY_LEFT:
                window_.AdvanceOneFrameLeft();
                break;

            case ci::app::KeyEvent::KEY_1:
                window_.GiveBallVelocity(0);
                break;
            case ci::app::KeyEvent::KEY_2:
                window_.GiveBallVelocity(1);
                break;
            case ci::app::KeyEvent::KEY_3:
                window_.GiveBallVelocity(2);
                break;
            case ci::app::KeyEvent::KEY_4:
                window_.GiveBallVelocity(3);
                break;
            case ci::app::KeyEvent::KEY_5:
                window_.GiveBallVelocity(4);
                break;
        }
    }

    void BrickBreakerClass::update() {
        window_.AdvanceOneFrame();
    }

}  // namespace brickbreaker