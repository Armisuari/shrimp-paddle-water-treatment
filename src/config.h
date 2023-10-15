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
#define CONFIG_MAIN_WIFI_DEFAULT_SSID                   "MikroTik-61E76E"
#endif /*CONFIG_MAIN_WIFI_DEFAULT_SSID*/

#ifndef CONFIG_MAIN_WIFI_DEFAULT_PASS
#define CONFIG_MAIN_WIFI_DEFAULT_PASS                   ""
#endif /*CONFIG_MAIN_WIFI_DEFAULT_PASS*/

#ifndef CONFIG_SENSOR_TEMPERATURE_PIN
#define CONFIG_SENSOR_TEMPERATURE_PIN                    (5)
#endif /*CONFIG_SENSOR_TEMPERATURE_PIN*/

#ifndef CONFIG_SENSOR_ADS_PIN_PH
#define CONFIG_SENSOR_ADS_PIN_PH                         (1)
#endif /*CONFIG_SENSOR_ADS_PIN_DO*/

#ifndef CONFIG_SENSOR_ADS_PIN_DO
#define CONFIG_SENSOR_ADS_PIN_DO                         (2)
#endif /*CONFIG_SENSOR_ADS_PIN_DO*/

#ifndef CONFIG_SENSOR_ADS_PIN_EC
#define CONFIG_SENSOR_ADS_PIN_EC                         (3)
#endif /*CONFIG_SENSOR_ADS_PIN_DO*/

#ifndef CONFIG_TB_MSG_BUFF
#define CONFIG_TB_MSG_BUFF                               (8192)
#endif /*CONFIG_TB_MSG_BUFF*/

#if __has_include("TBCredentials.h")
    #include "TBCredentials.h"
#else
    #error Buat File "TBCredentials.h" yang berisi configurasi untuk thingboard token
    
    #define CONFIG_TB_TOKEN      "YOUR ACCES TOKEN"
#endif /*__has_include("TBCredentials.h")*/