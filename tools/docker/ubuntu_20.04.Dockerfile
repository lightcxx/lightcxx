FROM ubuntu:20.04

# Generally useful stuff
RUN apt-get update --fix-missing
RUN apt-get -y install apt-utils software-properties-common curl wget xz-utils libz3-4 zsh \
                       libtinfo5 ninja-build unzip fontconfig gcc-9 g++-9
RUN curl -SL https://github.com/llvm/llvm-project/releases/download/llvmorg-10.0.0/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz | tar -xJC .
RUN wget -c https://github.com/Kitware/CMake/releases/download/v3.16.4/cmake-3.16.4-Linux-x86_64.tar.gz -O - | tar -xz

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 800 --slave /usr/bin/g++ g++ /usr/bin/g++-9
RUN ln -s /usr/lib/x86_64-linux-gnu/libz3.so.4 /usr/lib/libz3.so.4.8
RUN mv clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04 /usr/clang
RUN mv cmake-3.16.4-Linux-x86_64 /usr/cmake

RUN mkdir -p /root/.local/share/fonts
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/JetBrains/JetBrainsMono/master/install_manual.sh)"

ENV LIBRARY_PATH $LIBRARY_PATH:/usr/clang/lib
ENV LD_LIBRARY_PATH $LD_LIBRARY_PATH:/usr/clang/lib
ENV PATH $PATH:/usr/clang/bin:/usr/cmake/bin

WORKDIR /code
