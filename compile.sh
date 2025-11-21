#!/bin/bash
set -e

project_name="CH559USB"
xram_size=0x0800
xram_loc=0x0600
code_size=0xEFFF
dfreq_sys=48000000

# config.h が無ければ生成
if [ ! -f config.h ]; then
    echo "//add your personal defines here" > config.h
fi

# 共通オプション
COMMON_OPTS="-V -mmcs51 --model-large --xram-size ${xram_size} --xram-loc ${xram_loc} --code-size ${code_size} -I/ -DFREQ_SYS=${dfreq_sys}"

sdcc -c $COMMON_OPTS main.c
sdcc -c $COMMON_OPTS util.c
sdcc -c $COMMON_OPTS USBHost.c
sdcc -c $COMMON_OPTS uart.c

sdcc main.rel util.rel USBHost.rel uart.rel $COMMON_OPTS -o ${project_name}.ihx

packihx ${project_name}.ihx > ${project_name}.hex

rm -f \
    ${project_name}.lk \
    ${project_name}.map \
    ${project_name}.mem \
    ${project_name}.ihx \
    *.asm *.lst *.rel *.rst *.sym

wchisp flash ${project_name}.hex

echo "Build completed. Output: ${project_name}.bin"
