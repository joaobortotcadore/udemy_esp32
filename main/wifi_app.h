/*
 * wifi_app.h
 *
 *  Created on: 18 de mai. de 2023
 *      Author: joao.cadore
 */

#ifndef MAIN_WIFI_APP_H_
#define MAIN_WIFI_APP_H_

#include "esp_netif.h"
#include "esp_wifi_types.h"
#include "freertos/FreeRTOS.h"

//WiFi application settings
#define WIFI_AP_SSID				"ESP32_AP" 			// AP name
#define WIFI_AP_PASSWORD			"password" 			// AP password
#define WIFI_AP_CHANNEL				1		   			// AP channel (https://www.espressif.com/sites/default/files/documentation/esp8266_wi-fi_channel_selection_guidelines_en.pdf)
#define WIFI_AP_SSID_HIDDEN			0		   			// AP visibility
#define WIFI_AP_MAX_CONNECTIONS		5		   			// AP max clients
#define WIFI_AP_BEACON_INTERVAL		100		   			// AP beacon: 100ms recommended (https://docs.espressif.com/projects/esp-idf/en/release-v4.2/esp32/api-guides/wifi.html#ap-basic-configuration)
#define WIFI_AP_IP					"192.168.0.1"		// AP de fault IP
#define WIFI_AP_GATEWAY				"192.168.0.1"		// AP default Gateway (should be the same as the IP)
#define WIFI_AP_NETMASK				"255.255.255.0"	    // AP netmask
#define WIFI_AP_BANDWIDTH			WIFI_BW_HT20		// AP bandwidth 20MHz (40 MHz is the other option) (https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/wifi.html#wi-fi-ht20-40)
#define WIFI_STA_POWER_SAVE			WIFI_PS_NONE		// Power save not used (https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/wifi.html#esp32-wi-fi-power-saving-mode)
#define MAX_SSID_LENGTH				32					// IEE standard maximum
#define MAX_PASSWORD_LENGTH			64					// IEE standard maximum
#define MAX_CONNECTION_RETRIES		5					// Retry number on disconnect

//netif object for the Station and Access Point
extern esp_netif_t* esp_netif_sta;
extern esp_netif_t* esp_netif_ap;

/**
 * Message IDs for the WiFi application task
 * @note Expand this based on your application requirements
 */
typedef enum wifi_app_message
{
	WIFI_APP_MSG_START_HTTP_SERVER = 0,
	WIFI_APP_MSG_CONNECTING_FROM_HTTP_SERVER,
	WIFI_APP_MSG_STA_CONNECTED_GOT_IP,
	WIFI_APP_MSG_USER_REQUESTED_STA_DISCONNECT,
	WIFI_APP_MSG_LOAD_SAVED_CREDENTIALS,
	WIFI_APP_MSG_STA_DISCONNECTED,
} wifi_app_message_e;

/**
 * Structure for the message queue
 * @note Expand this based on application requirements e.g. add another type and parameter as required
 */
typedef struct wifi_app_queue_message
{
	wifi_app_message_e msgID;
} wifi_app_queue_message_t;

/**
 * Sends a message to the queue
 * @param msgID message ID from the wifi_app_message_e enum.
 * @return pdTRUE if an item was successfully sent to the queue, otherwise pdFALSE
 * @note Expand the parameter list based on your requirements e.g. how you've expanded the wifi_app_queue_message_t
 */
BaseType_t wifi_app_send_message(wifi_app_message_e msgID);

/**
 * Starts the WiFi RTOS task
 */
void wifi_app_start(void);

#endif /* MAIN_WIFI_APP_H_ */
