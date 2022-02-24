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

/* This file is designed for use with ISim build 0xfbc00daa */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/home/student/Desktop/CN2/lab5/lab05_skel/control_unit.v";
static int ng1[] = {0, 0};
static int ng2[] = {1, 0};
static int ng3[] = {7, 0};
static const char *ng4 = "\nPC => %d";
static unsigned int ng5[] = {15U, 15U};
static int ng6[] = {37, 0};
static int ng7[] = {38, 0};
static int ng8[] = {2, 0};
static int ng9[] = {39, 0};
static int ng10[] = {3, 0};
static int ng11[] = {46, 0};
static int ng12[] = {4, 0};
static int ng13[] = {50, 0};
static int ng14[] = {5, 0};
static int ng15[] = {48, 0};
static int ng16[] = {6, 0};
static int ng17[] = {45, 0};
static unsigned int ng18[] = {0U, 0U};
static unsigned int ng19[] = {65535U, 65535U};
static int ng20[] = {27, 0};
static unsigned int ng21[] = {255U, 255U};
static int ng22[] = {22, 0};
static int ng23[] = {23, 0};
static int ng24[] = {28, 0};
static int ng25[] = {24, 0};
static int ng26[] = {25, 0};
static int ng27[] = {26, 0};
static unsigned int ng28[] = {191U, 0U};
static unsigned int ng29[] = {1U, 0U};



static void Always_152_0(char *t0)
{
    char t13[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    char *t30;

LAB0:    t1 = (t0 + 9760U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(152, ng0);
    t2 = (t0 + 13056);
    *((int *)t2) = 1;
    t3 = (t0 + 9792);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(153, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB5;

LAB6:    xsi_set_current_line(155, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng2)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB11;

LAB8:    if (t18 != 0)
        goto LAB10;

LAB9:    *((unsigned int *)t13) = 1;

LAB11:    t12 = (t13 + 4);
    t21 = *((unsigned int *)t12);
    t22 = (~(t21));
    t23 = *((unsigned int *)t13);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB12;

LAB13:
LAB14:
LAB7:    goto LAB2;

LAB5:    xsi_set_current_line(154, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 7888);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 16, 0LL);
    goto LAB7;

LAB10:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB11;

LAB12:    xsi_set_current_line(155, ng0);

LAB15:    xsi_set_current_line(156, ng0);
    t26 = (t0 + 2048U);
    t27 = *((char **)t26);
    t26 = (t0 + 7888);
    xsi_vlogvar_wait_assign_value(t26, t27, 0, 0, 16, 0LL);
    xsi_set_current_line(157, ng0);
    t2 = (t0 + 7248);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng3)));
    memset(t13, 0, 8);
    t11 = (t4 + 4);
    if (*((unsigned int *)t11) != 0)
        goto LAB17;

LAB16:    t12 = (t5 + 4);
    if (*((unsigned int *)t12) != 0)
        goto LAB17;

LAB20:    if (*((unsigned int *)t4) < *((unsigned int *)t5))
        goto LAB18;

LAB19:    t27 = (t13 + 4);
    t6 = *((unsigned int *)t27);
    t7 = (~(t6));
    t8 = *((unsigned int *)t13);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB21;

LAB22:
LAB23:    goto LAB14;

LAB17:    t26 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t26) = 1;
    goto LAB19;

LAB18:    *((unsigned int *)t13) = 1;
    goto LAB19;

LAB21:    xsi_set_current_line(157, ng0);

LAB24:    xsi_set_current_line(158, ng0);
    t28 = (t0 + 7248);
    t29 = (t28 + 56U);
    t30 = *((char **)t29);
    xsi_vlogfile_write(1, 0, 0, ng4, 2, t0, (char)118, t30, 10);
    goto LAB23;

}

static void Always_165_1(char *t0)
{
    char t6[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t28;
    char *t29;
    int t30;

LAB0:    t1 = (t0 + 10008U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(165, ng0);
    t2 = (t0 + 13072);
    *((int *)t2) = 1;
    t3 = (t0 + 10040);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(165, ng0);

LAB5:    xsi_set_current_line(166, ng0);
    t4 = (t0 + 3968U);
    t5 = *((char **)t4);
    t4 = ((char*)((ng1)));
    memset(t6, 0, 8);
    t7 = (t5 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t4);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB9;

LAB6:    if (t18 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t6) = 1;

LAB9:    t22 = (t6 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB10;

LAB11:    xsi_set_current_line(168, ng0);

LAB13:    xsi_set_current_line(169, ng0);
    t2 = (t0 + 5568U);
    t3 = *((char **)t2);

LAB14:    t2 = ((char*)((ng6)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng7)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng9)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng11)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng13)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng15)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB25;

LAB26:    t2 = ((char*)((ng17)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB27;

LAB28:
LAB30:
LAB29:    xsi_set_current_line(185, ng0);
    t2 = ((char*)((ng1)));
    t4 = (t0 + 7408);
    xsi_vlogvar_assign_value(t4, t2, 0, 0, 4);

LAB31:
LAB12:    goto LAB2;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(167, ng0);
    t28 = ((char*)((ng5)));
    t29 = (t0 + 7408);
    xsi_vlogvar_assign_value(t29, t28, 0, 0, 4);
    goto LAB12;

LAB15:    xsi_set_current_line(171, ng0);
    t4 = ((char*)((ng2)));
    t5 = (t0 + 7408);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

LAB17:    xsi_set_current_line(173, ng0);
    t4 = ((char*)((ng8)));
    t5 = (t0 + 7408);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

LAB19:    xsi_set_current_line(175, ng0);
    t4 = ((char*)((ng10)));
    t5 = (t0 + 7408);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

LAB21:    xsi_set_current_line(177, ng0);
    t4 = ((char*)((ng12)));
    t5 = (t0 + 7408);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

LAB23:    xsi_set_current_line(179, ng0);
    t4 = ((char*)((ng14)));
    t5 = (t0 + 7408);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

LAB25:    xsi_set_current_line(181, ng0);
    t4 = ((char*)((ng16)));
    t5 = (t0 + 7408);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

LAB27:    xsi_set_current_line(183, ng0);
    t4 = ((char*)((ng3)));
    t5 = (t0 + 7408);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

}

static void Always_193_2(char *t0)
{
    char t13[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    char *t26;
    char *t27;

LAB0:    t1 = (t0 + 10256U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(193, ng0);
    t2 = (t0 + 13088);
    *((int *)t2) = 1;
    t3 = (t0 + 10288);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(194, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB5;

LAB6:    xsi_set_current_line(197, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng8)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB12;

LAB9:    if (t18 != 0)
        goto LAB11;

LAB10:    *((unsigned int *)t13) = 1;

LAB12:    t12 = (t13 + 4);
    t21 = *((unsigned int *)t12);
    t22 = (~(t21));
    t23 = *((unsigned int *)t13);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB13;

LAB14:
LAB15:
LAB7:    goto LAB2;

LAB5:    xsi_set_current_line(194, ng0);

LAB8:    xsi_set_current_line(195, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 7728);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 8, 0LL);
    xsi_set_current_line(196, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 7568);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 8, 0LL);
    goto LAB7;

LAB11:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB12;

LAB13:    xsi_set_current_line(197, ng0);

LAB16:    xsi_set_current_line(198, ng0);
    t26 = (t0 + 2848U);
    t27 = *((char **)t26);
    t26 = (t0 + 7728);
    xsi_vlogvar_wait_assign_value(t26, t27, 0, 0, 8, 0LL);
    xsi_set_current_line(199, ng0);
    t2 = (t0 + 2688U);
    t3 = *((char **)t2);
    t2 = (t0 + 7568);
    xsi_vlogvar_wait_assign_value(t2, t3, 0, 0, 8, 0LL);
    goto LAB15;

}

static void Cont_204_3(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 10504U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(204, ng0);
    t2 = (t0 + 8368);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 13328);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 255U;
    t11 = t10;
    t12 = (t4 + 4);
    t13 = *((unsigned int *)t4);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t5, 0, 7);
    t18 = (t0 + 13104);
    *((int *)t18) = 1;

LAB1:    return;
}

static void Always_205_4(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;

LAB0:    t1 = (t0 + 10752U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(205, ng0);
    t2 = (t0 + 13120);
    *((int *)t2) = 1;
    t3 = (t0 + 10784);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(206, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB5;

LAB6:    xsi_set_current_line(209, ng0);
    t2 = (t0 + 4288U);
    t3 = *((char **)t2);
    t2 = (t0 + 8368);
    xsi_vlogvar_wait_assign_value(t2, t3, 0, 0, 8, 0LL);

LAB7:    goto LAB2;

LAB5:    xsi_set_current_line(207, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 8368);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 8, 0LL);
    goto LAB7;

}

static void Always_214_5(char *t0)
{
    char t13[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    char *t26;
    char *t27;

LAB0:    t1 = (t0 + 11000U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(214, ng0);
    t2 = (t0 + 13136);
    *((int *)t2) = 1;
    t3 = (t0 + 11032);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(215, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB5;

LAB6:    xsi_set_current_line(217, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng10)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB11;

LAB8:    if (t18 != 0)
        goto LAB10;

LAB9:    *((unsigned int *)t13) = 1;

LAB11:    t12 = (t13 + 4);
    t21 = *((unsigned int *)t12);
    t22 = (~(t21));
    t23 = *((unsigned int *)t13);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB12;

LAB13:
LAB14:
LAB7:    goto LAB2;

LAB5:    xsi_set_current_line(216, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 8048);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 8, 0LL);
    goto LAB7;

LAB10:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB11;

LAB12:    xsi_set_current_line(218, ng0);
    t26 = (t0 + 4448U);
    t27 = *((char **)t26);
    t26 = (t0 + 8048);
    xsi_vlogvar_wait_assign_value(t26, t27, 0, 0, 8, 0LL);
    goto LAB14;

}

static void Cont_220_6(char *t0)
{
    char t4[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    unsigned int t25;
    unsigned int t26;
    char *t27;
    unsigned int t28;
    unsigned int t29;
    char *t30;
    unsigned int t31;
    unsigned int t32;
    char *t33;

LAB0:    t1 = (t0 + 11248U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(220, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng10)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB7;

LAB4:    if (t16 != 0)
        goto LAB6;

LAB5:    *((unsigned int *)t4) = 1;

LAB7:    t20 = (t0 + 13392);
    t21 = (t20 + 56U);
    t22 = *((char **)t21);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    memset(t24, 0, 8);
    t25 = 1U;
    t26 = t25;
    t27 = (t4 + 4);
    t28 = *((unsigned int *)t4);
    t25 = (t25 & t28);
    t29 = *((unsigned int *)t27);
    t26 = (t26 & t29);
    t30 = (t24 + 4);
    t31 = *((unsigned int *)t24);
    *((unsigned int *)t24) = (t31 | t25);
    t32 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t32 | t26);
    xsi_driver_vfirst_trans(t20, 0, 0);
    t33 = (t0 + 13152);
    *((int *)t33) = 1;

LAB1:    return;
LAB6:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB7;

}

static void Cont_230_7(char *t0)
{
    char t3[8];
    char t4[8];
    char t6[8];
    char t14[8];
    char t29[8];
    char t37[8];
    char t45[8];
    char t84[8];
    char t85[8];
    char t88[8];
    char t107[8];
    char t116[8];
    char *t1;
    char *t2;
    char *t5;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    char *t27;
    char *t28;
    char *t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    char *t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    char *t44;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    char *t49;
    char *t50;
    char *t51;
    unsigned int t52;
    unsigned int t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    char *t59;
    char *t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    char *t73;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    unsigned int t77;
    unsigned int t78;
    char *t79;
    char *t80;
    unsigned int t81;
    unsigned int t82;
    unsigned int t83;
    char *t86;
    char *t87;
    char *t89;
    unsigned int t90;
    unsigned int t91;
    unsigned int t92;
    unsigned int t93;
    unsigned int t94;
    unsigned int t95;
    char *t96;
    unsigned int t97;
    unsigned int t98;
    unsigned int t99;
    unsigned int t100;
    unsigned int t101;
    char *t102;
    char *t103;
    unsigned int t104;
    unsigned int t105;
    unsigned int t106;
    char *t108;
    char *t109;
    char *t110;
    char *t111;
    unsigned int t112;
    unsigned int t113;
    unsigned int t114;
    unsigned int t115;
    char *t117;
    char *t118;
    char *t119;
    char *t120;
    char *t121;
    char *t122;
    unsigned int t123;
    unsigned int t124;
    unsigned int t125;
    unsigned int t126;
    char *t127;
    char *t128;
    char *t129;
    char *t130;
    char *t131;
    char *t132;
    unsigned int t133;
    unsigned int t134;
    char *t135;
    unsigned int t136;
    unsigned int t137;
    char *t138;
    unsigned int t139;
    unsigned int t140;
    char *t141;

LAB0:    t1 = (t0 + 11496U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(230, ng0);
    t2 = (t0 + 5728U);
    t5 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t7 = (t5 + 4);
    t8 = *((unsigned int *)t5);
    t9 = (t8 >> 6);
    t10 = (t9 & 1);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t7);
    t12 = (t11 >> 6);
    t13 = (t12 & 1);
    *((unsigned int *)t2) = t13;
    memset(t14, 0, 8);
    t15 = (t6 + 4);
    t16 = *((unsigned int *)t15);
    t17 = (~(t16));
    t18 = *((unsigned int *)t6);
    t19 = (t18 & t17);
    t20 = (t19 & 1U);
    if (t20 != 0)
        goto LAB4;

LAB5:    if (*((unsigned int *)t15) != 0)
        goto LAB6;

LAB7:    t22 = (t14 + 4);
    t23 = *((unsigned int *)t14);
    t24 = (!(t23));
    t25 = *((unsigned int *)t22);
    t26 = (t24 || t25);
    if (t26 > 0)
        goto LAB8;

LAB9:    memcpy(t45, t14, 8);

LAB10:    memset(t4, 0, 8);
    t73 = (t45 + 4);
    t74 = *((unsigned int *)t73);
    t75 = (~(t74));
    t76 = *((unsigned int *)t45);
    t77 = (t76 & t75);
    t78 = (t77 & 1U);
    if (t78 != 0)
        goto LAB18;

LAB19:    if (*((unsigned int *)t73) != 0)
        goto LAB20;

LAB21:    t80 = (t4 + 4);
    t81 = *((unsigned int *)t4);
    t82 = *((unsigned int *)t80);
    t83 = (t81 || t82);
    if (t83 > 0)
        goto LAB22;

LAB23:    t123 = *((unsigned int *)t4);
    t124 = (~(t123));
    t125 = *((unsigned int *)t80);
    t126 = (t124 || t125);
    if (t126 > 0)
        goto LAB24;

LAB25:    if (*((unsigned int *)t80) > 0)
        goto LAB26;

LAB27:    if (*((unsigned int *)t4) > 0)
        goto LAB28;

LAB29:    memcpy(t3, t127, 8);

LAB30:    t128 = (t0 + 13456);
    t129 = (t128 + 56U);
    t130 = *((char **)t129);
    t131 = (t130 + 56U);
    t132 = *((char **)t131);
    memset(t132, 0, 8);
    t133 = 65535U;
    t134 = t133;
    t135 = (t3 + 4);
    t136 = *((unsigned int *)t3);
    t133 = (t133 & t136);
    t137 = *((unsigned int *)t135);
    t134 = (t134 & t137);
    t138 = (t132 + 4);
    t139 = *((unsigned int *)t132);
    *((unsigned int *)t132) = (t139 | t133);
    t140 = *((unsigned int *)t138);
    *((unsigned int *)t138) = (t140 | t134);
    xsi_driver_vfirst_trans(t128, 0, 15);
    t141 = (t0 + 13168);
    *((int *)t141) = 1;

LAB1:    return;
LAB4:    *((unsigned int *)t14) = 1;
    goto LAB7;

LAB6:    t21 = (t14 + 4);
    *((unsigned int *)t14) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB7;

LAB8:    t27 = (t0 + 5728U);
    t28 = *((char **)t27);
    memset(t29, 0, 8);
    t27 = (t29 + 4);
    t30 = (t28 + 4);
    t31 = *((unsigned int *)t28);
    t32 = (t31 >> 9);
    t33 = (t32 & 1);
    *((unsigned int *)t29) = t33;
    t34 = *((unsigned int *)t30);
    t35 = (t34 >> 9);
    t36 = (t35 & 1);
    *((unsigned int *)t27) = t36;
    memset(t37, 0, 8);
    t38 = (t29 + 4);
    t39 = *((unsigned int *)t38);
    t40 = (~(t39));
    t41 = *((unsigned int *)t29);
    t42 = (t41 & t40);
    t43 = (t42 & 1U);
    if (t43 != 0)
        goto LAB11;

LAB12:    if (*((unsigned int *)t38) != 0)
        goto LAB13;

LAB14:    t46 = *((unsigned int *)t14);
    t47 = *((unsigned int *)t37);
    t48 = (t46 | t47);
    *((unsigned int *)t45) = t48;
    t49 = (t14 + 4);
    t50 = (t37 + 4);
    t51 = (t45 + 4);
    t52 = *((unsigned int *)t49);
    t53 = *((unsigned int *)t50);
    t54 = (t52 | t53);
    *((unsigned int *)t51) = t54;
    t55 = *((unsigned int *)t51);
    t56 = (t55 != 0);
    if (t56 == 1)
        goto LAB15;

LAB16:
LAB17:    goto LAB10;

LAB11:    *((unsigned int *)t37) = 1;
    goto LAB14;

LAB13:    t44 = (t37 + 4);
    *((unsigned int *)t37) = 1;
    *((unsigned int *)t44) = 1;
    goto LAB14;

LAB15:    t57 = *((unsigned int *)t45);
    t58 = *((unsigned int *)t51);
    *((unsigned int *)t45) = (t57 | t58);
    t59 = (t14 + 4);
    t60 = (t37 + 4);
    t61 = *((unsigned int *)t59);
    t62 = (~(t61));
    t63 = *((unsigned int *)t14);
    t64 = (t63 & t62);
    t65 = *((unsigned int *)t60);
    t66 = (~(t65));
    t67 = *((unsigned int *)t37);
    t68 = (t67 & t66);
    t69 = (~(t64));
    t70 = (~(t68));
    t71 = *((unsigned int *)t51);
    *((unsigned int *)t51) = (t71 & t69);
    t72 = *((unsigned int *)t51);
    *((unsigned int *)t51) = (t72 & t70);
    goto LAB17;

LAB18:    *((unsigned int *)t4) = 1;
    goto LAB21;

LAB20:    t79 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t79) = 1;
    goto LAB21;

LAB22:    t86 = (t0 + 5728U);
    t87 = *((char **)t86);
    memset(t88, 0, 8);
    t86 = (t88 + 4);
    t89 = (t87 + 4);
    t90 = *((unsigned int *)t87);
    t91 = (t90 >> 12);
    t92 = (t91 & 1);
    *((unsigned int *)t88) = t92;
    t93 = *((unsigned int *)t89);
    t94 = (t93 >> 12);
    t95 = (t94 & 1);
    *((unsigned int *)t86) = t95;
    memset(t85, 0, 8);
    t96 = (t88 + 4);
    t97 = *((unsigned int *)t96);
    t98 = (~(t97));
    t99 = *((unsigned int *)t88);
    t100 = (t99 & t98);
    t101 = (t100 & 1U);
    if (t101 != 0)
        goto LAB31;

LAB32:    if (*((unsigned int *)t96) != 0)
        goto LAB33;

LAB34:    t103 = (t85 + 4);
    t104 = *((unsigned int *)t85);
    t105 = *((unsigned int *)t103);
    t106 = (t104 || t105);
    if (t106 > 0)
        goto LAB35;

LAB36:    t112 = *((unsigned int *)t85);
    t113 = (~(t112));
    t114 = *((unsigned int *)t103);
    t115 = (t113 || t114);
    if (t115 > 0)
        goto LAB37;

LAB38:    if (*((unsigned int *)t103) > 0)
        goto LAB39;

LAB40:    if (*((unsigned int *)t85) > 0)
        goto LAB41;

LAB42:    memcpy(t84, t116, 8);

LAB43:    goto LAB23;

LAB24:    t127 = ((char*)((ng19)));
    goto LAB25;

LAB26:    xsi_vlog_unsigned_bit_combine(t3, 16, t84, 16, t127, 16);
    goto LAB30;

LAB28:    memcpy(t3, t84, 8);
    goto LAB30;

LAB31:    *((unsigned int *)t85) = 1;
    goto LAB34;

LAB33:    t102 = (t85 + 4);
    *((unsigned int *)t85) = 1;
    *((unsigned int *)t102) = 1;
    goto LAB34;

LAB35:    t108 = (t0 + 8528);
    t109 = (t108 + 56U);
    t110 = *((char **)t109);
    t111 = ((char*)((ng18)));
    xsi_vlogtype_concat(t107, 16, 16, 2U, t111, 8, t110, 8);
    goto LAB36;

LAB37:    t117 = (t0 + 7728);
    t118 = (t117 + 56U);
    t119 = *((char **)t118);
    t120 = (t0 + 7568);
    t121 = (t120 + 56U);
    t122 = *((char **)t121);
    xsi_vlogtype_concat(t116, 16, 16, 2U, t122, 8, t119, 8);
    goto LAB38;

LAB39:    xsi_vlog_unsigned_bit_combine(t84, 16, t107, 16, t116, 16);
    goto LAB43;

LAB41:    memcpy(t84, t107, 8);
    goto LAB43;

}

static void Cont_247_8(char *t0)
{
    char t3[8];
    char t4[8];
    char t6[8];
    char t25[8];
    char t26[8];
    char t29[8];
    char t56[8];
    char t57[8];
    char t60[8];
    char t87[8];
    char t103[8];
    char *t1;
    char *t2;
    char *t5;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    char *t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    char *t27;
    char *t28;
    char *t30;
    char *t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    char *t44;
    char *t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    char *t51;
    char *t52;
    unsigned int t53;
    unsigned int t54;
    unsigned int t55;
    char *t58;
    char *t59;
    char *t61;
    char *t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    unsigned int t73;
    unsigned int t74;
    char *t75;
    char *t76;
    unsigned int t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    char *t82;
    char *t83;
    unsigned int t84;
    unsigned int t85;
    unsigned int t86;
    char *t88;
    char *t89;
    char *t90;
    char *t91;
    char *t92;
    unsigned int t93;
    unsigned int t94;
    unsigned int t95;
    unsigned int t96;
    unsigned int t97;
    unsigned int t98;
    unsigned int t99;
    unsigned int t100;
    unsigned int t101;
    unsigned int t102;
    char *t104;
    char *t105;
    char *t106;
    char *t107;
    char *t108;
    unsigned int t109;
    unsigned int t110;
    unsigned int t111;
    unsigned int t112;
    unsigned int t113;
    unsigned int t114;
    unsigned int t115;
    unsigned int t116;
    unsigned int t117;
    unsigned int t118;
    char *t119;
    char *t120;
    char *t121;
    unsigned int t122;
    unsigned int t123;
    unsigned int t124;
    unsigned int t125;
    char *t126;
    char *t127;
    char *t128;
    char *t129;
    char *t130;
    char *t131;
    unsigned int t132;
    unsigned int t133;
    char *t134;
    unsigned int t135;
    unsigned int t136;
    char *t137;
    unsigned int t138;
    unsigned int t139;
    char *t140;

LAB0:    t1 = (t0 + 11744U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(247, ng0);
    t2 = (t0 + 5408U);
    t5 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t7 = (t5 + 4);
    t8 = *((unsigned int *)t5);
    t9 = (t8 >> 1);
    t10 = (t9 & 1);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t7);
    t12 = (t11 >> 1);
    t13 = (t12 & 1);
    *((unsigned int *)t2) = t13;
    memset(t4, 0, 8);
    t14 = (t6 + 4);
    t15 = *((unsigned int *)t14);
    t16 = (~(t15));
    t17 = *((unsigned int *)t6);
    t18 = (t17 & t16);
    t19 = (t18 & 1U);
    if (t19 != 0)
        goto LAB4;

LAB5:    if (*((unsigned int *)t14) != 0)
        goto LAB6;

LAB7:    t21 = (t4 + 4);
    t22 = *((unsigned int *)t4);
    t23 = *((unsigned int *)t21);
    t24 = (t22 || t23);
    if (t24 > 0)
        goto LAB8;

LAB9:    t122 = *((unsigned int *)t4);
    t123 = (~(t122));
    t124 = *((unsigned int *)t21);
    t125 = (t123 || t124);
    if (t125 > 0)
        goto LAB10;

LAB11:    if (*((unsigned int *)t21) > 0)
        goto LAB12;

LAB13:    if (*((unsigned int *)t4) > 0)
        goto LAB14;

LAB15:    memcpy(t3, t126, 8);

LAB16:    t127 = (t0 + 13520);
    t128 = (t127 + 56U);
    t129 = *((char **)t128);
    t130 = (t129 + 56U);
    t131 = *((char **)t130);
    memset(t131, 0, 8);
    t132 = 255U;
    t133 = t132;
    t134 = (t3 + 4);
    t135 = *((unsigned int *)t3);
    t132 = (t132 & t135);
    t136 = *((unsigned int *)t134);
    t133 = (t133 & t136);
    t137 = (t131 + 4);
    t138 = *((unsigned int *)t131);
    *((unsigned int *)t131) = (t138 | t132);
    t139 = *((unsigned int *)t137);
    *((unsigned int *)t137) = (t139 | t133);
    xsi_driver_vfirst_trans(t127, 0, 7);
    t140 = (t0 + 13184);
    *((int *)t140) = 1;

LAB1:    return;
LAB4:    *((unsigned int *)t4) = 1;
    goto LAB7;

LAB6:    t20 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t20) = 1;
    goto LAB7;

LAB8:    t27 = (t0 + 5568U);
    t28 = *((char **)t27);
    t27 = ((char*)((ng20)));
    memset(t29, 0, 8);
    t30 = (t28 + 4);
    t31 = (t27 + 4);
    t32 = *((unsigned int *)t28);
    t33 = *((unsigned int *)t27);
    t34 = (t32 ^ t33);
    t35 = *((unsigned int *)t30);
    t36 = *((unsigned int *)t31);
    t37 = (t35 ^ t36);
    t38 = (t34 | t37);
    t39 = *((unsigned int *)t30);
    t40 = *((unsigned int *)t31);
    t41 = (t39 | t40);
    t42 = (~(t41));
    t43 = (t38 & t42);
    if (t43 != 0)
        goto LAB20;

LAB17:    if (t41 != 0)
        goto LAB19;

LAB18:    *((unsigned int *)t29) = 1;

LAB20:    memset(t26, 0, 8);
    t45 = (t29 + 4);
    t46 = *((unsigned int *)t45);
    t47 = (~(t46));
    t48 = *((unsigned int *)t29);
    t49 = (t48 & t47);
    t50 = (t49 & 1U);
    if (t50 != 0)
        goto LAB21;

LAB22:    if (*((unsigned int *)t45) != 0)
        goto LAB23;

LAB24:    t52 = (t26 + 4);
    t53 = *((unsigned int *)t26);
    t54 = *((unsigned int *)t52);
    t55 = (t53 || t54);
    if (t55 > 0)
        goto LAB25;

LAB26:    t115 = *((unsigned int *)t26);
    t116 = (~(t115));
    t117 = *((unsigned int *)t52);
    t118 = (t116 || t117);
    if (t118 > 0)
        goto LAB27;

LAB28:    if (*((unsigned int *)t52) > 0)
        goto LAB29;

LAB30:    if (*((unsigned int *)t26) > 0)
        goto LAB31;

LAB32:    memcpy(t25, t121, 8);

LAB33:    goto LAB9;

LAB10:    t126 = ((char*)((ng21)));
    goto LAB11;

LAB12:    xsi_vlog_unsigned_bit_combine(t3, 8, t25, 8, t126, 8);
    goto LAB16;

LAB14:    memcpy(t3, t25, 8);
    goto LAB16;

LAB19:    t44 = (t29 + 4);
    *((unsigned int *)t29) = 1;
    *((unsigned int *)t44) = 1;
    goto LAB20;

LAB21:    *((unsigned int *)t26) = 1;
    goto LAB24;

LAB23:    t51 = (t26 + 4);
    *((unsigned int *)t26) = 1;
    *((unsigned int *)t51) = 1;
    goto LAB24;

LAB25:    t58 = (t0 + 6528U);
    t59 = *((char **)t58);
    t58 = ((char*)((ng1)));
    memset(t60, 0, 8);
    t61 = (t59 + 4);
    t62 = (t58 + 4);
    t63 = *((unsigned int *)t59);
    t64 = *((unsigned int *)t58);
    t65 = (t63 ^ t64);
    t66 = *((unsigned int *)t61);
    t67 = *((unsigned int *)t62);
    t68 = (t66 ^ t67);
    t69 = (t65 | t68);
    t70 = *((unsigned int *)t61);
    t71 = *((unsigned int *)t62);
    t72 = (t70 | t71);
    t73 = (~(t72));
    t74 = (t69 & t73);
    if (t74 != 0)
        goto LAB37;

LAB34:    if (t72 != 0)
        goto LAB36;

LAB35:    *((unsigned int *)t60) = 1;

LAB37:    memset(t57, 0, 8);
    t76 = (t60 + 4);
    t77 = *((unsigned int *)t76);
    t78 = (~(t77));
    t79 = *((unsigned int *)t60);
    t80 = (t79 & t78);
    t81 = (t80 & 1U);
    if (t81 != 0)
        goto LAB38;

LAB39:    if (*((unsigned int *)t76) != 0)
        goto LAB40;

LAB41:    t83 = (t57 + 4);
    t84 = *((unsigned int *)t57);
    t85 = *((unsigned int *)t83);
    t86 = (t84 || t85);
    if (t86 > 0)
        goto LAB42;

LAB43:    t99 = *((unsigned int *)t57);
    t100 = (~(t99));
    t101 = *((unsigned int *)t83);
    t102 = (t100 || t101);
    if (t102 > 0)
        goto LAB44;

LAB45:    if (*((unsigned int *)t83) > 0)
        goto LAB46;

LAB47:    if (*((unsigned int *)t57) > 0)
        goto LAB48;

LAB49:    memcpy(t56, t103, 8);

LAB50:    goto LAB26;

LAB27:    t119 = (t0 + 7568);
    t120 = (t119 + 56U);
    t121 = *((char **)t120);
    goto LAB28;

LAB29:    xsi_vlog_unsigned_bit_combine(t25, 8, t56, 8, t121, 8);
    goto LAB33;

LAB31:    memcpy(t25, t56, 8);
    goto LAB33;

LAB36:    t75 = (t60 + 4);
    *((unsigned int *)t60) = 1;
    *((unsigned int *)t75) = 1;
    goto LAB37;

LAB38:    *((unsigned int *)t57) = 1;
    goto LAB41;

LAB40:    t82 = (t57 + 4);
    *((unsigned int *)t57) = 1;
    *((unsigned int *)t82) = 1;
    goto LAB41;

LAB42:    t88 = (t0 + 8688);
    t89 = (t88 + 56U);
    t90 = *((char **)t89);
    memset(t87, 0, 8);
    t91 = (t87 + 4);
    t92 = (t90 + 4);
    t93 = *((unsigned int *)t90);
    t94 = (t93 >> 0);
    *((unsigned int *)t87) = t94;
    t95 = *((unsigned int *)t92);
    t96 = (t95 >> 0);
    *((unsigned int *)t91) = t96;
    t97 = *((unsigned int *)t87);
    *((unsigned int *)t87) = (t97 & 255U);
    t98 = *((unsigned int *)t91);
    *((unsigned int *)t91) = (t98 & 255U);
    goto LAB43;

LAB44:    t104 = (t0 + 8688);
    t105 = (t104 + 56U);
    t106 = *((char **)t105);
    memset(t103, 0, 8);
    t107 = (t103 + 4);
    t108 = (t106 + 4);
    t109 = *((unsigned int *)t106);
    t110 = (t109 >> 8);
    *((unsigned int *)t103) = t110;
    t111 = *((unsigned int *)t108);
    t112 = (t111 >> 8);
    *((unsigned int *)t107) = t112;
    t113 = *((unsigned int *)t103);
    *((unsigned int *)t103) = (t113 & 255U);
    t114 = *((unsigned int *)t107);
    *((unsigned int *)t107) = (t114 & 255U);
    goto LAB45;

LAB46:    xsi_vlog_unsigned_bit_combine(t56, 8, t87, 8, t103, 8);
    goto LAB50;

LAB48:    memcpy(t56, t87, 8);
    goto LAB50;

}

static void Always_267_9(char *t0)
{
    char t13[8];
    char t28[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    char *t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    char *t36;

LAB0:    t1 = (t0 + 11992U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(267, ng0);
    t2 = (t0 + 13200);
    *((int *)t2) = 1;
    t3 = (t0 + 12024);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(267, ng0);

LAB5:    xsi_set_current_line(268, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(270, ng0);
    t2 = (t0 + 5728U);
    t3 = *((char **)t2);
    memset(t13, 0, 8);
    t2 = (t13 + 4);
    t4 = (t3 + 4);
    t6 = *((unsigned int *)t3);
    t7 = (t6 >> 3);
    t8 = (t7 & 1);
    *((unsigned int *)t13) = t8;
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 3);
    t14 = (t10 & 1);
    *((unsigned int *)t2) = t14;
    t5 = (t13 + 4);
    t15 = *((unsigned int *)t5);
    t16 = (~(t15));
    t17 = *((unsigned int *)t13);
    t18 = (t17 & t16);
    t19 = (t18 != 0);
    if (t19 > 0)
        goto LAB9;

LAB10:    xsi_set_current_line(272, ng0);
    t2 = (t0 + 5408U);
    t3 = *((char **)t2);
    memset(t13, 0, 8);
    t2 = (t13 + 4);
    t4 = (t3 + 4);
    t6 = *((unsigned int *)t3);
    t7 = (t6 >> 0);
    t8 = (t7 & 1);
    *((unsigned int *)t13) = t8;
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 0);
    t14 = (t10 & 1);
    *((unsigned int *)t2) = t14;
    t5 = (t13 + 4);
    t15 = *((unsigned int *)t5);
    t16 = (~(t15));
    t17 = *((unsigned int *)t13);
    t18 = (t17 & t16);
    t19 = (t18 != 0);
    if (t19 > 0)
        goto LAB12;

LAB13:    xsi_set_current_line(274, ng0);
    t2 = (t0 + 5568U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng22)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t22 = (t15 & t19);
    if (t22 != 0)
        goto LAB18;

LAB15:    if (t18 != 0)
        goto LAB17;

LAB16:    *((unsigned int *)t13) = 1;

LAB18:    t12 = (t13 + 4);
    t23 = *((unsigned int *)t12);
    t24 = (~(t23));
    t25 = *((unsigned int *)t13);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB19;

LAB20:    xsi_set_current_line(276, ng0);
    t2 = (t0 + 5568U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng23)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t22 = (t15 & t19);
    if (t22 != 0)
        goto LAB25;

LAB22:    if (t18 != 0)
        goto LAB24;

LAB23:    *((unsigned int *)t13) = 1;

LAB25:    t12 = (t13 + 4);
    t23 = *((unsigned int *)t12);
    t24 = (~(t23));
    t25 = *((unsigned int *)t13);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB26;

LAB27:
LAB28:
LAB21:
LAB14:
LAB11:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(269, ng0);
    t11 = ((char*)((ng18)));
    t12 = (t0 + 8208);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 8, 0LL);
    goto LAB8;

LAB9:    xsi_set_current_line(271, ng0);
    t11 = (t0 + 8048);
    t12 = (t11 + 56U);
    t20 = *((char **)t12);
    t21 = (t0 + 8208);
    xsi_vlogvar_wait_assign_value(t21, t20, 0, 0, 8, 0LL);
    goto LAB11;

LAB12:    xsi_set_current_line(273, ng0);
    t11 = (t0 + 4768U);
    t12 = *((char **)t11);
    t11 = (t0 + 8208);
    xsi_vlogvar_wait_assign_value(t11, t12, 0, 0, 8, 0LL);
    goto LAB14;

LAB17:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB18;

LAB19:    xsi_set_current_line(275, ng0);
    t20 = (t0 + 6208U);
    t21 = *((char **)t20);
    memset(t28, 0, 8);
    t20 = (t28 + 4);
    t29 = (t21 + 4);
    t30 = *((unsigned int *)t21);
    t31 = (t30 >> 0);
    *((unsigned int *)t28) = t31;
    t32 = *((unsigned int *)t29);
    t33 = (t32 >> 0);
    *((unsigned int *)t20) = t33;
    t34 = *((unsigned int *)t28);
    *((unsigned int *)t28) = (t34 & 255U);
    t35 = *((unsigned int *)t20);
    *((unsigned int *)t20) = (t35 & 255U);
    t36 = (t0 + 8208);
    xsi_vlogvar_wait_assign_value(t36, t28, 0, 0, 8, 0LL);
    goto LAB21;

LAB24:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB25;

LAB26:    xsi_set_current_line(277, ng0);
    t20 = (t0 + 7568);
    t21 = (t20 + 56U);
    t29 = *((char **)t21);
    t36 = (t0 + 8208);
    xsi_vlogvar_wait_assign_value(t36, t29, 0, 0, 8, 0LL);
    goto LAB28;

}

static void Always_284_10(char *t0)
{
    char t13[8];
    char t28[8];
    char t54[8];
    char t56[8];
    char t60[8];
    char t98[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    char *t26;
    char *t27;
    char *t29;
    char *t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    char *t43;
    char *t44;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    char *t50;
    char *t51;
    char *t52;
    char *t53;
    char *t55;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    char *t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    char *t72;
    char *t73;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    unsigned int t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    int t82;
    int t83;
    unsigned int t84;
    unsigned int t85;
    unsigned int t86;
    unsigned int t87;
    unsigned int t88;
    unsigned int t89;
    char *t90;
    unsigned int t91;
    unsigned int t92;
    unsigned int t93;
    unsigned int t94;
    unsigned int t95;
    char *t96;
    char *t97;
    char *t99;
    char *t100;
    unsigned int t101;
    unsigned int t102;
    unsigned int t103;
    unsigned int t104;
    unsigned int t105;
    unsigned int t106;
    unsigned int t107;
    unsigned int t108;
    unsigned int t109;
    unsigned int t110;
    unsigned int t111;
    unsigned int t112;
    char *t113;
    char *t114;
    unsigned int t115;
    unsigned int t116;
    unsigned int t117;
    unsigned int t118;
    unsigned int t119;
    char *t120;
    char *t121;

LAB0:    t1 = (t0 + 12240U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(284, ng0);
    t2 = (t0 + 13216);
    *((int *)t2) = 1;
    t3 = (t0 + 12272);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(284, ng0);

LAB5:    xsi_set_current_line(285, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(288, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng8)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB12;

LAB9:    if (t18 != 0)
        goto LAB11;

LAB10:    *((unsigned int *)t13) = 1;

LAB12:    t12 = (t13 + 4);
    t21 = *((unsigned int *)t12);
    t22 = (~(t21));
    t23 = *((unsigned int *)t13);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB13;

LAB14:    xsi_set_current_line(298, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng12)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB28;

LAB25:    if (t18 != 0)
        goto LAB27;

LAB26:    *((unsigned int *)t13) = 1;

LAB28:    memset(t28, 0, 8);
    t12 = (t13 + 4);
    t21 = *((unsigned int *)t12);
    t22 = (~(t21));
    t23 = *((unsigned int *)t13);
    t24 = (t23 & t22);
    t25 = (t24 & 1U);
    if (t25 != 0)
        goto LAB29;

LAB30:    if (*((unsigned int *)t12) != 0)
        goto LAB31;

LAB32:    t27 = (t28 + 4);
    t31 = *((unsigned int *)t28);
    t32 = *((unsigned int *)t27);
    t33 = (t31 || t32);
    if (t33 > 0)
        goto LAB33;

LAB34:    memcpy(t60, t28, 8);

LAB35:    t90 = (t60 + 4);
    t91 = *((unsigned int *)t90);
    t92 = (~(t91));
    t93 = *((unsigned int *)t60);
    t94 = (t93 & t92);
    t95 = (t94 != 0);
    if (t95 > 0)
        goto LAB47;

LAB48:
LAB49:
LAB15:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(286, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 8688);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 16, 0LL);
    goto LAB8;

LAB11:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB12;

LAB13:    xsi_set_current_line(288, ng0);

LAB16:    xsi_set_current_line(289, ng0);
    t26 = (t0 + 5568U);
    t27 = *((char **)t26);
    t26 = ((char*)((ng20)));
    memset(t28, 0, 8);
    t29 = (t27 + 4);
    t30 = (t26 + 4);
    t31 = *((unsigned int *)t27);
    t32 = *((unsigned int *)t26);
    t33 = (t31 ^ t32);
    t34 = *((unsigned int *)t29);
    t35 = *((unsigned int *)t30);
    t36 = (t34 ^ t35);
    t37 = (t33 | t36);
    t38 = *((unsigned int *)t29);
    t39 = *((unsigned int *)t30);
    t40 = (t38 | t39);
    t41 = (~(t40));
    t42 = (t37 & t41);
    if (t42 != 0)
        goto LAB20;

LAB17:    if (t40 != 0)
        goto LAB19;

LAB18:    *((unsigned int *)t28) = 1;

LAB20:    t44 = (t28 + 4);
    t45 = *((unsigned int *)t44);
    t46 = (~(t45));
    t47 = *((unsigned int *)t28);
    t48 = (t47 & t46);
    t49 = (t48 != 0);
    if (t49 > 0)
        goto LAB21;

LAB22:
LAB23:    goto LAB15;

LAB19:    t43 = (t28 + 4);
    *((unsigned int *)t28) = 1;
    *((unsigned int *)t43) = 1;
    goto LAB20;

LAB21:    xsi_set_current_line(289, ng0);

LAB24:    xsi_set_current_line(295, ng0);
    t50 = (t0 + 7248);
    t51 = (t50 + 56U);
    t52 = *((char **)t51);
    t53 = ((char*)((ng2)));
    memset(t54, 0, 8);
    xsi_vlog_unsigned_add(t54, 32, t52, 10, t53, 32);
    t55 = (t0 + 8688);
    xsi_vlogvar_wait_assign_value(t55, t54, 0, 0, 16, 0LL);
    goto LAB23;

LAB27:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB28;

LAB29:    *((unsigned int *)t28) = 1;
    goto LAB32;

LAB31:    t26 = (t28 + 4);
    *((unsigned int *)t28) = 1;
    *((unsigned int *)t26) = 1;
    goto LAB32;

LAB33:    t29 = (t0 + 5568U);
    t30 = *((char **)t29);
    t29 = ((char*)((ng24)));
    memset(t54, 0, 8);
    t43 = (t30 + 4);
    t44 = (t29 + 4);
    t34 = *((unsigned int *)t30);
    t35 = *((unsigned int *)t29);
    t36 = (t34 ^ t35);
    t37 = *((unsigned int *)t43);
    t38 = *((unsigned int *)t44);
    t39 = (t37 ^ t38);
    t40 = (t36 | t39);
    t41 = *((unsigned int *)t43);
    t42 = *((unsigned int *)t44);
    t45 = (t41 | t42);
    t46 = (~(t45));
    t47 = (t40 & t46);
    if (t47 != 0)
        goto LAB39;

LAB36:    if (t45 != 0)
        goto LAB38;

LAB37:    *((unsigned int *)t54) = 1;

LAB39:    memset(t56, 0, 8);
    t51 = (t54 + 4);
    t48 = *((unsigned int *)t51);
    t49 = (~(t48));
    t57 = *((unsigned int *)t54);
    t58 = (t57 & t49);
    t59 = (t58 & 1U);
    if (t59 != 0)
        goto LAB40;

LAB41:    if (*((unsigned int *)t51) != 0)
        goto LAB42;

LAB43:    t61 = *((unsigned int *)t28);
    t62 = *((unsigned int *)t56);
    t63 = (t61 & t62);
    *((unsigned int *)t60) = t63;
    t53 = (t28 + 4);
    t55 = (t56 + 4);
    t64 = (t60 + 4);
    t65 = *((unsigned int *)t53);
    t66 = *((unsigned int *)t55);
    t67 = (t65 | t66);
    *((unsigned int *)t64) = t67;
    t68 = *((unsigned int *)t64);
    t69 = (t68 != 0);
    if (t69 == 1)
        goto LAB44;

LAB45:
LAB46:    goto LAB35;

LAB38:    t50 = (t54 + 4);
    *((unsigned int *)t54) = 1;
    *((unsigned int *)t50) = 1;
    goto LAB39;

LAB40:    *((unsigned int *)t56) = 1;
    goto LAB43;

LAB42:    t52 = (t56 + 4);
    *((unsigned int *)t56) = 1;
    *((unsigned int *)t52) = 1;
    goto LAB43;

LAB44:    t70 = *((unsigned int *)t60);
    t71 = *((unsigned int *)t64);
    *((unsigned int *)t60) = (t70 | t71);
    t72 = (t28 + 4);
    t73 = (t56 + 4);
    t74 = *((unsigned int *)t28);
    t75 = (~(t74));
    t76 = *((unsigned int *)t72);
    t77 = (~(t76));
    t78 = *((unsigned int *)t56);
    t79 = (~(t78));
    t80 = *((unsigned int *)t73);
    t81 = (~(t80));
    t82 = (t75 & t77);
    t83 = (t79 & t81);
    t84 = (~(t82));
    t85 = (~(t83));
    t86 = *((unsigned int *)t64);
    *((unsigned int *)t64) = (t86 & t84);
    t87 = *((unsigned int *)t64);
    *((unsigned int *)t64) = (t87 & t85);
    t88 = *((unsigned int *)t60);
    *((unsigned int *)t60) = (t88 & t84);
    t89 = *((unsigned int *)t60);
    *((unsigned int *)t60) = (t89 & t85);
    goto LAB46;

LAB47:    xsi_set_current_line(299, ng0);

LAB50:    xsi_set_current_line(300, ng0);
    t96 = (t0 + 6528U);
    t97 = *((char **)t96);
    t96 = ((char*)((ng1)));
    memset(t98, 0, 8);
    t99 = (t97 + 4);
    t100 = (t96 + 4);
    t101 = *((unsigned int *)t97);
    t102 = *((unsigned int *)t96);
    t103 = (t101 ^ t102);
    t104 = *((unsigned int *)t99);
    t105 = *((unsigned int *)t100);
    t106 = (t104 ^ t105);
    t107 = (t103 | t106);
    t108 = *((unsigned int *)t99);
    t109 = *((unsigned int *)t100);
    t110 = (t108 | t109);
    t111 = (~(t110));
    t112 = (t107 & t111);
    if (t112 != 0)
        goto LAB54;

LAB51:    if (t110 != 0)
        goto LAB53;

LAB52:    *((unsigned int *)t98) = 1;

LAB54:    t114 = (t98 + 4);
    t115 = *((unsigned int *)t114);
    t116 = (~(t115));
    t117 = *((unsigned int *)t98);
    t118 = (t117 & t116);
    t119 = (t118 != 0);
    if (t119 > 0)
        goto LAB55;

LAB56:    xsi_set_current_line(307, ng0);

LAB59:    xsi_set_current_line(311, ng0);
    t2 = ((char*)((ng19)));
    t3 = (t0 + 8688);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 16, 0LL);

LAB57:    goto LAB49;

LAB53:    t113 = (t98 + 4);
    *((unsigned int *)t98) = 1;
    *((unsigned int *)t113) = 1;
    goto LAB54;

LAB55:    xsi_set_current_line(300, ng0);

LAB58:    xsi_set_current_line(306, ng0);
    t120 = ((char*)((ng19)));
    t121 = (t0 + 8688);
    xsi_vlogvar_wait_assign_value(t121, t120, 0, 0, 16, 0LL);
    goto LAB57;

}

static void Always_318_11(char *t0)
{
    char t13[8];
    char t32[8];
    char t38[8];
    char t63[8];
    char t73[8];
    char t75[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    char *t26;
    char *t27;
    int t28;
    char *t29;
    char *t30;
    char *t31;
    char *t33;
    char *t34;
    char *t35;
    char *t36;
    char *t37;
    char *t39;
    char *t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    char *t53;
    char *t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    char *t60;
    char *t61;
    char *t62;
    char *t64;
    char *t65;
    char *t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    char *t74;
    char *t76;

LAB0:    t1 = (t0 + 12488U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(318, ng0);
    t2 = (t0 + 13232);
    *((int *)t2) = 1;
    t3 = (t0 + 12520);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(318, ng0);

LAB5:    xsi_set_current_line(319, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(321, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng10)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB13;

LAB10:    if (t18 != 0)
        goto LAB12;

LAB11:    *((unsigned int *)t13) = 1;

LAB13:    t12 = (t13 + 4);
    t21 = *((unsigned int *)t12);
    t22 = (~(t21));
    t23 = *((unsigned int *)t13);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB14;

LAB15:    xsi_set_current_line(350, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng14)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB52;

LAB49:    if (t18 != 0)
        goto LAB51;

LAB50:    *((unsigned int *)t13) = 1;

LAB52:    t12 = (t13 + 4);
    t21 = *((unsigned int *)t12);
    t22 = (~(t21));
    t23 = *((unsigned int *)t13);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB53;

LAB54:
LAB55:
LAB16:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(319, ng0);

LAB9:    xsi_set_current_line(320, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 7248);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 10, 0LL);
    goto LAB8;

LAB12:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB13;

LAB14:    xsi_set_current_line(321, ng0);

LAB17:    xsi_set_current_line(322, ng0);
    t26 = (t0 + 5568U);
    t27 = *((char **)t26);

LAB18:    t26 = ((char*)((ng25)));
    t28 = xsi_vlog_unsigned_case_compare(t27, 8, t26, 32);
    if (t28 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng26)));
    t28 = xsi_vlog_unsigned_case_compare(t27, 8, t2, 32);
    if (t28 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng27)));
    t28 = xsi_vlog_unsigned_case_compare(t27, 8, t2, 32);
    if (t28 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng20)));
    t28 = xsi_vlog_unsigned_case_compare(t27, 8, t2, 32);
    if (t28 == 1)
        goto LAB25;

LAB26:
LAB28:
LAB27:    xsi_set_current_line(346, ng0);

LAB48:    xsi_set_current_line(347, ng0);
    t2 = (t0 + 7248);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t13, 0, 8);
    xsi_vlog_unsigned_add(t13, 32, t4, 10, t5, 32);
    t11 = (t0 + 8848);
    xsi_vlogvar_wait_assign_value(t11, t13, 0, 0, 10, 0LL);

LAB29:    goto LAB16;

LAB19:    xsi_set_current_line(323, ng0);

LAB30:    xsi_set_current_line(324, ng0);
    t29 = (t0 + 8368);
    t30 = (t29 + 56U);
    t31 = *((char **)t30);
    t33 = (t0 + 8368);
    t34 = (t33 + 72U);
    t35 = *((char **)t34);
    t36 = (t0 + 6368U);
    t37 = *((char **)t36);
    xsi_vlog_generic_get_index_select_value(t32, 32, t31, t35, 2, t37, 3, 2);
    t36 = ((char*)((ng2)));
    memset(t38, 0, 8);
    t39 = (t32 + 4);
    t40 = (t36 + 4);
    t41 = *((unsigned int *)t32);
    t42 = *((unsigned int *)t36);
    t43 = (t41 ^ t42);
    t44 = *((unsigned int *)t39);
    t45 = *((unsigned int *)t40);
    t46 = (t44 ^ t45);
    t47 = (t43 | t46);
    t48 = *((unsigned int *)t39);
    t49 = *((unsigned int *)t40);
    t50 = (t48 | t49);
    t51 = (~(t50));
    t52 = (t47 & t51);
    if (t52 != 0)
        goto LAB34;

LAB31:    if (t50 != 0)
        goto LAB33;

LAB32:    *((unsigned int *)t38) = 1;

LAB34:    t54 = (t38 + 4);
    t55 = *((unsigned int *)t54);
    t56 = (~(t55));
    t57 = *((unsigned int *)t38);
    t58 = (t57 & t56);
    t59 = (t58 != 0);
    if (t59 > 0)
        goto LAB35;

LAB36:    xsi_set_current_line(327, ng0);
    t2 = (t0 + 7248);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t13, 0, 8);
    xsi_vlog_unsigned_add(t13, 32, t4, 10, t5, 32);
    t11 = (t0 + 8848);
    xsi_vlogvar_wait_assign_value(t11, t13, 0, 0, 10, 0LL);

LAB37:    goto LAB29;

LAB21:    xsi_set_current_line(329, ng0);

LAB38:    xsi_set_current_line(330, ng0);
    t3 = (t0 + 8368);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t11 = (t0 + 8368);
    t12 = (t11 + 72U);
    t26 = *((char **)t12);
    t29 = (t0 + 6368U);
    t30 = *((char **)t29);
    xsi_vlog_generic_get_index_select_value(t13, 32, t5, t26, 2, t30, 3, 2);
    t29 = ((char*)((ng1)));
    memset(t32, 0, 8);
    t31 = (t13 + 4);
    t33 = (t29 + 4);
    t6 = *((unsigned int *)t13);
    t7 = *((unsigned int *)t29);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t31);
    t10 = *((unsigned int *)t33);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t31);
    t17 = *((unsigned int *)t33);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB42;

LAB39:    if (t18 != 0)
        goto LAB41;

LAB40:    *((unsigned int *)t32) = 1;

LAB42:    t35 = (t32 + 4);
    t21 = *((unsigned int *)t35);
    t22 = (~(t21));
    t23 = *((unsigned int *)t32);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB43;

LAB44:    xsi_set_current_line(333, ng0);
    t2 = (t0 + 7248);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t13, 0, 8);
    xsi_vlog_unsigned_add(t13, 32, t4, 10, t5, 32);
    t11 = (t0 + 8848);
    xsi_vlogvar_wait_assign_value(t11, t13, 0, 0, 10, 0LL);

LAB45:    goto LAB29;

LAB23:    xsi_set_current_line(335, ng0);

LAB46:    xsi_set_current_line(336, ng0);
    t3 = (t0 + 7248);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t11 = (t0 + 6208U);
    t12 = *((char **)t11);
    memset(t13, 0, 8);
    t11 = (t13 + 4);
    t26 = (t12 + 4);
    t6 = *((unsigned int *)t12);
    t7 = (t6 >> 0);
    *((unsigned int *)t13) = t7;
    t8 = *((unsigned int *)t26);
    t9 = (t8 >> 0);
    *((unsigned int *)t11) = t9;
    t10 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t10 & 1023U);
    t14 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t14 & 1023U);
    memset(t32, 0, 8);
    xsi_vlog_unsigned_add(t32, 32, t5, 10, t13, 32);
    t29 = ((char*)((ng2)));
    memset(t38, 0, 8);
    xsi_vlog_unsigned_add(t38, 32, t32, 32, t29, 32);
    t30 = (t0 + 8848);
    xsi_vlogvar_wait_assign_value(t30, t38, 0, 0, 10, 0LL);
    goto LAB29;

LAB25:    xsi_set_current_line(338, ng0);

LAB47:    xsi_set_current_line(344, ng0);
    t3 = (t0 + 7248);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t11 = (t0 + 6208U);
    t12 = *((char **)t11);
    memset(t13, 0, 8);
    t11 = (t13 + 4);
    t26 = (t12 + 4);
    t6 = *((unsigned int *)t12);
    t7 = (t6 >> 0);
    *((unsigned int *)t13) = t7;
    t8 = *((unsigned int *)t26);
    t9 = (t8 >> 0);
    *((unsigned int *)t11) = t9;
    t10 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t10 & 1023U);
    t14 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t14 & 1023U);
    memset(t32, 0, 8);
    xsi_vlog_unsigned_add(t32, 32, t5, 10, t13, 32);
    t29 = ((char*)((ng2)));
    memset(t38, 0, 8);
    xsi_vlog_unsigned_add(t38, 32, t32, 32, t29, 32);
    t30 = (t0 + 8848);
    xsi_vlogvar_wait_assign_value(t30, t38, 0, 0, 10, 0LL);
    goto LAB29;

LAB33:    t53 = (t38 + 4);
    *((unsigned int *)t38) = 1;
    *((unsigned int *)t53) = 1;
    goto LAB34;

LAB35:    xsi_set_current_line(325, ng0);
    t60 = (t0 + 7248);
    t61 = (t60 + 56U);
    t62 = *((char **)t61);
    t64 = (t0 + 6208U);
    t65 = *((char **)t64);
    memset(t63, 0, 8);
    t64 = (t63 + 4);
    t66 = (t65 + 4);
    t67 = *((unsigned int *)t65);
    t68 = (t67 >> 0);
    *((unsigned int *)t63) = t68;
    t69 = *((unsigned int *)t66);
    t70 = (t69 >> 0);
    *((unsigned int *)t64) = t70;
    t71 = *((unsigned int *)t63);
    *((unsigned int *)t63) = (t71 & 1023U);
    t72 = *((unsigned int *)t64);
    *((unsigned int *)t64) = (t72 & 1023U);
    memset(t73, 0, 8);
    xsi_vlog_unsigned_add(t73, 32, t62, 10, t63, 32);
    t74 = ((char*)((ng2)));
    memset(t75, 0, 8);
    xsi_vlog_unsigned_add(t75, 32, t73, 32, t74, 32);
    t76 = (t0 + 8848);
    xsi_vlogvar_wait_assign_value(t76, t75, 0, 0, 10, 0LL);
    goto LAB37;

LAB41:    t34 = (t32 + 4);
    *((unsigned int *)t32) = 1;
    *((unsigned int *)t34) = 1;
    goto LAB42;

LAB43:    xsi_set_current_line(331, ng0);
    t36 = (t0 + 7248);
    t37 = (t36 + 56U);
    t39 = *((char **)t37);
    t40 = (t0 + 6208U);
    t53 = *((char **)t40);
    memset(t38, 0, 8);
    t40 = (t38 + 4);
    t54 = (t53 + 4);
    t41 = *((unsigned int *)t53);
    t42 = (t41 >> 0);
    *((unsigned int *)t38) = t42;
    t43 = *((unsigned int *)t54);
    t44 = (t43 >> 0);
    *((unsigned int *)t40) = t44;
    t45 = *((unsigned int *)t38);
    *((unsigned int *)t38) = (t45 & 1023U);
    t46 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t46 & 1023U);
    memset(t63, 0, 8);
    xsi_vlog_unsigned_add(t63, 32, t39, 10, t38, 32);
    t60 = ((char*)((ng2)));
    memset(t73, 0, 8);
    xsi_vlog_unsigned_add(t73, 32, t63, 32, t60, 32);
    t61 = (t0 + 8848);
    xsi_vlogvar_wait_assign_value(t61, t73, 0, 0, 10, 0LL);
    goto LAB45;

LAB51:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB52;

LAB53:    xsi_set_current_line(350, ng0);

LAB56:    xsi_set_current_line(351, ng0);
    t26 = (t0 + 5568U);
    t29 = *((char **)t26);
    t26 = ((char*)((ng24)));
    memset(t32, 0, 8);
    t30 = (t29 + 4);
    t31 = (t26 + 4);
    t41 = *((unsigned int *)t29);
    t42 = *((unsigned int *)t26);
    t43 = (t41 ^ t42);
    t44 = *((unsigned int *)t30);
    t45 = *((unsigned int *)t31);
    t46 = (t44 ^ t45);
    t47 = (t43 | t46);
    t48 = *((unsigned int *)t30);
    t49 = *((unsigned int *)t31);
    t50 = (t48 | t49);
    t51 = (~(t50));
    t52 = (t47 & t51);
    if (t52 != 0)
        goto LAB60;

LAB57:    if (t50 != 0)
        goto LAB59;

LAB58:    *((unsigned int *)t32) = 1;

LAB60:    t34 = (t32 + 4);
    t55 = *((unsigned int *)t34);
    t56 = (~(t55));
    t57 = *((unsigned int *)t32);
    t58 = (t57 & t56);
    t59 = (t58 != 0);
    if (t59 > 0)
        goto LAB61;

LAB62:    xsi_set_current_line(357, ng0);

LAB65:    xsi_set_current_line(358, ng0);
    t2 = (t0 + 8848);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 7248);
    xsi_vlogvar_wait_assign_value(t5, t4, 0, 0, 10, 0LL);

LAB63:    goto LAB55;

LAB59:    t33 = (t32 + 4);
    *((unsigned int *)t32) = 1;
    *((unsigned int *)t33) = 1;
    goto LAB60;

LAB61:    xsi_set_current_line(351, ng0);

LAB64:    xsi_set_current_line(356, ng0);
    t35 = (t0 + 8848);
    t36 = (t35 + 56U);
    t37 = *((char **)t36);
    t39 = (t0 + 7248);
    xsi_vlogvar_wait_assign_value(t39, t37, 0, 0, 10, 0LL);
    goto LAB63;

}

static void Always_368_12(char *t0)
{
    char t13[8];
    char t22[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    char *t20;
    char *t21;
    char *t23;

LAB0:    t1 = (t0 + 12736U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(368, ng0);
    t2 = (t0 + 13248);
    *((int *)t2) = 1;
    t3 = (t0 + 12768);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(368, ng0);

LAB5:    xsi_set_current_line(369, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(372, ng0);
    t2 = (t0 + 5408U);
    t3 = *((char **)t2);
    memset(t13, 0, 8);
    t2 = (t13 + 4);
    t4 = (t3 + 4);
    t6 = *((unsigned int *)t3);
    t7 = (t6 >> 6);
    t8 = (t7 & 1);
    *((unsigned int *)t13) = t8;
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 6);
    t14 = (t10 & 1);
    *((unsigned int *)t2) = t14;
    t5 = (t13 + 4);
    t15 = *((unsigned int *)t5);
    t16 = (~(t15));
    t17 = *((unsigned int *)t13);
    t18 = (t17 & t16);
    t19 = (t18 != 0);
    if (t19 > 0)
        goto LAB9;

LAB10:    xsi_set_current_line(374, ng0);
    t2 = (t0 + 5408U);
    t3 = *((char **)t2);
    memset(t13, 0, 8);
    t2 = (t13 + 4);
    t4 = (t3 + 4);
    t6 = *((unsigned int *)t3);
    t7 = (t6 >> 7);
    t8 = (t7 & 1);
    *((unsigned int *)t13) = t8;
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 7);
    t14 = (t10 & 1);
    *((unsigned int *)t2) = t14;
    t5 = (t13 + 4);
    t15 = *((unsigned int *)t5);
    t16 = (~(t15));
    t17 = *((unsigned int *)t13);
    t18 = (t17 & t16);
    t19 = (t18 != 0);
    if (t19 > 0)
        goto LAB12;

LAB13:
LAB14:
LAB11:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(370, ng0);
    t11 = ((char*)((ng28)));
    t12 = (t0 + 8528);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 8, 0LL);
    goto LAB8;

LAB9:    xsi_set_current_line(373, ng0);
    t11 = (t0 + 8528);
    t12 = (t11 + 56U);
    t20 = *((char **)t12);
    t21 = ((char*)((ng29)));
    memset(t22, 0, 8);
    xsi_vlog_unsigned_minus(t22, 8, t20, 8, t21, 8);
    t23 = (t0 + 8528);
    xsi_vlogvar_wait_assign_value(t23, t22, 0, 0, 8, 0LL);
    goto LAB11;

LAB12:    xsi_set_current_line(375, ng0);
    t11 = (t0 + 8528);
    t12 = (t11 + 56U);
    t20 = *((char **)t12);
    t21 = ((char*)((ng29)));
    memset(t22, 0, 8);
    xsi_vlog_unsigned_add(t22, 8, t20, 8, t21, 8);
    t23 = (t0 + 8528);
    xsi_vlogvar_wait_assign_value(t23, t22, 0, 0, 8, 0LL);
    goto LAB14;

}


extern void work_m_16406118477946760835_1351276808_init()
{
	static char *pe[] = {(void *)Always_152_0,(void *)Always_165_1,(void *)Always_193_2,(void *)Cont_204_3,(void *)Always_205_4,(void *)Always_214_5,(void *)Cont_220_6,(void *)Cont_230_7,(void *)Cont_247_8,(void *)Always_267_9,(void *)Always_284_10,(void *)Always_318_11,(void *)Always_368_12};
	xsi_register_didat("work_m_16406118477946760835_1351276808", "isim/control_unit_isim_beh.exe.sim/work/m_16406118477946760835_1351276808.didat");
	xsi_register_executes(pe);
}
