FROM debian:stretch
RUN \
apt-get -y update && \
apt-get -y install \
    make cmake clang \
    libboost-dev libboost-test-dev \
    doxygen graphviz \
    python \
    valgrind cppcheck && \
apt-get clean autoclean && \
apt-get autoremove -y && \
rm -rf /var/lib/{apt,dpkg,cache,log}/
