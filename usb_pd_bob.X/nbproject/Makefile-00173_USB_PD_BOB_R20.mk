#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-00173_USB_PD_BOB_R20.mk)" "nbproject/Makefile-local-00173_USB_PD_BOB_R20.mk"
include nbproject/Makefile-local-00173_USB_PD_BOB_R20.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=00173_USB_PD_BOB_R20
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/usb_pd_bob.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/usb_pd_bob.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/_root/generic/fdrv_FaultHandler.c ../src/_root/generic/task_manager.c ../src/_root/generic/fdrv_TrapHandler.c ../src/_root/generic/task_scheduler.c ../src/apl/config/tasks.c ../src/apl/config/UserStartupCode.c ../src/apl/config/application.c ../src/apl/resources/pd_timer/upd_timer.c ../src/apl/resources/spi2/spi2.c ../src/apl/resources/zeus_stack/pd/cfg_globals.c ../src/apl/resources/zeus_stack/pd/debug.c ../src/apl/resources/zeus_stack/pd/generic_timer.c ../src/apl/resources/zeus_stack/pd/int_globals.c ../src/apl/resources/zeus_stack/pd/pd_main.c ../src/apl/resources/zeus_stack/pd/policy_engine.c ../src/apl/resources/zeus_stack/pd/policy_engine_fwup.c ../src/apl/resources/zeus_stack/pd/policy_engine_snk.c ../src/apl/resources/zeus_stack/pd/policy_engine_src.c ../src/apl/resources/zeus_stack/pd/policy_manager.c ../src/apl/resources/zeus_stack/pd/protocol_layer.c ../src/apl/resources/zeus_stack/pd/typeC_control.c ../src/apl/resources/zeus_stack/pd/upd_hw.c ../src/apl/resources/zeus_stack/pd/upd_interrupts.c ../src/apl/resources/zeus_stack/hook_functions.c ../src/apl/resources/zeus_stack/thermal_power_management.c ../src/apl/tasks/task_FaultHandler.c ../src/apl/tasks/task_Idle.c ../src/apl/tasks/task_SystemStatus.c ../src/apl/tasks/task_PDStack.c ../src/apl/apl.c ../src/hal/initialization/init_fosc.c ../src/hal/initialization/init_gpio.c ../src/hal/initialization/init_timer.c ../src/hal/initialization/init_irq.c ../src/hal/initialization/init_dsp.c ../src/hal/hal.c ../src/mcal/config/config_bits_P33CH.c ../src/mcal/config/config_bits_P33CK.c ../src/mcal/mcal.c ../src/sfl/isr/isr_timer.c ../src/sfl/sfl.c ../src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o ${OBJECTDIR}/_ext/949971983/task_manager.o ${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o ${OBJECTDIR}/_ext/949971983/task_scheduler.o ${OBJECTDIR}/_ext/687227054/tasks.o ${OBJECTDIR}/_ext/687227054/UserStartupCode.o ${OBJECTDIR}/_ext/687227054/application.o ${OBJECTDIR}/_ext/2109991248/upd_timer.o ${OBJECTDIR}/_ext/1494078692/spi2.o ${OBJECTDIR}/_ext/1666088709/cfg_globals.o ${OBJECTDIR}/_ext/1666088709/debug.o ${OBJECTDIR}/_ext/1666088709/generic_timer.o ${OBJECTDIR}/_ext/1666088709/int_globals.o ${OBJECTDIR}/_ext/1666088709/pd_main.o ${OBJECTDIR}/_ext/1666088709/policy_engine.o ${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o ${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o ${OBJECTDIR}/_ext/1666088709/policy_engine_src.o ${OBJECTDIR}/_ext/1666088709/policy_manager.o ${OBJECTDIR}/_ext/1666088709/protocol_layer.o ${OBJECTDIR}/_ext/1666088709/typeC_control.o ${OBJECTDIR}/_ext/1666088709/upd_hw.o ${OBJECTDIR}/_ext/1666088709/upd_interrupts.o ${OBJECTDIR}/_ext/481295256/hook_functions.o ${OBJECTDIR}/_ext/481295256/thermal_power_management.o ${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o ${OBJECTDIR}/_ext/1838571682/task_Idle.o ${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o ${OBJECTDIR}/_ext/1838571682/task_PDStack.o ${OBJECTDIR}/_ext/659850787/apl.o ${OBJECTDIR}/_ext/1752484138/init_fosc.o ${OBJECTDIR}/_ext/1752484138/init_gpio.o ${OBJECTDIR}/_ext/1752484138/init_timer.o ${OBJECTDIR}/_ext/1752484138/init_irq.o ${OBJECTDIR}/_ext/1752484138/init_dsp.o ${OBJECTDIR}/_ext/659857049/hal.o ${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o ${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o ${OBJECTDIR}/_ext/1019117317/mcal.o ${OBJECTDIR}/_ext/1724212984/isr_timer.o ${OBJECTDIR}/_ext/659867775/sfl.o ${OBJECTDIR}/_ext/1360937237/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o.d ${OBJECTDIR}/_ext/949971983/task_manager.o.d ${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o.d ${OBJECTDIR}/_ext/949971983/task_scheduler.o.d ${OBJECTDIR}/_ext/687227054/tasks.o.d ${OBJECTDIR}/_ext/687227054/UserStartupCode.o.d ${OBJECTDIR}/_ext/687227054/application.o.d ${OBJECTDIR}/_ext/2109991248/upd_timer.o.d ${OBJECTDIR}/_ext/1494078692/spi2.o.d ${OBJECTDIR}/_ext/1666088709/cfg_globals.o.d ${OBJECTDIR}/_ext/1666088709/debug.o.d ${OBJECTDIR}/_ext/1666088709/generic_timer.o.d ${OBJECTDIR}/_ext/1666088709/int_globals.o.d ${OBJECTDIR}/_ext/1666088709/pd_main.o.d ${OBJECTDIR}/_ext/1666088709/policy_engine.o.d ${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o.d ${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o.d ${OBJECTDIR}/_ext/1666088709/policy_engine_src.o.d ${OBJECTDIR}/_ext/1666088709/policy_manager.o.d ${OBJECTDIR}/_ext/1666088709/protocol_layer.o.d ${OBJECTDIR}/_ext/1666088709/typeC_control.o.d ${OBJECTDIR}/_ext/1666088709/upd_hw.o.d ${OBJECTDIR}/_ext/1666088709/upd_interrupts.o.d ${OBJECTDIR}/_ext/481295256/hook_functions.o.d ${OBJECTDIR}/_ext/481295256/thermal_power_management.o.d ${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o.d ${OBJECTDIR}/_ext/1838571682/task_Idle.o.d ${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o.d ${OBJECTDIR}/_ext/1838571682/task_PDStack.o.d ${OBJECTDIR}/_ext/659850787/apl.o.d ${OBJECTDIR}/_ext/1752484138/init_fosc.o.d ${OBJECTDIR}/_ext/1752484138/init_gpio.o.d ${OBJECTDIR}/_ext/1752484138/init_timer.o.d ${OBJECTDIR}/_ext/1752484138/init_irq.o.d ${OBJECTDIR}/_ext/1752484138/init_dsp.o.d ${OBJECTDIR}/_ext/659857049/hal.o.d ${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o.d ${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o.d ${OBJECTDIR}/_ext/1019117317/mcal.o.d ${OBJECTDIR}/_ext/1724212984/isr_timer.o.d ${OBJECTDIR}/_ext/659867775/sfl.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o ${OBJECTDIR}/_ext/949971983/task_manager.o ${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o ${OBJECTDIR}/_ext/949971983/task_scheduler.o ${OBJECTDIR}/_ext/687227054/tasks.o ${OBJECTDIR}/_ext/687227054/UserStartupCode.o ${OBJECTDIR}/_ext/687227054/application.o ${OBJECTDIR}/_ext/2109991248/upd_timer.o ${OBJECTDIR}/_ext/1494078692/spi2.o ${OBJECTDIR}/_ext/1666088709/cfg_globals.o ${OBJECTDIR}/_ext/1666088709/debug.o ${OBJECTDIR}/_ext/1666088709/generic_timer.o ${OBJECTDIR}/_ext/1666088709/int_globals.o ${OBJECTDIR}/_ext/1666088709/pd_main.o ${OBJECTDIR}/_ext/1666088709/policy_engine.o ${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o ${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o ${OBJECTDIR}/_ext/1666088709/policy_engine_src.o ${OBJECTDIR}/_ext/1666088709/policy_manager.o ${OBJECTDIR}/_ext/1666088709/protocol_layer.o ${OBJECTDIR}/_ext/1666088709/typeC_control.o ${OBJECTDIR}/_ext/1666088709/upd_hw.o ${OBJECTDIR}/_ext/1666088709/upd_interrupts.o ${OBJECTDIR}/_ext/481295256/hook_functions.o ${OBJECTDIR}/_ext/481295256/thermal_power_management.o ${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o ${OBJECTDIR}/_ext/1838571682/task_Idle.o ${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o ${OBJECTDIR}/_ext/1838571682/task_PDStack.o ${OBJECTDIR}/_ext/659850787/apl.o ${OBJECTDIR}/_ext/1752484138/init_fosc.o ${OBJECTDIR}/_ext/1752484138/init_gpio.o ${OBJECTDIR}/_ext/1752484138/init_timer.o ${OBJECTDIR}/_ext/1752484138/init_irq.o ${OBJECTDIR}/_ext/1752484138/init_dsp.o ${OBJECTDIR}/_ext/659857049/hal.o ${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o ${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o ${OBJECTDIR}/_ext/1019117317/mcal.o ${OBJECTDIR}/_ext/1724212984/isr_timer.o ${OBJECTDIR}/_ext/659867775/sfl.o ${OBJECTDIR}/_ext/1360937237/main.o

# Source Files
SOURCEFILES=../src/_root/generic/fdrv_FaultHandler.c ../src/_root/generic/task_manager.c ../src/_root/generic/fdrv_TrapHandler.c ../src/_root/generic/task_scheduler.c ../src/apl/config/tasks.c ../src/apl/config/UserStartupCode.c ../src/apl/config/application.c ../src/apl/resources/pd_timer/upd_timer.c ../src/apl/resources/spi2/spi2.c ../src/apl/resources/zeus_stack/pd/cfg_globals.c ../src/apl/resources/zeus_stack/pd/debug.c ../src/apl/resources/zeus_stack/pd/generic_timer.c ../src/apl/resources/zeus_stack/pd/int_globals.c ../src/apl/resources/zeus_stack/pd/pd_main.c ../src/apl/resources/zeus_stack/pd/policy_engine.c ../src/apl/resources/zeus_stack/pd/policy_engine_fwup.c ../src/apl/resources/zeus_stack/pd/policy_engine_snk.c ../src/apl/resources/zeus_stack/pd/policy_engine_src.c ../src/apl/resources/zeus_stack/pd/policy_manager.c ../src/apl/resources/zeus_stack/pd/protocol_layer.c ../src/apl/resources/zeus_stack/pd/typeC_control.c ../src/apl/resources/zeus_stack/pd/upd_hw.c ../src/apl/resources/zeus_stack/pd/upd_interrupts.c ../src/apl/resources/zeus_stack/hook_functions.c ../src/apl/resources/zeus_stack/thermal_power_management.c ../src/apl/tasks/task_FaultHandler.c ../src/apl/tasks/task_Idle.c ../src/apl/tasks/task_SystemStatus.c ../src/apl/tasks/task_PDStack.c ../src/apl/apl.c ../src/hal/initialization/init_fosc.c ../src/hal/initialization/init_gpio.c ../src/hal/initialization/init_timer.c ../src/hal/initialization/init_irq.c ../src/hal/initialization/init_dsp.c ../src/hal/hal.c ../src/mcal/config/config_bits_P33CH.c ../src/mcal/config/config_bits_P33CK.c ../src/mcal/mcal.c ../src/sfl/isr/isr_timer.c ../src/sfl/sfl.c ../src/main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-00173_USB_PD_BOB_R20.mk dist/${CND_CONF}/${IMAGE_TYPE}/usb_pd_bob.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33CK64MP505
MP_LINKER_FILE_OPTION=,--script=p33CK64MP505.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o: ../src/_root/generic/fdrv_FaultHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/949971983" 
	@${RM} ${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/_root/generic/fdrv_FaultHandler.c  -o ${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/949971983/task_manager.o: ../src/_root/generic/task_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/949971983" 
	@${RM} ${OBJECTDIR}/_ext/949971983/task_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/949971983/task_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/_root/generic/task_manager.c  -o ${OBJECTDIR}/_ext/949971983/task_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/949971983/task_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/949971983/task_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o: ../src/_root/generic/fdrv_TrapHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/949971983" 
	@${RM} ${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/_root/generic/fdrv_TrapHandler.c  -o ${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/949971983/task_scheduler.o: ../src/_root/generic/task_scheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/949971983" 
	@${RM} ${OBJECTDIR}/_ext/949971983/task_scheduler.o.d 
	@${RM} ${OBJECTDIR}/_ext/949971983/task_scheduler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/_root/generic/task_scheduler.c  -o ${OBJECTDIR}/_ext/949971983/task_scheduler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/949971983/task_scheduler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/949971983/task_scheduler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/687227054/tasks.o: ../src/apl/config/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/687227054" 
	@${RM} ${OBJECTDIR}/_ext/687227054/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/687227054/tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/config/tasks.c  -o ${OBJECTDIR}/_ext/687227054/tasks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/687227054/tasks.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/687227054/tasks.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/687227054/UserStartupCode.o: ../src/apl/config/UserStartupCode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/687227054" 
	@${RM} ${OBJECTDIR}/_ext/687227054/UserStartupCode.o.d 
	@${RM} ${OBJECTDIR}/_ext/687227054/UserStartupCode.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/config/UserStartupCode.c  -o ${OBJECTDIR}/_ext/687227054/UserStartupCode.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/687227054/UserStartupCode.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/687227054/UserStartupCode.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/687227054/application.o: ../src/apl/config/application.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/687227054" 
	@${RM} ${OBJECTDIR}/_ext/687227054/application.o.d 
	@${RM} ${OBJECTDIR}/_ext/687227054/application.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/config/application.c  -o ${OBJECTDIR}/_ext/687227054/application.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/687227054/application.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/687227054/application.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2109991248/upd_timer.o: ../src/apl/resources/pd_timer/upd_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2109991248" 
	@${RM} ${OBJECTDIR}/_ext/2109991248/upd_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/2109991248/upd_timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/pd_timer/upd_timer.c  -o ${OBJECTDIR}/_ext/2109991248/upd_timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2109991248/upd_timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/2109991248/upd_timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1494078692/spi2.o: ../src/apl/resources/spi2/spi2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1494078692" 
	@${RM} ${OBJECTDIR}/_ext/1494078692/spi2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494078692/spi2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/spi2/spi2.c  -o ${OBJECTDIR}/_ext/1494078692/spi2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1494078692/spi2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494078692/spi2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/cfg_globals.o: ../src/apl/resources/zeus_stack/pd/cfg_globals.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/cfg_globals.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/cfg_globals.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/cfg_globals.c  -o ${OBJECTDIR}/_ext/1666088709/cfg_globals.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/cfg_globals.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/cfg_globals.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/debug.o: ../src/apl/resources/zeus_stack/pd/debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/debug.c  -o ${OBJECTDIR}/_ext/1666088709/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/debug.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/generic_timer.o: ../src/apl/resources/zeus_stack/pd/generic_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/generic_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/generic_timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/generic_timer.c  -o ${OBJECTDIR}/_ext/1666088709/generic_timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/generic_timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/generic_timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/int_globals.o: ../src/apl/resources/zeus_stack/pd/int_globals.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/int_globals.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/int_globals.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/int_globals.c  -o ${OBJECTDIR}/_ext/1666088709/int_globals.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/int_globals.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/int_globals.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/pd_main.o: ../src/apl/resources/zeus_stack/pd/pd_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/pd_main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/pd_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/pd_main.c  -o ${OBJECTDIR}/_ext/1666088709/pd_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/pd_main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/pd_main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/policy_engine.o: ../src/apl/resources/zeus_stack/pd/policy_engine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/policy_engine.c  -o ${OBJECTDIR}/_ext/1666088709/policy_engine.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/policy_engine.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/policy_engine.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o: ../src/apl/resources/zeus_stack/pd/policy_engine_fwup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/policy_engine_fwup.c  -o ${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o: ../src/apl/resources/zeus_stack/pd/policy_engine_snk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/policy_engine_snk.c  -o ${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/policy_engine_src.o: ../src/apl/resources/zeus_stack/pd/policy_engine_src.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine_src.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine_src.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/policy_engine_src.c  -o ${OBJECTDIR}/_ext/1666088709/policy_engine_src.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/policy_engine_src.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/policy_engine_src.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/policy_manager.o: ../src/apl/resources/zeus_stack/pd/policy_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/policy_manager.c  -o ${OBJECTDIR}/_ext/1666088709/policy_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/policy_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/policy_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/protocol_layer.o: ../src/apl/resources/zeus_stack/pd/protocol_layer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/protocol_layer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/protocol_layer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/protocol_layer.c  -o ${OBJECTDIR}/_ext/1666088709/protocol_layer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/protocol_layer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/protocol_layer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/typeC_control.o: ../src/apl/resources/zeus_stack/pd/typeC_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/typeC_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/typeC_control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/typeC_control.c  -o ${OBJECTDIR}/_ext/1666088709/typeC_control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/typeC_control.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/typeC_control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/upd_hw.o: ../src/apl/resources/zeus_stack/pd/upd_hw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/upd_hw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/upd_hw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/upd_hw.c  -o ${OBJECTDIR}/_ext/1666088709/upd_hw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/upd_hw.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/upd_hw.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/upd_interrupts.o: ../src/apl/resources/zeus_stack/pd/upd_interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/upd_interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/upd_interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/upd_interrupts.c  -o ${OBJECTDIR}/_ext/1666088709/upd_interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/upd_interrupts.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/upd_interrupts.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/481295256/hook_functions.o: ../src/apl/resources/zeus_stack/hook_functions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/481295256" 
	@${RM} ${OBJECTDIR}/_ext/481295256/hook_functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/481295256/hook_functions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/hook_functions.c  -o ${OBJECTDIR}/_ext/481295256/hook_functions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/481295256/hook_functions.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/481295256/hook_functions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/481295256/thermal_power_management.o: ../src/apl/resources/zeus_stack/thermal_power_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/481295256" 
	@${RM} ${OBJECTDIR}/_ext/481295256/thermal_power_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/481295256/thermal_power_management.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/thermal_power_management.c  -o ${OBJECTDIR}/_ext/481295256/thermal_power_management.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/481295256/thermal_power_management.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/481295256/thermal_power_management.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o: ../src/apl/tasks/task_FaultHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1838571682" 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/tasks/task_FaultHandler.c  -o ${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1838571682/task_Idle.o: ../src/apl/tasks/task_Idle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1838571682" 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_Idle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_Idle.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/tasks/task_Idle.c  -o ${OBJECTDIR}/_ext/1838571682/task_Idle.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1838571682/task_Idle.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1838571682/task_Idle.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o: ../src/apl/tasks/task_SystemStatus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1838571682" 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o.d 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/tasks/task_SystemStatus.c  -o ${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1838571682/task_PDStack.o: ../src/apl/tasks/task_PDStack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1838571682" 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_PDStack.o.d 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_PDStack.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/tasks/task_PDStack.c  -o ${OBJECTDIR}/_ext/1838571682/task_PDStack.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1838571682/task_PDStack.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1838571682/task_PDStack.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659850787/apl.o: ../src/apl/apl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659850787" 
	@${RM} ${OBJECTDIR}/_ext/659850787/apl.o.d 
	@${RM} ${OBJECTDIR}/_ext/659850787/apl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/apl.c  -o ${OBJECTDIR}/_ext/659850787/apl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/659850787/apl.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/659850787/apl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1752484138/init_fosc.o: ../src/hal/initialization/init_fosc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1752484138" 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_fosc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_fosc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/hal/initialization/init_fosc.c  -o ${OBJECTDIR}/_ext/1752484138/init_fosc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1752484138/init_fosc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1752484138/init_fosc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1752484138/init_gpio.o: ../src/hal/initialization/init_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1752484138" 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_gpio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/hal/initialization/init_gpio.c  -o ${OBJECTDIR}/_ext/1752484138/init_gpio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1752484138/init_gpio.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1752484138/init_gpio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1752484138/init_timer.o: ../src/hal/initialization/init_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1752484138" 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/hal/initialization/init_timer.c  -o ${OBJECTDIR}/_ext/1752484138/init_timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1752484138/init_timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1752484138/init_timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1752484138/init_irq.o: ../src/hal/initialization/init_irq.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1752484138" 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_irq.o.d 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_irq.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/hal/initialization/init_irq.c  -o ${OBJECTDIR}/_ext/1752484138/init_irq.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1752484138/init_irq.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1752484138/init_irq.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1752484138/init_dsp.o: ../src/hal/initialization/init_dsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1752484138" 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_dsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_dsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/hal/initialization/init_dsp.c  -o ${OBJECTDIR}/_ext/1752484138/init_dsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1752484138/init_dsp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1752484138/init_dsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659857049/hal.o: ../src/hal/hal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659857049" 
	@${RM} ${OBJECTDIR}/_ext/659857049/hal.o.d 
	@${RM} ${OBJECTDIR}/_ext/659857049/hal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/hal/hal.c  -o ${OBJECTDIR}/_ext/659857049/hal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/659857049/hal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/659857049/hal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o: ../src/mcal/config/config_bits_P33CH.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/391766742" 
	@${RM} ${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o.d 
	@${RM} ${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/mcal/config/config_bits_P33CH.c  -o ${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o: ../src/mcal/config/config_bits_P33CK.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/391766742" 
	@${RM} ${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o.d 
	@${RM} ${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/mcal/config/config_bits_P33CK.c  -o ${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1019117317/mcal.o: ../src/mcal/mcal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1019117317" 
	@${RM} ${OBJECTDIR}/_ext/1019117317/mcal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019117317/mcal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/mcal/mcal.c  -o ${OBJECTDIR}/_ext/1019117317/mcal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1019117317/mcal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1019117317/mcal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1724212984/isr_timer.o: ../src/sfl/isr/isr_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1724212984" 
	@${RM} ${OBJECTDIR}/_ext/1724212984/isr_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1724212984/isr_timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/sfl/isr/isr_timer.c  -o ${OBJECTDIR}/_ext/1724212984/isr_timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1724212984/isr_timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1724212984/isr_timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659867775/sfl.o: ../src/sfl/sfl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659867775" 
	@${RM} ${OBJECTDIR}/_ext/659867775/sfl.o.d 
	@${RM} ${OBJECTDIR}/_ext/659867775/sfl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/sfl/sfl.c  -o ${OBJECTDIR}/_ext/659867775/sfl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/659867775/sfl.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/659867775/sfl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/main.c  -o ${OBJECTDIR}/_ext/1360937237/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o: ../src/_root/generic/fdrv_FaultHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/949971983" 
	@${RM} ${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/_root/generic/fdrv_FaultHandler.c  -o ${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/949971983/fdrv_FaultHandler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/949971983/task_manager.o: ../src/_root/generic/task_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/949971983" 
	@${RM} ${OBJECTDIR}/_ext/949971983/task_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/949971983/task_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/_root/generic/task_manager.c  -o ${OBJECTDIR}/_ext/949971983/task_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/949971983/task_manager.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/949971983/task_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o: ../src/_root/generic/fdrv_TrapHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/949971983" 
	@${RM} ${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/_root/generic/fdrv_TrapHandler.c  -o ${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/949971983/fdrv_TrapHandler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/949971983/task_scheduler.o: ../src/_root/generic/task_scheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/949971983" 
	@${RM} ${OBJECTDIR}/_ext/949971983/task_scheduler.o.d 
	@${RM} ${OBJECTDIR}/_ext/949971983/task_scheduler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/_root/generic/task_scheduler.c  -o ${OBJECTDIR}/_ext/949971983/task_scheduler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/949971983/task_scheduler.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/949971983/task_scheduler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/687227054/tasks.o: ../src/apl/config/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/687227054" 
	@${RM} ${OBJECTDIR}/_ext/687227054/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/687227054/tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/config/tasks.c  -o ${OBJECTDIR}/_ext/687227054/tasks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/687227054/tasks.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/687227054/tasks.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/687227054/UserStartupCode.o: ../src/apl/config/UserStartupCode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/687227054" 
	@${RM} ${OBJECTDIR}/_ext/687227054/UserStartupCode.o.d 
	@${RM} ${OBJECTDIR}/_ext/687227054/UserStartupCode.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/config/UserStartupCode.c  -o ${OBJECTDIR}/_ext/687227054/UserStartupCode.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/687227054/UserStartupCode.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/687227054/UserStartupCode.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/687227054/application.o: ../src/apl/config/application.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/687227054" 
	@${RM} ${OBJECTDIR}/_ext/687227054/application.o.d 
	@${RM} ${OBJECTDIR}/_ext/687227054/application.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/config/application.c  -o ${OBJECTDIR}/_ext/687227054/application.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/687227054/application.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/687227054/application.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2109991248/upd_timer.o: ../src/apl/resources/pd_timer/upd_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2109991248" 
	@${RM} ${OBJECTDIR}/_ext/2109991248/upd_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/2109991248/upd_timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/pd_timer/upd_timer.c  -o ${OBJECTDIR}/_ext/2109991248/upd_timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2109991248/upd_timer.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/2109991248/upd_timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1494078692/spi2.o: ../src/apl/resources/spi2/spi2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1494078692" 
	@${RM} ${OBJECTDIR}/_ext/1494078692/spi2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494078692/spi2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/spi2/spi2.c  -o ${OBJECTDIR}/_ext/1494078692/spi2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1494078692/spi2.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494078692/spi2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/cfg_globals.o: ../src/apl/resources/zeus_stack/pd/cfg_globals.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/cfg_globals.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/cfg_globals.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/cfg_globals.c  -o ${OBJECTDIR}/_ext/1666088709/cfg_globals.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/cfg_globals.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/cfg_globals.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/debug.o: ../src/apl/resources/zeus_stack/pd/debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/debug.c  -o ${OBJECTDIR}/_ext/1666088709/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/debug.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/generic_timer.o: ../src/apl/resources/zeus_stack/pd/generic_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/generic_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/generic_timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/generic_timer.c  -o ${OBJECTDIR}/_ext/1666088709/generic_timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/generic_timer.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/generic_timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/int_globals.o: ../src/apl/resources/zeus_stack/pd/int_globals.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/int_globals.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/int_globals.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/int_globals.c  -o ${OBJECTDIR}/_ext/1666088709/int_globals.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/int_globals.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/int_globals.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/pd_main.o: ../src/apl/resources/zeus_stack/pd/pd_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/pd_main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/pd_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/pd_main.c  -o ${OBJECTDIR}/_ext/1666088709/pd_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/pd_main.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/pd_main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/policy_engine.o: ../src/apl/resources/zeus_stack/pd/policy_engine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/policy_engine.c  -o ${OBJECTDIR}/_ext/1666088709/policy_engine.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/policy_engine.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/policy_engine.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o: ../src/apl/resources/zeus_stack/pd/policy_engine_fwup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/policy_engine_fwup.c  -o ${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/policy_engine_fwup.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o: ../src/apl/resources/zeus_stack/pd/policy_engine_snk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/policy_engine_snk.c  -o ${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/policy_engine_snk.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/policy_engine_src.o: ../src/apl/resources/zeus_stack/pd/policy_engine_src.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine_src.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_engine_src.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/policy_engine_src.c  -o ${OBJECTDIR}/_ext/1666088709/policy_engine_src.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/policy_engine_src.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/policy_engine_src.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/policy_manager.o: ../src/apl/resources/zeus_stack/pd/policy_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/policy_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/policy_manager.c  -o ${OBJECTDIR}/_ext/1666088709/policy_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/policy_manager.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/policy_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/protocol_layer.o: ../src/apl/resources/zeus_stack/pd/protocol_layer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/protocol_layer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/protocol_layer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/protocol_layer.c  -o ${OBJECTDIR}/_ext/1666088709/protocol_layer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/protocol_layer.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/protocol_layer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/typeC_control.o: ../src/apl/resources/zeus_stack/pd/typeC_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/typeC_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/typeC_control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/typeC_control.c  -o ${OBJECTDIR}/_ext/1666088709/typeC_control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/typeC_control.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/typeC_control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/upd_hw.o: ../src/apl/resources/zeus_stack/pd/upd_hw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/upd_hw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/upd_hw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/upd_hw.c  -o ${OBJECTDIR}/_ext/1666088709/upd_hw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/upd_hw.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/upd_hw.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1666088709/upd_interrupts.o: ../src/apl/resources/zeus_stack/pd/upd_interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1666088709" 
	@${RM} ${OBJECTDIR}/_ext/1666088709/upd_interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1666088709/upd_interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/pd/upd_interrupts.c  -o ${OBJECTDIR}/_ext/1666088709/upd_interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1666088709/upd_interrupts.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1666088709/upd_interrupts.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/481295256/hook_functions.o: ../src/apl/resources/zeus_stack/hook_functions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/481295256" 
	@${RM} ${OBJECTDIR}/_ext/481295256/hook_functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/481295256/hook_functions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/hook_functions.c  -o ${OBJECTDIR}/_ext/481295256/hook_functions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/481295256/hook_functions.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/481295256/hook_functions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/481295256/thermal_power_management.o: ../src/apl/resources/zeus_stack/thermal_power_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/481295256" 
	@${RM} ${OBJECTDIR}/_ext/481295256/thermal_power_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/481295256/thermal_power_management.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/resources/zeus_stack/thermal_power_management.c  -o ${OBJECTDIR}/_ext/481295256/thermal_power_management.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/481295256/thermal_power_management.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/481295256/thermal_power_management.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o: ../src/apl/tasks/task_FaultHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1838571682" 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/tasks/task_FaultHandler.c  -o ${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1838571682/task_FaultHandler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1838571682/task_Idle.o: ../src/apl/tasks/task_Idle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1838571682" 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_Idle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_Idle.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/tasks/task_Idle.c  -o ${OBJECTDIR}/_ext/1838571682/task_Idle.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1838571682/task_Idle.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1838571682/task_Idle.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o: ../src/apl/tasks/task_SystemStatus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1838571682" 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o.d 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/tasks/task_SystemStatus.c  -o ${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1838571682/task_SystemStatus.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1838571682/task_PDStack.o: ../src/apl/tasks/task_PDStack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1838571682" 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_PDStack.o.d 
	@${RM} ${OBJECTDIR}/_ext/1838571682/task_PDStack.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/tasks/task_PDStack.c  -o ${OBJECTDIR}/_ext/1838571682/task_PDStack.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1838571682/task_PDStack.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1838571682/task_PDStack.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659850787/apl.o: ../src/apl/apl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659850787" 
	@${RM} ${OBJECTDIR}/_ext/659850787/apl.o.d 
	@${RM} ${OBJECTDIR}/_ext/659850787/apl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/apl/apl.c  -o ${OBJECTDIR}/_ext/659850787/apl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/659850787/apl.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/659850787/apl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1752484138/init_fosc.o: ../src/hal/initialization/init_fosc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1752484138" 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_fosc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_fosc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/hal/initialization/init_fosc.c  -o ${OBJECTDIR}/_ext/1752484138/init_fosc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1752484138/init_fosc.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1752484138/init_fosc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1752484138/init_gpio.o: ../src/hal/initialization/init_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1752484138" 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_gpio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/hal/initialization/init_gpio.c  -o ${OBJECTDIR}/_ext/1752484138/init_gpio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1752484138/init_gpio.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1752484138/init_gpio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1752484138/init_timer.o: ../src/hal/initialization/init_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1752484138" 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/hal/initialization/init_timer.c  -o ${OBJECTDIR}/_ext/1752484138/init_timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1752484138/init_timer.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1752484138/init_timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1752484138/init_irq.o: ../src/hal/initialization/init_irq.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1752484138" 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_irq.o.d 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_irq.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/hal/initialization/init_irq.c  -o ${OBJECTDIR}/_ext/1752484138/init_irq.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1752484138/init_irq.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1752484138/init_irq.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1752484138/init_dsp.o: ../src/hal/initialization/init_dsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1752484138" 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_dsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1752484138/init_dsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/hal/initialization/init_dsp.c  -o ${OBJECTDIR}/_ext/1752484138/init_dsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1752484138/init_dsp.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1752484138/init_dsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659857049/hal.o: ../src/hal/hal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659857049" 
	@${RM} ${OBJECTDIR}/_ext/659857049/hal.o.d 
	@${RM} ${OBJECTDIR}/_ext/659857049/hal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/hal/hal.c  -o ${OBJECTDIR}/_ext/659857049/hal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/659857049/hal.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/659857049/hal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o: ../src/mcal/config/config_bits_P33CH.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/391766742" 
	@${RM} ${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o.d 
	@${RM} ${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/mcal/config/config_bits_P33CH.c  -o ${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/391766742/config_bits_P33CH.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o: ../src/mcal/config/config_bits_P33CK.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/391766742" 
	@${RM} ${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o.d 
	@${RM} ${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/mcal/config/config_bits_P33CK.c  -o ${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/391766742/config_bits_P33CK.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1019117317/mcal.o: ../src/mcal/mcal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1019117317" 
	@${RM} ${OBJECTDIR}/_ext/1019117317/mcal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019117317/mcal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/mcal/mcal.c  -o ${OBJECTDIR}/_ext/1019117317/mcal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1019117317/mcal.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1019117317/mcal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1724212984/isr_timer.o: ../src/sfl/isr/isr_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1724212984" 
	@${RM} ${OBJECTDIR}/_ext/1724212984/isr_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1724212984/isr_timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/sfl/isr/isr_timer.c  -o ${OBJECTDIR}/_ext/1724212984/isr_timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1724212984/isr_timer.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1724212984/isr_timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659867775/sfl.o: ../src/sfl/sfl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659867775" 
	@${RM} ${OBJECTDIR}/_ext/659867775/sfl.o.d 
	@${RM} ${OBJECTDIR}/_ext/659867775/sfl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/sfl/sfl.c  -o ${OBJECTDIR}/_ext/659867775/sfl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/659867775/sfl.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/659867775/sfl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/main.c  -o ${OBJECTDIR}/_ext/1360937237/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d"      -mno-eds-warn  -g -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -O3 -falign-arrays -I"../h" -I"../../plib/p33SMPS_mcal.X/plibs" -msmart-io=1 -Wall -msfr-warn=off   -fgnu89-inline -Wno-switch -std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/usb_pd_bob.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../plib/p33SMPS_mcal.X/dist/__P33SMPS_CK__/debug/p33SMPS_mcal.X.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/usb_pd_bob.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\plib\p33SMPS_mcal.X\dist\__P33SMPS_CK__\debug\p33SMPS_mcal.X.a  -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC"  -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/usb_pd_bob.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../plib/p33SMPS_mcal.X/dist/__P33SMPS_CK__/production/p33SMPS_mcal.X.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/usb_pd_bob.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\plib\p33SMPS_mcal.X\dist\__P33SMPS_CK__\production\p33SMPS_mcal.X.a  -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -D__00173_USB_PD_BOB_R20__ -D__CODE_OPT_LEVEL_3__ -DXPRJ_00173_USB_PD_BOB_R20=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -finline-functions -I"../src/apl/resources/zeus_stack/include" -I"../src/apl/resources/zeus_stack/portable/dsPIC" -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/usb_pd_bob.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:
	cd /D ../../plib/p33SMPS_mcal.X && ${MAKE}  -f Makefile CONF=__P33SMPS_CK__


# Subprojects
.clean-subprojects:
	cd /D ../../plib/p33SMPS_mcal.X && rm -rf "build/__P33SMPS_CK__" "dist/__P33SMPS_CK__"

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/00173_USB_PD_BOB_R20
	${RM} -r dist/00173_USB_PD_BOB_R20

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
