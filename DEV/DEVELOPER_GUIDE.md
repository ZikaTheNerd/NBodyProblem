# Developer Guide

## Before you start:

It is recommended to develop on linux/unix. We might add support for Windows in the future.

Requirements:

```bash
make
cmake
xorg-dev
git
```

All of the above can be installed using package managers that come with many linux distributions.
For development purposes it is also recommended to have a fairly modern c++ compiler (standard
we use is C++14).

Once you clone the project, you should make a build directory inside of project root:

```bash
mkdir build && cd build
```

Then run the following commands in succession:

```bash
cmake ..
make
```

To run the code you need to be in the build directory.
The following command runs the code:

```bash
./NBodyProblem 
```

## Coding Style and Practices

Coding style is documented inside of ``.clang-format`` and ``.clang-tidy``
files. This is a bit modified google development style for c++.
If you are working inside of VS Code with C/C++ extension, it should warn you
if you make any styling mistakes (please pay attention to the warnings).
This helps us maintain a homogenous coding style while also reducing silly mistakes.

**Please use descriptive commit messages!**

## Git

For this project we have no limitations regarding pull requests and branch creation/naming.
You can push to remote main branch without any obstructions. If you decide to create remote branches
of your own (this is generally a good practice) you should delete them after merging with main. Furthermore,
when you merge your remote branches with the main branch please rebase and squash.
Again, there is no PR/Code Review process or anything similar.



