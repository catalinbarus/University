/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_10058239494147324899_0457016286_init();
    work_m_01469768745708863870_0266380040_init();
    work_m_17034824526613824818_0782664348_init();
    work_m_05274668823053730225_1262452598_init();
    work_m_10467465676061714548_3648169201_init();
    work_m_16406118477946760835_1351276808_init();
    work_m_16541823861846354283_2073120511_init();


    xsi_register_tops("work_m_16406118477946760835_1351276808");
    xsi_register_tops("work_m_16541823861846354283_2073120511");


    return xsi_run_simulation(argc, argv);

}
