# Feature
Reduce the boring work when you have to release software based on the Qt Install Framework.
- Automatically increment the version in the "Version" tag, manually update the "ReleaseDate" tag as the current date.
- To easily integrate into the self-building system.
# build
Windows mingw cmd
"
git clone git@github.com:xdien/autoincrement4qtif.git
cd autoincrement4qtif
mkdir build
cd build
qmake ../
mingw32-make
"
windeployqt autoincrement4qtif.exe
# Use
autoincrement4qtif.exe package.xml
