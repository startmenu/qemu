/*
 * QEMU PowerMac emulation shared definitions and prototypes
 *
 * Copyright (c) 2004-2007 Fabrice Bellard
 * Copyright (c) 2007 Jocelyn Mayer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef PPC_MAC_H
#define PPC_MAC_H

#include "qemu/units.h"
#include "exec/memory.h"
#include "hw/boards.h"
#include "hw/sysbus.h"
#include "hw/ide/internal.h"
#include "hw/input/adb.h"
#include "hw/misc/mos6522.h"
#include "hw/ppc/mac_dbdma.h"
#include "hw/pci/pci_host.h"
#include "hw/pci-host/uninorth.h"
#include "audio/audio.h"

/* SMP is not enabled, for now */
#define MAX_CPUS 1

#define BIOS_SIZE        (1 * MiB)
#define NVRAM_SIZE        0x2000
#define PROM_FILENAME    "openbios-ppc"
#define PROM_ADDR         0xfff00000

#define KERNEL_LOAD_ADDR 0x01000000
#define KERNEL_GAP       0x00100000

#define ESCC_CLOCK 3686400

/* Old World IRQs */
#define OLDWORLD_CUDA_IRQ      0x12
#define OLDWORLD_ESCCB_IRQ     0x10
#define OLDWORLD_ESCCA_IRQ     0xf
#define OLDWORLD_IDE0_IRQ      0xd
#define OLDWORLD_IDE0_DMA_IRQ  0x2
#define OLDWORLD_IDE1_IRQ      0xe
#define OLDWORLD_IDE1_DMA_IRQ  0x3
#define OLDWORLD_SCREAMER_TX_IRQ  0x11
#define OLDWORLD_SCREAMER_TX_DMA_IRQ 0x08
#define OLDWORLD_SCREAMER_RX_IRQ  0x09

/* New World IRQs */
#define NEWWORLD_CUDA_IRQ      0x19
#define NEWWORLD_PMU_IRQ       0x19
#define NEWWORLD_ESCCB_IRQ     0x24
#define NEWWORLD_ESCCA_IRQ     0x25
#define NEWWORLD_IDE0_IRQ      0xd
#define NEWWORLD_IDE0_DMA_IRQ  0x2
#define NEWWORLD_IDE1_IRQ      0xe
#define NEWWORLD_IDE1_DMA_IRQ  0x3
#define NEWWORLD_EXTING_GPIO1  0x2f
#define NEWWORLD_EXTING_GPIO9  0x37
#define NEWWORLD_SCREAMER_IRQ  0x18
#define NEWWORLD_SCREAMER_DMA_IRQ 0x09
#define NEWWORLD_SCREAMER_RX_IRQ 0x0a

/* Core99 machine */
#define TYPE_CORE99_MACHINE MACHINE_TYPE_NAME("mac99")
#define CORE99_MACHINE(obj) OBJECT_CHECK(Core99MachineState, (obj), \
                                         TYPE_CORE99_MACHINE)

#define CORE99_VIA_CONFIG_CUDA     0x0
#define CORE99_VIA_CONFIG_PMU      0x1
#define CORE99_VIA_CONFIG_PMU_ADB  0x2

typedef struct Core99MachineState {
    /*< private >*/
    MachineState parent;

    uint8_t via_config;
} Core99MachineState;

/* Screamer */
#define TYPE_SCREAMER "screamer"
#define SCREAMER(obj) OBJECT_CHECK(ScreamerState, (obj), TYPE_SCREAMER)

#define SCREAMER_BUFFER_SIZE 0x4000

typedef struct ScreamerState {
    /*< private >*/
    SysBusDevice parent_obj;
    /*< public >*/
    MemoryRegion mem;
    qemu_irq irq;
    void *dbdma;
    qemu_irq dma_tx_irq;
    qemu_irq dma_rx_irq;

    QEMUSoundCard card;
    SWVoiceOut *voice;
    uint8_t  buf[SCREAMER_BUFFER_SIZE];
    uint32_t bpos;
    uint32_t ppos;
    uint32_t rate;
    DBDMA_io io;

    uint32_t regs[6];
    uint32_t codec_ctrl_regs[8];
} ScreamerState;

void macio_screamer_register_dma(ScreamerState *s, void *dbdma, int txchannel, int rxchannel);

/* Grackle PCI */
#define TYPE_GRACKLE_PCI_HOST_BRIDGE "grackle-pcihost"

/* Mac NVRAM */
#define TYPE_MACIO_NVRAM "macio-nvram"
#define MACIO_NVRAM(obj) \
    OBJECT_CHECK(MacIONVRAMState, (obj), TYPE_MACIO_NVRAM)

typedef struct MacIONVRAMState {
    /*< private >*/
    SysBusDevice parent_obj;
    /*< public >*/

    uint32_t size;
    uint32_t it_shift;

    MemoryRegion mem;
    uint8_t *data;
} MacIONVRAMState;

void pmac_format_nvram_partition (MacIONVRAMState *nvr, int len);
#endif /* PPC_MAC_H */
