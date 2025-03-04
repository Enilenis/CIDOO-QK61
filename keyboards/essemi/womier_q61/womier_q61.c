/* Copyright 2023 Finalkey
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "../../lib/rdr_lib/rdr_common.h"

void matrix_io_delay(void) {
}

void matrix_output_select_delay(void) {
}

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
}

led_config_t g_led_config = { {
    { 0        , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED    },
	{ NO_LED   , 1        , 2        , 3        , 4        , 5        , 6        , 7        , 8        , 9        , 10       , 11       , 12       , 13       , NO_LED   , NO_LED    },
	{ 14       , 15       , 16       , 17       , 18       , 19       , 20       , 21       , 22       , 23       , 24       , 25       , 26       , 27       , NO_LED   , NO_LED    },
	{ 28       , 29       , 30       , 31       , 32       , 33       , 34       , 35       , 36       , 37       , 38       , 39       , NO_LED   , 40       , NO_LED   , NO_LED    },
	{ 41       , NO_LED   , 42       , 43       , 44       , 45       , 46       , 47       , 48       , 49       , 50       , 51       , 52       , 53       , NO_LED   , NO_LED    },
	{ 54       , 55       , 56       , NO_LED   , NO_LED   , 57       , NO_LED   , NO_LED   , NO_LED   , 58       , 59       , 60       , 61       , 62       , NO_LED   , NO_LED    }
},{
    { 0 , 10},  { 16, 10},  { 32, 10},  { 48, 10},  { 64, 10},   { 80, 10},  { 96,  10}, { 112, 10}, { 128, 10}, { 144, 10}, { 160, 10}, { 176, 10}, { 192, 10}, { 220, 10},
    { 4 , 20},  { 24, 20},  { 40, 20},  { 56, 20},  { 72, 20},   { 88, 20},  { 104, 20}, { 120, 20}, { 136, 20}, { 152, 20}, { 168, 20}, { 184, 20}, { 200, 20}, { 222, 20},
    { 4 , 30},  { 28, 30},  { 44, 30},  { 60, 30},  { 76, 30},   { 92, 30},  { 108, 30}, { 124, 30}, { 140, 30}, { 156, 30}, { 172, 30}, { 188, 30},             { 216, 30},
    { 8 , 40},              { 35, 40},  { 51, 40},  { 67, 40},   { 83, 40},  { 99 , 40}, { 115, 40}, { 131, 40}, { 147, 40}, { 163, 40}, { 180, 40}, { 208, 40}, { 224, 40},
    { 0 , 50},  { 20, 50},  { 40, 50},                           { 110,50},                                      { 160, 50}, { 176, 50}, { 192, 50}, { 208, 40}, { 224, 40},

    { 225, 65}, { 225, 65}, {225, 65}
}, {
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,
    1,      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,          1,              1,  1,  1,  1,  1,

    0,  0, 0
} };
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    User_Led_Show();
    return false;
}

void notify_usb_device_state_change_user(enum usb_device_state usb_device_state)  {
    if (Keyboard_Info.Key_Mode == QMK_USB_MODE) {
        if(usb_device_state == USB_DEVICE_STATE_CONFIGURED) {
            Usb_If_Ok = true;//usb枚举完成
            Usb_If_Ok_Led = true;
            Usb_If_Ok_Delay = 0;
        } else {
            Usb_If_Ok = false;
		    Usb_If_Ok_Led = false;
        }
    } else {
        Usb_If_Ok = false;
	    Usb_If_Ok_Led = false;
    }
}

void housekeeping_task_user(void) {
    if (User_EE_CLR_Start_Flag) {
        User_EE_CLR_Start_Flag = false;
        User_Keyboard_Reset();
        return;
    }

    es_chibios_user_idle_loop_hook();
}

void board_init(void) {
    User_Keyboard_Init();
}

void keyboard_post_init_user(void) {
    User_Keyboard_Post_Init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {   /*键盘只要有按键按下就会调用此函数*/
    Usb_Change_Mode_Delay = 0;                                      /*只要有按键就不会进入休眠*/
    Usb_Change_Mode_Wakeup = false;

    switch (keycode) {
        case QMK_KB_MODE_2P4G: {                                    //2.4G
            if (Keyboard_Info.Key_Mode != QMK_2P4G_MODE) {
                return true;
            }
            if (record->event.pressed) {
                Key_2p4g_Status = true;
            } else {
                Key_2p4g_Status = false;
            }
            Time_3s_Count = 0;
        } return true;
        case QMK_KB_MODE_BLE1: {                                    //BLE 1
            if (Keyboard_Info.Key_Mode != QMK_BLE_MODE) {
                return true;
            }
            if (record->event.pressed) {
                Key_Ble_1_Status = true;
                if (Keyboard_Info.Ble_Channel != QMK_BLE_CHANNEL_1) {
                    Keyboard_Info.Ble_Channel = QMK_BLE_CHANNEL_1;
                    Spi_Send_Commad(USER_SWITCH_BLE_1_MODE);        /*发送SPI命令*/
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = true;
                }
            } else {
                Key_Ble_1_Status = false;
            }
            Time_3s_Count = 0;
        } return true;
        case QMK_KB_MODE_BLE2: {                                    //BLE 2
            if (Keyboard_Info.Key_Mode != QMK_BLE_MODE) {
                return true;
            }

            if (record->event.pressed) {
                Key_Ble_2_Status = true;
                if (Keyboard_Info.Ble_Channel != QMK_BLE_CHANNEL_2) {
                    Keyboard_Info.Ble_Channel = QMK_BLE_CHANNEL_2;
                    Spi_Send_Commad(USER_SWITCH_BLE_2_MODE);        /*发送SPI命令*/
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = true;
                }
            } else {
                Key_Ble_2_Status = false;
            }
            Time_3s_Count = 0;
        } return true;
        case QMK_KB_MODE_BLE3: {                                    //BLE 3
            if (Keyboard_Info.Key_Mode != QMK_BLE_MODE) {
                return true;
            }

            if (record->event.pressed) {
                Key_Ble_3_Status = true;
                if (Keyboard_Info.Ble_Channel != QMK_BLE_CHANNEL_3) {
                    Keyboard_Info.Ble_Channel = QMK_BLE_CHANNEL_3;
                    Spi_Send_Commad(USER_SWITCH_BLE_3_MODE);        /*发送SPI命令*/
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = true;
                }
            } else {
                Key_Ble_3_Status = false;
            }
            Time_3s_Count = 0;
        } return true;
        case QMK_KB_MODE_USB: {                                     //USB
            if (record->event.pressed) {
                if (Keyboard_Info.Key_Mode != QMK_USB_MODE) {
                    Keyboard_Info.Key_Mode = QMK_USB_MODE;
                    Spi_Send_Commad(USER_SWITCH_USB_MODE);          /*发送SPI命令*/
                    es_restart_usb_driver();
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = false;
                }
            }
        } return true;
        case QMK_BATT_NUM: {                                        //电池状态显示
            if (record->event.pressed) {
                User_Key_Batt_Num_Show = true;
                User_Key_Batt_Count = 0;
            } else {
                User_Key_Batt_Num_Show = false;
                User_Key_Batt_Count = 0;
            }
        } return true;
        case QMK_WIN_LOCK: {                                        //锁WIN
            if (!record->event.pressed) {
                if (Keyboard_Info.Mac_Win_Mode == INIT_MAC_MODE) {
                    if (Keyboard_Info.Win_Lock == INIT_WIN_LOCK) {
                        Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
                        Save_Flash_Set();
                    }
                } else {
                    if (Keyboard_Info.Win_Lock == INIT_WIN_NLOCK) {
                        Keyboard_Info.Win_Lock = INIT_WIN_LOCK;
                        unregister_code(KC_LGUI); unregister_code(KC_RGUI); unregister_code(KC_APP);
                    } else {
                        Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
                    }
                    Save_Flash_Set();
                }
            }
        } return true;
        case QMK_KB_SIX_N_CH: {                                     //六键全键无冲切换
            if (record->event.pressed) {
                if(keymap_config.nkro) {
                    es_change_qmk_nkro_mode_disable();
                    Mac_Win_Point_Count = 3;
                } else {
                    es_change_qmk_nkro_mode_enable();
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case KC_LGUI: {                                             //key_win_l
            if (Keyboard_Info.Win_Lock) {
                record->event.pressed = false;
            }
        } return true;
        case KC_RGUI: {                                             //key_win_r
            if (Keyboard_Info.Win_Lock) {
                record->event.pressed = false;
            }
        } return true;
        case KC_APP: {                                              //key_app
            if (Keyboard_Info.Win_Lock) {
                record->event.pressed = false;
            }
        } return true;
        case RGB_VAI: {                                             //亮度加
            if (!record->event.pressed) {
                if (rgb_matrix_get_val() >= RGB_MATRIX_MAXIMUM_BRIGHTNESS) {
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case RGB_VAD: {                                             //亮度减
            if (!record->event.pressed) {
                if (rgb_matrix_get_val() <= 0) {
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case RGB_SPI: {                                             //速度加
            if (!record->event.pressed) {
                if (rgb_matrix_get_speed() >= 255) {
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case RGB_SPD: {                                             //速度减
            if (!record->event.pressed) {
                if (rgb_matrix_get_speed() <= 0) {
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case RGB_RTOG: {                                            //开关闭背光
            if (!record->event.pressed) {
                if (Keyboard_Info.Led_On_Off) {
                    Keyboard_Info.Logo_On_Off = INIT_LED_ON;
                    Keyboard_Info.Led_On_Off = INIT_LED_ON;
                    if (rgb_matrix_get_val() <= 0) {                // 获取当前指示灯亮度
                        rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), RGB_MATRIX_MAXIMUM_BRIGHTNESS);//设置RGB灯的色相（hue）、饱和度(sat)、亮度
                    }
                } else {
                    Keyboard_Info.Logo_On_Off = INIT_LED_OFF;
                    Keyboard_Info.Led_On_Off = INIT_LED_OFF;
                }
                Save_Flash_Set();
            }
        } return true;
        case MO(2): {                                               //FN
            if (record->event.pressed) {
                Key_Fn_Status = true;
            } else {
                Key_Fn_Status = false;
            }
        } return true;
        case MO(3): {                                               //FN
            if (record->event.pressed) {
                Key_Fn_Status = true;
            } else {
                Key_Fn_Status = false;
            }
        } return true;
        case TO(0): {                                               //WIN
            if (!record->event.pressed) {
                if ((record->event.key.col == WIN_COL) && (record->event.key.row == WIN_ROL) && (Keyboard_Info.Mac_Win_Mode != INIT_WIN_MODE)) {
                    Keyboard_Info.Mac_Win_Mode = INIT_WIN_MODE;
                    Mac_Win_Point_Count = 1;
                    unregister_code(KC_LALT); unregister_code(KC_LGUI); unregister_code(KC_RALT); unregister_code(KC_RGUI); unregister_code(KC_APP);
                    Save_Flash_Set();
                }
            }
        } return true;
        case TO(1): {                                               //MAC
            if (!record->event.pressed) {
                if ((record->event.key.col == MAC_COL) && (record->event.key.row == MAC_ROL) && (Keyboard_Info.Mac_Win_Mode != INIT_MAC_MODE)) {
                    Keyboard_Info.Mac_Win_Mode = INIT_MAC_MODE;
                    Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
                    Mac_Win_Point_Count = 3;
                    unregister_code(KC_LALT); unregister_code(KC_LGUI); unregister_code(KC_RALT); unregister_code(KC_RGUI); unregister_code(KC_APP);
                    Save_Flash_Set();
                }
            }
        } return true;
        case U_EE_CLR: {                                              //系统复位
            if (record->event.pressed) {
                User_QMK_EE_CLR_Flag = true;
            } else {
                User_QMK_EE_CLR_Flag = false;
                Time_3s_EE_CLR_Count = 0;
            }
        } return true;
    #if LOGO_LED_ENABLE
        case LOGO_TOG: {                                            //logo 灯光开关
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off) {
                    Keyboard_Info.Logo_On_Off = LOGO_LED_ON;
                    if (Keyboard_Info.Logo_Brightness <= LOGO_MIN_BRIGHTNESS) {
                        Keyboard_Info.Logo_Brightness = LOGO_MAX_BRIGHTNESS;
                    }
                } else {
                    Keyboard_Info.Logo_On_Off = LOGO_LED_OFF;
                }
                Logo_Init();
                Save_Flash_Set();
            }
        } return true;
        case LOGO_MOD: {                                            //logo 模式切换
            if (!record->event.pressed) {
                // if (Keyboard_Info.Logo_On_Off) {
                //     return true;
                // } else {
                    if (Keyboard_Info.Logo_Mode < LOGO_OFF_MODE) {
                        Keyboard_Info.Logo_Mode ++;
                        if(Keyboard_Info.Logo_Mode == LOGO_OFF_MODE)
                        {
                            Keyboard_Info.Logo_On_Off = 1;
                        }
                    } else {
                        Keyboard_Info.Logo_On_Off = 0;
                        Keyboard_Info.Logo_Mode = INIT_LOGO_MODE;
                    }
                //}
                Logo_Init();
                Save_Flash_Set();
            }
        } return true;
        case LOGO_RMOD: {                                           //logo 模式切换
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off) {
                    return true;
                } else {
                    if (Keyboard_Info.Logo_Mode > INIT_LOGO_MODE) {
                        Keyboard_Info.Logo_Mode--;
                    } else {
                        Keyboard_Info.Logo_Mode = LOGO_OFF_MODE;
                    }
                }
                Logo_Init();
                Save_Flash_Set();
            }
        } return true;
        case LOGO_HUI: {                                            //logo 颜色增加
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off || (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE) || (Keyboard_Info.Logo_Mode == LOGO_WAVE_RGB_MODE) || (Keyboard_Info.Logo_Mode == LOGO_SPECTRUM_MODE)) {
                    return true;
                } else {
                    if (Keyboard_Info.Logo_Colour < (LOGO_MAX_COLOUR - COLOUR_LEVEL)) {
                        Keyboard_Info.Logo_Colour += COLOUR_LEVEL;
                    } else {
                        Keyboard_Info.Logo_Colour = ((Keyboard_Info.Logo_Colour + COLOUR_LEVEL) - LOGO_MAX_COLOUR);
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case LOGO_HUD: {                                            //logo 颜色减小
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off || (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE) || (Keyboard_Info.Logo_Mode == LOGO_WAVE_RGB_MODE) || (Keyboard_Info.Logo_Mode == LOGO_SPECTRUM_MODE)) {
                    return true;
                } else {
                    if ((Keyboard_Info.Logo_Colour - COLOUR_LEVEL) > LOGO_MIN_COLOUR) {
                        Keyboard_Info.Logo_Colour -= COLOUR_LEVEL;
                    } else {
                        Keyboard_Info.Logo_Colour = ((LOGO_MAX_COLOUR - COLOUR_LEVEL) + Keyboard_Info.Logo_Colour);
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case LOGO_SAI: {                                            //logo 饱和度增加
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off || (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE)) {
                    return true;
                } else {
                    if ((Keyboard_Info.Logo_Saturation - SATURATION_LEVEL) > LOGO_MAX_SATURATION) {
                        Keyboard_Info.Logo_Saturation -= SATURATION_LEVEL;
                    } else {
                        Keyboard_Info.Logo_Saturation = LOGO_MAX_SATURATION;
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case LOGO_SAD: {                                            //logo 饱和度减小
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off || (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE)) {
                    return true;
                } else {
                    if (Keyboard_Info.Logo_Saturation < (LOGO_MIN_SATURATION - SATURATION_LEVEL)) {
                        Keyboard_Info.Logo_Saturation += SATURATION_LEVEL;
                    } else {
                        Keyboard_Info.Logo_Saturation = LOGO_MIN_SATURATION;
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case LOGO_VAI: {                                            //logo 亮度增加
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off || (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE)) {
                    return true;
                } else {
                    if (Keyboard_Info.Logo_Brightness < (LOGO_MAX_BRIGHTNESS - BRIGHTNESS_LEVEL)) {
                        Keyboard_Info.Logo_Brightness += BRIGHTNESS_LEVEL;
                    } else {
                        Keyboard_Info.Logo_Brightness = LOGO_MAX_BRIGHTNESS;
                        Led_Point_Count = 3;
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case LOGO_VAD: {                                            //logo 亮度减小
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off || (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE)) {
                    return true;
                } else {
                    if ((Keyboard_Info.Logo_Brightness - BRIGHTNESS_LEVEL) > LOGO_MIN_BRIGHTNESS) {
                        Keyboard_Info.Logo_Brightness -= BRIGHTNESS_LEVEL;
                    } else {
                        Keyboard_Info.Logo_Brightness = LOGO_MIN_BRIGHTNESS;
                        Led_Point_Count = 3;
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case LOGO_SPI: {                                            //logo 速度增加
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off || (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE)) {
                    return true;
                } else {
                    if (Keyboard_Info.Logo_Speed < (LOGO_MAX_SPEED - SPEED_LEVEL)) {
                        Keyboard_Info.Logo_Speed += SPEED_LEVEL;
                    } else {
                        Keyboard_Info.Logo_Speed = LOGO_MAX_SPEED;
                        Led_Point_Count = 3;
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case LOGO_SPD: {                                            //logo 速度减小
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off || (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE)) {
                    return true;
                } else {
                    if ((Keyboard_Info.Logo_Speed - SPEED_LEVEL) > LOGO_MIN_SPEED) {
                        Keyboard_Info.Logo_Speed -= SPEED_LEVEL;
                    } else {
                        Keyboard_Info.Logo_Speed = LOGO_MIN_SPEED;
                        Led_Point_Count = 3;
                    }
                }
                Save_Flash_Set();
            }
        } return true;
    #endif
    #if SIDE_LED_ENABLE
        case SIDE_TOG: {                                            //侧灯 灯光开关
            if (!record->event.pressed) {
                if (Keyboard_Info.Side_On_Off) {
                    Keyboard_Info.Side_On_Off = SIDE_LED_ON;
                    if (Keyboard_Info.Side_Brightness <= SIDE_MIN_BRIGHTNESS) {
                        Keyboard_Info.Side_Brightness = SIDE_MAX_BRIGHTNESS;
                    }
                } else {
                    Keyboard_Info.Side_On_Off = SIDE_LED_OFF;
                }
                Side_Init();
                Save_Flash_Set();
            }
        } return true;
        case SIDE_MOD: {                                            //侧灯 模式切换
            if (!record->event.pressed) {
                if (Keyboard_Info.Side_On_Off) {
                    return true;
                } else {
                    if (Keyboard_Info.Side_Mode < SIDE_OFF_MODE) {
                        Keyboard_Info.Side_Mode ++;
                    } else {
                        Keyboard_Info.Side_Mode = INIT_SIDE_MODE;
                    }
                }
                Side_Init();
                Save_Flash_Set();
            }
        } return true;
        case SIDE_RMOD: {                                           //侧灯 模式切换
            if (!record->event.pressed) {
                if (Keyboard_Info.Side_On_Off) {
                    return true;
                } else {
                    if (Keyboard_Info.Side_Mode > INIT_SIDE_MODE) {
                        Keyboard_Info.Side_Mode--;
                    } else {
                        Keyboard_Info.Side_Mode = SIDE_OFF_MODE;
                    }
                }
                Side_Init();
                Save_Flash_Set();
            }
        } return true;
        case SIDE_HUI: {                                            //侧灯 颜色增加
            if (!record->event.pressed) {
                if (Keyboard_Info.Side_On_Off || (Keyboard_Info.Side_Mode == SIDE_OFF_MODE) || (Keyboard_Info.Side_Mode == SIDE_WAVE_RGB_MODE) || (Keyboard_Info.Side_Mode == SIDE_SPECTRUM_MODE)) {
                    return true;
                } else {
                    if (Keyboard_Info.Side_Colour < (SIDE_MAX_COLOUR - SIDE_COLOUR_LEVEL)) {
                        Keyboard_Info.Side_Colour += SIDE_COLOUR_LEVEL;
                    } else {
                        Keyboard_Info.Side_Colour = ((Keyboard_Info.Side_Colour + SIDE_COLOUR_LEVEL) - SIDE_MAX_COLOUR);
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case SIDE_HUD: {                                            //侧灯 颜色减小
            if (!record->event.pressed) {
                if (Keyboard_Info.Side_On_Off || (Keyboard_Info.Side_Mode == SIDE_OFF_MODE) || (Keyboard_Info.Side_Mode == SIDE_WAVE_RGB_MODE) || (Keyboard_Info.Side_Mode == SIDE_SPECTRUM_MODE)) {
                    return true;
                } else {
                    if ((Keyboard_Info.Side_Colour - SIDE_COLOUR_LEVEL) > SIDE_MIN_COLOUR) {
                        Keyboard_Info.Side_Colour -= SIDE_COLOUR_LEVEL;
                    } else {
                        Keyboard_Info.Side_Colour = ((SIDE_MAX_COLOUR - SIDE_COLOUR_LEVEL) + Keyboard_Info.Side_Colour);
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case SIDE_SAI: {                                            //侧灯 饱和度增加
            if (!record->event.pressed) {
                if (Keyboard_Info.Side_On_Off || (Keyboard_Info.Side_Mode == SIDE_OFF_MODE)) {
                    return true;
                } else {
                    if ((Keyboard_Info.Side_Saturation - SIDE_SATURATION_LEVEL) > SIDE_MAX_SATURATION) {
                        Keyboard_Info.Side_Saturation -= SIDE_SATURATION_LEVEL;
                    } else {
                        Keyboard_Info.Side_Saturation = SIDE_MAX_SATURATION;
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case SIDE_SAD: {                                            //侧灯 饱和度减小
            if (!record->event.pressed) {
                if (Keyboard_Info.Side_On_Off || (Keyboard_Info.Side_Mode == SIDE_OFF_MODE)) {
                    return true;
                } else {
                    if (Keyboard_Info.Side_Saturation < (SIDE_MIN_SATURATION - SIDE_SATURATION_LEVEL)) {
                        Keyboard_Info.Side_Saturation += SIDE_SATURATION_LEVEL;
                    } else {
                        Keyboard_Info.Side_Saturation = SIDE_MIN_SATURATION;
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case SIDE_VAI: {                                            //侧灯 亮度增加
            if (!record->event.pressed) {
                if (Keyboard_Info.Side_On_Off || (Keyboard_Info.Side_Mode == SIDE_OFF_MODE)) {
                    return true;
                } else {
                    if (Keyboard_Info.Side_Brightness < (SIDE_MAX_BRIGHTNESS - SIDE_BRIGHTNESS_LEVEL)) {
                        Keyboard_Info.Side_Brightness += SIDE_BRIGHTNESS_LEVEL;
                    } else {
                        Keyboard_Info.Side_Brightness = SIDE_MAX_BRIGHTNESS;
                        Led_Point_Count = 3;
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case SIDE_VAD: {                                            //侧灯 亮度减小
            if (!record->event.pressed) {
                if (Keyboard_Info.Side_On_Off || (Keyboard_Info.Side_Mode == SIDE_OFF_MODE)) {
                    return true;
                } else {
                    if ((Keyboard_Info.Side_Brightness - SIDE_BRIGHTNESS_LEVEL) > SIDE_MIN_BRIGHTNESS) {
                        Keyboard_Info.Side_Brightness -= SIDE_BRIGHTNESS_LEVEL;
                    } else {
                        Keyboard_Info.Side_Brightness = SIDE_MIN_BRIGHTNESS;
                        Led_Point_Count = 3;
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case SIDE_SPI: {                                            //侧灯 速度增加
            if (!record->event.pressed) {
                if (Keyboard_Info.Side_On_Off || (Keyboard_Info.Side_Mode == SIDE_OFF_MODE)) {
                    return true;
                } else {
                    if (Keyboard_Info.Side_Speed < (SIDE_MAX_SPEED - SIDE_SPEED_LEVEL)) {
                        Keyboard_Info.Side_Speed += SIDE_SPEED_LEVEL;
                    } else {
                        Keyboard_Info.Side_Speed = SIDE_MAX_SPEED;
                        Led_Point_Count = 3;
                    }
                }
                Save_Flash_Set();
            }
        } return true;
        case SIDE_SPD: {                                            //侧灯 速度减小
            if (!record->event.pressed) {
                if (Keyboard_Info.Side_On_Off || (Keyboard_Info.Side_Mode == SIDE_OFF_MODE)) {
                    return true;
                } else {
                    if ((Keyboard_Info.Side_Speed - SIDE_SPEED_LEVEL) > SIDE_MIN_SPEED) {
                        Keyboard_Info.Side_Speed -= SIDE_SPEED_LEVEL;
                    } else {
                        Keyboard_Info.Side_Speed = SIDE_MIN_SPEED;
                        Led_Point_Count = 3;
                    }
                }
                Save_Flash_Set();
            }
        } return true;
    #endif
        default:    return true; // Process all other keycodes normally
    }
}
