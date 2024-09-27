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
RUN lfphp-get golang && mv /usr/local/go /usr/local/go-1.16.8
RUN wget -O go1.18.5.linux-amd64.tar.gz https://dl.google.com/go/go1.18.5.linux-amd64.tar.gz && tar -C /usr/local -xvf go1.18.5.linux-amd64.tar.gz && mv /usr/local/go /usr/local/go-1.18.5
RUN wget -O go1.21.8.linux-amd64.tar.gz https://dl.google.com/go/go1.21.8.linux-amd64.tar.gz && tar -C /usr/local -xvf go1.21.8.linux-amd64.tar.gz && mv /usr/local/go /usr/local/go-1.21.8
RUN ln -s /usr/local/go-1.16.8 /usr/local/go

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
RUN mv /root/go /home/go-1.16.8 && ln -s /home/go-1.16.8 /home/go && mkdir -p /home/go-1.18.5 && mkdir -p /home/go-1.21.8
RUN cd /home/flareuser && mkdir bin && mkdir log && touch /home/flareuser/log/check.log
#RUN cd /home/flareuser && git clone https://github.com/flare-foundation/go-songbird.git
RUN cd /home/flareuser && git clone https://github.com/flare-foundation/go-flare.git

# Checking out lastest version of go-songbird - CURRENT HEAD is v0.6.5
#RUN cd /home/flareuser/go-songbird && git checkout v0.6.5 && source /etc/bashrc && cd avalanchego && ./scripts/build.sh && chown -R flareuser:flare /home/go && chmod -R 775 /home/go && chown -R flareuser:flare /home/flareuser && ln -s /home/flareuser/go-songbird /home/flareuser/flare

# Checking out lastest version of go-flare - CURRENT HEAD is v0.6.6-songbird
RUN cd /home/flareuser/go-flare && git checkout v0.6.6-songbird && rm /usr/local/go && ln -s /usr/local/go-1.21.8 /usr/local/go && rm /home/go && ln -s /home/go-1.21.8 /home/go && source /etc/bashrc && cd avalanchego && ./scripts/build.sh && chown -R flareuser:flare /home/go && chmod -R 775 /home/go && chown -R flareuser:flare /home/flareuser && rm /usr/local/go && ln -s /usr/local/go-1.16.8 /usr/local/go && rm /home/go && ln -s /home/go-1.16.8 /home/go

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

# Set up flareuser bashrc
RUN echo "export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/go/bin" >> /home/flareuser/.bashrc
RUN echo "export GOPATH=/home/go" >> /home/flareuser/.bashrc

# Change root password
RUN echo "root:toor" | chpasswd

WORKDIR /home/flareuser/flare

USER flareuser

CMD ["/usr/bin/flare"]
