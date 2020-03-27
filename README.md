
## Get the source

git clone https://github.com/tim-ashton/tech_challenge.git

git submodule update --init

## Setup

```
apt install -y cmake nlohmann-json-dev
```

## Building

mkdir build
cd build
cmake ../

## Run Unit Tests (from Build directory)
./test/tech_challenge_test
