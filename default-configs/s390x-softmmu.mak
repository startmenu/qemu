CONFIG_PCI=y
CONFIG_VIRTIO_PCI=$(CONFIG_PCI)
include virtio.mak
CONFIG_SCLPCONSOLE=y
CONFIG_TERMINAL3270=y
CONFIG_S390_FLIC=y
CONFIG_S390_FLIC_KVM=$(CONFIG_KVM)
CONFIG_WDT_DIAG288=y
CONFIG_S390_CCW_VIRTIO=y
CONFIG_VFIO=$(CONFIG_LINUX)
CONFIG_VFIO_CCW=y
CONFIG_VFIO_AP=y
