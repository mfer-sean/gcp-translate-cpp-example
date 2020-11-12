# translate-cpp-test

Note: This is meant to be run on GCP Cloud VM.
Make sure VM is allowed to execute all GCP Access scopes.

## Initial setup on CentOS 7
```sh
#initial linux tools setup
cd ~
yum install gcc-c++
yum group install "Development Tools"
yum install libcurl

# compile restclient library
git clone https://github.com/mrtazz/restclient-cpp.git
cd restclient-cpp/
yum install curl-devel
./autogen.sh
./configure
make install

# link newly compiled libraries
vi /etc/ld.so.conf.d/locallib.conf
	/usr/local/lib/ ← save and quit

# setup this repo
cd ..
git clone THIS_REPO.git
cd REPO folder

# test code
chmod u+x run.sh
./run.sh

```
