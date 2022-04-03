# sudo docker build -t coffee .
# sudo docker run -d -p 7294:7294 --rm -it coffee

FROM ubuntu:20.04

RUN apt-get update

RUN useradd -d /home/ctf/ -m -p ctf -s /bin/bash ctf
RUN apt-get install patchelf -y
RUN echo "ctf:ctf" | chpasswd

WORKDIR /home/ctf

COPY challenge/chal .
COPY challenge/flag.txt .
COPY challenge/ynetd .
COPY challenge/ld-2.31.so .
COPY challenge/libc.so.6 .
RUN patchelf --set-interpreter ./ld-2.31.so ./chal
RUN patchelf --set-rpath ./ ./chal

RUN chown -R root:root /home/ctf

USER ctf
EXPOSE 7294
CMD ./ynetd -p 7294 ./chal
