#include "brick_breaker_app.h"

using brickbreaker::BrickBreakerClass;

void prepareSettings(BrickBreakerClass::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(BrickBreakerClass, ci::app::RendererGl, prepareSettings);
