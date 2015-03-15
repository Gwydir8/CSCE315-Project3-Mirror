# Eugenics-System
A system designed to generate a visualize a circuit generation algorithm.
Consists of the engine server and visualization client.

CSCE315 Project 3 - Team 15
- Christopher Findeisen cfindeisen7@email.tamu.edu
- Sam Gwydir gwydir8@gmail.com
- Jerego Orlino jjo498@email.tamu.edu
- Vincent Valenti vincentv18@email.tamu.edu

## Directories

- src := source code for project
- share := scripts, docs
- include := library headers
- lib := shared/static libraries
- etc := configuration files
- var := logs, caches, temporary files
- local := external library install prefix

## Branches

* Main Branches
  - master := latest *compiling* code
  - develop := latest code, compiling or not. Default branch.

* Other Branches
  - feature/name := feature branch, merged into develop. note feature/ is a prefix. (e.g. feature/add-logging)
  - experimental/<name> := a contributors experimental branch.

## Building
### Dependencies
- gflags 2.1.1
- cmake
- FLTK (not yet)

#### Linux
Use your package manager to install cmake.

If building on Linux, `share/scripts/install-gflags.sh` will install gflags into `$PROJECT_ROOT/local`.

```bash
cd $PROJECT_ROOT;
./share/scripts/install-gflags.sh
```

#### OS X
If you have [homebrew](https://github.com/Homebrew/homebrew) installed:
```bash
brew install cmake
brew install https://raw.githubusercontent.com/Gwydir8/Eugenics/develop/share/scripts/gflags.rb
```

If you don't have [homebrew](https://github.com/Homebrew/homebrew) installed:
```bash
echo "Come back when you do!"
```

### Manual Build
- note this builds the release build by default.
- run `cmake -DCMAKE_BUILD_TYPE=Debug ..` in build to build debug build
- run `cmake -DCMAKE_BUILD_TYPE=Release ..` in build to build release build explicitly

```bash
mkdir build
cd build
cmake ..
```

### Automated Build
- PROJECT_ROOT is where you cloned the repository.
```bash
cd $PROJECT_ROOT;
./build.sh
# release binary will be build/eugenics-system/{eugenics, lookingglass}
# debug binary will be debug/eugenics-system/{eugenics, lookingglass}
```

## Help
```bash
man $PROJECT_ROOT/share/man/eugenics.1
man $PROJECT_ROOT/share/man/lookingglass.1
```
