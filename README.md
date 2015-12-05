# t3
Command line tic, tac, toe game.

Small toy program created in order to:
* write code that pleases my eyes
* gain experience with C++14
* evaluate tools usable for C++ projects
* exercise design

Written in C++ with focus on correctness and maintainability. Target platform is GNU/Linux. Project is very probably portable (but untested).

## downloading

prerequisities
* git

```
git clone https://github.com/koja/t3.git
```

You can download and unpack sources via GitHub web interface as well.

## installation

### native

prerequisities
* linux
* cmake
* clang >= 3.6
* libboost-dev
* libboost-test-dev

In the same directory where `t3` is located run:

```
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=clang++ ../t3 && make
```

Try to avoid building in-source as there might be issues with `cmake` when running testing tools.

### docker

For dependency hassle free demo custom Docker image (t3-sandbox) is available.

prerequisities
* linux
* docker
* Depending on your (or your distribution) configuration you might need to add your user to group `docker` or run commands with `sudo`.

```
cd directory/where/t3/repository/is/located/BUT/not/inside/t3
# start the virtual container ...
docker run -v $(pwd):/tmp/t3 -w /tmp/t3 -it koja/t3-sandbox bash
# ... and follow the native installation commands
```

To run any commands described below (generating docs, running tests or the game) just run those inside the container.

[t3-sandbox Docker image](https://hub.docker.com/r/koja/t3-sandbox/)

## documentation

prerequisities
* graphviz
* doxygen

Go to repository root (inside `t3`) and run
```
make doc
```
to generate doxygen documentation. See `doc/html/index.html`.


## starting ...

To run the game inside `build` directory:
```
./t3
```

To run unit tests inside `build` directory:
```
ls test-*
./test-model
...
```

To run testing tools inside `t3` repository:
```
cd testing_tools/project_checks
ls
./no_duplicate_include_guard
...

cd ../code_analysis
ls use*
./use_clang_addr_san
...
```

## project guidelines
### design
* Separate UI and model.
* Avoid unnecessary dependencies.
* Don't over-generalize or over-engineer, respect KISS and YAGNI.

### code
#### readability
* Prefer simple and maintainable solutions.
* Use proper names and self-documenting code.
* Maintain code uniformity.
* Document interfaces (especially "exception specification").
* Avoid low value comments.
* Do not exploit every possible way to spare runtime computation. Avoid complex template metaprogramming solutions and precomputed data.

#### prefer correctness to performance
* Try to avoid anything non-standard.
* Avoid premature optimization.
* Prefer `std::shared_ptr` over potentially dangling references.
* Prefer simple object copying to potentially dangerous reference tricks where appropriate.
* Don't use "naked" pointers.
* Don't use bounds-unchecked access to containers.
* Minimize usage of type casts, don't use non-explicit c-tors.
* Select STL containers in regard to guarantees provided first not in regard to performance.
* Strive for const-correctness. Also use const for pass by value function parameters as these should not be mutable in function implementation.

### testing
* Use unit (or almost-unit) tests in the sense that not all dependencies need to be mocked.
* Take testability into consideration when thinking about design but only as a hint not hard requirement.
* Strive for every line of code be run in tests.
* Strive for selective and isolated testing. Testing large parts of code at once means lower test specificity and longer debugging in case of fail.
* Test every functionality for "happy path" and every exception specified in documentation.
* If possible try to have more inputs, corner cases or even all possible input for important functionality. But do not necessarily test "everything".
* Try to keep tests implementation and maintenance time reasonable. Spared time can be used for other bug prevention/finding measures.

## tools overview

I used proven mainstream tools not anything fancy. In several cases I was evaluating tools for potential future use.

### build-system
#### motivation
* Writing makefiles by hand costs too much time.
* Maintaining header dependencies costs too much time.
* Project portability is not requirement but would be nice to have.

I used *cmake* mainly because I wanted comparison to *autools* that I was already exposed to. Cmake creates own interface wrapper over compiler interface which was frustrating at times. Simple and known compiler interface (e. g. `-std` flag) was not working and the cmake way had to be learned. I will definitely evaluate also some yet some other build systems in the future for comparison.

[Cmake](https://cmake.org/)

### compiler
#### requirements
* reasonable support of *C++14*
* user friendly diagnostic info
* as many reasonable warning features as possible

I used *clang* 3.6.2. This version is almost a year old and maybe not yet production-ready but ok for a toy project (found one compiler crashing bug during development). I am using `-Weverything` flag and white-listing warnings to be ignored.

[Clang](http://clang.llvm.org/)

### testing-framework
I used *Boost Unit Test Framework* because of pleasant past experience. Two minor imperfections I am aware of are:
* Framework heavy usage of macros implies minor issues with multi-argument templates (comma in macro parameter).
* No nice out-of-the-box way for parameterized testcases. Unary test function templates are without autoregistration (and little awkward).

[Boost UTF](http://www.boost.org/doc/libs/release/libs/test/)

### IDE
#### requirements
* FOSS working on GNU/Linux
* Full C++ parser.
* Continuous static analysis as a first line of defense.

Because of good past experience I used *Eclipse CDT*. (Besides - there is not much choice anyway.) Code indexing might be memory hungry and CPU intensive and Eclipse needs to be allocated enough memory in configuration.

[Eclipse CDT](https://eclipse.org/cdt/)

### static analysis tools
#### requirements
* FOSS

##### Clang static analyzer
* The clang compiler itself is a good starting point for static analysis.
* Clang analyzer is not part of the compiler yet in 3.6.
* Integration with cmake was in some cases not right out of the box but generally close enough.
* Memory sanitizer checker not working with older kernels.
* Some issues with Boost libraries were encountered and will be explored later.

[Clang Static Analyzer](http://clang-analyzer.llvm.org/)

##### cppcheck
* Checking only single file at a time and also having false positive because of that.

[Cppcheck](http://cppcheck.sourceforge.net/)

##### cpplint
* Actually using only very few checks as not every Google guideline rule makes sense for every project.
* Some rules are becoming obsolete.

[cpplint](http://google.github.io/styleguide/cppguide.html#cpplint)

#### experience
* Some analyzers need to build the whole project.
* All integrate with cmake just fine and required at most few lines of very simple bash script to be used conveniently.

From my perspective the big unsolved problem in these tools in general is how to handle false-positives selectively on case by case basis semi-automatically or automatically and with reasonable maintenance costs. I like neither code changes because of compiler false-positive warnings nor comment annotations for static analysis tools. Turning off specific warnings might lead to turning them off all in the end for bigger projects.

### runtime analysis tools
#### tools
I am running tests and main binary under *valgrind*. This required very little work.

[Valgrind](http://valgrind.org/)

### custom testing tools
I am using simple *bash* scripts utilizing mainly *grep* to check certain bugs (e. g. constructing an exception and not throwing it).

### source code overview
#### requirement
* Produce high level perspective of source code.
* Produce basis for developer documentation.

#### tool
Utilized *doxygen* for generating documentation.

* Useful dependency, inheritance, caller/callee relationship diagrams.
* Nice documentation generating features
* Some unexpected results with `BUILTIN_STL_SUPPORT` and `EXCLUDE_SYMBOLS` config options.

[Doxygen](http://www.doxygen.org/)

### ?
#### requirement
* Provide users with painless way to play with the project.
* Don't rely solely on cmake.
* Don't bother even testing on different GNU/Linux distributions.

Mainly out of my own curiosity I created *docker* image for testing purposes.
* The only issue I encountered is size of image.

[Docker](https://www.docker.com/)
