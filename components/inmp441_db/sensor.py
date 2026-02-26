import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, CONF_NAME
from esphome import pins

DEPENDENCIES = ["esp32"]

CONF_LRCLK = "lrclk_pin"
CONF_BCLK = "bclk_pin"
CONF_DIN = "din_pin"

inmp441_ns = cg.esphome_ns.namespace("inmp441_db")
INMP441DB = inmp441_ns.class_("INMP441DB", cg.Component, sensor.Sensor)

CONFIG_SCHEMA = (
    sensor.sensor_schema()
    .extend(
        {
            cv.GenerateID(): cv.declare_id(INMP441DB),
            cv.Required(CONF_LRCLK): pins.gpio_output_pin_schema,
            cv.Required(CONF_BCLK): pins.gpio_output_pin_schema,
            cv.Required(CONF_DIN): pins.gpio_input_pin_schema,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)

    lrclk = await cg.gpio_pin_expression(config[CONF_LRCLK])
    bclk = await cg.gpio_pin_expression(config[CONF_BCLK])
    din = await cg.gpio_pin_expression(config[CONF_DIN])

    cg.add(var.set_pins(lrclk, bclk, din))
