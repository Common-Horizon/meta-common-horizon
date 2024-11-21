# Settings for the meta-ti-bsp beaglebone machine.

# taken from meta-freescale/conf/machine/include/utilities.inc
def make_dtb_boot_files(d):
    # Generate IMAGE_BOOT_FILES entries for device tree files listed in
    # KERNEL_DEVICETREE.
    # Use only the basename for dtb files:
    alldtbs = d.getVar('KERNEL_DEVICETREE')


    # DTBs may be built out of kernel with devicetree.bbclass
    if not alldtbs:
        return ''

    def transform(dtb):
        if not (dtb.endswith('dtb') or dtb.endswith('dtbo')):
            # eg: whatever/bcm2708-rpi-b.dtb has:
            #     DEPLOYDIR file: bcm2708-rpi-b.dtb
            #     destination: bcm2708-rpi-b.dtb
            bb.error("KERNEL_DEVICETREE entry %s is not a .dtb or .dtbo file." % (dtb) )
        return os.path.basename(dtb)

    return ' '.join([transform(dtb) for dtb in alldtbs.split() if dtb])

WKS_FILE = "sdimage-2part.wks"
WKS_FILE_DEPENDS:remove = "tezi-metadata virtual/dtb"
CORE_IMAGE_BASE_INSTALL:append = "resize-helper"

KERNEL_BUILTIN_WIREGUARD:beaglebone = "1"
CORE_IMAGE_BASE_INSTALL:remove = "kernel-module-wireguard wireguard-tools"
IMAGE_INSTALL:append:beaglebone = " wl18xx-fw wlconf linux-firmware-wlcommon"
PREFERRED_PROVIDER_virtual/bootloader = "u-boot-bb.org"
PREFERRED_PROVIDER_virtual/bootloader:sota = "u-boot-bb.org"
PREFERRED_PROVIDER_virtual/bootloader:beaglebone = "u-boot-bb.org"
PREFERRED_PROVIDER_u-boot:beaglebone = "u-boot-bb.org"
PREFERRED_PROVIDER_virtual/dtb = ""
WKS_FILE_DEPENDS_BOOTLOADERS:beaglebone = "virtual/bootloader"
WKS_FILE_DEPENDS:append:beaglebone = " u-boot-default-script"
PREFERRED_PROVIDER_u-boot-default-script:beaglebone = "u-boot-distro-boot"
PREFERRED_PROVIDER_u-boot-default-script:sota:beaglebone = "u-boot-distro-boot"

PREFERRED_PROVIDER_u-boot-fw-utils = "libubootenv"
PREFERRED_RPROVIDER_u-boot-fw-utils = "libubootenv"

IMAGE_FSTYPES:remove:beaglebone = "ext3 jffs2 teziimg"

# We need ota-ext4 and wic for beagle
IMAGE_FSTYPES_REMOVE = ""
IMAGE_BOOT_FILES:beaglebone = "u-boot.img MLO ${@make_dtb_boot_files(d)} boot.scr uEnv.txt "
IMAGE_BOOT_FILES:sota:beaglebone = "u-boot.img MLO ${@make_dtb_boot_files(d)} "
IMAGE_BOOT_FILES_REMOVE:sota:remove = "boot.scr-${MACHINE};boot.scr"
IMAGE_BOOT_FILES:append = " boot.scr-${MACHINE};boot.scr "

OSTREE_KERNEL:beaglebone = "zImage"
OSTREE_DEPLOY_DEVICETREE:beaglebone = "0"
KERNEL_IMAGETYPE:beaglebone = "zImage"
KERNEL_IMAGETYPE:sota:beaglebone = "zImage"

LINUX_VERSION_EXTENSION = "-torizon-${LINUX_KERNEL_TYPE}"

## same bahavior
# This boot arguments are the same from torizon.bbclass
OSTREE_KERNEL_ARGS:sota:append:beaglebone = "console=ttyS0,115200 root=LABEL=otaroot rootfstype=ext4 quiet logo.nologo vt.global_cursor_default=0 plymouth.ignore-serial-consoles splash "

UBOOT_BINARY_OTA_IGNORE:beaglebone = "1"

BBMASK += " \
    meta-raspberrypi/recipes-bsp/u-boot/u-boot_%.bbappend \
    meta-common-torizon/recipes-bsp/u-boot/u-boot-toradex-ti_%.bbappend \
"
