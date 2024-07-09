# 基础镜像
FROM ubuntu:latest

# 配置apt源为阿里云镜像
RUN sed -i 's/archive.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list && \
    sed -i 's/security.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list

# 更新apt源并安装必要的软件包和依赖
RUN apt-get update 
RUN apt-get install -y build-essential \
                    qt6-base-dev \
                    qmake6 \
                    qt6-charts-dev \
                    libmysqlclient-dev \
                    linguist-qt6 \
                    libqt6sql6-mysql \
                    qt6-l10n-tools

# 设置工作目录

WORKDIR /app

# 复制项目文件到容器中

COPY . /app

# 创建构建目录

RUN mkdir build && cd build

# 列出 /app 目录中的文件，以验证文件已被复制
RUN ls -l /app


# 编译项目

RUN make

# 设置启动命令 (可选)

CMD ["./Tank_Trouble_IV"]