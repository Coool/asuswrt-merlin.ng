/*
   Copyright (c) 2015 Broadcom Corporation
   All Rights Reserved

   <:label-BRCM:2015:DUAL/GPL:standard
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License, version 2, as published by
   the Free Software Foundation (the "GPL").
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   
   A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
   writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
   
   :>
   */
/*
 * lport_defs.h
 *
 *  Created on: 24 ����� 2015
 *      Author: yonatani
 */

#ifndef SHARED_OPENSOURCE_DRV_LPORT_LPORT_DEFS_H_
#define SHARED_OPENSOURCE_DRV_LPORT_LPORT_DEFS_H_


//defines
#define LPORT_NUM_OF_PORTS_PER_XLMAC 4
#define LPORT_NUM_OF_XLMACS 2
/* ONLY 7 ports are applicable in revision A0 */
#define LPORT_NUM_OF_PORTS ((LPORT_NUM_OF_XLMACS * LPORT_NUM_OF_PORTS_PER_XLMAC) - 1)
#define LPORT_NUM_OF_RGMII 3
#define LPORT_LAST_EGPHY_PORT 3
#define LPORT_FIRST_RGMII_PORT 4
#define LPORT_IS_SERDES_PORT(_port_) (_port_!= PORT_UNAVAIL \
    && _port_ <= PORT_XFI)

#ifdef _CFE_
#include "lib_types.h"
#else
#include <linux/types.h>
#endif

//typedefs
typedef enum
{
    LPORT_ERR_OK = 0,
    LPORT_ERR_PARAM = -1,
    LPORT_ERR_STATE = -2,
    LPORT_ERR_IO = -3,
    LPORT_ERR_RANGE = -3,


}LPORT_RC;

typedef enum
{
    PORT_UNAVAIL = 0,
    PORT_SGMII_SLAVE,
    PORT_SGMII_1000BASE_X,
    PORT_HSGMII,
    PORT_XFI,
    PORT_GPHY,
    PORT_RGMII
}LPORT_PORT_MUX_SELECT;

typedef enum
{
    LPORT_RATE_UNKNOWN = 0,
    LPORT_RATE_10MB = (1<<0),
    LPORT_RATE_100MB = (1<<1),
    LPORT_RATE_1000MB = (1<<2),
    LPORT_RATE_2500MB = (1<<3),
    LPORT_RATE_10G = (1<<4),
}LPORT_PORT_RATE;

typedef enum
{
    LPORT_HALF_DUPLEX,
    LPORT_FULL_DUPLEX
}LPORT_PORT_DUPLEX;

typedef enum
{
    XLMAC_CRC_APPEND,
    XLMAC_CRC_KEEP,
    XLMAC_CRC_REPLACE,
    XLMAC_CRC_PERPKT
}XLMAC_CRC_MODE;

typedef struct
{
    uint8_t valid;
    uint8_t eee_enable;
    uint8_t rvmii_ref;/*0=50mhz,1=25mhz*/
    uint8_t portmode;/*2=Mii,3=RGMII,4=RvMII*/
    uint8_t idelay_dis;/*rgmii internal delay disable*/
    uint8_t ib_status_overide;/*if set user can set the status ,used when working in MAC2MAC mode*/
    uint8_t phy_attached; /*Phy is connected to RGMII port*/
    uint16_t phyid;/*PhyID if exists*/
}lport_rgmii_cfg_s;

typedef struct
{
    LPORT_PORT_MUX_SELECT  prt_mux_sel[LPORT_NUM_OF_PORTS];
}lport_init_s;

typedef struct
{
    uint8_t local_loopback;
    uint8_t pad_en;
    uint8_t pad_threashold;
    uint8_t average_igp;
    uint8_t tx_threshold;
    uint8_t tx_preamble_len;
    LPORT_PORT_RATE speed;
}lport_port_cfg_s;

typedef struct
{
    uint64_t tx_ctrl_sa;
    uint64_t rx_ctrl_sa;
    uint8_t  rx_pass_ctrl;
    uint8_t  rx_pass_pause;
    uint16_t pause_xoff_timer;
    uint8_t  rx_pause_en;
    uint8_t  tx_pause_en;
    uint8_t  pause_refresh_en;
    uint16_t pause_refresh_timer;
}lport_flow_ctrl_cfg_s;

typedef struct
{
    uint8_t autoneg_en;
    uint8_t port_up;
    LPORT_PORT_RATE rate;
    LPORT_PORT_DUPLEX duplex;
    uint8_t rx_pause_en;
    uint8_t tx_pause_en;
}lport_port_status_s;

typedef struct
{
    uint8_t autoneg_en;
    uint8_t port_up;
    uint32_t rate_adv_map;
    LPORT_PORT_DUPLEX duplex;
    uint8_t rx_pause_en;
    uint8_t tx_pause_en;
}lport_port_phycfg_s;

typedef struct
{
    uint8_t rgmii_da_mac[6];
    uint16_t payload_len;
    uint8_t ate_en;
}lport_rgmii_ate_s;

#endif /* SHARED_OPENSOURCE_DRV_LPORT_LPORT_DEFS_H_ */
