TDX_COMMON = "1"

require torizon-os-version.inc
require torizon-core-docker.bb
require torizon-core-dev.inc

CORE_IMAGE_BASE_INSTALL:append = " \
    telemetry \
"

DESCRIPTION = "TorizonCore Linux development image"
IMAGE_VARIANT = "Common Docker Development"
