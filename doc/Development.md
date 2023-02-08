It's good to see you here at the page as it means, you have posible interest in contributing to the project... but probably not, who knows.
Anyway, at the page you may find instructions how to set up build environment for the project.

Raspberry Pi Pico SDK
===

Install in some folder Pico SDK from here: https://github.com/raspberrypi/pico-sdk

I did it by the command:

`git clone https://github.com/raspberrypi/pico-sdk.git`

and followed instructions from the README.md file of the project.

Nothing hard here, just a reminder: do not forget to define environment variable `PICO_SDK_PATH`

And yet another note: I have Fedora, but instructions from the project describe a way for Debian-based distros, so there are commands to install all needed packages under RPM-based distros:

`sudo dnf install -y cmake arm-none-eabi-binutils-cs  arm-none-eabi-gcc-cs arm-none-eabi-gcc-cs-c++ arm-none-eabi-newlib`

Other tools
===

You also need to install GoogleTest and Freecad.

deb-based distros:
`sudo apt install googletest google-mock freecad`

RPM-based distros:

`sudo dnf -y install gtest-devel gmock-devel freecad`

Getting sources
===

It's simply:

`mkdir -p ~/myprojects`

`cd ~/myprojects`

`git clone https://github.com/slavaz/SmartFilamentSensor.git`

`cd SmartFilamentSensor`

Build project
===
`cmake -B build`

`cd build`

`make all test`

If you want to get a tarball with assebmled files, run the command:

`make package`

after it, you will have a tarball into `build/package` folder.

The tarball contains a firmware binary file and STL-files with 3D models.
