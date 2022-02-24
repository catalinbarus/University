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
    work_m_11013316020800693640_0457016286_init();
    work_m_01469768745708863870_0266380040_init();
    work_m_07005960154240995210_0782664348_init();
    work_m_01276634957841831408_1893023533_init();
    work_m_04589000363562567223_3648169201_init();
    work_m_02707949722278456711_3412419721_init();
    work_m_00125329693255237152_0052631370_init();
    work_m_11632838583333669648_3356059340_init();
    work_m_14825895199902896100_1696645267_init();
    work_m_06558127173802137560_1835084805_init();
    work_m_18380682457505228395_3243429440_init();
    work_m_15224468725643625091_0038435860_init();
    work_m_10604980023699150217_2803750191_init();
    work_m_07843681846439222080_1200043877_init();
    work_m_03973151036416723807_2038303166_init();
    work_m_16541823861846354283_2073120511_init();


    xsi_register_tops("work_m_03973151036416723807_2038303166");
    xsi_register_tops("work_m_16541823861846354283_2073120511");


    return xsi_run_simulation(argc, argv);

}
