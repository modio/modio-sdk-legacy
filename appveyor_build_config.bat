mkdir test_build
cd test_build
cmake -D mode=static -D test=on -D gtest_force_shared_crt=on -G "Visual Studio 15" c:\projects\source
cmake --build . --config "Debug"
cd ..

if %APPVEYOR_REPO_TAG% == true (
  echo "Release tag detected, building and deploying releases"
  mkdir dynamic_x86
  cd dynamic_x86
  cmake -D test=on -G "Visual Studio 15" c:\projects\source
  cmake --build . --config "Release"
  mkdir ..\dynamic_x64
  cd ..\dynamic_x64
  cmake -G "Visual Studio 15 Win64" c:\projects\source
  cmake --build . --config "Release"
  mkdir ..\static_x86
  cd ..\static_x86
  cmake -D mode=static -G "Visual Studio 15" c:\projects\source
  cmake --build . --config "Release"
  mkdir ..\static_x64
  cd ..\static_x64
  cmake -D mode=static -G "Visual Studio 15 Win64" c:\projects\source
  cmake --build . --config "Release"
  cd ..
  7z a Windows.zip dynamic_x86\Release\* dynamic_x64\Release\* static_x86\Release\* static_x64\Release\*
) else (
  echo "Release tag not detected, not building releases"
)