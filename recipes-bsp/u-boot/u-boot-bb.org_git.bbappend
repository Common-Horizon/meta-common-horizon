FILESEXTRAPATHS:prepend := "${THISDIR}/u-boot-bb.org:"

SRC_URI:append:beaglebone = " \
    file://0001-ARM-dts-am335x-pocketbeagle-choose-tick-timer.patch \
	"
