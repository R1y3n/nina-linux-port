#!/bin/sh
# Rebuild the sandbox toolchain used in the previous session (Ubuntu 24.04, root). Network access to github.com + apt needed.
set -e
dpkg --add-architecture i386; apt-get update -qq
apt-get install -y -qq gcc-mingw-w64-i686 libc6-dev-i386 gcc-multilib p7zip-full openjdk-25-jdk-headless \
  libsdl2-2.0-0:i386 libgl1:i386 libgl1-mesa-dri:i386 libglx-mesa0:i386 mesa-common-dev xvfb unzip zip
pip install pefile capstone --break-system-packages
# Optional (only to redo the decompilation): Ghidra 12.2 needs JDK 25 (JAVA_HOME=/usr/lib/jvm/java-25-openjdk-amd64)
# curl -L -o ghidra.zip https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_12.2_build/ghidra_12.2_PUBLIC_20261016.zip
# Optional (Windows test): apt-get install -y wine32:i386 wine64
