#!/bin/bash
STM32_BIN=build-stm32/src/stm32f7-mnist-x_cube_ai.bin
OFFSET=0x8000000
st-flash --reset write "${STM32_BIN}" "${OFFSET}"
