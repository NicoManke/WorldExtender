# GameLab III - World Extender - Repository

|  General Info  | |
| ---|---|
| Working Title | `World Extender` |
| Game Title | `World Extender` |
| Engine Title | `ChunkMapEngine` |
| Creator | `Nico Manke` |
| Target Platform(s) | `Windows` |
| Start Date | 08.11.2022 |
| Study Program | Games Engineering B.Sc.|
| Engine Version | OpenGL 4.6 |
| IDE | Visual Studio 2019 |
| Compiler | MSVC 19.29.30137.0 |
| Build System | CMake (3.20) |
| C++ Version | C++17 |

### Packages in Use
- GLAD (4.6)
- GLFW (3.4.0 LANGUAGES C)
- GLM (0.9.9.9)
- tinyGLTF (2.4.0)
- stb_image (2.27)
- SoLoud (202002)
- Box2D (2.4.1)

### Abstract

`World Extender is a relaxing 2D top-down view sandbox, farming and construction game. The goal is to escape a magic mini dimension by generating new flying islands with more resources and new structures.`

## Repository Structure - where to find what!

```
RepositoryRoot/
    ├── README.md   
    ├── THIRD-PARTY-NOTICE.md   // references to all thirs party assets
    ├── logo.png         
    ├── builds/             
    │   ├── WorldExtender.zip   // a playable executable of World Extender
    │   └── ChunkMapEngine.zip  // the engine library
    ├── code/
    │   └── code/
    │       ├── engine/         // ChunkMapEngine specific code
    │       ├── game/           // World Extender specific code
    │       ├── extern/         // collection of used third party libraries
    │       ├── assets/         // folder of the assets used for World Extender
    │       ├── CMakeLists.txt
    │       └── ...
    ├── documentation/      
    │   ├── World Extender Documentation.pdf    // "How to get started" and gameplay documentation for World Extender
    │   ├── ChunkMapEngine HTML Documentation/  // this folder contains all files for the html version of the documentation
    │   │   ├── index.html                      // open the index.html file to see the documentation in your browser
    │   │   └── ...
    │   ├── ChunkMapEngine Documentation.pdf    // rich text version of ChunkMapEngine's html documentation
    │   └── ...
    ├── poster/    // PDF of World Extender's poster
    ├── report/    // PDF of World Extender's and ChunkMapEngine's report
    └── trailer/   // mp4 of World Extender's and ChunkMapEngine's trailer
```

## Documentation Explanation
- "ChunkMapEngine Code Documentation (HTML).zip" 
  -> unzip and open "index.html" inside to open the code documentation in the browser.
- "ChunkMapEngine Code Documentation (RichText).pdf"
  -> summarices the above code documentation in one PDF file.
- "World Extender Documentation.pdf"
  -> a quick start up for building the game based on the repo code and a quick game explanation for World Extender.