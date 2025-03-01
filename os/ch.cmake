# This file set sources of ChibiOS to ${CHIBIOS_XASM_SRC} ${CHIBIOS_C_SRC}, ${CHIBIOS_CPP_SRC}, and add corresponding
#   directory to include_directories. Extract from Makefiles and .mk files from ChibiOS.

# By liuzikai 2018-01-29

set(CHIBIOS .) # this file is included in the CMakeLists.txt in the upper directory.

# $(CHIBIOS)/os/license/license.mk
include_directories(${CHIBIOS}/os/license)


# $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32f4xx.mk
set(CHIBIOS_C_SRC ${CHIBIOS_C_SRC}
        ${CHIBIOS}/os/common/startup/ARMCMx/compilers/GCC/crt1.c)

set(CHIBIOS_XASM_SRC ${CHIBIOS_XASM_SRC}
        ${CHIBIOS}/os/common/startup/ARMCMx/compilers/GCC/crt0_v7m.S
        ${CHIBIOS}/os/common/startup/ARMCMx/compilers/GCC/vectors.S)

include_directories(${CHIBIOS}/os/common/portability/GCC
        ${CHIBIOS}/os/common/startup/ARMCMx/compilers/GCC
        ${CHIBIOS}/os/common/startup/ARMCMx/devices/STM32F4xx
        ${CHIBIOS}/os/common/ext/ARM/CMSIS/Core/Include
        ${CHIBIOS}/os/common/ports/ARM-common/include
        ${CHIBIOS}/os/common/ext/ST/STM32F4xx        )


# $(CHIBIOS)/os/hal/hal.mk
set(CHIBIOS_C_SRC ${CHIBIOS_C_SRC}
        ${CHIBIOS}/os/hal/src/hal.c
        ${CHIBIOS}/os/hal/src/hal_adc.c
        ${CHIBIOS}/os/hal/src/hal_buffered_serial.c
        ${CHIBIOS}/os/hal/src/hal_buffers.c
        ${CHIBIOS}/os/hal/src/hal_can.c
        ${CHIBIOS}/os/hal/src/hal_crypto.c
        ${CHIBIOS}/os/hal/src/hal_dac.c
        ${CHIBIOS}/os/hal/src/hal_efl.c
        ${CHIBIOS}/os/hal/src/hal_flash.c
        ${CHIBIOS}/os/hal/src/hal_gpt.c
        ${CHIBIOS}/os/hal/src/hal_i2c.c
        ${CHIBIOS}/os/hal/src/hal_i2s.c
        ${CHIBIOS}/os/hal/src/hal_icu.c
        ${CHIBIOS}/os/hal/src/hal_mac.c
        ${CHIBIOS}/os/hal/src/hal_mmc_spi.c
        ${CHIBIOS}/os/hal/src/hal_mmcsd.c
        ${CHIBIOS}/os/hal/src/hal_pal.c
        ${CHIBIOS}/os/hal/src/hal_pwm.c
        ${CHIBIOS}/os/hal/src/hal_queues.c
        ${CHIBIOS}/os/hal/src/hal_rtc.c
        ${CHIBIOS}/os/hal/src/hal_sdc.c
        ${CHIBIOS}/os/hal/src/hal_serial.c
        ${CHIBIOS}/os/hal/src/hal_serial_usb.c
        ${CHIBIOS}/os/hal/src/hal_sio.c
        ${CHIBIOS}/os/hal/src/hal_spi.c
        ${CHIBIOS}/os/hal/src/hal_st.c
        ${CHIBIOS}/os/hal/src/hal_uart.c
        ${CHIBIOS}/os/hal/src/hal_usb.c
        ${CHIBIOS}/os/hal/src/hal_spi_v1.inc
        ${CHIBIOS}/os/hal/src/hal_spi_v2.inc)

include_directories(${CHIBIOS}/os/hal/include)


# $(CHIBIOS)/os/hal/ports/STM32/STM32F4xx/platform.mk
set(CHIBIOS_C_SRC ${CHIBIOS_C_SRC}
        ${CHIBIOS}/os/hal/ports/common/ARMCMx/nvic.c
        ${CHIBIOS}/os/hal/ports/STM32/STM32F4xx/stm32_isr.c
        ${CHIBIOS}/os/hal/ports/STM32/STM32F4xx/hal_lld.c)

set(CHIBIOS_C_SRC ${CHIBIOS_C_SRC}
        ${CHIBIOS}/os/hal/ports/STM32/LLD/ADCv6/hal_adc_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/CANv1/hal_can_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/DACv2/hal_dac_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/DMAv2/stm32_dma.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti0.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti0_1.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti1.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti2.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti2_3.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti3.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti4.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti4_15.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti5.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti5_9.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti6.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti7.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti8.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti9.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti10.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti10_15.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti11.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti12.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti13.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti14.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti15.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti16.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti16-31-33.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti16-35_38.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti16-40_41.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti16_34.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti17.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti18.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti19.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti19-21.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti20.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti20_21.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti21.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti21_22.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti21_22-29.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti22.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti23.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti30_32.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti33.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti45.inc
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/GPIOv2/hal_pal_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/I2Cv3/hal_i2c_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/MACv2/hal_mac_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/QUADSPIv2/hal_wspi_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/RTCv3/hal_rtc_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/SPIv1/hal_spi_v2_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/SDIOv1/hal_sdc_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/TIMv1/hal_gpt_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/TIMv1/hal_icu_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/TIMv1/hal_pwm_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/USARTv1/hal_serial_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/USARTv1/hal_uart_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/xWDGv1/hal_wdg_lld.c)

include_directories(${CHIBIOS}/os/hal/ports/common/ARMCMx
        ${CHIBIOS}/os/hal/ports/STM32/STM32F4xx)

include_directories(${CHIBIOS}/os/hal/ports/STM32/LLD/ADCv2
        ${CHIBIOS}/os/hal/ports/STM32/LLD/CANv1
        ${CHIBIOS}/os/hal/ports/STM32/LLD/DACv1
        ${CHIBIOS}/os/hal/ports/STM32/LLD/DMAv2
        ${CHIBIOS}/os/hal/ports/STM32/LLD/EXTIv1
        ${CHIBIOS}/os/hal/ports/STM32/LLD/GPIOv2
        ${CHIBIOS}/os/hal/ports/STM32/LLD/I2Cv1
        ${CHIBIOS}/os/hal/ports/STM32/LLD/MACv1
        ${CHIBIOS}/os/hal/ports/STM32/LLD/OTGv1
        ${CHIBIOS}/os/hal/ports/STM32/LLD/QUADSPIv1
        ${CHIBIOS}/os/hal/ports/STM32/LLD/RTCv2
        ${CHIBIOS}/os/hal/ports/STM32/LLD/SPIv1
        ${CHIBIOS}/os/hal/ports/STM32/LLD/SDIOv1
        ${CHIBIOS}/os/hal/ports/STM32/LLD/SYSTICKv1/
        ${CHIBIOS}/os/hal/ports/STM32/LLD/TIMv1
        ${CHIBIOS}/os/hal/ports/STM32/LLD/USARTv1
        ${CHIBIOS}/os/hal/ports/STM32/LLD/USART
        ${CHIBIOS}/os/hal/ports/STM32/LLD/xWDGv1)

# $(CHIBIOS)/os/hal/ports/STM32/LLD/TIMv1/driver.mk
set(CHIBIOS_C_SRC ${CHIBIOS_C_SRC}
        ${CHIBIOS}/os/hal/ports/STM32/LLD/SYSTICKv1/hal_st_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/TIMv1/hal_gpt_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/TIMv1/hal_icu_lld.c
        ${CHIBIOS}/os/hal/ports/STM32/LLD/TIMv1/hal_pwm_lld.c)

include_directories(${CHIBIOS}/os/hal/ports/STM32/LLD/TIMv1)

## $(CHIBIOS)/dev/board/board.mk
#set(CHIBIOS_C_SRC ${CHIBIOS_C_SRC}
#        ${CHIBIOS}/dev/board/board.c)

include_directories(${CHIBIOS}/dev/board)


# $(CHIBIOS)/os/hal/osal/rt/osal.mk
set(CHIBIOS_C_SRC ${CHIBIOS_C_SRC}
        ${CHIBIOS}/os/hal/osal/rt-nil/osal.c)

include_directories(${CHIBIOS}/os/hal/osal/rt-nil)


# $(CHIBIOS)/os/rt/rt.mk
set(CHIBIOS_C_SRC ${CHIBIOS_C_SRC}
        ${CHIBIOS}/os/rt/src/chsys.c
        ${CHIBIOS}/os/rt/src/chdebug.c
        ${CHIBIOS}/os/rt/src/chtrace.c
        ${CHIBIOS}/os/rt/src/chvt.c
        ${CHIBIOS}/os/rt/src/chschd.c
        ${CHIBIOS}/os/rt/src/chthreads.c
        ${CHIBIOS}/os/rt/src/chtm.c
        ${CHIBIOS}/os/rt/src/chstats.c
        ${CHIBIOS}/os/rt/src/chregistry.c
        ${CHIBIOS}/os/rt/src/chsem.c
        ${CHIBIOS}/os/rt/src/chmtx.c
        ${CHIBIOS}/os/rt/src/chcond.c
        ${CHIBIOS}/os/rt/src/chevents.c
        ${CHIBIOS}/os/rt/src/chmsg.c
        ${CHIBIOS}/os/rt/src/chinstances.c
        ${CHIBIOS}/os/rt/src/chrfcu.c
        ${CHIBIOS}/os/rt/src/chdynamic.c
        ${CHIBIOS}/os/oslib/src/chdelegates.c
        ${CHIBIOS}/os/oslib/src/chfactory.c
        ${CHIBIOS}/os/oslib/src/chmboxes.c
        ${CHIBIOS}/os/oslib/src/chmemchecks.c
        ${CHIBIOS}/os/oslib/src/chmemcore.c
        ${CHIBIOS}/os/oslib/src/chmemheaps.c
        ${CHIBIOS}/os/oslib/src/chmempools.c
        ${CHIBIOS}/os/oslib/src/chobjcaches.c
        ${CHIBIOS}/os/oslib/src/chpipes.c
)

include_directories(${CHIBIOS}/os/rt/include
        ${CHIBIOS}/os/oslib/include)


# $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/port_v7m.mk
set(CHIBIOS_C_SRC ${CHIBIOS_C_SRC}
        ${CHIBIOS}/os/common/ports/ARMv7-M/chcore.c)

set(CHIBIOS_XASM_SRC ${CHIBIOS_XASM_SRC}
        ${CHIBIOS}/os/common/ports/ARMv7-M/compilers/GCC/chcoreasm.S)

include_directories(${CHIBIOS}/os/common/ports/ARMv7-M
        ${CHIBIOS}/os/common/ports/ARM-common
        ${CHIBIOS}/os/common/ports/ARMv7-M/compilers/GCC)

# $(CHIBIOS)/os/various/cpp_wrappers/chcpp.mk
set(CHIBIOS_CPP_SRC ${CHIBIOS_CPP_SRC}
        ${CHIBIOS}/os/various/cpp_wrappers/ch.cpp)

include_directories(${CHIBIOS}/os/various/cpp_wrappers)


# $(CHIBIOS)/os/hal/lib/streams/streams.mk
set(CHIBIOS_C_SRC ${CHIBIOS_C_SRC}
#        ${CHIBIOS}/os/hal/lib/streams/chprintf.c
        ${CHIBIOS}/os/hal/lib/streams/memstreams.c
        ${CHIBIOS}/os/hal/lib/streams/nullstreams.c)

include_directories(${CHIBIOS}/os/hal/lib/streams)

set(CHIBIOS_C_SRC ${CHIBIOS_C_SRC}
        ${CHIBIOS}/os/various/syscalls.c)

# $(CHIBIOS)/os/various/shell/shell.mk
#set(CHIBIOS_C_SRC ${CHIBIOS_C_SRC}
#        ${CHIBIOS}/os/various/shell/shell.c
#        ${CHIBIOS}/os/various/shell/shell_cmd.c)

#include_directories(${CHIBIOS}/os/various/shell)
