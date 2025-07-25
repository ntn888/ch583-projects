/********************************** (C) COPYRIGHT *******************************
 * File Name          : lwns_config.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2021/11/17
 * Description        : lwnsÅäÖÃÑ¡Ïî
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#ifndef _LWNS_CONFIG_H_
#define _LWNS_CONFIG_H_

#include "CONFIG.h"
#include "CH58x_common.h"
#include "WCH_LWNS_LIB.h"

#define LWNS_ADDR_USE_BLE_MAC     1   //ÊÇ·ñÊ¹ÓÃÀ¶ÑÀÓ²ŒþµÄmacµØÖ·×÷ÎªÄ¬ÈÏlwnsµØÖ·

#define LWNS_ENCRYPT_ENABLE       1   //ÊÇ·ñÊ¹ÄÜŒÓÃÜ

#define QBUF_MANUAL_NUM           4   //qbuf»ºŽæÊýÁ¿ÅäÖÃ

#define ROUTE_ENTRY_MANUAL_NUM    32  //Â·ÓÉÌõÄ¿ÊýÁ¿ÅäÖÃ

#define LWNS_NEIGHBOR_MAX_NUM     8   //×îŽóÁÚŸÓÊýÁ¿

#endif /* _LWNS_CONFIG_H_ */
