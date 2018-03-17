/*!
\file
\brief основной файл main

Запуск приложения
*/

#include <iostream>
#include "library.h"

/*!
Точка вызова программы
\return {возвращает 0}

*/
int main()
{
    std::cout << "Hello world!" << std::endl;
#ifdef PROJECT_VERSION_MINOR
    std::cout << "Version " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << "." << version() << std::endl;
#else
    std::cout << "Version " << PROJECT_VERSION_MAJOR << "." << 0  << "." << version() << std::endl;
#endif
    
    return 0; 
}

