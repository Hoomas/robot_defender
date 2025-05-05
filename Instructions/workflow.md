## Архитектура проекта и принципы ветвления

1. **main** - стабильная версия с рабочей сборкой

2. **develop** - интеграционная ветка для тестирования

3. **feature/** - изолированная разработка классов

4. **release/** - для подготовки релиза. Из develop создаётся ветка, где проводится финальное тестирование, обновляется документация, версия и changelog.

Разберем жизненный цикл класса от задачи до слияния с main

## 1. Создание ветки для нового класса

bash

`git checkout -b feature/move-class develop`

От ветки develop создатся новая ветка feature/name-class
После завершения разработки функции изолированно, эта ветка сливается с веткой develope см ниже.

## 2. Структура файлов в ветке

text

```
/src   
    /Move    
        Move.h    
        Move.cpp  
    /Sensors    
      ... 
/main.cpp
```

## 3. Разработка класса

```cpp
// Move.h
#pragma once
class Move {
public:
  void forward(int speed);
  void rotate(int degrees);
private:
  void applyMotorControl();
};
```

```cpp
// Move.cpp
#include "Move.h"
void Move::forward(int speed) {
  // Реализация движения
}
```

*Важно:* Коммитить изменения мелкими порциями[8](https://www.linkedin.com/pulse/best-practices-branching-merging-managing-codebases-using-elumalai-0lyfc)

bash

```bash
git add src/Move/* git commit -m "Implement base movement logic"
git push origin feature/move-class
// Если етка новая
git push -u origin feature/move-class
```

## 4. Интеграция с main.cpp

**Слияние с develop**

- После завершения работы ветка feature/name-class сливается с develop через Pull Request
  
  ```bash
  git checkout develop
  git merge feature/move-class
  ```
  
  После слияния класс тестируется в интеграции с main.cpp

```cpp
#include "Move/Move.h" 
Move robotMove; 
void setup() {   
    robotMove.forward(100); 
}
```

## 5. **Релиз через main**

- Когда develop стабилен, создаёте релизную ветку:

```bash
git checkout -b release/v1.0 develop
```

- Тестируете финальную версию, затем:
  
  ```bash
  git checkout main git merge release/v1.0 git tag -a v1.0 -m "Релиз движения"
  ```

Для слияния с main также создается Pull Request
