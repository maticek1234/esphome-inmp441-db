#include "inmp441_db.h"
#include "esphome/core/log.h"

namespace esphome {
namespace inmp441_db {

static const char *TAG = "inmp441_db";

void INMP441DB::set_pins(GPIOPin *lrclk, GPIOPin *bclk, GPIOPin *din) {
  lrclk_pin_ = lrclk;
  bclk_pin_ = bclk;
  din_pin_ = din;
}

void INMP441DB::setup() {
  i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
      .sample_rate = 16000,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
      .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
      .communication_format = I2S_COMM_FORMAT_I2S,
      .intr_alloc_flags = 0,
      .dma_buf_count = 4,
      .dma_buf_len = 256,
      .use_apll = false,
      .tx_desc_auto_clear = false,
      .fixed_mclk = 0};

  i2s_pin_config_t pin_config = {
      .bck_io_num = bclk_pin_->get_pin(),
      .ws_io_num = lrclk_pin_->get_pin(),
      .data_out_num = I2S_PIN_NO_CHANGE,
      .data_in_num = din_pin_->get_pin()};

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
}

float INMP441DB::calculate_db(int32_t sample) {
  float normalized = abs(sample) / 2147483648.0;
  if (normalized <= 0.000001) return 0;
  return 20.0 * log10(normalized) + 120.0;
}

void INMP441DB::loop() {
  int32_t sample = 0;
  size_t bytes_read;

  i2s_read(I2S_NUM_0, &sample, sizeof(sample), &bytes_read, portMAX_DELAY);

  if (bytes_read > 0) {
    float db = calculate_db(sample);
    publish_state(db);
  }
}

}  // namespace inmp441_db
}  // namespace esphome
