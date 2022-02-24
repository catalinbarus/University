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
static const char *ng0 = "/home/student/Desktop/CN2/lab8/lab08_skel_2021_2/lab08_skel/interrupt_controller.v";
static int ng1[] = {0, 0};
static unsigned int ng2[] = {7U, 0U};
static int ng3[] = {1, 0};
static unsigned int ng4[] = {11U, 0U};
static unsigned int ng5[] = {9U, 0U};
static unsigned int ng6[] = {10U, 0U};



static void Always_15_0(char *t0)
{
    char t13[8];
    char t14[8];
    char t22[8];
    char t30[8];
    char t38[8];
    char t70[8];
    char t84[8];
    char t92[8];
    char t100[8];
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
    char *t15;
    char *t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    char *t20;
    char *t21;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    char *t37;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    char *t42;
    char *t43;
    char *t44;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    char *t52;
    char *t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    int t62;
    int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    char *t71;
    unsigned int t72;
    unsigned int t73;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    char *t77;
    char *t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    char *t82;
    char *t83;
    char *t85;
    unsigned int t86;
    unsigned int t87;
    unsigned int t88;
    unsigned int t89;
    unsigned int t90;
    unsigned int t91;
    char *t93;
    unsigned int t94;
    unsigned int t95;
    unsigned int t96;
    unsigned int t97;
    unsigned int t98;
    char *t99;
    unsigned int t101;
    unsigned int t102;
    unsigned int t103;
    char *t104;
    char *t105;
    char *t106;
    unsigned int t107;
    unsigned int t108;
    unsigned int t109;
    unsigned int t110;
    unsigned int t111;
    unsigned int t112;
    unsigned int t113;
    char *t114;
    char *t115;
    unsigned int t116;
    unsigned int t117;
    unsigned int t118;
    unsigned int t119;
    unsigned int t120;
    unsigned int t121;
    unsigned int t122;
    unsigned int t123;
    int t124;
    int t125;
    unsigned int t126;
    unsigned int t127;
    unsigned int t128;
    unsigned int t129;
    unsigned int t130;
    unsigned int t131;
    char *t132;
    unsigned int t133;
    unsigned int t134;
    unsigned int t135;
    unsigned int t136;
    unsigned int t137;
    char *t138;
    char *t139;

LAB0:    t1 = (t0 + 3432U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(15, ng0);
    t2 = (t0 + 3752);
    *((int *)t2) = 1;
    t3 = (t0 + 3464);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(15, ng0);

LAB5:    xsi_set_current_line(16, ng0);
    t4 = (t0 + 1480U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(19, ng0);

LAB10:    xsi_set_current_line(38, ng0);
    t2 = (t0 + 1960U);
    t3 = *((char **)t2);
    t2 = (t0 + 1920U);
    t4 = (t2 + 72U);
    t5 = *((char **)t4);
    t11 = ((char*)((ng2)));
    xsi_vlog_generic_get_index_select_value(t13, 1, t3, t5, 2, t11, 3, 2);
    memset(t14, 0, 8);
    t12 = (t13 + 4);
    t6 = *((unsigned int *)t12);
    t7 = (~(t6));
    t8 = *((unsigned int *)t13);
    t9 = (t8 & t7);
    t10 = (t9 & 1U);
    if (t10 != 0)
        goto LAB11;

LAB12:    if (*((unsigned int *)t12) != 0)
        goto LAB13;

LAB14:    t16 = (t14 + 4);
    t17 = *((unsigned int *)t14);
    t18 = *((unsigned int *)t16);
    t19 = (t17 || t18);
    if (t19 > 0)
        goto LAB15;

LAB16:    memcpy(t38, t14, 8);

LAB17:    memset(t70, 0, 8);
    t71 = (t38 + 4);
    t72 = *((unsigned int *)t71);
    t73 = (~(t72));
    t74 = *((unsigned int *)t38);
    t75 = (t74 & t73);
    t76 = (t75 & 1U);
    if (t76 != 0)
        goto LAB25;

LAB26:    if (*((unsigned int *)t71) != 0)
        goto LAB27;

LAB28:    t78 = (t70 + 4);
    t79 = *((unsigned int *)t70);
    t80 = *((unsigned int *)t78);
    t81 = (t79 || t80);
    if (t81 > 0)
        goto LAB29;

LAB30:    memcpy(t100, t70, 8);

LAB31:    t132 = (t100 + 4);
    t133 = *((unsigned int *)t132);
    t134 = (~(t133));
    t135 = *((unsigned int *)t100);
    t136 = (t135 & t134);
    t137 = (t136 != 0);
    if (t137 > 0)
        goto LAB39;

LAB40:    xsi_set_current_line(41, ng0);
    t2 = (t0 + 1960U);
    t3 = *((char **)t2);
    t2 = (t0 + 1920U);
    t4 = (t2 + 72U);
    t5 = *((char **)t4);
    t11 = ((char*)((ng2)));
    xsi_vlog_generic_get_index_select_value(t13, 1, t3, t5, 2, t11, 3, 2);
    memset(t14, 0, 8);
    t12 = (t13 + 4);
    t6 = *((unsigned int *)t12);
    t7 = (~(t6));
    t8 = *((unsigned int *)t13);
    t9 = (t8 & t7);
    t10 = (t9 & 1U);
    if (t10 != 0)
        goto LAB43;

LAB44:    if (*((unsigned int *)t12) != 0)
        goto LAB45;

LAB46:    t16 = (t14 + 4);
    t17 = *((unsigned int *)t14);
    t18 = *((unsigned int *)t16);
    t19 = (t17 || t18);
    if (t19 > 0)
        goto LAB47;

LAB48:    memcpy(t38, t14, 8);

LAB49:    memset(t70, 0, 8);
    t71 = (t38 + 4);
    t72 = *((unsigned int *)t71);
    t73 = (~(t72));
    t74 = *((unsigned int *)t38);
    t75 = (t74 & t73);
    t76 = (t75 & 1U);
    if (t76 != 0)
        goto LAB57;

LAB58:    if (*((unsigned int *)t71) != 0)
        goto LAB59;

LAB60:    t78 = (t70 + 4);
    t79 = *((unsigned int *)t70);
    t80 = *((unsigned int *)t78);
    t81 = (t79 || t80);
    if (t81 > 0)
        goto LAB61;

LAB62:    memcpy(t100, t70, 8);

LAB63:    t132 = (t100 + 4);
    t133 = *((unsigned int *)t132);
    t134 = (~(t133));
    t135 = *((unsigned int *)t100);
    t136 = (t135 & t134);
    t137 = (t136 != 0);
    if (t137 > 0)
        goto LAB71;

LAB72:    xsi_set_current_line(44, ng0);
    t2 = (t0 + 1960U);
    t3 = *((char **)t2);
    t2 = (t0 + 1920U);
    t4 = (t2 + 72U);
    t5 = *((char **)t4);
    t11 = ((char*)((ng2)));
    xsi_vlog_generic_get_index_select_value(t13, 1, t3, t5, 2, t11, 3, 2);
    memset(t14, 0, 8);
    t12 = (t13 + 4);
    t6 = *((unsigned int *)t12);
    t7 = (~(t6));
    t8 = *((unsigned int *)t13);
    t9 = (t8 & t7);
    t10 = (t9 & 1U);
    if (t10 != 0)
        goto LAB75;

LAB76:    if (*((unsigned int *)t12) != 0)
        goto LAB77;

LAB78:    t16 = (t14 + 4);
    t17 = *((unsigned int *)t14);
    t18 = *((unsigned int *)t16);
    t19 = (t17 || t18);
    if (t19 > 0)
        goto LAB79;

LAB80:    memcpy(t38, t14, 8);

LAB81:    memset(t70, 0, 8);
    t71 = (t38 + 4);
    t72 = *((unsigned int *)t71);
    t73 = (~(t72));
    t74 = *((unsigned int *)t38);
    t75 = (t74 & t73);
    t76 = (t75 & 1U);
    if (t76 != 0)
        goto LAB89;

LAB90:    if (*((unsigned int *)t71) != 0)
        goto LAB91;

LAB92:    t78 = (t70 + 4);
    t79 = *((unsigned int *)t70);
    t80 = *((unsigned int *)t78);
    t81 = (t79 || t80);
    if (t81 > 0)
        goto LAB93;

LAB94:    memcpy(t100, t70, 8);

LAB95:    t132 = (t100 + 4);
    t133 = *((unsigned int *)t132);
    t134 = (~(t133));
    t135 = *((unsigned int *)t100);
    t136 = (t135 & t134);
    t137 = (t136 != 0);
    if (t137 > 0)
        goto LAB103;

LAB104:    xsi_set_current_line(47, ng0);

LAB107:    xsi_set_current_line(48, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 2360);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);

LAB105:
LAB73:
LAB41:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(16, ng0);

LAB9:    xsi_set_current_line(17, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 2360);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 1, 0LL);
    xsi_set_current_line(18, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 2520);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 10, 0LL);
    goto LAB8;

LAB11:    *((unsigned int *)t14) = 1;
    goto LAB14;

LAB13:    t15 = (t14 + 4);
    *((unsigned int *)t14) = 1;
    *((unsigned int *)t15) = 1;
    goto LAB14;

LAB15:    t20 = (t0 + 1800U);
    t21 = *((char **)t20);
    memset(t22, 0, 8);
    t20 = (t22 + 4);
    t23 = (t21 + 4);
    t24 = *((unsigned int *)t21);
    t25 = (t24 >> 0);
    t26 = (t25 & 1);
    *((unsigned int *)t22) = t26;
    t27 = *((unsigned int *)t23);
    t28 = (t27 >> 0);
    t29 = (t28 & 1);
    *((unsigned int *)t20) = t29;
    memset(t30, 0, 8);
    t31 = (t22 + 4);
    t32 = *((unsigned int *)t31);
    t33 = (~(t32));
    t34 = *((unsigned int *)t22);
    t35 = (t34 & t33);
    t36 = (t35 & 1U);
    if (t36 != 0)
        goto LAB18;

LAB19:    if (*((unsigned int *)t31) != 0)
        goto LAB20;

LAB21:    t39 = *((unsigned int *)t14);
    t40 = *((unsigned int *)t30);
    t41 = (t39 & t40);
    *((unsigned int *)t38) = t41;
    t42 = (t14 + 4);
    t43 = (t30 + 4);
    t44 = (t38 + 4);
    t45 = *((unsigned int *)t42);
    t46 = *((unsigned int *)t43);
    t47 = (t45 | t46);
    *((unsigned int *)t44) = t47;
    t48 = *((unsigned int *)t44);
    t49 = (t48 != 0);
    if (t49 == 1)
        goto LAB22;

LAB23:
LAB24:    goto LAB17;

LAB18:    *((unsigned int *)t30) = 1;
    goto LAB21;

LAB20:    t37 = (t30 + 4);
    *((unsigned int *)t30) = 1;
    *((unsigned int *)t37) = 1;
    goto LAB21;

LAB22:    t50 = *((unsigned int *)t38);
    t51 = *((unsigned int *)t44);
    *((unsigned int *)t38) = (t50 | t51);
    t52 = (t14 + 4);
    t53 = (t30 + 4);
    t54 = *((unsigned int *)t14);
    t55 = (~(t54));
    t56 = *((unsigned int *)t52);
    t57 = (~(t56));
    t58 = *((unsigned int *)t30);
    t59 = (~(t58));
    t60 = *((unsigned int *)t53);
    t61 = (~(t60));
    t62 = (t55 & t57);
    t63 = (t59 & t61);
    t64 = (~(t62));
    t65 = (~(t63));
    t66 = *((unsigned int *)t44);
    *((unsigned int *)t44) = (t66 & t64);
    t67 = *((unsigned int *)t44);
    *((unsigned int *)t44) = (t67 & t65);
    t68 = *((unsigned int *)t38);
    *((unsigned int *)t38) = (t68 & t64);
    t69 = *((unsigned int *)t38);
    *((unsigned int *)t38) = (t69 & t65);
    goto LAB24;

LAB25:    *((unsigned int *)t70) = 1;
    goto LAB28;

LAB27:    t77 = (t70 + 4);
    *((unsigned int *)t70) = 1;
    *((unsigned int *)t77) = 1;
    goto LAB28;

LAB29:    t82 = (t0 + 1640U);
    t83 = *((char **)t82);
    memset(t84, 0, 8);
    t82 = (t84 + 4);
    t85 = (t83 + 4);
    t86 = *((unsigned int *)t83);
    t87 = (t86 >> 0);
    t88 = (t87 & 1);
    *((unsigned int *)t84) = t88;
    t89 = *((unsigned int *)t85);
    t90 = (t89 >> 0);
    t91 = (t90 & 1);
    *((unsigned int *)t82) = t91;
    memset(t92, 0, 8);
    t93 = (t84 + 4);
    t94 = *((unsigned int *)t93);
    t95 = (~(t94));
    t96 = *((unsigned int *)t84);
    t97 = (t96 & t95);
    t98 = (t97 & 1U);
    if (t98 != 0)
        goto LAB32;

LAB33:    if (*((unsigned int *)t93) != 0)
        goto LAB34;

LAB35:    t101 = *((unsigned int *)t70);
    t102 = *((unsigned int *)t92);
    t103 = (t101 & t102);
    *((unsigned int *)t100) = t103;
    t104 = (t70 + 4);
    t105 = (t92 + 4);
    t106 = (t100 + 4);
    t107 = *((unsigned int *)t104);
    t108 = *((unsigned int *)t105);
    t109 = (t107 | t108);
    *((unsigned int *)t106) = t109;
    t110 = *((unsigned int *)t106);
    t111 = (t110 != 0);
    if (t111 == 1)
        goto LAB36;

LAB37:
LAB38:    goto LAB31;

LAB32:    *((unsigned int *)t92) = 1;
    goto LAB35;

LAB34:    t99 = (t92 + 4);
    *((unsigned int *)t92) = 1;
    *((unsigned int *)t99) = 1;
    goto LAB35;

LAB36:    t112 = *((unsigned int *)t100);
    t113 = *((unsigned int *)t106);
    *((unsigned int *)t100) = (t112 | t113);
    t114 = (t70 + 4);
    t115 = (t92 + 4);
    t116 = *((unsigned int *)t70);
    t117 = (~(t116));
    t118 = *((unsigned int *)t114);
    t119 = (~(t118));
    t120 = *((unsigned int *)t92);
    t121 = (~(t120));
    t122 = *((unsigned int *)t115);
    t123 = (~(t122));
    t124 = (t117 & t119);
    t125 = (t121 & t123);
    t126 = (~(t124));
    t127 = (~(t125));
    t128 = *((unsigned int *)t106);
    *((unsigned int *)t106) = (t128 & t126);
    t129 = *((unsigned int *)t106);
    *((unsigned int *)t106) = (t129 & t127);
    t130 = *((unsigned int *)t100);
    *((unsigned int *)t100) = (t130 & t126);
    t131 = *((unsigned int *)t100);
    *((unsigned int *)t100) = (t131 & t127);
    goto LAB38;

LAB39:    xsi_set_current_line(38, ng0);

LAB42:    xsi_set_current_line(39, ng0);
    t138 = ((char*)((ng3)));
    t139 = (t0 + 2360);
    xsi_vlogvar_wait_assign_value(t139, t138, 0, 0, 1, 0LL);
    xsi_set_current_line(40, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 2520);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 10, 0LL);
    goto LAB41;

LAB43:    *((unsigned int *)t14) = 1;
    goto LAB46;

LAB45:    t15 = (t14 + 4);
    *((unsigned int *)t14) = 1;
    *((unsigned int *)t15) = 1;
    goto LAB46;

LAB47:    t20 = (t0 + 1800U);
    t21 = *((char **)t20);
    memset(t22, 0, 8);
    t20 = (t22 + 4);
    t23 = (t21 + 4);
    t24 = *((unsigned int *)t21);
    t25 = (t24 >> 1);
    t26 = (t25 & 1);
    *((unsigned int *)t22) = t26;
    t27 = *((unsigned int *)t23);
    t28 = (t27 >> 1);
    t29 = (t28 & 1);
    *((unsigned int *)t20) = t29;
    memset(t30, 0, 8);
    t31 = (t22 + 4);
    t32 = *((unsigned int *)t31);
    t33 = (~(t32));
    t34 = *((unsigned int *)t22);
    t35 = (t34 & t33);
    t36 = (t35 & 1U);
    if (t36 != 0)
        goto LAB50;

LAB51:    if (*((unsigned int *)t31) != 0)
        goto LAB52;

LAB53:    t39 = *((unsigned int *)t14);
    t40 = *((unsigned int *)t30);
    t41 = (t39 & t40);
    *((unsigned int *)t38) = t41;
    t42 = (t14 + 4);
    t43 = (t30 + 4);
    t44 = (t38 + 4);
    t45 = *((unsigned int *)t42);
    t46 = *((unsigned int *)t43);
    t47 = (t45 | t46);
    *((unsigned int *)t44) = t47;
    t48 = *((unsigned int *)t44);
    t49 = (t48 != 0);
    if (t49 == 1)
        goto LAB54;

LAB55:
LAB56:    goto LAB49;

LAB50:    *((unsigned int *)t30) = 1;
    goto LAB53;

LAB52:    t37 = (t30 + 4);
    *((unsigned int *)t30) = 1;
    *((unsigned int *)t37) = 1;
    goto LAB53;

LAB54:    t50 = *((unsigned int *)t38);
    t51 = *((unsigned int *)t44);
    *((unsigned int *)t38) = (t50 | t51);
    t52 = (t14 + 4);
    t53 = (t30 + 4);
    t54 = *((unsigned int *)t14);
    t55 = (~(t54));
    t56 = *((unsigned int *)t52);
    t57 = (~(t56));
    t58 = *((unsigned int *)t30);
    t59 = (~(t58));
    t60 = *((unsigned int *)t53);
    t61 = (~(t60));
    t62 = (t55 & t57);
    t63 = (t59 & t61);
    t64 = (~(t62));
    t65 = (~(t63));
    t66 = *((unsigned int *)t44);
    *((unsigned int *)t44) = (t66 & t64);
    t67 = *((unsigned int *)t44);
    *((unsigned int *)t44) = (t67 & t65);
    t68 = *((unsigned int *)t38);
    *((unsigned int *)t38) = (t68 & t64);
    t69 = *((unsigned int *)t38);
    *((unsigned int *)t38) = (t69 & t65);
    goto LAB56;

LAB57:    *((unsigned int *)t70) = 1;
    goto LAB60;

LAB59:    t77 = (t70 + 4);
    *((unsigned int *)t70) = 1;
    *((unsigned int *)t77) = 1;
    goto LAB60;

LAB61:    t82 = (t0 + 1640U);
    t83 = *((char **)t82);
    memset(t84, 0, 8);
    t82 = (t84 + 4);
    t85 = (t83 + 4);
    t86 = *((unsigned int *)t83);
    t87 = (t86 >> 1);
    t88 = (t87 & 1);
    *((unsigned int *)t84) = t88;
    t89 = *((unsigned int *)t85);
    t90 = (t89 >> 1);
    t91 = (t90 & 1);
    *((unsigned int *)t82) = t91;
    memset(t92, 0, 8);
    t93 = (t84 + 4);
    t94 = *((unsigned int *)t93);
    t95 = (~(t94));
    t96 = *((unsigned int *)t84);
    t97 = (t96 & t95);
    t98 = (t97 & 1U);
    if (t98 != 0)
        goto LAB64;

LAB65:    if (*((unsigned int *)t93) != 0)
        goto LAB66;

LAB67:    t101 = *((unsigned int *)t70);
    t102 = *((unsigned int *)t92);
    t103 = (t101 & t102);
    *((unsigned int *)t100) = t103;
    t104 = (t70 + 4);
    t105 = (t92 + 4);
    t106 = (t100 + 4);
    t107 = *((unsigned int *)t104);
    t108 = *((unsigned int *)t105);
    t109 = (t107 | t108);
    *((unsigned int *)t106) = t109;
    t110 = *((unsigned int *)t106);
    t111 = (t110 != 0);
    if (t111 == 1)
        goto LAB68;

LAB69:
LAB70:    goto LAB63;

LAB64:    *((unsigned int *)t92) = 1;
    goto LAB67;

LAB66:    t99 = (t92 + 4);
    *((unsigned int *)t92) = 1;
    *((unsigned int *)t99) = 1;
    goto LAB67;

LAB68:    t112 = *((unsigned int *)t100);
    t113 = *((unsigned int *)t106);
    *((unsigned int *)t100) = (t112 | t113);
    t114 = (t70 + 4);
    t115 = (t92 + 4);
    t116 = *((unsigned int *)t70);
    t117 = (~(t116));
    t118 = *((unsigned int *)t114);
    t119 = (~(t118));
    t120 = *((unsigned int *)t92);
    t121 = (~(t120));
    t122 = *((unsigned int *)t115);
    t123 = (~(t122));
    t124 = (t117 & t119);
    t125 = (t121 & t123);
    t126 = (~(t124));
    t127 = (~(t125));
    t128 = *((unsigned int *)t106);
    *((unsigned int *)t106) = (t128 & t126);
    t129 = *((unsigned int *)t106);
    *((unsigned int *)t106) = (t129 & t127);
    t130 = *((unsigned int *)t100);
    *((unsigned int *)t100) = (t130 & t126);
    t131 = *((unsigned int *)t100);
    *((unsigned int *)t100) = (t131 & t127);
    goto LAB70;

LAB71:    xsi_set_current_line(41, ng0);

LAB74:    xsi_set_current_line(42, ng0);
    t138 = ((char*)((ng3)));
    t139 = (t0 + 2360);
    xsi_vlogvar_wait_assign_value(t139, t138, 0, 0, 1, 0LL);
    xsi_set_current_line(43, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 2520);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 10, 0LL);
    goto LAB73;

LAB75:    *((unsigned int *)t14) = 1;
    goto LAB78;

LAB77:    t15 = (t14 + 4);
    *((unsigned int *)t14) = 1;
    *((unsigned int *)t15) = 1;
    goto LAB78;

LAB79:    t20 = (t0 + 1800U);
    t21 = *((char **)t20);
    memset(t22, 0, 8);
    t20 = (t22 + 4);
    t23 = (t21 + 4);
    t24 = *((unsigned int *)t21);
    t25 = (t24 >> 2);
    t26 = (t25 & 1);
    *((unsigned int *)t22) = t26;
    t27 = *((unsigned int *)t23);
    t28 = (t27 >> 2);
    t29 = (t28 & 1);
    *((unsigned int *)t20) = t29;
    memset(t30, 0, 8);
    t31 = (t22 + 4);
    t32 = *((unsigned int *)t31);
    t33 = (~(t32));
    t34 = *((unsigned int *)t22);
    t35 = (t34 & t33);
    t36 = (t35 & 1U);
    if (t36 != 0)
        goto LAB82;

LAB83:    if (*((unsigned int *)t31) != 0)
        goto LAB84;

LAB85:    t39 = *((unsigned int *)t14);
    t40 = *((unsigned int *)t30);
    t41 = (t39 & t40);
    *((unsigned int *)t38) = t41;
    t42 = (t14 + 4);
    t43 = (t30 + 4);
    t44 = (t38 + 4);
    t45 = *((unsigned int *)t42);
    t46 = *((unsigned int *)t43);
    t47 = (t45 | t46);
    *((unsigned int *)t44) = t47;
    t48 = *((unsigned int *)t44);
    t49 = (t48 != 0);
    if (t49 == 1)
        goto LAB86;

LAB87:
LAB88:    goto LAB81;

LAB82:    *((unsigned int *)t30) = 1;
    goto LAB85;

LAB84:    t37 = (t30 + 4);
    *((unsigned int *)t30) = 1;
    *((unsigned int *)t37) = 1;
    goto LAB85;

LAB86:    t50 = *((unsigned int *)t38);
    t51 = *((unsigned int *)t44);
    *((unsigned int *)t38) = (t50 | t51);
    t52 = (t14 + 4);
    t53 = (t30 + 4);
    t54 = *((unsigned int *)t14);
    t55 = (~(t54));
    t56 = *((unsigned int *)t52);
    t57 = (~(t56));
    t58 = *((unsigned int *)t30);
    t59 = (~(t58));
    t60 = *((unsigned int *)t53);
    t61 = (~(t60));
    t62 = (t55 & t57);
    t63 = (t59 & t61);
    t64 = (~(t62));
    t65 = (~(t63));
    t66 = *((unsigned int *)t44);
    *((unsigned int *)t44) = (t66 & t64);
    t67 = *((unsigned int *)t44);
    *((unsigned int *)t44) = (t67 & t65);
    t68 = *((unsigned int *)t38);
    *((unsigned int *)t38) = (t68 & t64);
    t69 = *((unsigned int *)t38);
    *((unsigned int *)t38) = (t69 & t65);
    goto LAB88;

LAB89:    *((unsigned int *)t70) = 1;
    goto LAB92;

LAB91:    t77 = (t70 + 4);
    *((unsigned int *)t70) = 1;
    *((unsigned int *)t77) = 1;
    goto LAB92;

LAB93:    t82 = (t0 + 1640U);
    t83 = *((char **)t82);
    memset(t84, 0, 8);
    t82 = (t84 + 4);
    t85 = (t83 + 4);
    t86 = *((unsigned int *)t83);
    t87 = (t86 >> 2);
    t88 = (t87 & 1);
    *((unsigned int *)t84) = t88;
    t89 = *((unsigned int *)t85);
    t90 = (t89 >> 2);
    t91 = (t90 & 1);
    *((unsigned int *)t82) = t91;
    memset(t92, 0, 8);
    t93 = (t84 + 4);
    t94 = *((unsigned int *)t93);
    t95 = (~(t94));
    t96 = *((unsigned int *)t84);
    t97 = (t96 & t95);
    t98 = (t97 & 1U);
    if (t98 != 0)
        goto LAB96;

LAB97:    if (*((unsigned int *)t93) != 0)
        goto LAB98;

LAB99:    t101 = *((unsigned int *)t70);
    t102 = *((unsigned int *)t92);
    t103 = (t101 & t102);
    *((unsigned int *)t100) = t103;
    t104 = (t70 + 4);
    t105 = (t92 + 4);
    t106 = (t100 + 4);
    t107 = *((unsigned int *)t104);
    t108 = *((unsigned int *)t105);
    t109 = (t107 | t108);
    *((unsigned int *)t106) = t109;
    t110 = *((unsigned int *)t106);
    t111 = (t110 != 0);
    if (t111 == 1)
        goto LAB100;

LAB101:
LAB102:    goto LAB95;

LAB96:    *((unsigned int *)t92) = 1;
    goto LAB99;

LAB98:    t99 = (t92 + 4);
    *((unsigned int *)t92) = 1;
    *((unsigned int *)t99) = 1;
    goto LAB99;

LAB100:    t112 = *((unsigned int *)t100);
    t113 = *((unsigned int *)t106);
    *((unsigned int *)t100) = (t112 | t113);
    t114 = (t70 + 4);
    t115 = (t92 + 4);
    t116 = *((unsigned int *)t70);
    t117 = (~(t116));
    t118 = *((unsigned int *)t114);
    t119 = (~(t118));
    t120 = *((unsigned int *)t92);
    t121 = (~(t120));
    t122 = *((unsigned int *)t115);
    t123 = (~(t122));
    t124 = (t117 & t119);
    t125 = (t121 & t123);
    t126 = (~(t124));
    t127 = (~(t125));
    t128 = *((unsigned int *)t106);
    *((unsigned int *)t106) = (t128 & t126);
    t129 = *((unsigned int *)t106);
    *((unsigned int *)t106) = (t129 & t127);
    t130 = *((unsigned int *)t100);
    *((unsigned int *)t100) = (t130 & t126);
    t131 = *((unsigned int *)t100);
    *((unsigned int *)t100) = (t131 & t127);
    goto LAB102;

LAB103:    xsi_set_current_line(44, ng0);

LAB106:    xsi_set_current_line(45, ng0);
    t138 = ((char*)((ng3)));
    t139 = (t0 + 2360);
    xsi_vlogvar_wait_assign_value(t139, t138, 0, 0, 1, 0LL);
    xsi_set_current_line(46, ng0);
    t2 = ((char*)((ng6)));
    t3 = (t0 + 2520);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 10, 0LL);
    goto LAB105;

}


extern void work_m_09629505680486892684_2373178884_init()
{
	static char *pe[] = {(void *)Always_15_0};
	xsi_register_didat("work_m_09629505680486892684_2373178884", "isim/cpu_test_isim_beh.exe.sim/work/m_09629505680486892684_2373178884.didat");
	xsi_register_executes(pe);
}
