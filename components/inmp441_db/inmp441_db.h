#pragma once
#include "esphome.h"
#include "driver/i2s.h"

namespace esphome {
namespace inmp441_db {

class INMP441DB : public Component, public sensor::Sensor {
 public:
  void set_pins(GPIOPin *lrclk, GPIOPin *bclk, GPIOPin *din);
  void setup() override;
  void loop() override;

 protected:
  GPIOPin *lrclk_pin_;
  GPIOPin *bclk_pin_;
  GPIOPin *din_pin_;

  float calculate_db(int32_t sample);
};

}  // namespace inmp441_db
}  // namespace esphome
