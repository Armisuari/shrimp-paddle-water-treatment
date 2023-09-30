#pragma once

#include <sdkconfig.h>

#ifndef CONFIG_MAIN_FW_VERSION_STRING
#define CONFIG_MAIN_FW_VERSION_STRING                   "v0.0.2"
#endif /*CONFIG_MAIN_FW_VERSION_STRING*/

#ifndef CONFIG_MAIN_CLIENT_ID_PREFIX
#define CONFIG_MAIN_CLIENT_ID_PREFIX                    "tambak-"
#endif /*CONFIG_MAIN_CLIENT_ID_PREFIX*/

#ifndef CONFIG_MAIN_HOST_TB
#define CONFIG_MAIN_HOST_TB                             "demo.thingsboard.io"
#endif /*CONFIG_MAIN_HOST_TB*/

#ifndef CONFIG_MAIN_TB_PORT
#define CONFIG_MAIN_TB_PORT                             1883U
#endif /*CONFIG_MAIN_TB_PORT_CONTABO*/

#ifndef CONFIG_MAIN_MAX_MESSAGE_SIZE
#define CONFIG_MAIN_MAX_MESSAGE_SIZE                    128U
#endif /*CONFIG_MAIN_MQTT_RAW_TOPIC_CONTABO*/

#ifndef CONFIG_MAIN_WIFI_DEFAULT_SSID
#define CONFIG_MAIN_WIFI_DEFAULT_SSID                   "eFisheryPlus"
#endif /*CONFIG_MAIN_WIFI_DEFAULT_SSID*/

#ifndef CONFIG_MAIN_WIFI_DEFAULT_PASS
#define CONFIG_MAIN_WIFI_DEFAULT_PASS                   "123123123"
#endif /*CONFIG_MAIN_WIFI_DEFAULT_PASS*/

#ifndef CONFIG_SENSOR_TEMPERATURE_PIN
#define CONFIG_SENSOR_TEMPERATURE_PIN                    (4)
#endif /*CONFIG_SENSOR_TEMPERATURE_PIN*/

#ifndef CONFIG_SENSOR_ADS_PIN_DO
#define CONFIG_SENSOR_ADS_PIN_DO                         (0)
#endif /*CONFIG_SENSOR_ADS_PIN_DO*/

#if __has_include("TBCredentials.h")
    #include "TBCredentials.h"
#else
    #error Buat File "TBCredentials.h" yang berisi configurasi untuk thingboard DPS
    
    #define CONFIG_TB_TOKEN      ""
#endif /*__has_include("TBCredentials.h")*/