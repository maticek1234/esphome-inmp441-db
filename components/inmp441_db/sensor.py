
"""ESPHome INMP441 DB Sensor Component"""

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID

CODEOWNERS = ["@maticek1234"]

inmp441_db_ns = cg.esphome_ns.namespace("inmp441_db")
INMP441DB = inmp441_db_ns.class_("INMP441DB", sensor.Sensor, cg.Component)

CONFIG_SCHEMA = sensor.sensor_schema(INMP441DB).extend(
    {
        cv.GenerateID(): cv.declare_id(INMP441DB),
    }
)

async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])
    await cg.register_component(var, config)
