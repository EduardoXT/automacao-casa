/* Simple GPIO Demo
   
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <sdkconfig.h>
#include <string.h>
#include <esp_log.h>

#include <app_reset.h>
#include "app_priv.h"

#define RMT_TX_CHANNEL RMT_CHANNEL_0
/* This is the button that is used for toggling the power */
#define BUTTON_GPIO          CONFIG_EXAMPLE_BOARD_BUTTON_GPIO
#define BUTTON_ACTIVE_LEVEL  0
/* This is the GPIO on which the power will be set */

#define OUTPUT_GPIO_poste  1ULL
#define OUTPUT_GPIO_varanda  2ULL
#define OUTPUT_GPIO_terraco  3ULL
#define OUTPUT_GPIO_frente  4ULL
#define OUTPUT_GPIO_lateral1  5ULL
#define OUTPUT_GPIO_lateral2  6ULL
#define OUTPUT_GPIO_quintal  7ULL
#define OUTPUT_GPIO_sala  8ULL

#define WIFI_RESET_BUTTON_TIMEOUT       3
#define FACTORY_RESET_BUTTON_TIMEOUT    10

esp_err_t app_driver_set_gpio(const char *name, bool state)
{
    if (strcmp(name, "Poste") == 0 {
        gpio_set_level(OUTPUT_GPIO_poste, state);
    } else if (strcmp(name, "Varanda") == 0) {
        gpio_set_level(OUTPUT_GPIO_varanda, state);
    } else if (strcmp(name, "Terraço") == 0) {
        gpio_set_level(OUTPUT_GPIO_terraco, state);
     } else if (strcmp(name, "Frente") == 0) {
        gpio_set_level(OUTPUT_GPIO_frente, state);
    } else if (strcmp(name, "Lateral Esquerdo") == 0) {
        gpio_set_level(OUTPUT_GPIO_lateral1, state);
    } else if (strcmp(name, "Lateral Direito") == 0) {
        gpio_set_level(OUTPUT_GPIO_lateral2, state);
    } else if (strcmp(name, "Quintal") == 0) {
        gpio_set_level(OUTPUT_GPIO_quintal, state);
    } else if (strcmp(name, "Sala") == 0) {
        gpio_set_level(OUTPUT_GPIO_sala, state);
    } else {
        return ESP_FAIL;
    }
    return ESP_OK;
}

void app_driver_init()
{
    app_reset_button_register(app_reset_button_create(BUTTON_GPIO, BUTTON_ACTIVE_LEVEL),
                WIFI_RESET_BUTTON_TIMEOUT, FACTORY_RESET_BUTTON_TIMEOUT);

    /* Configure power */
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = 1,
    };
    uint64_t pin_mask = (((uint64_t)1 << OUTPUT_GPIO_poste ) | ((uint64_t)1 << OUTPUT_GPIO_varanda ) | ((uint64_t)1 << OUTPUT_GPIO_terraco ) | ((uint64_t)1 << OUTPUT_GPIO_frente )
    | ((uint64_t)1 << OUTPUT_GPIO_lateral1 ) | ((uint64_t)1 << OUTPUT_GPIO_lateral2 ) | ((uint64_t)1 << OUTPUT_GPIO_quintal ) | ((uint64_t)1 << OUTPUT_GPIO_sala ));
    io_conf.pin_bit_mask = pin_mask;
    /* Configure the GPIO */
    gpio_config(&io_conf);
    gpio_set_level(OUTPUT_GPIO_poste, false);
    gpio_set_level(OUTPUT_GPIO_varanda, false);
    gpio_set_level(OUTPUT_GPIO_terraco, false);
    gpio_set_level(OUTPUT_GPIO_frente, false);
    gpio_set_level(OUTPUT_GPIO_lateral1, false);
    gpio_set_level(OUTPUT_GPIO_lateral2, false);
    gpio_set_level(OUTPUT_GPIO_quintal, false);
    gpio_set_level(OUTPUT_GPIO_sala, false);
}
