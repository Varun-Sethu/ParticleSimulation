echo 'Cleaning up previous build files...';
rm -rf build

mkdir -p build && cd build
cmake ..

if [ $# -eq 0 ]
then
	make Playing
else
	make tests
fi

cd ../
