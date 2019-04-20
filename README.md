# myls
My implementation of the ls UNIX command

### Installing

```
git clone https://github.com/AustinAWhite/myls.git
```
In root directory:
```
make
```
an executable 'myls' will be created

### Usage

```
./myls -[command opts] [command args]
```

##### Command Opts
* l, use a long listing format
* a, do not ignore entries starting with .
* r, reverse order while sorting
* t, sort by modification time, newest first
* R, list subdirectories recursively 
