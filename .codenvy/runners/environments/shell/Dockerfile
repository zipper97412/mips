

FROM codenvy/cpp
RUN sudo apt-get install -y gdb
ENV CODENVY_APP_BIND_DIR /home/user/app
VOLUME ["/home/user/app"]
RUN echo "export HOME=/home/user/app/src; cd" >> /home/user/.bashrc
CMD sleep 365d
