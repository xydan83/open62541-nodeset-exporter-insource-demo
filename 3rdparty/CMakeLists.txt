#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# Copyright 2025 (c) Aleksander Rozhkov <aleksprog@hotmail.com>
#

add_subdirectory(open62541)
set(NODESETEXPORTER_CONAN_ENABLE OFF) # Disable Conan's internal dependency because we have a problem with aliases. <-- todo fix it
set(NODESETEXPORTER_OPEN62541_IS_SUBMODULE ON)
# set(OPEN62541_VERSION "v1.4.x" CACHE STRING "What version of the Open62541 library are you using?") # Set this option if you are using Open62541 v1.4.x.
add_subdirectory(open62541-nodeset-exporter)