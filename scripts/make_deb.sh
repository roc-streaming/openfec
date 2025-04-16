#! /usr/bin/env bash

set -euo pipefail

cd "$(dirname "$0")/.."

docker run --rm -t --pull always \
       -w "$(pwd)" \
       -v "$(pwd):$(pwd)" \
       debian:bullseye \
       /bin/bash -c "$(cat <<'END'
set -euxo pipefail

export DEBIAN_FRONTEND=noninteractive

apt-get update
apt-get install -y --no-install-suggests \
        build-essential debhelper devscripts dh-exec \
        $(grep -Po '(?<=Build-Depends:).*' debian/control \
            | egrep -o '[a-zA-Z][a-zA-Z0-9+-]+' | tr '\n' ' ')

apt-get clean

dpkg-buildpackage -b -rfakeroot -us -uc

mkdir -p dist
rm -f dist/*.deb

mv ../*.deb dist
rm -f dist/*-dbgsym_*.deb

chown -R 1000:1000 dist
END
)"
