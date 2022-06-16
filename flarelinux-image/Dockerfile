FROM asclinux/linuxforphp-8.2-ultimate:src

MAINTAINER Andrew Caya <andrewscaya@yahoo.ca>

USER root

WORKDIR /root

# bind-utils setup
RUN lfphp-get bind-utils

# Node 10.24.1 setup
RUN lfphp-get --force node.js-10
RUN npm install --global yarn

# Golang 1.16.8 setup
RUN lfphp-get golang

# jq setup
RUN lfphp-get jq

# libtirpc and lsof setup
RUN lfphp-get lsof

# gflags, libsnappy, LevelDB, and RocksDB setup
RUN lfphp-get rocksdb

# Fcron setup
RUN rm -rf /services/*
RUN lfphp-get fcron

# Clean up
RUN cd && rm -rf *.tar.gz && rm -rf *.tar.xz

# Flare Network setup
RUN groupadd flare && useradd -g flare flareuser && cp -rf /etc/skel /home/flareuser && chown -R flareuser:flare /home/flareuser && echo "flareuser:flarepass" | chpasswd
RUN sed -i 's/GOPATH=\/root\/go/GOPATH=\/home\/go/' /etc/bashrc
RUN mv /root/go /home
RUN cd /home/flareuser && mkdir bin && mkdir log && touch /home/flareuser/log/check.log
RUN cd /home/flareuser && git clone https://github.com/flare-foundation/flare.git

# Checking out lastest version - CURRENT HEAD is v0.6.1
RUN cd /home/flareuser/flare && git checkout v0.6.1 && source /etc/bashrc && ./scripts/build.sh && chown -R flareuser:flare /home/go && chmod -R 775 /home/go && chown -R flareuser:flare /home/flareuser

# Copy core files
COPY ./flare /usr/bin
COPY ./cronup /usr/bin
COPY ./crondown /usr/bin
COPY ./sgbcheck.js /home/flareuser/bin
COPY ./sgbcheckcmd /home/flareuser/bin
COPY ./sgbchecklogcmd /home/flareuser/bin

# Set up crons
RUN echo "#*/10 * * * * flareuser bash --login -c '/home/flareuser/bin/sgbcheckcmd > /home/flareuser/log/check.log 2>&1'" >> /etc/fcrontab
RUN echo "#*/2 * * * * flareuser bash --login -c '/home/flareuser/bin/sgbchecklogcmd > /home/flareuser/log/checklog.log 2>&1'" >> /etc/fcrontab

# Change root password
RUN echo "root:toor" | chpasswd

WORKDIR /home/flareuser/flare

USER flareuser

CMD ["/usr/bin/flare"]
