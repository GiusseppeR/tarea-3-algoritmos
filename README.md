Para la implementación se utilizó CLion de JetBrains. CLion es de pago, pero al inscribirse con el correo de la universidad se puede utilizar gratis. La tarea no funciona con las herramientas de compilado y construcción de VisualStudio.

Para poder compilar y ejecutar, se logra desde el mismo programa con el botón "Run" en la esquina superior derecha. Alternativamente, se puede utilizar sólo para crear el ejecutable con el botón "Build" al lado de "Run. El ejecutable se encuentra en la carpeta "cmake-build-debug".

La tarea se probó en Windows, Mac. Hemos visto comportamientos muy variados dependiendo del hardware y del sistema operativo.

A continuación se muestra cómo configurar CLion:

## Configuración Mac

- Descargar CLion para Linux desde la página oficial

- Descargar e instalar xcode desde la appstore

- Abrir el proyecto


## Configuración Windows

- Descargar CLion e instalar para Windows desde la página oficial

- Abrir la tarea

- En File >> Settings >> Build, Execution, Deployment >> Toolchains, asegurarse de tener la configuración por defecto. Es decir, que el toolchain sea MinGW, CMake sea "bundled", la build tool sea "ninja.exe" del ambiente local de CLion, y el compilador de C sea "gcc.exe" del ambiente local de Clion.

## Configuración Linux (Kali Linux)

- Descargar CLion para Linux desde la página oficial

- Extraer el archivo y abrir el directorio resultante en la consola. Ejecutar $sh bin/clion.sh para abrirlo. Es posible que la primera vez se tenga que correr el comando dos veces.

- La configuración por defecto debería ser suficiente.

## Información adicional

Opcionalmente (no garantizado), se puede compilar la tarea usando solo el CMake. En una carpeta "build" dentro del directorio, hacer:
```
cmake ..
cmake --build .
```
