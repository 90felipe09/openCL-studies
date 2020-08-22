# openCL-studies
Open project for studying openCL implementations

# The devlog directory
It's where i'll be jotting down what is going on my mind while I study this subject. Kind of a journal.

# How i'm building
I'm using a computer with an Ubuntu OS installed. It has a GeForce 610M.

I'm building my solution with a Makefile.

So, if you're using windows, you can use the VS Community solutions to simplify things out.

All the code is being made in C/C++.

So, if you want to build this, just type `make`.

# Installing nvidia drivers safely on Ubuntu

Ok, listen me, i'm dumb and i made my ubuntu unbootable because of nvidia drivers installation. So... there must be a safe way of doing that. I'll try doing it the right way and hopefully you won't need to feel the same stress that i've felt.

`ubuntu-drivers autoinstall`

will install the last tested driver by Canonical, the enterprise that takes care of Ubuntu. But you can add the repository of the PPA of the "Graphic Device" team with this command before invoking ubuntu-drivers autoinstall:

`sudo apt-add-repository ppa:graphics-drivers/ppa && sudo apt update`

after that, reboot your system and check if it's installed by calling

`nvidia-smi`

Also, checks if the nouveau is loaded:

`lsmod | grep nouveau`

The nouveau module is a pre built module for the linux kernel that is a default driver that try to access basic functionalities of your graphic card. Ensure that it's disabled after installing nvidia drivers. Please, search on google how to disable nouveau if something appears on your terminal after executing that command.

## Checking your devices

You can check the gpu that you have in your computer using the following command (if you have a NVidia card):

`lspci | grep -i nvidia`

### The lspci command

The union of ls and pci. So a command that exhibit all of your Peripheral Controller Interconnect (PCI) devices. PCI devices are computer hardware that plugs directly into a PCI slot in your motherboard. So examples of PCI devices that you may have are your network card, your audio card and, now you see, your GPU.

So, if you run `lspci` alone you will see a list of PCI devices plugged on your computer.

So, even if you aren't sure about the GPU device that you have, simply use this command alone without the `| grep -i nvidia` that i've used to find out mine and recognize the entry that contains a GPGPU vendor name.

## Installing the GPU vendor sdk

If you have an AMD GPU, install their ATI SDK:
(https://developer.amd.com/tools-and-sdks/)

If you have a NVidia GPU, install their CUDA SDK:
(https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html)

"Wait, i thought that since i was using openCL I wouldn't need to install anything like CUDA (NVidia SDK) or ATI (AMD SDK) sdk vendor-specific in order to make it work.". Yeah... let's talk about it:

### What is openCL exactly

OpenCL is not a library. OpenCL is just a specification, a standard. Khronos Group (https://www.khronos.org/) is a group that creates and maintains open standards in the industry and openCL is one of those Standards. But why such a thing exist in first place? Imagine that there was a moment when NVidia had it own toolsets and libraries to implement software solutions to run in their GPU devices, it is, CUDA. And at the same time, AMD had it's own, the ATI. Imagine now a lot of scientist and developers world wide discovering that implementing their solutions with one of them would compromise their entire work with that vendor, or worse, that your developers team would have to code for both solutions in order to ship your application to all of your costumers. That would be a mess and costs would be higher for parallel computing applications development.

And what this standard standardize exactly? In terms of code, it specify a header file with functions signatures, constants definitions and etc that a specific vendor should or already implement. Imagine it as an interface in OOP. So, the common concepts for GPGPU applications are preempted in this open standard making it possible for developers coding agnostic-vendor applications.

I know that nowadays everyone is talking about developing AI with CUDA and that "You should only use CUDA for AI and etc.", but i recogize the importance of stepping back and being prepared by making a good use of openCL because what if AMD overcome NVidia in this field? What if FPGA usage proves itself a better alternative to train DNN? (I used this question because you can use openCL in order to make use of a FPGA as a computational device). So that's the point of why i'm giving it a try instead of jumping over and coding directly with CUDA. And also, since this will be an agnostic-vendor solution, maybe it can be of great help for those that have an AMD GPU in their computer.

Ok, if openCL is not a library, how do i "code it" exactly? Well, you'll have to install the SDK of your vendor in your machine and links it to your project. The difference here is that your code will be oriented by openCL terminology and functions signatures. The actual library in your vendor SDK will then provide the implementation, it is, the actual functions definitions of each of these functions that the openCL standard specify so that their drivers for their devices recognizes what you coded.


