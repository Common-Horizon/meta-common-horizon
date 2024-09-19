FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://0001-disable-boot-splash-later.patch \
    file://torizon-splash.png \
    file://torizon-splash-dev.png \
    file://commontorizonlogo.png \
    file://commontorizonlogo-dev.png \
    file://0001-themes-only-install-spinner.patch \
    file://torizonlogo-white.png \
    file://torizonlogo-labs.png \
    file://spinner.plymouth \
"

PACKAGECONFIG = "drm"

EXTRA_OECONF += "--with-udev --with-runtimedir=/run"

do_install:append () {
    # use the labs logo if we are building the engineering image
    if [ "${TDX_DEBUG}" = "1" ]; then
        install -m 0644 ${WORKDIR}/torizon-splash-dev.png ${D}${datadir}/plymouth/themes/spinner/watermark.png
    else
        install -m 0644 ${WORKDIR}/torizon-splash.png ${D}${datadir}/plymouth/themes/spinner/watermark.png
    fi

    install -m 0644 ${WORKDIR}/spinner.plymouth ${D}${datadir}/plymouth/themes/spinner/spinner.plymouth
}
