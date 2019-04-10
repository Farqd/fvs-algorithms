# fvs-algorithms



Before building you need to install buck  
https://buckbuild.com/  

You can do it by building from sources or as follows:

```bash
wget https://github.com/facebook/buck/releases/download/v2019.01.10.01/buck.2019.01.10.01_all.deb
sudo dpkg -i buck.2019.01.10.01_all.deb
```

# build & run tests

in main folder:

```bash
buck build test:test
buck test test:test
```

# build library

```bash

buck build //:fvs-algorithms

```