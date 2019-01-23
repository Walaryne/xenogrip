# libxenogrip.so

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/1316f71ae7d2437ba461e8a8bfdfe006)](https://app.codacy.com/app/Walaryne/xenogrip?utm_source=github.com&utm_medium=referral&utm_content=Walaryne/xenogrip&utm_campaign=Badge_Grade_Dashboard)

---
A shared library utilizing the ELF standard's .init section and mprotect() to on-the-fly patch instructions into a binary.

#### Instructions
---
The code in options.hpp is setup for the x86_64 version of `ls` on Linux. (Specifically `ls` version 8.25)

Currently, all `xeno()` does is patch a `mov rax, <address of test>` and after that, a `jmp rax` call.

`test()` is internally defined in `xenogrip.cpp`, all it does at the moment is call `print()` and prints a message, letting you know the process of patching succeeded. "It worked!"

The current target for `INITIAL_WRITE_POINTER` is the entry point to `main()`.

`INITIAL_WRITE_POINTER` should be set to where ever in memory you wish to patch. A common place to set this would be the entry point to a function.

Finding where you want to write to can be done many ways, but using Radare2 and analyzing the binary to find the offset is how I did it.

(Using the lovely [example code user Wisk wrote](https://reverseengineering.stackexchange.com/questions/20395/how-do-i-go-about-overriding-a-function-internally-defined-in-a-binary-on-linux) in the question I asked on the Reverse Engineering Stack Exchange, I was able to simplify this stuff **MASSIVELY.**)

#### Compiling
---
Fire up CMake's GUI, or use the command line and do the usual configure than generate. Run make (or whatever you're using) in the build directory.

#### Running
---
Running it is simple. For the example (while in your build directory), run:

```LD_PRELOAD=./libxenogrip.so ls```

As long as your using the 64 bit version of `ls` and version 8.25, you should see the message "It worked!" instead of a listing of files in your directory.
You'll also see some information about things as they happen prefixed with `[xeno]`.
