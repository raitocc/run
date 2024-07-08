# 使用包含 g++ 和 cmake 的镜像

FROM ubuntu:latest

# 配置中国区镜像源

RUN sed -i 's/archive.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list && \
 sed -i 's/security.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list

# 更新软件包列表

RUN apt-get update

# 安装必要的软件包

RUN apt-get install -y build-essential cmake git \
 libfmt-dev libgtest-dev

# 安装软件属性公共包和添加 Qt PPA
RUN echo "Adding Qt PPA..." && \
    apt-get install -y software-properties-common && \
    apt-add-repository -y ppa:ubuntu-sdk-team/ppa

# 更新软件包列表
RUN echo "Updating package lists..." && \
    apt-get update

# 安装 Qt6 相关软件包
RUN echo "Installing Qt6 packages..." && \
    apt-get install -y qt6-base qt6-declarative qt6-tools

# 设置工作目录

WORKDIR /app

# 复制项目文件到容器中

COPY . /app

# 创建构建目录

RUN mkdir build && cd build

# 使用 QMake 生成 Makefile

RUN qmake .

# 编译项目

RUN make

# 设置启动命令 (可选)

CMD ["./Tank_Trouble_IV"]