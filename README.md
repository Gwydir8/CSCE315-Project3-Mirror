# Artificial Intelligence
## CSCE315 Project 3

### Branches

- master := latest *compiling* code
- develop := latest code, compiling or not. Default branch.

### Directories

- src := source code for project
- share := scripts, docs
- include := library headers
- lib := shared/static libraries
- etc := configuration files
- var := logs, caches, temporary files

### Links

  - [Project 3 Spec](http://faculty.cse.tamu.edu/ritchey/courses/csce315/spring15/homework/project3.pdf)
  - [Gitter](https://gitter.im/Gwydir8/CSCE315-Project3-Mirror?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&content=body_link)

### Team 15
* Christopher Findeisen
  - cfindeisen7@email.tamu.edu

* Sam Gwydir
  - gwydir8@gmail.com

* Jerego Orlino
  - jjo498@email.tamu.edu

* Vincent Valenti
  - vincentv18@email.tamu.edu

### Building
#### Manual Build
- note this builds the release build by default.
- run `cmake -DCMAKE_BUILD_TYPE=Debug ..` in build to build debug build
- run `cmake -DCMAKE_BUILD_TYPE=Release ..` in build to build release build explicitly
```bash
mkdir build
cd build
cmake ..
```
#### Automated Build
- PROJECT_ROOT is where you cloned the repository.
```bash
cd $PROJECT_ROOT;
./share/build.sh
# release binary will be build/bin/gauss
# debug binary will be debug/bin/gauss
```
