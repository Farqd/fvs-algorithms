# fvs-algorithms

wget https://github.com/facebook/buck/releases/download/v2019.01.10.01/buck.2019.01.10.01_all.deb
sudo dpkg -i buck.2019.01.10.01_all.deb


# build & run tests
# in main folder:

buck build test:test
buck test test:test


# build library

buck build //:fvs-algorithms
