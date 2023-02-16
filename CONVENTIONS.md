## C++ Coding Style Conventions

Here it is a list with some of the code conventions used by South Invaders:

Code element | Convention | Example
--- | :---: | ---
Defines | ALL_CAPS | `#define PLATFORM_DESKTOP`
Macros | ALL_CAPS | `#define MIN(a,b) (((a)<(b))?(a):(b))`
Variables | snake_case | `int count = 0;`, `float radius = 0.016f;`
Local variables | snake_case | `int hp = 0;`
Global variables | ALL_CAPS | `bool DEBUG = false;`
Constants | ALL_CAPS | `const int MAX_VALUE = 8;`
Pointers | MyType *pointer | `std::vector<int> *array = nullptr;`
References | MyType &reference | `std::vector<int> &array = getArrayRef();`
float values | always x.xf | `float gravity = 10.0f`
Operators | value1 * value2 | `int product = value * 6;`
Operators | value1 / value2 | `int division = value / 4;`
Operators | value1 + value2 | `int sum = value + 10;`
Operators | value1 - value2 | `int res = value - 5;`
Union | camelCase | `union messageValue`
Enum | camelCase | `enum eventType`
Enum members | ALL_CAPS | `ENEMY_SPAWN`
Struct | PascalCase | `struct Vec2`, `struct DeathEvent`
Struct members | snake_case | `Vec2.width`, `enemy.direction_angle`
Class | PascalCase | `class Position`, `class SystemManager`
Class members | snake_case (with underscore prefix) | `Vec2 _value;`, `int _nb_xp;`
Methods | snake_case | `pos.get_value()`, `systems.run()`
Functions | snake_case | `spawn_entity()`, `summon_enemy()`
Functions params | snake_case | `snake_size`, `nb_coin`
Ternary Operator | ((condition) ? result1 : result2) | `std::cout << ((active) ? "true" : "false")`

Some other conventions to follow:
 - **ALWAYS** initialize all defined variables.
 - **Do not use TABS**, use 4 spaces instead.
 - Avoid trailing spaces, please, avoid them
 - All conditions checks are **always between parenthesis** but not boolean values:
```cpp
if ((value > 1) && (value < 50) && valueActive) {
    // case A
} else if ((value > 49) && (value < 100) && valueActive) {
    // case B
} else {
    // case C
}
```
 - When dealing with braces or curly brackets, open-close them in aligned mode:
```cpp
void SomeFunction()
{
   // TODO: Do something here!
}
```

**If proposing new functions, please try to use a clear naming for function-name and functions-parameters, in case of doubt, open an issue for discussion.**

## Files and Directories Naming Conventions
 
  - Directories will be named using `snake_case`: `assets/models`, `assets/fonts`
  
  - Files will be named using `snake_case`: `main_title.png`, `cubicmap.png`, `sound.wav`

  - excepting files that define classes which are named using `PascalCase`: `Registry.cpp`, `Registry.hpp`
  
_NOTE: Avoid any space or special character in the files/dir naming!_
  
## Games/Examples Directories Organization Conventions
  
 - Data files should be organized by context and usage in the game, think about the loading requirements for data and put all the resources that need to be loaded at the same time together.
 - Use descriptive names for the files, it would be perfect if just reading the name of the file, it was possible to know what is that file and where fits in the game.
 - Here it is an example, note that some resources require to be loaded all at once while other require to be loaded only at initialization (gui, font).
  
```
assets/audio/fx/long_jump.wav
assets/audio/music/main_theme.ogg
assets/screens/logo/logo.png
assets/screens/title/title.png
assets/screens/gameplay/background.png
assets/characters/player.png
assets/characters/enemy_slime.png
assets/common/font_arial.ttf
assets/common/gui.png
```
