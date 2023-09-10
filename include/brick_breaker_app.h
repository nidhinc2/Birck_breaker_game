#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_window.h"

namespace brickbreaker {

/**
 * An app for visualizing the game screen
 */
class BrickBreakerClass : public ci::app::App {
 public:
  BrickBreakerClass();
  /**
   * draws the game screen.
   */
  void draw() override;

  /**
   * Calls all the functions that handle collisions
   */
  void update() override;

  /**
   * Takes in either left arrow or right arrow key and calls the appropriate advance frame function.
   * @param event
   */
  void keyDown(ci::app::KeyEvent event) override;

  //size of screen
  const int kWindowSize = 875;

 private:
  GameWindow window_;
};

}  // namespace brickbreaker
