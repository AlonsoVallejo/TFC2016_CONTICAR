[1mdiff --git a/FLASH/Sources/app/LineScanCamera.o b/FLASH/Sources/app/LineScanCamera.o[m
[1mindex 2551bac..3fdbe75 100644[m
Binary files a/FLASH/Sources/app/LineScanCamera.o and b/FLASH/Sources/app/LineScanCamera.o differ
[1mdiff --git a/FLASH/Sources/app/ServoMotor.o b/FLASH/Sources/app/ServoMotor.o[m
[1mindex edec5e7..4b22760 100644[m
Binary files a/FLASH/Sources/app/ServoMotor.o and b/FLASH/Sources/app/ServoMotor.o differ
[1mdiff --git a/FLASH/Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.o b/FLASH/Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.o[m
[1mindex 7892233..5752367 100644[m
Binary files a/FLASH/Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.o and b/FLASH/Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.o differ
[1mdiff --git a/FLASH/Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.o b/FLASH/Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.o[m
[1mindex 7ba9460..5ce3c83 100644[m
Binary files a/FLASH/Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.o and b/FLASH/Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.o differ
[1mdiff --git a/FLASH/TFC2016_CONTICAR.elf b/FLASH/TFC2016_CONTICAR.elf[m
[1mindex b81ade2..426750f 100644[m
Binary files a/FLASH/TFC2016_CONTICAR.elf and b/FLASH/TFC2016_CONTICAR.elf differ
[1mdiff --git a/FLASH/TFC2016_CONTICAR.map b/FLASH/TFC2016_CONTICAR.map[m
[1mindex 48bee21..ffee317 100644[m
[1m--- a/FLASH/TFC2016_CONTICAR.map[m
[1m+++ b/FLASH/TFC2016_CONTICAR.map[m
[36m@@ -65,9 +65,19 @@[m [mAllocating common symbols[m
 Common symbol       size              file[m
 [m
 temp                0x1               ./Sources/app/LineScanCamera.o[m
[32m+[m[32mubyStoreMinValReadAdcAout[m
[32m+[m[32m                    0x1               ./Sources/app/LineScanCamera.o[m
 tempservo           0x1               ./Sources/app/ServoMotor.o[m
[31m-linescancamera      0x106             ./Sources/app/LineScanCamera.o[m
[32m+[m[32msbyError            0x1               ./Sources/app/LineScanCamera.o[m
[32m+[m[32msbyErrorPrev        0x1               ./Sources/app/LineScanCamera.o[m
[32m+[m[32msbyGetPromedyDerSignal[m
[32m+[m[32m                    0x1               ./Sources/app/LineScanCamera.o[m
[32m+[m[32mlinescancamera      0x104             ./Sources/app/LineScanCamera.o[m
[32m+[m[32mubyStoreMaxValReadAdcAout[m
[32m+[m[32m                    0x1               ./Sources/app/LineScanCamera.o[m
 rt_curOpMode        0x2               ./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core.o[m
[32m+[m[32mubyLineLocationPoint[m
[32m+[m[32m                    0x1               ./Sources/app/LineScanCamera.o[m
 [m
 Discarded input sections[m
 [m
[36m@@ -85,9 +95,27 @@[m [mDiscarded input sections[m
  .text          0x00000000        0x0 ./Sources/app/ServoMotor.o[m
  .data          0x00000000        0x0 ./Sources/app/ServoMotor.o[m
  .bss           0x00000000        0x0 ./Sources/app/ServoMotor.o[m
[32m+[m[32m .debug_info    0x00000000       0x8c ./Sources/app/ServoMotor.o[m
[32m+[m[32m .debug_abbrev  0x00000000       0x46 ./Sources/app/ServoMotor.o[m
[32m+[m[32m .debug_aranges[m
[32m+[m[32m                0x00000000       0x18 ./Sources/app/ServoMotor.o[m
[32m+[m[32m .debug_macinfo[m
[32m+[m[32m                0x00000000    0x269b4 ./Sources/app/ServoMotor.o[m
[32m+[m[32m .debug_line    0x00000000      0x2da ./Sources/app/ServoMotor.o[m
[32m+[m[32m .debug_str     0x00000000      0x146 ./Sources/app/ServoMotor.o[m
[32m+[m[32m .comment       0x00000000       0x7a ./Sources/app/ServoMotor.o[m
[32m+[m[32m .ARM.attributes[m
[32m+[m[32m                0x00000000       0x31 ./Sources/app/ServoMotor.o[m
[32m+[m[32m COMMON         0x00000000        0x1 ./Sources/app/ServoMotor.o[m
  .text          0x00000000        0x0 ./Sources/app/LineScanCamera.o[m
  .data          0x00000000        0x0 ./Sources/app/LineScanCamera.o[m
  .bss           0x00000000        0x0 ./Sources/app/LineScanCamera.o[m
[32m+[m[32m .text.vfn_LineScanCameraProcessing[m
[32m+[m[32m                0x00000000       0x84 ./Sources/app/LineScanCamera.o[m
[32m+[m[32m .text.vfn_GetDerivateSingal_lscAout[m
[32m+[m[32m                0x00000000       0x7c ./Sources/app/LineScanCamera.o[m
[32m+[m[32m .text.s8_GetLineLocationValue_DerivateSiganl[m
[32m+[m[32m                0x00000000       0xd0 ./Sources/app/LineScanCamera.o[m
  .text          0x00000000        0x0 ./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.o[m
  .data          0x00000000        0x0 ./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.o[m
  .bss           0x00000000        0x0 ./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.o[m
[36m@@ -172,6 +200,8 @@[m [mDiscarded input sections[m
  .bss           0x00000000        0x0 ./Sources/mcl/TPM.o[m
  .text.vfn_Init_DCmotors[m
                 0x00000000       0xfc ./Sources/mcl/TPM.o[m
[32m+[m[32m .text.vfn_SetPosition_SteeringServo[m
[32m+[m[32m                0x00000000       0x60 ./Sources/mcl/TPM.o[m
  .text.vfn_Set_RightMotors_PWM[m
                 0x00000000       0x2c ./Sources/mcl/TPM.o[m
  .text.vfn_Set_LeftMotors_PWM[m
[36m@@ -378,8 +408,8 @@[m [mLOAD ./Sources/mcl/ARM_SysTick.o[m
 LOAD ./Sources/mcl/ADC.o[m
 LOAD ./Sources/sa_mtb.o[m
 LOAD ./Sources/main.o[m
[31m-                0x00002da0                __pformatter = __pformatter_[m
[31m-                [0x000031c8]                __sformatter = __sformatter[m
[32m+[m[32m                0x00002d28                __pformatter = __pformatter_[m
[32m+[m[32m                [0x00003150]                __sformatter = __sformatter[m
 START GROUP[m
 LOAD C:/Freescale/CW MCU v10.6/MCU/ARM_GCC_Support/ewl/lib/armv6-m\libc.a[m
 LOAD C:/Freescale/CW MCU v10.6/MCU/ARM_GCC_Support/ewl/lib/armv6-m\libm.a[m
[36m@@ -405,7 +435,7 @@[m [mEND GROUP[m
  *(.cfmconfig)[m
                 0x00000400                . = ALIGN (0x4)[m
 [m
[31m-.text           0x00000800     0x3668[m
[32m+[m[32m.text           0x00000800     0x35f0[m
                 0x00000800                . = ALIGN (0x4)[m
  *(.text)[m
  .text          0x00000800       0x14 c:/freescale/cw mcu v10.6/cross_tools/arm-none-eabi-gcc-4_7_3/bin/../lib/gcc/arm-none-eabi/4.7.3/armv6-m\libgcc.a(_thumb1_case_sqi.o)[m
[36m@@ -505,145 +535,140 @@[m [mEND GROUP[m
  .text._ExitProcess[m
                 0x00001fa8        0xc ./Project_Settings/Startup_Code/__arm_end.o[m
                 0x00001fa8                _ExitProcess[m
[31m- .text.vfn_TestServo[m
[31m-                0x00001fb4       0x18 ./Sources/app/ServoMotor.o[m
[31m-                0x00001fb4                vfn_TestServo[m
  .text.vfn_StateMachine_LSC_InSignals[m
[31m-                0x00001fcc      0x150 ./Sources/app/LineScanCamera.o[m
[31m-                0x00001fcc                vfn_StateMachine_LSC_InSignals[m
[32m+[m[32m                0x00001fb4      0x154 ./Sources/app/LineScanCamera.o[m
[32m+[m[32m                0x00001fb4                vfn_StateMachine_LSC_InSignals[m
  .text.vfn_ReadAout_LineScanCamera[m
[31m-                0x0000211c       0x38 ./Sources/app/LineScanCamera.o[m
[31m-                0x0000211c                vfn_ReadAout_LineScanCamera[m
[32m+[m[32m                0x00002108       0x34 ./Sources/app/LineScanCamera.o[m
[32m+[m[32m                0x00002108                vfn_ReadAout_LineScanCamera[m
  .text.gsc_sch_core_tick_isr[m
[31m-                0x00002154       0x14 ./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.o[m
[31m-                0x00002154                gsc_sch_core_tick_isr[m
[32m+[m[32m                0x0000213c       0x14 ./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.o[m
[32m+[m[32m                0x0000213c                gsc_sch_core_tick_isr[m
  .text.gsc_sch_core_Init[m
[31m-                0x00002168       0x60 ./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core.o[m
[31m-                0x00002168                gsc_sch_core_Init[m
[32m+[m[32m            