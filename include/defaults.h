
#define AIO_SERVER         "mqtt"
#define AIO_SERVERPORT     1883                   // Use 8883 for SSL
#define AIO_USERNAME       "iot"
#define AIO_KEY            "iot"

#define MODULE_01_SWITCH_PIN           2
#define MODULE_01_SWITCH_FEED         AIO_USERNAME "/" ROOM "/" MODULE_01_NAME "/switch"
#define MODULE_01_TEMPERATURE_FEED    AIO_USERNAME "/" ROOM "/" MODULE_01_NAME "/temperature"
#define MODULE_01_HUMIDITY_FEED       AIO_USERNAME "/" ROOM "/" MODULE_01_NAME "/humidity"
