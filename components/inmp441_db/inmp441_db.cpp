#include "inmp441_db.h"
#include "esphome/core/log.h"

namespace esphome {
namespace inmp441_db {

static const char *TAG = "inmp441_db";

void INMP441DB::setup() {
  ESP_LOGI(TAG, "INMP441DB sensor setup complete");
}

void INMP441DB::dump_config() {
  ESP_LOGCONFIG(TAG, "INMP441DB Sensor");
}

}  // namespace inmp441_db
}  // namespace esphome
