# libxenogrip.so
---
A shared library utilizing the ELF standard's .init section and mprotect() to on-the-fly patch instructions into a binary.

#### Instructions
---
The code in options.hpp is setup for the x86_64 version of `ls` on Linux. (Specifically `ls` version 8.25)

Currently, all `xeno()` does is patch a `mov rax, <address of test>` and after that, a `jmp rax` call.

`test()` is internally defined in `xenogrip.cpp`, all it does at the moment is call `print()` and prints a message, letting you know the process of patching succeeded. "It worked!"

The current targets are the page alignment for where `main()` is located within the binary, and an offset from that page alignment high enough to encapsulate the first few instructions of `main()`

`PAGE_BASE_POINTER` is the start of the memory location aligned to page boundaries. It is commonly a multiple of 4096 on many Linux systems.

`MEMSET_SIZE` is the total amount of memory you want to have encompassed in the `mprotect()` call. This is the size *working from* the `PAGE_BASE_POINTER`. It also should be set **higher** than the `INITIAL_WRITE_POINTER`.

`INITIAL_WRITE_POINTER` should be set to where ever in memory you wish to patch. A common place to set this would be the entry point to a function.

Finding what these values can be done many ways, but using Radare2 and analyzing the binary to find the offsets is how I did it.

#### Compiling
---
Fire up CMake's GUI, or use the command line and do the usual configure than generate. Run make (or whatever you're using) in the build directory.


#### Running
---
Running it is simple. For the example (while in your build directory), run:

```LD_PRELOAD=./libxenogrip.so ls```

As long as your using the 64 bit version of `ls` and version 8.25, you should see the message "It worked!" instead of a listing of files in your directory.
You'll also see some information about things as they happen prefixed with `[xeno]`.
