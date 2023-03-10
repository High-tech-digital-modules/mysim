# My sim
This repository is example template how to split business logic of application code with platform 
specific code. This approach enables additionally also simulate platform specific code on your 
host machine by overriding functions.

We are developers, and we should think about our code in a bigger picture if we follow this 
template we can easily add support for different platforms just by creating new specific 
static library the relevant one. Code is also more clear because it is straightforward what code is 
portable and which not. Template creates also nice API abstraction.

## Note
There is existing simulation platform e.q. [qemu](https://www.qemu.org/) or [renode](https://renode.io/)
renode especially looks great in terms of emulating real processor architecture and also 
emulating multiple nodes. This template is not replacing any of them it is just representation of 
way how code should be split with benefit of simulation using standard executable for PC to 
check business logic of your application.

## Demo application
Application demonstrated here is targeted for stm32f4 platforms and also code could be simulated.
Demo will printf some output at the beginning, and then every specific number of cycles printf 
message

### Prerequisites 
- Now tested only on linux platform
- Cmake 
- make
- git
- arm-none-eabi-gcc

### Installation
Make sure that following packages are installed on your machine
```shell
apt install cmake git make arm-none-eabi-gcc
```

### Build 
- for the stm32f4 platform
```shell
mkdir build-stm32f4 && cd build-stm32f4
cmake ../ -DBOARD="stm32f4" -DCMAKE_TOOLCHAIN_FILE=../toolchains/arm-none-eabi.toolchain.cmake 
make
```
Final application is available in app-business-logic/minimal_cpu.elf

- for simulation
```shell
mkdir build-simulation && cd build-simulation
cmake ../ -DBOARD="simulation"
make
```
Final application is available in app-business-logic/minimal_cpu

### Runtime
Let's start with simulation it is easier to run. Just navigate to root of this repository and
```
./build-simulation/app-business-logic/minimal_cpu
```

#### Real device
Well now if we run code compiled for stm32f4_discovery-kit it will behave exactly same when 
connecting to serial monitor to uart2. In case not real device is not available this moment
let's try it using **renode**.

#### Warning!!!: following steps counting with docker installed on your machine

First we need to run renode monitor and well there is docker available great!
```shell
docker run -ti -e DISPLAY -v $XAUTHORITY:/home/developer/.Xauthority --net=host antmicro/renode
```
This will pop up renode monitor

in the second terminal copy elf to docker
```shell
# check name by running: 
docker ps
docker cp build-stm32f4/app-business-logic/minimal_cpu.elf <DOCKER_NAME>/opt/renode/
```

Copy one important file for platform to be used later

```shell
docker cp renode/minimal_cpu.repl <DOCKER_NAME>/opt/renode/
```

Great lets go to monitor console copy without **(monitor)** and **(monitor-0)**
```shell
(monitor) mach create
(machine-0) machine LoadPlatformDescription @minimal_cpu.repl
(machine-0) sysbus LoadELF @minimal_cpu.elf
(machine-0) showAnalyzer sysbus.usart2
(machine-0) start
```

Well now second window will pop up with **hello world!** message exactly same as on simulation.

